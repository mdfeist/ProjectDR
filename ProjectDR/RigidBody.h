/**
 * RigidBody.h
 * Created By: Michael Feist
 */

#pragma once
#include <string>
#include <vector>

#include "Eigen\Core.h"
#include "Eigen\src\Geometry\RotationBase.h"
#include "Eigen\src\Geometry\Quaternion.h"

#include "Marker.h"

#include "NatNetSDK\include\NatNetTypes.h"

/*
 * The RigidBody class handles transformation data
 * of a single rigid body.
 */
class RigidBody
{
private:
	int id;									// RigidBody identifier
	char name[MAX_NAMELENGTH];				// RigidBody name

	Eigen::Vector3f position;				// RigidBody Position
	Eigen::Quaternionf rotation;			// RigidBody Rotation

	std::vector<Marker> markers;			// Vector of all the markers

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	RigidBody(void);
	~RigidBody(void);

	// Markers
	// Delete all markers
	void clearMarkers() { this->markers.clear(); }
	// Add a marker
	void addMarker(Marker marker) { this->markers.push_back(marker); }
	// Get all the markers in a vector
	std::vector<Marker> getMarkersVector() { return this->markers; }

	// Getter/Setters for the ID of the Rigid Body.
	void setID(int id) { this->id = id; }
	int getID() { return this->id; }

	// Getter/Setters for the name of the Rigid Body.
	void setName(char* name) { strncpy_s(this->name, name, strlen(name)); }
	char* getName() { return this->name; }

	// Getter/Setters for the auto transform of the Rigid Body.
	Eigen::Vector3f getPosition() { return this->position; }
	Eigen::Quaternionf getRotation() { return this->rotation; }
	
	float& x() { return this->position.x(); }
	float& y() { return this->position.y(); }
	float& z() { return this->position.z(); }

	float& qx() { return this->rotation.x(); }
	float& qy() { return this->rotation.y(); }
	float& qz() { return this->rotation.z(); }
	float& qw() { return this->rotation.w(); }

	// Update the transformation of the Rigid Body
	void addFrame(Eigen::Vector3f position, Eigen::Quaternionf& rotation);
};
