#pragma once
#include <windows.h>
#include "OpenGL.h"

class Camera;
class RenderManager;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace System::Threading;

public ref class Renderer : 
      public System::Windows::Forms::NativeWindow
{
public:
	Renderer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight);

	Camera* getActiveCamera();
	RenderManager* getManager();

	System::Void Resize(GLsizei iWidth, GLsizei iHeight);

	property bool Running {
		bool get() { return _running; }
		void set(bool value) { _running = value; }
	}

	property bool Active {
		bool get() { return _active; }
		void set(bool value) { _active = value; }
	}

	property bool Ready {
		bool get() { return _glReady; }
		void set(bool value) { _glReady = value; }
	}

	bool IsThreadDone();

private:
    HDC								m_hDC;		// Private GDI Device Contex
    HGLRC							m_hglrc;	// Permanent Rendering Context

	Camera*							camera;		// Camera for rendering
	RenderManager*					manager;	// Handles all the OpenGL rendering

	GLsizei							width;
	GLsizei							height;
	bool							needsResize;

	bool							_running;
	bool							_active;
	bool							_glReady;

	System::Threading::Thread^		glThread;
	
	System::Void InitGL(System::Void);
	System::Void RunLoop(System::Void);
	System::Void Update(System::Void);
	System::Void Render(System::Void);
	System::Void SwapOpenGLBuffers(System::Void);
	System::Void GetFrame(System::Void);
protected:
    ~Renderer(System::Void);

	GLint CreatePixelFormat(HDC hdc);
};

