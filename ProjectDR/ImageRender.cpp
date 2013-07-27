#include "StdAfx.h"
#include "ImageRender.h"

#include <iostream>

ImageRender::ImageRender(void) : Actor()
{
	width = 0;
	height = 0;

	data = 0;

	initialized = false;
}


ImageRender::~ImageRender(void)
{
	free(data);
}

void ImageRender::init()
{
	if (width == 0 || height == 0)
		return;

	std::cout << "- Allocating Memory for Image Data." << std::endl;
	data = (GLubyte*) malloc(4*width*height*sizeof(GLubyte));

	std::cout << "- Create OpenGL Texture" << std::endl;
	// Initialize textures
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (GLvoid*) data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // OpenGL setup
    glClearColor(0,0,0,0);
    glClearDepth(1.0f);

	initialized = true;		
}

bool ImageRender::needsInit()
{
	return !initialized;
}

void ImageRender::createImage(GLsizei iWidth, GLsizei iHeight)
{
	width = iWidth;
	height = iHeight;
}

GLubyte* ImageRender::getImageData()
{
	return data;
}

void ImageRender::render(Camera* camera)
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	 // Camera setup
    glViewport(0, 0, camera->getWidth(), camera->getHeight());
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (GLvoid*)data);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 0, 0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(width, 0, 0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(width, height, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, height, 0.0f);
    glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
