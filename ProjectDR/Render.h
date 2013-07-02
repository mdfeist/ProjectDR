#pragma once
#include <Windows.h>
#include <msclr\auto_gcroot.h>

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "Thread.h"
#include "RenderWindow.h"

#include "vtkObject.h"
#include "vtkSmartPointer.h"
#include "vtkCommandDelegator.h"

class vtkCriticalSection;
class vtkProp;
class vtkCamera;
class vtkWin32OpenGLRenderWindow;
class vtkWin32RenderWindowInteractor;
class vtkRenderer;
class vtkInteractorStyle;

using namespace System::Windows::Forms;

class Render : public Thread
{
public:
	Render(void);
	~Render(void);

	void lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);
	void unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);

	void setBackground(float r, float g, float b);
	void addActor(vtkProp* p);

	void setFullScreen(Screen^ screen);
	vtkCamera* getCamera();
	
	void start();

	bool lock();
	void unlock();
protected:
	virtual DWORD runThread();
	virtual void startRender();

	void initRenderer();
	void waitForInit();

	HANDLE g_hMutex;

	HWND windowID;

	vtkSmartPointer<vtkCamera> pCam;

	vtkSmartPointer<vtkRenderer> pRen;
	vtkSmartPointer<vtkWin32OpenGLRenderWindow> pRenWin;
	vtkSmartPointer<vtkWin32RenderWindowInteractor> pIRen;
	msclr::auto_gcroot<ProjectDR::RenderWindow^> renderWin;

	bool initialized;

	msclr::auto_gcroot<Screen^> screen;

	vtkSmartPointer<vtkInteractorStyle> style;
	vtkSmartPointer<vtkCommandDelegator<Render>> pStartInteractionCommand;
	vtkSmartPointer<vtkCommandDelegator<Render>> pEndInteractionCommand;
};



