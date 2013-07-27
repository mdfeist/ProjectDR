//------------------------------------------------------------------------------
// <copyright file="KinectFusionBasics.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

// System includes
#include "stdafx.h"
#include <string>
#include <strsafe.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <new>

#include <iostream>

// Project includes
#include "resource.h"
#include "KinectFusionBasics.h"

/// <summary>
/// Set Identity in a Matrix4
/// </summary>
/// <param name="mat">The matrix to set to identity</param>
void SetIdentityMatrix(Matrix4 &mat)
{
    mat.M11 = 1; mat.M12 = 0; mat.M13 = 0; mat.M14 = 0;
    mat.M21 = 0; mat.M22 = 1; mat.M23 = 0; mat.M24 = 0;
    mat.M31 = 0; mat.M32 = 0; mat.M33 = 1; mat.M34 = 0;
    mat.M41 = 0; mat.M42 = 0; mat.M43 = 0; mat.M44 = 1;
}

/// <summary>
/// Constructor
/// </summary>
CKinectFusionBasics::CKinectFusionBasics() :
    m_pVolume(nullptr),
    m_pNuiSensor(nullptr),
    m_imageResolution(NUI_IMAGE_RESOLUTION_640x480),
    m_cImageSize(0),
    m_hNextDepthFrameEvent(INVALID_HANDLE_VALUE),
    m_pDepthStreamHandle(INVALID_HANDLE_VALUE),
    m_bNearMode(true),
    m_bMirrorDepthFrame(false),
    m_bTranslateResetPoseByMinDepthThreshold(true),
    m_bAutoResetReconstructionWhenLost(false),
    m_cLostFrameCounter(0),
    m_bTrackingFailed(false),
    m_cFrameCounter(0),
    m_pDepthImagePixelBuffer(nullptr),
    m_pDepthFloatImage(nullptr),
    m_pPointCloud(nullptr),
    m_pShadedSurface(nullptr),
	m_pImageData(nullptr),
    m_bInitializeError(false)
{
    // Get the depth frame size from the NUI_IMAGE_RESOLUTION enum
    // You can use NUI_IMAGE_RESOLUTION_640x480 or NUI_IMAGE_RESOLUTION_320x240 in this sample
    // Smaller resolutions will be faster in per-frame computations, but show less detail in reconstructions.
    DWORD width = 0, height = 0;
    NuiImageResolutionToSize(m_imageResolution, width, height);
    m_cDepthWidth = width;
    m_cDepthHeight = height;
    m_cImageSize = m_cDepthWidth*m_cDepthHeight;

    // create heap storage for depth pixel data in RGBX format
    m_pDepthRGBX = new BYTE[m_cImageSize*cBytesPerPixel];

    // Define a cubic Kinect Fusion reconstruction volume,
    // with the Kinect at the center of the front face and the volume directly in front of Kinect.
    m_reconstructionParams.voxelsPerMeter = 256;// 1000mm / 256vpm = ~3.9mm/voxel    
    m_reconstructionParams.voxelCountX = 512;   // 512 / 256vpm = 2m wide reconstruction
    m_reconstructionParams.voxelCountY = 384;   // Memory = 512*384*512 * 4bytes per voxel
    m_reconstructionParams.voxelCountZ = 512;   // This will require a GPU with at least 512MB

    // These parameters specify the maximum translation and rotation that can occur between frames
    // before we consider camera tracking to be lost. They specify a typical maximum speed of motion
    // for a hand-held Kinect camera, assuming you are running at 30Hz.
    m_fMaxTranslationDelta = 0.3f;    // 0.15 - 0.3m per frame typical
    m_fMaxRotationDelta = 20.0f;   // 10-20 degrees per frame typical

    // These parameters are for optionally clipping the input depth image 
    m_fMinDepthThreshold = NUI_FUSION_DEFAULT_MINIMUM_DEPTH;   // min depth in meters
    m_fMaxDepthThreshold = NUI_FUSION_DEFAULT_MAXIMUM_DEPTH;    // max depth in meters

    // This parameter is the temporal averaging parameter for depth integration into the reconstruction
    m_cMaxIntegrationWeight = NUI_FUSION_DEFAULT_INTEGRATION_WEIGHT;	// Reasonable for static scenes

    // This parameter sets whether GPU or CPU processing is used. Note that the CPU will likely be 
    // too slow for real-time processing.
    m_processorType = NUI_FUSION_RECONSTRUCTION_PROCESSOR_TYPE_AMP;

    // If GPU processing is selected, we can choose the index of the device we would like to
    // use for processing by setting this zero-based index parameter. Note that setting -1 will cause
    // automatic selection of the most suitable device (specifically the DirectX11 compatible device 
    // with largest memory), which is useful in systems with multiple GPUs when only one reconstruction
    // volume is required. Note that the automatic choice will not load balance across multiple 
    // GPUs, hence users should manually select GPU indices when multiple reconstruction volumes 
    // are required, each on a separate device.
    m_deviceIndex = -1;    // automatically choose device index for processing

    SetIdentityMatrix(m_worldToCameraTransform);
    SetIdentityMatrix(m_defaultWorldToVolumeTransform);

    m_cLastFrameTimeStamp.QuadPart = 0;
}

