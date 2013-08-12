#include "StdAfx.h"
#include "Renderer.h"

#include <math.h>
#include <iostream>

#include <MMSystem.h>

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

	System::Threading::ThreadStart^ threadDelegate = 
		gcnew System::Threading::ThreadStart(this, &Renderer::InitGL);
	glThread = gcnew System::Threading::Thread(threadDelegate);
	glThread->Start();

	while(!_glReady)
		Sleep(500);
}

Renderer::~Renderer(System::Void)
{
	_active = false;
	_running = false;

	delete camera;
	delete manager;
	this->DestroyHandle();
}

System::Void Renderer::InitGL(System::Void)
{
	if(m_hDC)
		CreatePixelFormat(m_hDC);

	manager = new RenderManager();

	if ( glewInit() != GLEW_OK )						// Init GLEW
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
		return;
	}

	if ( !glewIsSupported("GL_VERSION_1_5") && !glewIsSupported( "GL_ARB_vertex_buffer_object" ) )
	{
		std::cout << "- ARB_vertex_buffer_object not supported" << std::endl;
		return;
	}

	glewGetExtension("glMultiTexCoord2fvARB");  
	if(glewGetExtension("GL_EXT_framebuffer_object") ) std::cout << "- GL_EXT_framebuffer_object support " << std::endl;
	if(glewGetExtension("GL_EXT_renderbuffer_object")) std::cout << "- GL_EXT_renderbuffer_object support " << std::endl;
	if(glewGetExtension("GL_ARB_vertex_buffer_object")) std::cout << "- GL_ARB_vertex_buffer_object support" << std::endl;
	if(GL_ARB_multitexture) std::cout << "- GL_ARB_multitexture support " << std::endl;
	
	if (glewGetExtension("GL_ARB_fragment_shader")      != GL_TRUE ||
		glewGetExtension("GL_ARB_vertex_shader")        != GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects")       != GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE)
	{
		 std::cout << "- Driver does not support OpenGL Shading Language" << std::endl;
	}

	glEnable (GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.f, 0.f, 0.f, 0.f);					// Set Background Color
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glDisable(GL_LIGHTING);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	camera = new Camera();
	camera->setFOV(45.f);

	_active = true;
	_running = true;

	_glReady = true;

	RunLoop();
}

System::Void Renderer::RunLoop(System::Void)
{
	float fps = (1000.f/60.f);
	float dwStartTime = 0.f;
	float dwEndUpdateTime = 0.f;
	float dwElapsedTime = 0.f;

	while (_running) {
		// Get Start Time
		dwStartTime = timeGetTime();

		if (_active) {
			// Draw scene
			GetFrame();
		}

		// Get End Time
		dwEndUpdateTime = timeGetTime();

		// Calculate time Elapsed time
		dwElapsedTime = dwEndUpdateTime - dwStartTime;

		float delay = fps - dwElapsedTime;

		if (delay > 0.f)
			Sleep(delay);
	}
}

bool Renderer::IsThreadDone()
{
	return !glThread->IsAlive;
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
		glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
		glLoadIdentity();						// Reset The Projection Matrix
		
		if (camera->shouldUseIntrinsicMatrix()) {
			//glOrtho(0, 0, width, height, 0.1f, 100.0f);
			glLoadMatrixf((const GLfloat*)camera->getIntrinsicMatrixData());
		} else {
			double aspect_ratio =					// Calculate The Aspect Ratio Of The Window
				(double)width / (double) height;
			gluPerspective(camera->getFOV(), aspect_ratio, 0.1f, 100.0f);
		}

		glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
		glLoadIdentity();						// Reset The Modelview Matrix
	}

	manager->update();
}

System::Void Renderer::Render(System::Void)
{
    // Clear the color and depth buffers.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();												// Load Identity
	gluLookAt(														// look from camera XYZ
		camera->getPosition().x(), 
		camera->getPosition().y(),
		camera->getPosition().z(),
		0, 0, 0,													// look at the origin
		0, 1, 0);													// positive Y up vector
	
	manager->render(camera);										// Render scene
}

System::Void Renderer::GetFrame(System::Void) {
	Update();
	Render();
	SwapOpenGLBuffers();
}
