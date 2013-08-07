#include "StdAfx.h"
#include "ImagePlane.h"

#include <iostream>

ImagePlane::ImagePlane(void) : Actor3D()
{
	width = 0;
	height = 0;

	data = 0;

	initialized = false;
	show = true;
}


ImagePlane::~ImagePlane(void)
{
	free(data);
}

void ImagePlane::toggleShow()
{
	show = !show;
}

void ImagePlane::init()
{
	std::cout << "- Create OpenGL Texture" << std::endl;
	// Initialize textures
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) data);
    glBindTexture(GL_TEXTURE_2D, 0);

	initialized = true;		
}

bool ImagePlane::needsInit()
{
	return !initialized;
}

void ImagePlane::createImage(GLsizei iWidth, GLsizei iHeight)
{
	width = iWidth;
	height = iHeight;

	if (width == 0 || height == 0)
		return;

	std::cout << "- Allocating Memory for Image Data." << std::endl;
	data = (GLubyte*) malloc(4*width*height*sizeof(GLubyte));

}

GLubyte* ImagePlane::getImageData()
{
	return data;
}

void ImagePlane::render(Camera* camera)
{
	if (show) {
		// Camera setup
		glViewport(0, 0, camera->getWidth(), camera->getHeight());
		glMatrixMode(GL_PROJECTION);												// Select The Projection Matrix
		glPushMatrix();
		glLoadIdentity();															// Reset The Projection Matrix
		gluPerspective(camera->getFOV(),											// Set Field of View
			(GLfloat)camera->getWidth()/(GLfloat)camera->getHeight(),				// Set aspect ratio
			camera->getNearClipping(),												// Set near clipping
			camera->getFarClipping());												// Set far clipping
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		gluLookAt(						/* look from camera XYZ */
			camera->getPosition().x(), 
			camera->getPosition().y(),
			camera->getPosition().z(),
			0, 0, 0, /* look at the origin */
			0, 1, 0); /* positive Y up vector */

		// OpenGL setup
		glClearColor(0,0,0,0);
		glClearDepth(1.0f);
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.5f, 0.0f, -0.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5f, 0.0f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}