/// <summary>
/// Destructor
/// </summary>
CKinectFusionBasics::~CKinectFusionBasics()
{
    HRESULT hr = S_OK;

    // Clean up Kinect Fusion
    SafeRelease(m_pVolume);

    if (m_pShadedSurface)
    {
        hr = NuiFusionReleaseImageFrame(m_pShadedSurface);
    }
    if (m_pPointCloud)
    {
        hr = NuiFusionReleaseImageFrame(m_pPointCloud);
    }
    if (m_pDepthFloatImage)
    {
        hr = NuiFusionReleaseImageFrame(m_pDepthFloatImage);
    }

    // Clean up Kinect
    if (m_pNuiSensor)
    {
        m_pNuiSensor->NuiShutdown();
        m_pNuiSensor->Release();
    }

    if (m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_hNextDepthFrameEvent);
    }

    // clean up the depth pixel array
    SAFE_DELETE_ARRAY(m_pDepthImagePixelBuffer);

    // done with depth pixel data
    SAFE_DELETE_ARRAY(m_pDepthRGBX);

}

/// <summary>
/// Main processing function
/// </summary>
void CKinectFusionBasics::Update()
{
    if (nullptr == m_pNuiSensor)
    {
        return;
    }

    if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hNextDepthFrameEvent, 0) )
    {
        ProcessDepth();
    }
}

/// <summary>
/// Create the first connected Kinect found 
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT CKinectFusionBasics::CreateFirstConnected()
{
    INuiSensor * pNuiSensor;
    HRESULT hr;

    int iSensorCount = 0;
    hr = NuiGetSensorCount(&iSensorCount);
    if (FAILED(hr))
    {
        std::cout << "No ready Kinect found!" << std::endl;
        return hr;
    }

    // Look at each Kinect sensor
    for (int i = 0; i < iSensorCount; ++i)
    {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex(i, &pNuiSensor);
        if (FAILED(hr))
        {
            continue;
        }

        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if (S_OK == hr)
        {
            m_pNuiSensor = pNuiSensor;
            break;
        }

        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }

    if (nullptr != m_pNuiSensor)
    {
        // Initialize the Kinect and specify that we'll be using depth
        hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH); 
        if (SUCCEEDED(hr))
        {
            // Create an event that will be signaled when depth data is available
            m_hNextDepthFrameEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

            // Open a depth image stream to receive depth frames
            hr = m_pNuiSensor->NuiImageStreamOpen(
                NUI_IMAGE_TYPE_DEPTH,
                m_imageResolution,
                0,
                2,
                m_hNextDepthFrameEvent,
                &m_pDepthStreamHandle);
        }

        if (m_bNearMode)
        {
            // Set near mode based on our internal state
            HRESULT nearHr = m_pNuiSensor->NuiImageStreamSetImageFrameFlags(m_pDepthStreamHandle, NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE);
        }
    }

    if (nullptr == m_pNuiSensor || FAILED(hr))
    {
		std::cout << "No ready Kinect found!" << std::endl;
        return E_FAIL;
    }


    return hr;
}

