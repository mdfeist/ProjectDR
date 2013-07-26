#include "StdAfx.h"
#include "RenderManager.h"

#include "OpenGL.h"

#include <iostream>

#include "Actor.h"

RenderManager::RenderManager(void)
{
}

RenderManager::~RenderManager(void)
{
	actors.clear();
}


void RenderManager::addActor(Actor* actor) {
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
}

void RenderManager::render(Camera* camera) {
	for each (Actor* actor in actors)
		actor->render(camera);
}