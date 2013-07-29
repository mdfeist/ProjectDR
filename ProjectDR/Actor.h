#pragma once
#include "Camera.h"

class Actor {
public:
	static int id_counter;

	Actor() { actor_id = id_counter++; }
    virtual ~Actor() {}
	virtual void init() = 0;
	virtual bool needsInit() = 0;
    virtual void render(Camera*) = 0;

	int getID() {
		return actor_id;
	}

protected:
	int actor_id;
};