#pragma once
#include "FormController.h"
#include "OpenGLView.h"

class Volume;
class RenderManager;

public class VolumeRenderManager :
	public FormController<VolumeRenderManager, ProjectDR::OpenGLView>
{
public:
	Volume* loadVolume(const char*);
	void addVolumeToScene();
	void removeVolumeFromScene();
private:
	Volume* volume;
};

