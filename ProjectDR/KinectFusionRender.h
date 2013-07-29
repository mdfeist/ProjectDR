#pragma once
#include "OpenGL.h"
#include "ImageRender.h"

#include <iostream>

class Camera;
class CKinectFusionBasics;

class KinectFusionRender : public ImageRender
{
public:
	KinectFusionRender(void);

	void attachKinectFusion(CKinectFusionBasics*);
	void setCameraRigidBodyId(int);

	void init();
	void render(Camera*);

private:
	CKinectFusionBasics*	fusion;
	int						cameraRigidBodyId;
	
	Eigen::Matrix4f			firstFrame;

	void setFusionMatrix(Eigen::Matrix4f& matrix);
	Eigen::Matrix4f getMatrix(int id);
};

