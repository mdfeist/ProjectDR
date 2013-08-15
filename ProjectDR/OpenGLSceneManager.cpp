#include "StdAfx.h"
#include "OpenGLSceneManager.h"

#include <iostream>

#pragma unmanaged
#include "ClientHandler.h" 
#include "RigidBody.h"
#include "Volume.h"
#include "VolumeLoader.h"
#include "RendererDelegator.h"
#include "ImagePlane.h"
#pragma managed

#include "Renderer.h"
#include "RenderManager.h"

using namespace System::Drawing;

OpenGLSceneManager* FormController<OpenGLSceneManager, ProjectDR::OpenGLView>::m_pInstance = NULL;
int RendererCallback::Callback_ID = 0;

OpenGLSceneManager::OpenGLSceneManager(void) : FormController<OpenGLSceneManager, ProjectDR::OpenGLView>() {
	volume = nullptr;
	calibrationGrid = nullptr;

	cameraNeedsUpdate = true;

	intrinsicMatrix = new float[16];
	useIntrinsic = false;

	fov = 45.0f;

	camera_x = 0.f;
	camera_y = 0.f;
	camera_z = -1.f;
	
	scale = 1.f;
	x_offset = y_offset = z_offset = 0.f;
	qx_offset = qy_offset = qz_offset = 0.f;
	rotation = Eigen::Quaternionf::Identity();

	updateDelegate = nullptr;
}

void OpenGLSceneManager::setGridRigidBody(int id) {
	gridRigidBodyID = id;
}

void OpenGLSceneManager::toggleGrid() {
	if (calibrationGrid != nullptr)
		calibrationGrid->toggleShow();
}