/// <summary>
/// Initialize Kinect Fusion volume and images for processing
/// </summary>
/// <returns>S_OK on success, otherwise failure code</returns>
HRESULT CKinectFusionBasics::InitializeKinectFusion()
{
    HRESULT hr = S_OK;

    // Create the Kinect Fusion Reconstruction Volume
    hr = NuiFusionCreateReconstruction(
        &m_reconstructionParams,
        m_processorType, m_deviceIndex,
        &m_worldToCameraTransform,
        &m_pVolume);

    if (FAILED(hr))
    {
        if (E_NUI_GPU_FAIL == hr)
        {
			std::cout << "Device " << m_deviceIndex << " not able to run Kinect Fusion, or error initializing." << std::endl;
        }
        else if (E_NUI_GPU_OUTOFMEMORY == hr)
        {
            std::cout << "Device " << m_deviceIndex << " out of memory error initializing reconstruction - try a smaller reconstruction volume." << std::endl;
        }
        else if (NUI_FUSION_RECONSTRUCTION_PROCESSOR_TYPE_CPU != m_processorType)
        {
            std::cout << "Failed to initialize Kinect Fusion reconstruction volume on device " << m_deviceIndex << std::endl;
        }
        else
        {
            std::cout << "Failed to initialize Kinect Fusion reconstruction volume on CPU." << std::endl;
        }

        return hr;
    }

    // Save the default world to volume transformation to be optionally used in ResetReconstruction
    hr = m_pVolume->GetCurrentWorldToVolumeTransform(&m_defaultWorldToVolumeTransform);
    if (FAILED(hr))
    {
        std::cout << "Failed in call to GetCurrentWorldToVolumeTransform." << std::endl;
        return hr;
    }

    if (m_bTranslateResetPoseByMinDepthThreshold)
    {
        // This call will set the world-volume transformation
        hr = ResetReconstruction();
        if (FAILED(hr))
        {
            return hr;
        }
    }

    // Frames generated from the depth input
    hr = NuiFusionCreateImageFrame(NUI_FUSION_IMAGE_TYPE_FLOAT, m_cDepthWidth, m_cDepthHeight, nullptr, &m_pDepthFloatImage);
    if (FAILED(hr))
    {
        std::cout << "Failed to initialize Kinect Fusion image." << std::endl;
        return hr;
    }

    // Create images to raycast the Reconstruction Volume
    hr = NuiFusionCreateImageFrame(NUI_FUSION_IMAGE_TYPE_POINT_CLOUD, m_cDepthWidth, m_cDepthHeight, nullptr, &m_pPointCloud);
    if (FAILED(hr))
    {
        std::cout << "Failed to initialize Kinect Fusion image." << std::endl;
        return hr;
    }

    // Create images to raycast the Reconstruction Volume
    hr = NuiFusionCreateImageFrame(NUI_FUSION_IMAGE_TYPE_COLOR, m_cDepthWidth, m_cDepthHeight, nullptr, &m_pShadedSurface);
    if (FAILED(hr))
    {
        std::cout << "Failed to initialize Kinect Fusion image." << std::endl;
        return hr;
    }

    m_pDepthImagePixelBuffer = new(std::nothrow) NUI_DEPTH_IMAGE_PIXEL[m_cImageSize];
    if (nullptr == m_pDepthImagePixelBuffer)
    {
        std::cout << "Failed to initialize Kinect Fusion depth image pixel buffer." << std::endl;
        return hr;
    }

    // Set an introductory message
    std::cout << "Click ‘Near Mode’ to change sensor range, and ‘Reset Reconstruction’ to clear!" << std::endl;

    return hr;
}

