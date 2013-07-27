#pragma once
#include "FormController.h"
#include "OpenGLView.h"

#include "KinectFusionRender.h"
#include "KinectFusionBasics.h"

class Volume;
class RenderManager;

public class VolumeRenderManager :
	public FormController<VolumeRenderManager, ProjectDR::OpenGLView>
{
public:
	void initFusion();

	Volume* loadVolume(const char*);
	void addVolumeToScene();
	void removeVolumeFromScene();

	void setRigidBody(int id);
private:
	Volume*					volume;
	KinectFusionRender*		fusionImage;
	CKinectFusionBasics*	fusion;

	int						rigidBodyID;
};

