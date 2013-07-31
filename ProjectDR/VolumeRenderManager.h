#pragma once
#include "FormController.h"
#include "OpenGLView.h"

#pragma unmanaged
#include "KinectFusionRender.h"
#pragma managed

#include "KinectFusion.h"

class Volume;
class RenderManager;

public class VolumeRenderManager :
	public FormController<VolumeRenderManager, ProjectDR::OpenGLView>
{
public:
	VolumeRenderManager(void);
	void initFusion();

	Volume* loadVolume(const char*);
	void addVolumeToScene();
	void removeVolumeFromScene();

	void setRigidBody(int id);
	void setMinIsoValue(float value);
private:
	Volume*					volume;
	KinectFusionRender*		fusionImage;
	CKinectFusion*			fusion;

	int						rigidBodyID;
};

