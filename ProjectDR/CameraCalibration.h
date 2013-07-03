#pragma once
#include <vector>

enum {
	CALIBRATION_OK = 0,
	NO_CAMERA_POSITIONS_FOR_OFFSET,
};

#pragma unmanaged
#include "Eigen\Core.h"
#include "Eigen\Geometry.h"

class CameraCalibration
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	CameraCalibration(void);
	~CameraCalibration(void);

	void init();

	void setCameraId(int id);
	int getCameraId();
	char* getCameraName();

	void addCameraOffset();
	int calculateOffset();

	Eigen::Quaternionf getCameraOffset();

	void setWorkingArea(int x, int y, int w, int h);

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	float getAspect();
private:
	char* getNameById(int id);

	int rbCameraId;
	Eigen::Quaternionf cameraOffset;

	std::vector<Eigen::Vector3f> cameraOffsetVectors;

	int screenX;
	int screenY;
	int screenWidth;
	int screenHeight;
};
#pragma managed

