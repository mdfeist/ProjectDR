#include "StdAfx.h"
#include "Render.h"

#include "vtkCriticalSection.h"
#include "vtkProperty.h" 
#include "vtkActor.h" 
#include "vtkRenderer.h" 
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"
#include "vtkCommandDelegator.h"
#include "vtkInteractorObserver.h"
#include "vtkInteractorStyleUser.h"

#pragma comment(lib, "user32.lib")

using namespace System::Drawing;

Render::Render(void) {
	CS = vtkSmartPointer<vtkCriticalSection>::New();
	pCam = NULL;

	initialized = false;
}

Render::~Render(void) {

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


void Render::setBackground(float r, float g, float b) {
	CS->Lock();
	pRen->SetBackground( r, g, b );
	CS->Unlock();
}

void Render::addActor(vtkActor* actor) {
	CS->Lock();
	pRen->AddActor(actor);
	CS->Unlock();
}

void Render::render() {
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
}

DWORD Render::runThread() {
	initRenderer();

	vtkSmartPointer<vtkInteractorStyleUser> style =
		vtkSmartPointer<vtkInteractorStyleUser>::New();
	pIRen->SetInteractorStyle(style);

	renderWin->Show();

	initialized = true;

	render();

	return 0;
}
