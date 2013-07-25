#include "StdAfx.h"
#include "Renderer.h"

#include <math.h>
#include <iostream>

#pragma unmanaged
#include "Camera.h"
#include "RenderManager.h"
#pragma managed

extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

Renderer::Renderer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight)
{
	needsResize = false;

	_running = false;
	_active = false;
	_glReady = false;

	CreateParams^ cp = gcnew CreateParams;

	// Set the position on the form
	cp->X = 0;
	cp->Y = 0;
	cp->Width = iWidth;
	cp->Height = iHeight;

	// Specify the form as the parent.
	cp->Parent = parentForm->Handle;

	// Create as a child of the specified parent
	// and make OpenGL compliant (no clipping)
	cp->Style = WS_CHILD | WS_VISIBLE | 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Create the actual window
	this->CreateHandle(cp);

	m_hDC = GetDC((HWND)this->Handle.ToPointer());

	if(m_hDC)
		CreatePixelFormat(m_hDC);

	manager = new RenderManager();
	manager->initGL();

	camera = new Camera();
	camera->setFOV(45.f);

	_active = true;
}

Renderer::~Renderer(System::Void)
{
	_active = false;

	delete camera;
	this->DestroyHandle();
}

Camera* Renderer::getActiveCamera() 
{
	return camera;
}
RenderManager* Renderer::getManager() 
{
	return manager;
}

System::Void Renderer::Resize(GLsizei iWidth, GLsizei iHeight)
{
	if (iHeight <= 0)						// Check if iHeight is less than or equal to zero
		iHeight = 1;						// If true then change iHeight to one to protect against zero divide

	width = iWidth;
	height = iHeight;

	needsResize = true;
}

GLint Renderer::CreatePixelFormat(HDC hdc) 
{
	PIXELFORMATDESCRIPTOR pfd = { 
            sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd 
            1,									// version number 
            PFD_DRAW_TO_WINDOW |				// support window 
            PFD_SUPPORT_OPENGL |				// support OpenGL 
            PFD_DOUBLEBUFFER |					// double buffered 
			PFD_SUPPORT_COMPOSITION,           
            PFD_TYPE_RGBA,						// RGBA type 
            24,									// 24-bit color depth 
            0, 0, 0, 0, 0, 0,					// color bits ignored 
            0,									// no alpha buffer 
            0,									// shift bit ignored 
            0,									// no accumulation buffer 
            0, 0, 0, 0,							// accum bits ignored 
            32,									// 32-bit z-buffer     
            0,									// no stencil buffer 
            0,									// no auxiliary buffer 
            PFD_MAIN_PLANE,						// main layer 
            0,									// reserved 
            0, 0, 0								// layer masks ignored 
        }; 
    
        GLint  iPixelFormat; 
     
        // get the device context's best, available pixel format match 
        if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
        {
            MessageBox::Show("ChoosePixelFormat Failed");
            return 0;
        }
         
        // make that match the device context's current pixel format 
        if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
        {
            MessageBox::Show("SetPixelFormat Failed");
            return 0;
        }
    
        if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
        {
            MessageBox::Show("wglCreateContext Failed");
            return 0;
        }
        
        if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
        {
            MessageBox::Show("wglMakeCurrent Failed");
            return 0;
        }
    
        return 1;
}

System::Void Renderer::SwapOpenGLBuffers(System::Void)
{
    SwapBuffers(m_hDC) ;
}

System::Void Renderer::Update(System::Void)
{
	if (needsResize) {
		camera->setWidth(width);				// Update camera width
		camera->setHeight(height);				// Update camera height

		glViewport(0, 0, width, height);		// Set Viewport
		double aspect_ratio = (double)width / (double) height;
		glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
		glLoadIdentity();						// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective(camera->getFOV(), aspect_ratio, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
		glLoadIdentity();						// Reset The Modelview Matrix
	}

	manager->update();
}

System::Void Renderer::Render(System::Void)
{
	static float angle = 0.f;

    // Clear the color and depth buffers.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();												// Load Identity
	glTranslatef(0, 0, -2.25);										// Set Camera Position
	glRotatef(25, 1, 0, 0);
	glRotatef(angle, 0, 1, 0);

	manager->render(camera);										// Render scene

	angle += 0.1f;
}

System::Void Renderer::GetFrame(System::Void) {
	Update();
	Render();
	SwapOpenGLBuffers();
}
