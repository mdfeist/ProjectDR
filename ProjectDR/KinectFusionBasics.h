//------------------------------------------------------------------------------
// <copyright file="KinectFusionBasics.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "resource.h"
#include <NuiApi.h>
#include <NuiKinectFusionApi.h>

#include <gl/GL.h>

class CKinectFusionBasics
{
    static const int            cBytesPerPixel = 4; // for depth float and int-per-pixel raycast images
    static const int            cResetOnTimeStampSkippedMilliseconds = 1000;
    static const int            cResetOnNumberOfLostFrames = 100;
    static const int            cStatusMessageMaxLen = MAX_PATH*2;
    static const int            cTimeDisplayInterval = 10;

public:
    /// <summary>
    /// Constructor
    /// </summary>
    CKinectFusionBasics();

    /// <summary>
    /// Destructor
    /// </summary>
    ~CKinectFusionBasics();

	/// <summary>
    /// Main processing function
    /// </summary>
    void                        Update();

	/// <summary>
    /// Create the first connected Kinect found 
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                     CreateFirstConnected();

    /// <summary>
    /// Initialize Kinect Fusion volume and images for processing
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                     InitializeKinectFusion();

    /// <summary>
    /// Copy the extended depth data out of a Kinect image frame
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                     CopyExtendedDepth(NUI_IMAGE_FRAME &imageFrame);

    /// <summary>
    /// Handle new depth data
    /// </summary>
    void                        ProcessDepth();

    /// <summary>
    /// Reset the reconstruction camera pose and clear the volume.
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                     ResetReconstruction();
	
	bool GetInitializeError() { return m_bInitializeError; }
	void SetInitializeError(bool value) { m_bInitializeError = value; }

	void SetImageData(GLubyte* data) { m_pImageData = data; }

	void SetCameraTransform(Matrix4 matrix);

private:
    bool                        m_bNearMode;

    // Current Kinect
    INuiSensor*                 m_pNuiSensor;
    NUI_IMAGE_RESOLUTION        m_imageResolution;
    int                         m_cDepthWidth;
    int                         m_cDepthHeight;
    int                         m_cImageSize;

    HANDLE                      m_pDepthStreamHandle;
    HANDLE                      m_hNextDepthFrameEvent;

    LARGE_INTEGER               m_cLastFrameTimeStamp;

    BYTE*                       m_pDepthRGBX;

    /// <summary>
    /// The Kinect Fusion Reconstruction Volume
    /// </summary>
    INuiFusionReconstruction*   m_pVolume;

    /// <summary>
    /// The Kinect Fusion Volume Parameters
    /// </summary>
    NUI_FUSION_RECONSTRUCTION_PARAMETERS m_reconstructionParams;

    /// <summary>
    // The Kinect Fusion Camera Transform
    /// </summary>
    Matrix4                     m_worldToCameraTransform;
	Matrix4                     m_cameraTransform;

    /// <summary>
    // The default Kinect Fusion World to Volume Transform
    /// </summary>
    Matrix4                     m_defaultWorldToVolumeTransform;

    /// <summary>
    /// Frames from the depth input
    /// </summary>
    NUI_DEPTH_IMAGE_PIXEL*      m_pDepthImagePixelBuffer;
    NUI_FUSION_IMAGE_FRAME*     m_pDepthFloatImage;

    /// <summary>
    /// Frames generated from ray-casting the Reconstruction Volume
    /// </summary>
    NUI_FUSION_IMAGE_FRAME*     m_pPointCloud;

    /// <summary>
    /// Images for display
    /// </summary>
    NUI_FUSION_IMAGE_FRAME*     m_pShadedSurface;
	GLubyte*					m_pImageData;

    /// <summary>
    /// Camera Tracking parameters
    /// </summary>
    int                         m_cLostFrameCounter;
    float                       m_fMaxTranslationDelta;
    float                       m_fMaxRotationDelta;
    bool                        m_bTrackingFailed;

    /// <summary>
    /// Parameter to turn automatic reset of the reconstruction when camera tracking is lost on or off.
    /// Set to true in the constructor to enable auto reset on cResetOnNumberOfLostFrames lost frames,
    /// or set false to never automatically reset.
    /// </summary>
    bool                        m_bAutoResetReconstructionWhenLost;

    /// <summary>
    /// Processing parameters
    /// </summary>
    int                         m_deviceIndex;
    NUI_FUSION_RECONSTRUCTION_PROCESSOR_TYPE m_processorType;
    bool                        m_bInitializeError;
    float                       m_fMinDepthThreshold;
    float                       m_fMaxDepthThreshold;
    bool                        m_bMirrorDepthFrame;
    unsigned short              m_cMaxIntegrationWeight;
    int                         m_cFrameCounter;

    /// <summary>
    /// Parameter to translate the reconstruction based on the minimum depth setting. When set to
    /// false, the reconstruction volume +Z axis starts at the camera lens and extends into the scene.
    /// Setting this true in the constructor will move the volume forward along +Z away from the
    /// camera by the minimum depth threshold to enable capture of very small reconstruction volumes
    /// by setting a non-identity camera transformation in the ResetReconstruction call.
    /// Small volumes should be shifted, as the Kinect hardware has a minimum sensing limit of ~0.35m,
    /// inside which no valid depth is returned, hence it is difficult to initialize and track robustly  
    /// when the majority of a small volume is inside this distance.
    /// </summary>
    bool                        m_bTranslateResetPoseByMinDepthThreshold;
};