/// <summary>
/// Copy the extended depth data out of a Kinect image frame
/// </summary>
/// <param name="imageFrame">The extended depth image frame to copy.</param>
/// <returns>S_OK on success, otherwise failure code</returns>
HRESULT CKinectFusionBasics::CopyExtendedDepth(NUI_IMAGE_FRAME &imageFrame)
{
    HRESULT hr = S_OK;

    if (nullptr == m_pDepthImagePixelBuffer)
    {
        std::cout << "Error depth image pixel buffer is nullptr." << std::endl;
        return E_FAIL;
    }

    INuiFrameTexture *extendedDepthTex = nullptr;

    // Extract the extended depth in NUI_DEPTH_IMAGE_PIXEL format from the frame
    BOOL nearModeOperational = FALSE;
    hr = m_pNuiSensor->NuiImageFrameGetDepthImagePixelFrameTexture(m_pDepthStreamHandle, &imageFrame, &nearModeOperational, &extendedDepthTex);
    if (FAILED(hr))
    {
        std::cout << "Error getting extended depth texture." << std::endl;
        return hr;
    }

    NUI_LOCKED_RECT extendedDepthLockedRect;

    // Lock the frame data to access the un-clamped NUI_DEPTH_IMAGE_PIXELs
    hr = extendedDepthTex->LockRect(0, &extendedDepthLockedRect, nullptr, 0);

    if (FAILED(hr) || extendedDepthLockedRect.Pitch == 0)
    {
        std::cout << "Error getting extended depth texture pixels." << std::endl;
        return hr;
    }

    // Copy the depth pixels so we can return the image frame
    errno_t err = memcpy_s(m_pDepthImagePixelBuffer, m_cImageSize * sizeof(NUI_DEPTH_IMAGE_PIXEL), extendedDepthLockedRect.pBits, extendedDepthTex->BufferLen());

    extendedDepthTex->UnlockRect(0);

    if(0 != err)
    {
        std::cout << "Error copying extended depth texture pixels." << std::endl;
        return hr;
    }

    return hr;
}

