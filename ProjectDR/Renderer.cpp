#include "StdAfx.h"
#include "Renderer.h"

#include <math.h>
#include <iostream>

#pragma unmanaged
#include "VolumeLoader.h"
#include "Volume.h"
#pragma managed

extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

Renderer::Renderer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight)
{
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

	if ( glewInit() != GLEW_OK )						// Init GLEW
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
		return;
	}

	if ( !glewIsSupported("GL_VERSION_1_5") && !glewIsSupported( "GL_ARB_vertex_buffer_object" ) )
	{
		std::cout << "ARB_vertex_buffer_object not supported!" << std::endl;
		return;
	}

	glewGetExtension("glMultiTexCoord2fvARB");  
	if(glewGetExtension("GL_EXT_framebuffer_object") ) std::cout << "GL_EXT_framebuffer_object support " << std::endl;
	if(glewGetExtension("GL_EXT_renderbuffer_object")) std::cout << "GL_EXT_renderbuffer_object support " << std::endl;
	if(glewGetExtension("GL_ARB_vertex_buffer_object")) std::cout << "GL_ARB_vertex_buffer_object support" << std::endl;
	if(GL_ARB_multitexture) std::cout << "GL_ARB_multitexture support \n" << std::endl;
	
	if (glewGetExtension("GL_ARB_fragment_shader")      != GL_TRUE ||
		glewGetExtension("GL_ARB_vertex_shader")        != GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects")       != GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE)
	{
		 std::cout << "Driver does not support OpenGL Shading Language" << std::endl;
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

	char volumeFile[] = "C:/Users/mdfeist/Desktop/ANGIO.raw";
	VolumeLoader* volumeLoader = new VolumeLoader();
	//volumeLoader->loadVolume(volumeFile);
	volumeLoader->loadRaw(volumeFile);

	volume = new Volume();
	volume->setAxisAngle(-M_PI/2.0, 1.f, 0.f, 0.f);
	volume->setVolumeData(volumeLoader);
	volume->setup();
	volume->init();
}

Renderer::~Renderer(System::Void)
{
	this->DestroyHandle();
}

System::Void Renderer::addActor(Actor* a) {						// Add actor to scene
	System::Object ^o = gcnew System::IntPtr(a);				// a is boxed in o
	System::IntPtr i = safe_cast<System::IntPtr>(o);			// Unbox the IntPtr
	actors.Add(i);
	//actors.push_back(a);										// Push actor into actors vector
}

Camera* Renderer::getActiveCamera() {
	return camera;
}

System::Void Renderer::Resize(GLsizei iWidth, GLsizei iHeight)
{
	camera->setWidth(iWidth);
	camera->setHeight(iHeight);

	glViewport(0, 0, iWidth, iHeight);		// Set Viewport
	double aspect_ratio = (double)iWidth /(double) iHeight;
	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, aspect_ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();						// Reset The Modelview Matrix
}

GLint Renderer::CreatePixelFormat(HDC hdc) 
{
	PIXELFORMATDESCRIPTOR pfd = { 
            sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
            1,                                // version number 
            PFD_DRAW_TO_WINDOW |              // support window 
            PFD_SUPPORT_OPENGL |              // support OpenGL 
            PFD_DOUBLEBUFFER,                 // double buffered 
            PFD_TYPE_RGBA,                    // RGBA type 
            24,                               // 24-bit color depth 
            0, 0, 0, 0, 0, 0,                 // color bits ignored 
            0,                                // no alpha buffer 
            0,                                // shift bit ignored 
            0,                                // no accumulation buffer 
            0, 0, 0, 0,                       // accum bits ignored 
            32,                               // 32-bit z-buffer     
            0,                                // no stencil buffer 
            0,                                // no auxiliary buffer 
            PFD_MAIN_PLANE,                   // main layer 
            0,                                // reserved 
            0, 0, 0                           // layer masks ignored 
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

System::Void Renderer::Render(System::Void)
{
    // Clear the color and depth buffers.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();												// Load Identity
	glTranslatef(0, 0, -2.25);										// Set Camera Position
	glRotatef(25, 1, 0, 0);

	volume->render(camera);											// Render actor
}
