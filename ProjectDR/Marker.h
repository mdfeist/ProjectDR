/**
 * Marker.h
 * Created By: Michael Feist
 */

#pragma once
#include <windows.h>

#include "Eigen\Core.h"

// Holds the data for an OptiTrack Marker
class Marker {
private:
	int id;
	Eigen::Vector3f position;
public:
	Marker(int id = 0, float x = 0.f, float y = 0.f, float z = 0.f, float size = 0.f) {
		this->id = id;
		this->position = Eigen::Vector3f(x, y, z);
	}

	inline bool operator == (const Marker& rhs) const
	{
		return position == rhs.position;
	}

	inline bool operator != (const Marker& rhs) const
	{
		return position != rhs.position;
	}

	inline bool operator < (const Marker& rhs) const
	{
		return true; //position < rhs.position;
	}

	void setID(int id) { this->id = id; }
	int getID() { return this->id; }

	void setPosition(Eigen::Vector3f position) { this->position = position; }
	Eigen::Vector3f getPosition() { return this->position; }
	float& x() { return this->position.x(); }
	float& y() { return this->position.y(); }
	float& z() { return this->position.z(); }
};
