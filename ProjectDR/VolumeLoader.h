#pragma once
#include "OpenGL.h"

class VolumeLoader
{
public:
	VolumeLoader(void);
	~VolumeLoader(void);

	int loadRaw(const char *directory);

	int getPixelCount();
	GLubyte* getData();
	
	float getSpacingX();
	float getSpacingY();
	float getSpacingZ();

	int getVolumeWidth();
	int getVolumeHeight();
	int getVolumeDepth();

private:
	int pixelCount;
	GLubyte *data;
	float spacingX, spacingY, spacingZ;
	int volumeWidth, volumeHeight, volumeDepth;
};


