#include "StdAfx.h"
#include "VolumeLoader.h"

#include <iostream>

VolumeLoader::VolumeLoader(void) {
	data = NULL;															// Set the volume data to NULL

	volumeWidth = 1;														// Set the default width to one
	volumeHeight = 1;														// Set the default height to one
	volumeDepth = 1;														// Set the default depth to one

	spacingX = 1.f;															// By default there is no spacing
	spacingY = 1.f;															// And all the dimensions of the
	spacingZ = 1.f;															// voxels are the same
}


VolumeLoader::~VolumeLoader(void) {
	if (data)
		delete [] data;
}

int VolumeLoader::loadRaw(const char *directory) {							// Loads raw volume data from a file
	FILE* dataFile = NULL;
	fopen_s(&dataFile, directory, "rb");									// Opens file

	if (dataFile) {															// Checks if file was able to open
		if (data != NULL) {													// Checks if volume data already exists
			delete[] data;													// If so delete it from memory
			data = NULL;													// Set pointer to NULL
		}

		std::cout << "- Loading: " << directory << std::endl; 
		fread(&spacingX, sizeof(float), 1, dataFile);						// Read X spacing size
		fread(&spacingY, sizeof(float), 1, dataFile);						// Read Y spacing size 
		fread(&spacingZ, sizeof(float), 1, dataFile);						// Read Z spacing size
		fread(&volumeWidth, sizeof(int), 1, dataFile);						// Read volume width
		fread(&volumeHeight, sizeof(int), 1, dataFile);						// Read volume height
		fread(&volumeDepth, sizeof(int), 1, dataFile);						// Read volume depth

		
		std::cout << "- Volume Spacing: " 
			<< "[" 
			<< spacingX << ", "
			<< spacingY << ", "
			<< spacingZ
			<< "]" << std::endl;

		std::cout << "- Volume Dimension: " 
			<< "[" 
			<< volumeWidth << ", "
			<< volumeHeight << ", "
			<< volumeDepth
			<< "]" << std::endl;

		pixelCount = volumeWidth * volumeHeight * volumeDepth;				// Calculate the number of voxels
		data = new GLubyte[pixelCount];										// Allocate memory for the volume data
		fread(data, sizeof(GLubyte), pixelCount, dataFile);					// Read volume data from file

		fclose(dataFile);													// Close file

		return EXIT_SUCCESS;
	} else {
		std::cout << "- Unable to open: " << directory << std::endl;
	}

	return EXIT_FAILURE;
}

int VolumeLoader::getPixelCount() {
	return pixelCount;
}

GLubyte* VolumeLoader::getData() {
	return data;
}

float VolumeLoader::getSpacingX() {
	return spacingX;
}

float VolumeLoader::getSpacingY() {
	return spacingY;
}

float VolumeLoader::getSpacingZ() {
	return spacingZ;
}

int VolumeLoader::getVolumeWidth() {
	return volumeWidth;
}

int VolumeLoader::getVolumeHeight() {
	return volumeHeight;
}

int VolumeLoader::getVolumeDepth() {
	return volumeDepth;
}
