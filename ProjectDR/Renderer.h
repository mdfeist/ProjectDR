#pragma once
#include <windows.h>
#include "OpenGL.h"

class Camera;
class RenderManager;

using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

public ref class Renderer : 
      public System::Windows::Forms::NativeWindow
{
public:
	Renderer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight);

	Camera* getActiveCamera();
	RenderManager* getManager();

	System::Void Resize(GLsizei iWidth, GLsizei iHeight);
	virtual System::Void Render(System::Void);
	System::Void SwapOpenGLBuffers(System::Void);

private:
    HDC					m_hDC;		// Private GDI Device Contex
    HGLRC				m_hglrc;	// Permanent Rendering Context

	Camera*				camera;		// Camera for rendering
	RenderManager*		manager;	// Handles all the OpenGL rendering
protected:
    ~Renderer(System::Void);

	GLint CreatePixelFormat(HDC hdc);
};

