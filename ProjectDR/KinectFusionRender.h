#pragma once
#include "OpenGL.h"
#include "ImageRender.h"
#include "KinectFusionBasics.h"
#include "ClientHandler.h"
#include "RigidBody.h"

#include <iostream>

class KinectFusionRender : public ImageRender
{
public:
	KinectFusionRender(void) : ImageRender() { cameraRigidBodyId = -1; }
	void attachKinectFusion(CKinectFusionBasics* f) { fusion = f; }

	void setCameraRigidBodyId(int id) { 
		cameraRigidBodyId = id;
	}

	void init() { ImageRender::init(); fusion->SetImageData(data); }

	void render(Camera* camera) {
		RigidBody* rb = ClientHandler::getInstance()->getRigidBody(cameraRigidBodyId);

		if (rb) {
			// Get Rigid Body Information
			Eigen::Quaternionf quat = Eigen::Quaternionf(rb->qw(), -rb->qx(), -rb->qz(), -rb->qy());
			Eigen::Vector3f pos = rb->getPosition();
			
			Eigen::Matrix3f rotationMatrix;
			Matrix4 mat;

			// Get Rotation of Camera
			rotationMatrix = quat.toRotationMatrix();

			// Copy the rotation matrix
			mat.M11 = rotationMatrix(0,0);
			mat.M12 = rotationMatrix(0,1);
			mat.M13 = rotationMatrix(0,2);
			mat.M14 = 0;

			mat.M21 = rotationMatrix(1,0);
			mat.M22 = rotationMatrix(1,1);
			mat.M23 = rotationMatrix(1,2);
			mat.M24 = 0;

			mat.M31 = rotationMatrix(2,0);
			mat.M32 = rotationMatrix(2,1);
			mat.M33 = rotationMatrix(2,2);
			mat.M34 = 0;

			mat.M41 = pos(0);
			mat.M42 = pos(2);
			mat.M43 = pos(1);
			mat.M44 = 1;

			fusion->SetCameraTransform(mat);
			fusion->Update(); 
		}

		ImageRender::render(camera); 
	}

private:
	CKinectFusionBasics*	fusion;
	int						cameraRigidBodyId;
};

