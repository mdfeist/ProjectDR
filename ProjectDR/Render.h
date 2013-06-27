#pragma once
#include <Windows.h>

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "vtkObject.h"
#include "vtkCommandDelegator.h"

class vtkCriticalSection;
class vtkActor;
class vtkCamera;
class vtkWin32OpenGLRenderWindow;
class vtkWin32RenderWindowInteractor;
class vtkRenderer;

class Render
{
public:
	Render(void);
	~Render(void);

	void lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);
	void unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);

	void runInBackground();
	void internalRunInteractor();

	void setBackground(float r, float g, float b);
	void addActor(vtkActor* actor);

	void setWindow(HWND handle);
	void setWindowSize(int x, int y, int width, int height);

	void runTest();
private:
	vtkRenderer* pRen;
	vtkWin32OpenGLRenderWindow* pRenWin;
	vtkWin32RenderWindowInteractor* pIRen;

	vtkCamera* pCam;

	vtkCriticalSection* CS;

	vtkCommandDelegator<Render>* pStartInteractionCommand;
	vtkCommandDelegator<Render>* pEndInteractionCommand;

	HWND windowID;
};

