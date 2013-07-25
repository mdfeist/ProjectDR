#include "StdAfx.h"
#include "VolumeRenderManager.h"

#include <iostream>

#include "Volume.h"
#include "VolumeLoader.h"
#include "Renderer.h"
#include "RenderManager.h"

VolumeRenderManager* FormController<VolumeRenderManager, ProjectDR::OpenGLView>::m_pInstance = NULL;

Volume* VolumeRenderManager::loadVolume(const char* volumeFile) {
	VolumeLoader* volumeLoader = new VolumeLoader();
	volumeLoader->loadRaw(volumeFile);

	volume = new Volume();
	volume->setAxisAngle(-(float)M_PI/2.0f, 1.f, 0.f, 0.f);
	volume->setVolumeData(volumeLoader);
	volume->setup();

	return volume;
}


void VolumeRenderManager::addVolumeToScene() {
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

void VolumeRenderManager::removeVolumeFromScene() {
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