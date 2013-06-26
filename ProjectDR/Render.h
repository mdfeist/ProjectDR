#pragma once
#include <Windows.h>

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "vtkCriticalSection.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h" 
#include "vtkActor.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderer.h" 
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"
#include "vtkCommandDelegator.h"

class Render
{
public:
	Render(void);
	~Render(void);

	void LockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);
	void UnlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);

	void RunInteractorInBackground();
	void InternalRunInteractor();

	void CameraAzimuth(double rot);

	void RunTest();
private:
	vtkRenderer* pRen;
	vtkRenderWindow* pRenWin;
	vtkRenderWindowInteractor* pIRen;

	vtkCamera* pCam;

	vtkCriticalSection* CS;

	vtkCommandDelegator<Render>* pStartInteractionCommand;
	vtkCommandDelegator<Render>* pEndInteractionCommand;
};

