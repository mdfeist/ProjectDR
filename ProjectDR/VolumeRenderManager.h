#pragma once
#include "FormController.h"
#include "OpenGLView.h"

#pragma unmanaged
#include "KinectFusionRender.h"
#include "RendererDelegator.h"
#pragma managed

#include "KinectFusion.h"

class Volume;
class RenderManager;

public class VolumeRenderManager :
	public FormController<VolumeRenderManager, ProjectDR::OpenGLView>
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	VolumeRenderManager(void);
	void initFusion();

	void setFOV(float);

	Volume* loadVolume(const char*);
	void addVolumeToScene();
	void removeVolumeFromScene();

	void setRigidBody(int id);
	void setMinIsoValue(float value);

	void setScale(float value);

	void setPositionX(float value);
	void setPositionY(float value);
	void setPositionZ(float value);

	void setRotationX(float value);
	void setRotationY(float value);
	void setRotationZ(float value);

	void updateVolume();
private:
	Volume*					volume;
	KinectFusionRender*		fusionImage;
	CKinectFusion*			fusion;

	int						rigidBodyID;	

	RendererDelegator<VolumeRenderManager>* updateVolumeDelegate;

	float					scale;

	float					x_offset;
	float					y_offset;
	float					z_offset;

	Eigen::Quaternionf		rotation;
	float					qx_offset;
	float					qy_offset;
	float					qz_offset;
};

