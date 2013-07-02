#include "StdAfx.h"
#include "RenderInteractor.h"

#include "vtkCriticalSection.h"
#include "vtkProperty.h" 
#include "vtkActor.h" 
#include "vtkRenderer.h" 
#include "vtkWin32OpenGLRenderWindow.h" 
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"
#include "vtkCommandDelegator.h"

#pragma comment(lib, "user32.lib")

using namespace System::Drawing;

RenderInteractor::RenderInteractor(void) : Render() {
}

RenderInteractor::~RenderInteractor(void) {
}

DWORD RenderInteractor::runThread() {
	style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	initRenderer();

	renderWin->Show();

	initialized = true;

	startRender();

	return 0;
}
