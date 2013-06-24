/**
 * RigidBody.cpp
 * Created By: Michael Feist
 */

#include "StdAfx.h"

#include "RigidBody.h"

#pragma unmanaged
RigidBody::RigidBody(void) {
	this->id = 0;
	this->name[0] = '\0';
}


RigidBody::~RigidBody(void) {
	
}

void RigidBody::addFrame(Eigen::Vector3f position, Eigen::Quaternionf& rotation) {
	this->position = position;
	this->rotation = rotation;
}
#pragma managed