void OpenGLSceneManager::init() {
	createForm();

	if (form && !form->IsDisposed) {
		Renderer^ renderer = form->GetRenderer();
		if (renderer != nullptr) {
			RenderManager* manager = renderer->getManager();

			if (manager) {
				if (updateDelegate != nullptr) {
					manager->removeUpdateDelegate(updateDelegate);
					delete updateDelegate;
					updateDelegate = nullptr;
				}

				updateDelegate = new RendererDelegator<OpenGLSceneManager>();
				updateDelegate->RegisterCallback(this, &OpenGLSceneManager::update);
				manager->addUpdateDelegate(updateDelegate);

				if (calibrationGrid == nullptr) {
					// Create a Bitmap object from an image file.
					Bitmap^ myBitmap = gcnew Bitmap("images/Grid.png");

					int width = myBitmap->Width;
					int height = myBitmap->Height;

					std::cout << "Width: " << width << std::endl;
					std::cout << "Height: " << height << std::endl;

					calibrationGrid = new ImagePlane();
					calibrationGrid->createImage(width, height);

					GLubyte* data = calibrationGrid->getImageData();

					for (int j = 0; j < height; j++) {
						for (int i = 0; i < width; i++) {
							// Get the color of a pixel within myBitmap.
							data[4*(j*width + i) + 0] = (GLubyte)myBitmap->GetPixel(i, j).R;
							data[4*(j*width + i) + 1] = (GLubyte)myBitmap->GetPixel(i, j).G;
							data[4*(j*width + i) + 2] = (GLubyte)myBitmap->GetPixel(i, j).B;
							data[4*(j*width + i) + 3] = (GLubyte)myBitmap->GetPixel(i, j).A;
						}
					}

					manager->addActor(calibrationGrid);
				}
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
}

void OpenGLSceneManager::initFusion() {
	createForm();

	fusionImage = new KinectFusionRender();
	fusionImage->createImage(640, 480);

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

void OpenGLSceneManager::setIntrinsicMatrix(float* matrix) {
	for (int i = 0; i < 16; i++)
		intrinsicMatrix[i] = matrix[i];

	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setUseIntrinsic(bool value) {
	useIntrinsic = value;
	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setFOV(float value) {
	fov = value;
	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setCameraX(float value) {
	camera_x = value;
	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setCameraY(float value) {
	camera_y = value;
	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setCameraZ(float value) {
	camera_z = value;
	cameraNeedsUpdate = true;
}

void OpenGLSceneManager::setRigidBody(int id) {
	rigidBodyID = id;
}

Volume* OpenGLSceneManager::loadVolume(const char* volumeFile) {
	VolumeLoader* volumeLoader = new VolumeLoader();
	volumeLoader->loadRaw(volumeFile);

	if (volume) {
		removeVolumeFromScene();

		delete volume;
		volume = nullptr;
	}

	volume = new Volume();
	volume->setVolumeData(volumeLoader);
	volume->setup();
	
	return volume;
}

void OpenGLSceneManager::addVolumeToScene() {
	createForm();

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		RenderManager* manager = renderer->getManager();
		
		if (manager) {
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

void OpenGLSceneManager::removeVolumeFromScene() {
	createForm();

	Renderer^ renderer = form->GetRenderer();
	if (renderer) {
		RenderManager* manager = renderer->getManager();
		
		if (manager) {
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

void OpenGLSceneManager::update() {
	if (cameraNeedsUpdate) {
		if (form && !form->IsDisposed) {
			Renderer^ renderer = form->GetRenderer();
			if (renderer != nullptr) {
				updateCamera(renderer->getActiveCamera());
				cameraNeedsUpdate = false;
			} else {
				std::cout << "Failed."<< std::endl;
				std::cout <<"************************" <<std::endl;
				std::cout << "Form Renderer was NULL" << std::endl;
				std::cout <<"************************" <<std::endl;
			}
		}
	}

	updateGrid();
	updateVolume();
}

void OpenGLSceneManager::updateCamera(Camera* camera) {
	if (useIntrinsic) {
		camera->useIntrinsicMatrix(true);

		Eigen::Matrix4f k(intrinsicMatrix);
		camera->setIntrinsicMatrix(k);
	} else {
		camera->useIntrinsicMatrix(false);
		camera->setFOV(fov);
	}

	camera->setPosition(camera_x, camera_y, camera_z);
}

void OpenGLSceneManager::updateGrid() {
	Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();

	RigidBody* rb = ClientHandler::getInstance()->getRigidBody(gridRigidBodyID);

	if (rb) {
		// Get Rigid Body Information
		Eigen::Quaternionf quat = Eigen::Quaternionf(rb->qw(), -rb->qx(), rb->qy(), -rb->qz());
		Eigen::Vector3f pos = rb->getPosition();

		Eigen::Matrix3f rotationMatrix;

		// Get Rotation of Camera
		rotationMatrix = quat.toRotationMatrix();

		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 3; i++)
				matrix(i,j) = rotationMatrix(i,j);

		matrix(0,3) = -pos(0);
		matrix(1,3) = pos(1);
		matrix(2,3) = -pos(2);
	}

	if (calibrationGrid)
		calibrationGrid->setMatrix(matrix);
}

void OpenGLSceneManager::updateVolume() {
	Eigen::Matrix4f rb_matrix = Eigen::Matrix4f::Identity();

	Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f scaleMatrix = Eigen::Matrix4f::Identity();

	scaleMatrix(0,0) = scaleMatrix(1,1) = scaleMatrix(2,2) = scale;

	Eigen::Matrix3f rotationMatrix = rotation.toRotationMatrix();

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 3; i++)
			matrix(i,j) = rotationMatrix(i,j);
	
	matrix(0,3) = x_offset;
	matrix(1,3) = -y_offset;
	matrix(2,3) = -z_offset;

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

void OpenGLSceneManager::setMinIsoValue(float value) {
	if (volume) {
		volume->setIsoValue(value);
	}
}

void OpenGLSceneManager::setScale(float value) {
	scale = value;
}

void OpenGLSceneManager::setPositionX(float value) {
	x_offset = value;
}

void OpenGLSceneManager::setPositionY(float value) {
	y_offset = value;
}

void OpenGLSceneManager::setPositionZ(float value) {
	z_offset = value;
}

void OpenGLSceneManager::setRotationX(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qx_offset) * M_PI/180.f, Eigen::Vector3f::UnitX());
	qx_offset = value;
}

void OpenGLSceneManager::setRotationY(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qy_offset) * M_PI/180.f, Eigen::Vector3f::UnitY());
	qy_offset = value;
}

void OpenGLSceneManager::setRotationZ(float value) {
	rotation = rotation * Eigen::AngleAxisf((value - qz_offset) * M_PI/180.f, Eigen::Vector3f::UnitZ());
	qz_offset = value;
}