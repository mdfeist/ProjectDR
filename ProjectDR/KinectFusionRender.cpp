#include "stdafx.h"
#include "KinectFusionRender.h"

#include "KinectFusion.h"
#include "ClientHandler.h"
#include "RigidBody.h"

KinectFusionRender::KinectFusionRender(void) : ImageRender() 
{
	fusion = nullptr;
	cameraRigidBodyId = -1;
	firstFrame = Eigen::Matrix4f::Identity();
}

Eigen::Matrix4f KinectFusionRender::getMatrix(int id) 
{
	Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();

	RigidBody* rb = ClientHandler::getInstance()->getRigidBody(id);

	if (rb) {
		// Get Rigid Body Information
		Eigen::Quaternionf quat = Eigen::Quaternionf(rb->qw(), rb->qx(), rb->qy(), rb->qz());
		Eigen::Vector3f pos = rb->getPosition();

		Eigen::Matrix3f rotationMatrix;

		// Get Rotation of Camera
		rotationMatrix = quat.toRotationMatrix();

		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 3; i++)
				matrix(i,j) = rotationMatrix(i,j);

		matrix(3,0) = pos(0);
		matrix(3,1) = pos(1);
		matrix(3,2) = pos(2); // Negate
	}

	return matrix;
}

void KinectFusionRender::attachKinectFusion(CKinectFusion* f) 
{ 
	fusion = f;
}

void KinectFusionRender::setFusionMatrix(Eigen::Matrix4f& matrix) 
{
	Matrix4 mat;

	// Copy the rotation matrix
	mat.M11 = matrix(0,0);
	mat.M12 = matrix(0,1);
	mat.M13 = matrix(0,2);
	mat.M14 = 0;

	mat.M21 = matrix(1,0);
	mat.M22 = matrix(1,1);
	mat.M23 = matrix(1,2);
	mat.M24 = 0;

	mat.M31 = matrix(2,0);
	mat.M32 = matrix(2,1);
	mat.M33 = matrix(2,2);
	mat.M34 = 0;

	mat.M41 = -matrix(3,0);
	mat.M42 = -matrix(3,1);
	mat.M43 = -matrix(3,2);
	mat.M44 = 1;

	fusion->SetCameraTransform(mat);
}

void KinectFusionRender::setCameraRigidBodyId(int id) 
{ 
	cameraRigidBodyId = id;
	firstFrame = getMatrix(id);
}

void KinectFusionRender::init() 
{ 
	ImageRender::init();
	fusion->SetImageData(data); 
}

void KinectFusionRender::render(Camera* camera) 
{
	Eigen::Matrix4f matrix = firstFrame * getMatrix(cameraRigidBodyId).inverse();
	setFusionMatrix(matrix);

	fusion->Update(); 

	ImageRender::render(camera); 
}