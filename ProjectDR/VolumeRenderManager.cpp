#include "StdAfx.h"
#include "VolumeRenderManager.h"

#include <iostream>

#pragma unmanaged
#include "ClientHandler.h"
#include "RigidBody.h"
#include "Volume.h"
#include "VolumeLoader.h"
#include "RendererDelegator.h"
#pragma managed

#include "Renderer.h"
#include "RenderManager.h"

VolumeRenderManager* FormController<VolumeRenderManager, ProjectDR::OpenGLView>::m_pInstance = NULL;
int RendererCallback::Callback_ID = 0;

VolumeRenderManager::VolumeRenderManager(void) : FormController<VolumeRenderManager, ProjectDR::OpenGLView>() {
	volume = nullptr;
	
	scale = 1.f;
	x_offset = y_offset = z_offset = 0.f;
	qx_offset = qy_offset = qz_offset = 0.f;
	rotation = Eigen::Quaternionf::Identity();
}

void VolumeRenderManager::initFusion() {
	createForm();

	fusionImage = new KinectFusionRender();
	fusionImage->createImage(640, 480);
	fusionImage->setCameraRigidBodyId(rigidBodyID);

	fusion = new CKinectFusion();
	fusionImage->attachKinectFusion(fusion);

	// Look for a connected Kinect, and create it if found
	HRESULT hr = fusion->CreateFirstConnected();	
	if (FAILED(hr))
	{
		fusion->SetInitializeError(true);
	}

	if (!fusion->GetInitializeError())
	{
		hr = fusion->InitializeKinectFusion();
		if(FAILED(hr))
		{
			fusion->SetInitializeError(true);
		}
	}

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		RenderManager* manager = renderer->getManager();
		
		if (manager) {
			manager->addActor(fusionImage);
		} else {
			std::cout << "Failed."<< std::endl;
			std::cout <<"************************" <<std::endl;
			std::cout << "RenderManager was NULL" << std::endl;
			std::cout << "***********************" <<std::endl;
		}

	} else {
		std::cout << "Failed."<< std::endl;
		std::cout <<"************************" <<std::endl;
		std::cout << "Form Renderer was NULL" << std::endl;
		std::cout <<"************************" <<std::endl;
	}
}

void VolumeRenderManager::setFOV(float value) {
	createForm();

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		renderer->getActiveCamera()->setFOV(value);
		renderer->getActiveCamera()->setPosition(0.f, 0.1669f, -1.1462f);
		renderer->getActiveCamera()->lookAt(0.f, 0.f, 0.f);
	} else {
		std::cout << "Failed."<< std::endl;
		std::cout <<"************************" <<std::endl;
		std::cout << "Form Renderer was NULL" << std::endl;
		std::cout <<"************************" <<std::endl;
	}
}

void VolumeRenderManager::setRigidBody(int id) {
	rigidBodyID = id;
}

Volume* VolumeRenderManager::loadVolume(const char* volumeFile) {
	VolumeLoader* volumeLoader = new VolumeLoader();
	volumeLoader->loadRaw(volumeFile);

	if (volume) {
		removeVolumeFromScene();

		delete volume;
		volume = nullptr;

		delete updateVolumeDelegate;
		updateVolumeDelegate = nullptr;
	}

	volume = new Volume();
	volume->setAxisAngle(-(float)M_PI/2.0f, 1.f, 0.f, 0.f);
	volume->setVolumeData(volumeLoader);
	volume->setup();

	updateVolumeDelegate = new RendererDelegator<VolumeRenderManager>();
	updateVolumeDelegate->RegisterCallback(VolumeRenderManager::getInstance(), &VolumeRenderManager::updateVolume);
	
	return volume;
}

void VolumeRenderManager::addVolumeToScene() {
	createForm();

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		RenderManager* manager = renderer->getManager();
		
		if (manager) {
			manager->addUpdateDelegate(updateVolumeDelegate);
			manager->addActor(volume);
		} else {
			std::cout << "Failed."<< std::endl;
			std::cout <<"************************" <<std::endl;
			std::cout << "RenderManager was NULL" << std::endl;
			std::cout << "***********************" <<std::endl;
		}

	} else {
		std::cout << "Failed."<< std::endl;
		std::cout <<"************************" <<std::endl;
		std::cout << "Form Renderer was NULL" << std::endl;
		std::cout <<"************************" <<std::endl;
	}
}

void VolumeRenderManager::removeVolumeFromScene() {
	createForm();

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		RenderManager* manager = renderer->getManager();
		
		if (manager) {
			manager->removeUpdateDelegate(updateVolumeDelegate);
			manager->removeActor(volume);
		} else {
			std::cout << "Failed."<< std::endl;
			std::cout <<"************************" <<std::endl;
			std::cout << "RenderManager was NULL" << std::endl;
			std::cout << "***********************" <<std::endl;
		}

	} else {
		std::cout << "Failed."<< std::endl;
		std::cout <<"************************" <<std::endl;
		std::cout << "Form Renderer was NULL" << std::endl;
		std::cout <<"************************" <<std::endl;
	}
}

void VolumeRenderManager::updateVolume() {
	Eigen::Matrix4f rb_matrix = Eigen::Matrix4f::Identity();

	Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f scaleMatrix = Eigen::Matrix4f::Identity();

	scaleMatrix(0,0) = scaleMatrix(1,1) = scaleMatrix(2,2) = scale;

	Eigen::Matrix3f rotationMatrix = rotation.toRotationMatrix();

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 3; i++)
			matrix(i,j) = rotationMatrix(i,j);
	
	matrix(0,3) = x_offset;
	matrix(1,3) = -z_offset;
	matrix(2,3) = -y_offset;

	RigidBody* rb = ClientHandler::getInstance()->getRigidBody(rigidBodyID);

	if (rb) {
		// Get Rigid Body Information
		Eigen::Quaternionf quat = Eigen::Quaternionf(rb->qw(), rb->qx(), -rb->qy(), -rb->qz());
		Eigen::Vector3f pos = rb->getPosition();

		Eigen::Matrix3f rotationMatrix;

		// Get Rotation of Camera
		rotationMatrix = quat.toRotationMatrix();

		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 3; i++)
				rb_matrix(i,j) = rotationMatrix(i,j);

		rb_matrix(0,3) = pos(0);
		rb_matrix(1,3) = -pos(1);
		rb_matrix(2,3) = -pos(2);
	}

	matrix = scaleMatrix * matrix;
	matrix = rb_matrix * matrix;

	if (volume)
		volume->setMatrix(matrix);
}

void VolumeRenderManager::setMinIsoValue(float value) {
	if (volume) {
		volume->setIsoValue(value);
	}
}

void VolumeRenderManager::setScale(float value) {
	scale = value;
}

void VolumeRenderManager::setPositionX(float value) {
	x_offset = value;
}

void VolumeRenderManager::setPositionY(float value) {
	y_offset = value;
}

void VolumeRenderManager::setPositionZ(float value) {
	z_offset = value;
}

void VolumeRenderManager::setRotationX(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qx_offset) * M_PI/180.f, Eigen::Vector3f::UnitX());
	qx_offset = value;
}

void VolumeRenderManager::setRotationY(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qy_offset) * M_PI/180.f, Eigen::Vector3f::UnitY());
	qy_offset = value;
}

void VolumeRenderManager::setRotationZ(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qz_offset) * M_PI/180.f, Eigen::Vector3f::UnitZ());
	qz_offset = value;
}