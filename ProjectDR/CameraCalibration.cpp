#include "StdAfx.h"
#include "CameraCalibration.h"

#include <string>

#include "CameraCalibrationFormController.h"
#include "ClientHandler.h"
#include "RigidBody.h"

#if _DEBUG
using namespace System;
using namespace System::Diagnostics;
using namespace System::IO;

void printFloat(float value) {
	Debug::Write(value);
}

void print(const char* value) {
	Debug::Write(gcnew System::String(value));
}

void println(const char* value) {
	Debug::WriteLine(gcnew System::String(value));
}
#endif

#pragma unmanaged
CameraCalibration::CameraCalibration(void)
{
}


CameraCalibration::~CameraCalibration(void)
{
}

void CameraCalibration::init() {
	this->rbCameraId = -1;
	this->screenX = 0;
	this->screenY = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;

	this->cameraOffsetVectors.clear();
}

void CameraCalibration::addCameraOffset() {
	RigidBody* body = ClientHandler::getInstance()->getRigidBody(this->rbCameraId);

	if (body)
	{
		// Get Rigid Body Information
		Eigen::Quaternionf quat = body->getRotation();
		Eigen::Vector3f pos = body->getPosition();

		Eigen::Matrix3f rotationMatrix;
		Eigen::Matrix4f matrix;
		Eigen::Matrix4f matrixInverse;

		// Get Rotation of Camera
		rotationMatrix = quat.toRotationMatrix();

		// Set the matrix to the identity
		matrix = Eigen::Matrix4f::Identity();

		// Copy the rotation matrix
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				matrix(i,j) = rotationMatrix(i,j);
			}
		}

		// Set the translation
		matrix(0,3) = pos(0);
		matrix(1,3) = pos(1);
		matrix(2,3) = pos(2);

		// Get the inverse
		matrixInverse = matrix.inverse();

		// Convert the position from Vector3f to Vector4f
		Eigen::Vector4f position;
		position(0) = pos(0);
		position(1) = pos(1);
		position(2) = pos(2);
		position(3) = 1.0f;

		// Apply transformation
		Eigen::Vector4f ray = matrixInverse * position;

		// Convert ray from Vector4f to Vector3f
		Eigen::Vector3f calculatedRay;

		calculatedRay(0) = ray(0);
		calculatedRay(1) = ray(1);
		calculatedRay(2) = ray(2);

		calculatedRay.normalize();

		// Add ray to the array
		this->cameraOffsetVectors.push_back(calculatedRay);

#if _DEBUG
		println("Ray:");
		printFloat(ray(0));
		print(", ");
		printFloat(ray(1));
		print(", ");
		printFloat(ray(2));
		print(", ");
		printFloat(ray(3));
		println("\n");

		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				printFloat(matrixInverse(i,j));
				print(", ");
			}
			println("");
		}
#endif
	}
}

int CameraCalibration::calculateOffset() {
	char buffer[512];
	std::string msg;

	if (this->cameraOffsetVectors.size() <= 0) {
		CameraCalibrationFormController::getInstance()->offsetCalibrationOutputLog("Error: You need at least one camera position.\n");
		return NO_CAMERA_POSITIONS_FOR_OFFSET;
	} else {
		sprintf_s(buffer, "You have %d different camera position(s)\n", this->cameraOffsetVectors.size());
		msg = buffer;
		CameraCalibrationFormController::getInstance()->offsetCalibrationOutputLog(msg);
	}

	// Get ray
	Eigen::Vector3f ray;

	for (unsigned int i = 0; i < this->cameraOffsetVectors.size(); i++)
		ray += this->cameraOffsetVectors[i];

	ray /= (float)this->cameraOffsetVectors.size();
	ray.normalize();

	// Message to Output Log
	sprintf_s(buffer, "Ray(%f, %f, %f)\n", ray(0), ray(1), ray(2));
	msg = buffer;
	CameraCalibrationFormController::getInstance()->offsetCalibrationOutputLog(msg);

	// Get Angle
	float a = ray.dot(Eigen::Vector3f(0.f, 0.f, 1.f));

	// Message to Output Log
	sprintf_s(buffer, "Dot product %f\n", a);
	msg = buffer;
	CameraCalibrationFormController::getInstance()->offsetCalibrationOutputLog(msg);

	if (a != a) {
		cameraOffset =  Eigen::Quaternionf::Identity();
		return CALIBRATION_OK;
	}

	float angle = acos(a);
	
	// Get axis
	Eigen::Vector3f axis;
	axis = ray.cross(Eigen::Vector3f(0.f, 0.f, 1.f));
	axis.normalized();

	// Message to Output Log
	sprintf_s(buffer, "Offset: (%f, %f, %f, %f)\n", angle, axis(0), axis(1), axis(2));
	msg = buffer;
	CameraCalibrationFormController::getInstance()->offsetCalibrationOutputLog(msg);

	cameraOffset = Eigen::Quaternionf(Eigen::AngleAxisf(angle, axis));

	return CALIBRATION_OK;
}

Eigen::Quaternionf CameraCalibration::getCameraOffset() {
	return this->cameraOffset;
}

char* CameraCalibration::getNameById(int id) {
	if (id < 0)
		return 0;

	RigidBody* body = ClientHandler::getInstance()->getRigidBody(id);

	if (body)
	{
		return body->getName();
	}
	return 0;
}

void CameraCalibration::setCameraId(int id) { this->rbCameraId = id; }
int CameraCalibration::getCameraId() { return this->rbCameraId; }
char* CameraCalibration::getCameraName() { return getNameById(this->rbCameraId); }

void CameraCalibration::setWorkingArea(int x, int y, int w, int h) {
	screenX = x;
	screenY = y;
	screenWidth = w;
	screenHeight = h;
}

int CameraCalibration::getX() { return this->screenX; }
int CameraCalibration::getY() { return this->screenY; }
int CameraCalibration::getWidth() { return this->screenWidth; }
int CameraCalibration::getHeight() { return this->screenHeight; }

float CameraCalibration::getAspect() { return (float)this->screenWidth/this->screenHeight; }

#pragma managed
