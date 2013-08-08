#pragma once
#include "OpenGL.h"
#include "Actor3D.h"

class ImagePlane : public Actor3D
{
public:
	ImagePlane(void);
	~ImagePlane(void);

	void createImage(GLsizei iWidth, GLsizei iHeight);
	GLubyte* getImageData();

	void init();
	bool needsInit();

	void setMatrix(const Eigen::Matrix4f& m);
	void toggleShow();
	bool isShown();

	void render(Camera*);

protected:
	GLubyte*		data;

	GLsizei			width;
	GLsizei			height;

	bool			initialized;
	bool			show;
private:
	GLuint			textureId;

	Eigen::Matrix4f matrix;
};

