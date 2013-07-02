#include "StdAfx.h"
#include "Render.h"

#include "vtkCriticalSection.h"
#include "vtkProperty.h" 
#include "vtkProp.h" 
#include "vtkRenderer.h" 
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"
#include "vtkCommandDelegator.h"
#include "vtkCallbackCommand.h"
#include "vtkInteractorObserver.h"
#include "vtkInteractorStyleUser.h"

#pragma comment(lib, "user32.lib")

using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::IO;

Render::Render(void) {
	this->g_hMutex = CreateMutex(
		NULL,
		//(LPSECURITY_ATTRIBUTES)SYNCHRONIZE, 
		FALSE, 
		NULL);

	pCam = NULL;

	initialized = false;
}

Render::~Render(void) {

}

// Lock the render
bool Render::lock() {
	// Request ownership of mutex
	DWORD  dwWaitResult;
	while(true) {
		// Wait for Mutex to be free
		dwWaitResult = WaitForSingleObject(g_hMutex, INFINITE);
		switch (dwWaitResult) {
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0: 
			return true;
			break; 

			// The thread got ownership of an abandoned mutex
			// The database is in an indeterminate state
		case WAIT_ABANDONED: 
			return false; 
			break;
		}
	}

	return false;
}

void Render::unlock() {
	ReleaseMutex(g_hMutex);
}

void Render::lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData) {
	lock();
}

void Render::unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData) {
	unlock();
}

void Render::start() {
	Thread::start();
	waitForInit();
}

void Render::waitForInit() {
	while (!initialized) {
		Sleep(17);
	}
}

void Render::setFullScreen(Screen^ screen) {
	this->screen = screen; 
}

vtkCamera* Render::getCamera() {
	return pCam;
}

void Render::setBackground(float r, float g, float b) {
	lock();
	pRen->SetBackground( r, g, b );
	unlock();
}

void Render::addActor(vtkProp* p) {
	lock();
	pRen->AddActor(p);
	unlock();
}

void Render::startRender() {
	pIRen->Initialize();
	pRenWin->Render();
	pIRen->Start();
}

void Render::initRenderer() {
	renderWin = gcnew ProjectDR::RenderWindow();
	windowID = renderWin->GetWindowID();

	pRen = vtkSmartPointer<vtkRenderer>::New();
	pRenWin = vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
	pRenWin->AddRenderer( pRen );
	pRenWin->SetParentId( windowID );
	renderWin->attachWindow( pRenWin );

	if (screen) {
		renderWin->FullScreen();
		System::Drawing::Rectangle rect = screen->WorkingArea;
		SetWindowPos(windowID, HWND_TOP, rect.X, rect.Y, rect.Width, rect.Height, SWP_SHOWWINDOW);
		pRenWin->SetSize( rect.Width, rect.Height );
	}

	pRen->SetBackground( 0.0, 0.0, 0.0 );
	pCam = pRen->GetActiveCamera();

	pIRen = vtkSmartPointer<vtkWin32RenderWindowInteractor>::New();
	pIRen->SetRenderWindow(pRenWin);

	pStartInteractionCommand = vtkSmartPointer<vtkCommandDelegator<Render>>::New();
	pStartInteractionCommand->RegisterCallback(this, &Render::lockCriticalSection);
	pEndInteractionCommand = vtkSmartPointer<vtkCommandDelegator<Render>>::New();
	pEndInteractionCommand->RegisterCallback(this, &Render::unlockCriticalSection);
	style->AddObserver(vtkCommand::StartInteractionEvent,pStartInteractionCommand);
	style->AddObserver(vtkCommand::EndInteractionEvent, pEndInteractionCommand);

	pRen->AddObserver(vtkCommand::StartEvent, pStartInteractionCommand);
	pRen->AddObserver(vtkCommand::EndEvent, pEndInteractionCommand);

	pIRen->SetInteractorStyle(style);
	pIRen->SetStillUpdateRate(15.0);
}

DWORD Render::runThread() {
	style = vtkSmartPointer<vtkInteractorStyleUser>::New();
	initRenderer();

	renderWin->Show();

	initialized = true;

	startRender();

	return 0;
}