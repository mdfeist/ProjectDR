#pragma once
#include <Windows.h>
#include <msclr\auto_gcroot.h>

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "Thread.h"
#include "RenderWindow.h"

#include "vtkObject.h"
#include "vtkSmartPointer.h"

class vtkCriticalSection;
class vtkActor;
class vtkCamera;
class vtkWin32OpenGLRenderWindow;
class vtkWin32RenderWindowInteractor;
class vtkRenderer;

using namespace System::Windows::Forms;

class Render : public Thread
{
public:
	Render(void);
	~Render(void);

	void setBackground(float r, float g, float b);
	void addActor(vtkActor* actor);

	void setFullScreen(Screen^ screen);

	void waitForInit();
protected:
	virtual DWORD runThread();
	virtual void render();

	void initRenderer();

	HWND windowID;

	vtkSmartPointer<vtkCamera> pCam;
	vtkSmartPointer<vtkCriticalSection> CS;

	vtkSmartPointer<vtkRenderer> pRen;
	vtkSmartPointer<vtkWin32OpenGLRenderWindow> pRenWin;
	vtkSmartPointer<vtkWin32RenderWindowInteractor> pIRen;
	msclr::auto_gcroot<ProjectDR::RenderWindow^> renderWin;

	bool initialized;

	msclr::auto_gcroot<Screen^> screen;
};


