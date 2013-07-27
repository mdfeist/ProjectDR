#pragma once
#include "OpenGL.h"
#include "Actor.h"

class ImageRender : public Actor
{
public:
	ImageRender(void);
	~ImageRender(void);

	void createImage(GLsizei iWidth, GLsizei iHeight);
	GLubyte* getImageData();

	void init();
	bool needsInit();

	void render(Camera*);

protected:
	GLubyte*		data;

	GLsizei			width;
	GLsizei			height;

	bool			initialized;

private:
	GLuint			textureId;
};

