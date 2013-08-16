#pragma once
#include "OpenGL.h"
#include "ImageRender.h"

#include <iostream>

class Camera;
class CKinectFusion;

class KinectFusionRender : public ImageRender
{
public:
	KinectFusionRender(void);
	~KinectFusionRender(void);
	
	void init();
	void render(Camera*);

private:
	CKinectFusion*			fusion;
};

