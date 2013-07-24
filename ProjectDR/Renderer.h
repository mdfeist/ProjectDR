#pragma once
#include <windows.h>
#include "OpenGL.h"

#include <vector>
#using <mscorlib.dll>

#pragma unmanaged
#include "Volume.h"
#pragma managed

class Camera;

using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

public ref class Renderer : 
      public System::Windows::Forms::NativeWindow
{
public:
	Renderer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight);

	System::Void addActor(Actor* a);
	Camera* getActiveCamera();

	System::Void Resize(GLsizei iWidth, GLsizei iHeight);
	virtual System::Void Render(System::Void);
	System::Void SwapOpenGLBuffers(System::Void);

private:
    HDC m_hDC;						// Private GDI Device Contex
    HGLRC m_hglrc;					// Permanent Rendering Context

	Camera*		camera;				// Camera for rendering
	Volume*		volume;

	List<System::IntPtr> actors;	// Render Actors
protected:
    ~Renderer(System::Void);

	GLint CreatePixelFormat(HDC hdc);
};

