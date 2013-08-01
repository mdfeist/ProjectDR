#include "StdAfx.h"
#include "RenderManager.h"

#include "OpenGL.h"

#include <iostream>

#include "Actor.h"
#include "RendererCallback.h"

RenderManager::RenderManager(void)
{
}

RenderManager::~RenderManager(void)
{
	actors.clear();

	for each (RendererCallback* callback in updateObservers) {
		delete callback;
		callback = nullptr;
	}

	updateObservers.clear();
}

void RenderManager::addUpdateDelegate(RendererCallback* callback) {
	bool found = false;
	for (int i = updateObservers.size() - 1; i >= 0; i--) { 
		if (callback->getID() == updateObservers[i]->getID()) {
			found = true;
			break;
		}
	}

	if (!found)
		updateObservers.push_back(callback);
}

void RenderManager::removeUpdateDelegate(RendererCallback* callback) {
	for (int i = updateObservers.size() - 1; i >= 0; i--) { 
		if (callback->getID() == updateObservers[i]->getID()) {
			updateObservers.erase(updateObservers.begin() + i);
		}
	}
}

void RenderManager::addActor(Actor* actor) {
	bool found = false;
	for (int i = actors.size() - 1; i >= 0; i--) { 
		if (actor->getID() == actors[i]->getID()) {
			found = true;
			break;
		}
	}

	if (!found)
		actors.push_back(actor);
}

void RenderManager::removeActor(Actor* actor) {
	for (int i = actors.size() - 1; i >= 0; i--) { 
		if (actor->getID() == actors[i]->getID()) {
			actors.erase(actors.begin() + i);
		}
	}
}

void RenderManager::update() {
	for each (Actor* actor in actors)
		if (actor->needsInit())
			actor->init();

	for each (RendererCallback* callback in updateObservers)
		callback->Execute();
}

void RenderManager::render(Camera* camera) {
	for each (Actor* actor in actors)
		actor->render(camera);
}