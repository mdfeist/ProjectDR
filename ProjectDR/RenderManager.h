#pragma once
#include <windows.h>
#include "OpenGL.h"

#include <vector>

class Actor;
class Camera;

class RenderManager
{
public:
	RenderManager(void);
	~RenderManager(void);

	void addActor(Actor*);
	void removeActor(Actor*);
	void update();
	void render(Camera*);

private:
	std::vector<Actor*> actors;
};

