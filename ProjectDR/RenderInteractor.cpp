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

RenderInteractor::RenderInteractor(void) : Render()
{
}


RenderInteractor::~RenderInteractor(void)
{
}

void RenderInteractor::lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
	CS->Lock();
}

void RenderInteractor::unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
	CS->Unlock();
}

DWORD RenderInteractor::runThread() {
	initRenderer();

	vtkInteractorStyleTrackballCamera *style =
		vtkInteractorStyleTrackballCamera::New();
	pIRen->SetInteractorStyle(style);

	pStartInteractionCommand = vtkCommandDelegator<RenderInteractor>::New();
	pStartInteractionCommand->RegisterCallback(this, &RenderInteractor::lockCriticalSection);
	pEndInteractionCommand = vtkCommandDelegator<RenderInteractor>::New();
	pEndInteractionCommand->RegisterCallback(this, &RenderInteractor::unlockCriticalSection);
	style->AddObserver(vtkCommand::StartInteractionEvent,pStartInteractionCommand);
	style->AddObserver(vtkCommand::EndInteractionEvent, pEndInteractionCommand);

	renderWin->Show();

	initialized = true;

	render();

	return 0;
}
