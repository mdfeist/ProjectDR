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
class ImagePlane;

public class VolumeRenderManager :
	public FormController<VolumeRenderManager, ProjectDR::OpenGLView>
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	VolumeRenderManager(void);
	void initFusion();

	void setFOV(float);

	void setCameraX(float);
	void setCameraY(float);
	void setCameraZ(float);

	Volume* loadVolume(const char*);
	void addVolumeToScene();
	void removeVolumeFromScene();

	void setRigidBody(int id);
	void setMinIsoValue(float);

	void setScale(float);

	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	void setRotationX(float);
	void setRotationY(float);
	void setRotationZ(float);

	void init();

	void updateVolume();
	void update();

	void toggleGrid();
private:
	Volume*					volume;
	KinectFusionRender*		fusionImage;
	CKinectFusion*			fusion;

	ImagePlane*				calibrationGrid;

	float					fov;
	float					camera_x;
	float					camera_y;
	float					camera_z;

	bool					cameraNeedsUpdate;

	int						rigidBodyID;	

	RendererDelegator<VolumeRenderManager>* updateDelegate;

	float					scale;

	float					x_offset;
	float					y_offset;
	float					z_offset;

	Eigen::Quaternionf		rotation;
	float					qx_offset;
	float					qy_offset;
	float					qz_offset;
};

