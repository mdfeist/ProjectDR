#pragma once
#include <windows.h>
#include "OpenGL.h"

#include <vector>

class Actor;
class Camera;
class RendererCallback;

class RenderManager
{
public:
	RenderManager(void);
	~RenderManager(void);

	void addUpdateDelegate(RendererCallback*);
	void removeUpdateDelegate(RendererCallback*);

	void addActor(Actor*);
	void removeActor(Actor*);
	void update();
	void render(Camera*);

private:
	std::vector<Actor*> actors;

	std::vector<RendererCallback*>	updateObservers;
};

