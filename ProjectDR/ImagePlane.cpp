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

bool ImagePlane::isShown()
{
	return show;
}

void ImagePlane::setMatrix(const Eigen::Matrix4f& m)
{
	matrix = m;
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
		glPushMatrix();
		glLoadIdentity();

		gluLookAt(						/* look from camera XYZ */
			camera->getPosition().x(), 
			camera->getPosition().y(),
			camera->getPosition().z(),
			0, 0, 0, /* look at the origin */
			0, 1, 0); /* positive Y up vector */

		glMultMatrixf((const GLfloat*)matrix.data());

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
		glPopMatrix();
	}
}