/// <summary>
/// Handle new depth data and perform Kinect Fusion processing
/// </summary>
void CKinectFusionBasics::ProcessDepth()
{
    if (m_bInitializeError)
    {
        return;
    }

    HRESULT hr = S_OK;
    NUI_IMAGE_FRAME imageFrame;

    ////////////////////////////////////////////////////////
    // Get an extended depth frame from Kinect

    hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_pDepthStreamHandle, 0, &imageFrame);
    if (FAILED(hr))
    {
        std::cout << "Kinect NuiImageStreamGetNextFrame call failed." << std::endl;
        return;
    }

    hr = CopyExtendedDepth(imageFrame);

    LARGE_INTEGER currentFrameTime = imageFrame.liTimeStamp;

    // Release the Kinect camera frame
    m_pNuiSensor->NuiImageStreamReleaseFrame(m_pDepthStreamHandle, &imageFrame);

    if (FAILED(hr))
    {
        return;
    }

    // To enable playback of a .xed file through Kinect Studio and reset of the reconstruction
    // if the .xed loops, we test for when the frame timestamp has skipped a large number. 
    // Note: this will potentially continually reset live reconstructions on slow machines which
    // cannot process a live frame in less time than the reset threshold. Increase the number of
    // milliseconds in cResetOnTimeStampSkippedMilliseconds if this is a problem.
    if (m_cFrameCounter != 0 && abs(currentFrameTime.QuadPart - m_cLastFrameTimeStamp.QuadPart) > cResetOnTimeStampSkippedMilliseconds)
    {
        ResetReconstruction();

        if (FAILED(hr))
        {
            return;
        }
    }

    m_cLastFrameTimeStamp = currentFrameTime;

    ////////////////////////////////////////////////////////
    // Depth to DepthFloat

    // Convert the pixels describing extended depth as unsigned short type in millimeters to depth
    // as floating point type in meters.
    hr = NuiFusionDepthToDepthFloatFrame(m_pDepthImagePixelBuffer, m_cDepthWidth, m_cDepthHeight, m_pDepthFloatImage, m_fMinDepthThreshold, m_fMaxDepthThreshold, m_bMirrorDepthFrame);

    if (FAILED(hr))
    {
        std::cout << "Kinect Fusion NuiFusionDepthToDepthFloatFrame call failed." << std::endl;
        return;
    }

    // Return if the volume is not initialized
    if (nullptr == m_pVolume)
    {
        std::cout << "Kinect Fusion reconstruction volume not initialized. Please try reducing volume size or restarting." << std::endl;
        return;
    }

    ////////////////////////////////////////////////////////
    // ProcessFrame

    // Perform the camera tracking and update the Kinect Fusion Volume
    // This will create memory on the GPU, upload the image, run camera tracking and integrate the
    // data into the Reconstruction Volume if successful. Note that passing nullptr as the final 
    // parameter will use and update the internal camera pose.
	//hr = m_pVolume->IntegrateFrame(m_pDepthFloatImage, 1000, &m_cameraTransform);
    hr = m_pVolume->ProcessFrame(m_pDepthFloatImage, NUI_FUSION_DEFAULT_ALIGN_ITERATION_COUNT, m_cMaxIntegrationWeight, &m_cameraTransform);
   
	std::cout 
		<< m_worldToCameraTransform.M11 << "," << m_worldToCameraTransform.M12 << "," << m_worldToCameraTransform.M13 << "," << m_worldToCameraTransform.M14 << std::endl
		<< m_worldToCameraTransform.M21 << "," << m_worldToCameraTransform.M22 << "," << m_worldToCameraTransform.M23 << "," << m_worldToCameraTransform.M24 << std::endl
		<< m_worldToCameraTransform.M31 << "," << m_worldToCameraTransform.M32 << "," << m_worldToCameraTransform.M33 << "," << m_worldToCameraTransform.M34 << std::endl
		<< m_worldToCameraTransform.M41 << "," << m_worldToCameraTransform.M42 << "," << m_worldToCameraTransform.M43 << "," << m_worldToCameraTransform.M44 << std::endl
		<< std::endl;
	
	// Test to see if camera tracking failed. 
    // If it did fail, no data integration or raycast for reference points and normals will have taken 
    //  place, and the internal camera pose will be unchanged.
    if (FAILED(hr))
    {
        if (hr == E_NUI_FUSION_TRACKING_ERROR)
        {
            m_cLostFrameCounter++;
            m_bTrackingFailed = true;
            std::cout << "Kinect Fusion camera tracking failed! Align the camera to the last tracked position. " << std::endl;
        }
        else
        {
            std::cout << "Kinect Fusion ProcessFrame call failed!" << std::endl;
            return;
        }
    }
    else
    {
        Matrix4 calculatedCameraPose;
        hr = m_pVolume->GetCurrentWorldToCameraTransform(&calculatedCameraPose);

        if (SUCCEEDED(hr))
        {
            // Set the pose
            m_worldToCameraTransform = calculatedCameraPose;
            m_cLostFrameCounter = 0;
            m_bTrackingFailed = false;
        }
    }
	/*
    if (m_bAutoResetReconstructionWhenLost && m_bTrackingFailed && m_cLostFrameCounter >= cResetOnNumberOfLostFrames)
    {
        // Automatically clear volume and reset tracking if tracking fails
        hr = ResetReconstruction();

        if (FAILED(hr))
        {
            return;
        }

        // Set bad tracking message
        std::cout << "Kinect Fusion camera tracking failed, automatically reset volume." << std::endl;
    }
	*/
    ////////////////////////////////////////////////////////
    // CalculatePointCloud

    // Raycast all the time, even if we camera tracking failed, to enable us to visualize what is happening with the system
    hr = m_pVolume->CalculatePointCloud(m_pPointCloud, &m_cameraTransform);

    if (FAILED(hr))
    {
        std::cout << "Kinect Fusion CalculatePointCloud call failed." << std::endl;
        return;
    }

    ////////////////////////////////////////////////////////
    // ShadePointCloud and render

    hr = NuiFusionShadePointCloud(m_pPointCloud, &m_cameraTransform, nullptr, m_pShadedSurface, nullptr);

    if (FAILED(hr))
    {
        std::cout << "Kinect Fusion NuiFusionShadePointCloud call failed." << std::endl;
        return;
    }

    // Draw the shaded raycast volume image
    INuiFrameTexture * pShadedImageTexture = m_pShadedSurface->pFrameTexture;
    NUI_LOCKED_RECT ShadedLockedRect;

    // Lock the frame data so the Kinect knows not to modify it while we're reading it
    hr = pShadedImageTexture->LockRect(0, &ShadedLockedRect, nullptr, 0);
    if (FAILED(hr))
    {
        return;
    }

    // Make sure we've received valid data
    if (ShadedLockedRect.Pitch != 0)
    {
		if (m_pImageData != 0) {
			BYTE * pBuffer = (BYTE *)ShadedLockedRect.pBits;
			const BYTE* dataEnd = pBuffer + (640*480*4);

			GLubyte* dest = m_pImageData; 

			while (pBuffer < dataEnd)
				*dest++ = *pBuffer++;
		}
    }

    // We're done with the texture so unlock it
    pShadedImageTexture->UnlockRect(0);

    ////////////////////////////////////////////////////////
    // Periodically Display Fps

    // Update frame counter
    m_cFrameCounter++;

    // Display fps count approximately every cTimeDisplayInterval seconds

}


/// <summary>
/// Reset the reconstruction camera pose and clear the volume.
/// </summary>
/// <returns>S_OK on success, otherwise failure code</returns>
HRESULT CKinectFusionBasics::ResetReconstruction()
{
    if (nullptr == m_pVolume)
    {
        return E_FAIL;
    }

    HRESULT hr = S_OK;

    SetIdentityMatrix(m_worldToCameraTransform);

    // Translate the reconstruction volume location away from the world origin by an amount equal
    // to the minimum depth threshold. This ensures that some depth signal falls inside the volume.
    // If set false, the default world origin is set to the center of the front face of the 
    // volume, which has the effect of locating the volume directly in front of the initial camera
    // position with the +Z axis into the volume along the initial camera direction of view.
    if (m_bTranslateResetPoseByMinDepthThreshold)
    {
        Matrix4 worldToVolumeTransform = m_defaultWorldToVolumeTransform;

        // Translate the volume in the Z axis by the minDepthThreshold distance
        float minDist = (m_fMinDepthThreshold < m_fMaxDepthThreshold) ? m_fMinDepthThreshold : m_fMaxDepthThreshold;
        worldToVolumeTransform.M43 -= (minDist * m_reconstructionParams.voxelsPerMeter);

        hr = m_pVolume->ResetReconstruction(&m_worldToCameraTransform, &worldToVolumeTransform);
    }
    else
    {
        hr = m_pVolume->ResetReconstruction(&m_worldToCameraTransform, nullptr);
    }

    m_cLostFrameCounter = 0;
    m_cFrameCounter = 0;

    if (SUCCEEDED(hr))
    {
        m_bTrackingFailed = false;

        std::cout << "Reconstruction has been reset." << std::endl;
    }
    else
    {
        std::cout << "Failed to reset reconstruction." << std::endl;
    }

    return hr;
}

void CKinectFusionBasics::SetCameraTransform(Matrix4 matrix)
{
	m_cameraTransform = matrix;
}