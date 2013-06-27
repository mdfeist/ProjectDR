#include "StdAfx.h"
#include "Render.h"

Render::Render(void)
{
	pRen = vtkRenderer::New();
	pRenWin = vtkWin32OpenGLRenderWindow::New();
	pRenWin->AddRenderer( pRen );

	CS = vtkCriticalSection::New();
	
	pCam = pRen->GetActiveCamera();
}

Render::~Render(void)
{
}

static DWORD WINAPI threadCallbackFunction(LPVOID lpParameter)
{
      Render *This = static_cast<Render *>(lpParameter);

      // Start the render window interactor in the background
      This->internalRunInteractor();
      return 0;
}


void Render::lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
	CS->Lock();
}

void Render::unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
	CS->Unlock();
}


void Render::runInBackground()
{
      // Start up the thread
      LPSECURITY_ATTRIBUTES attr = NULL;
      SIZE_T stackSize = 0; // default = 1 MB
      DWORD dwCreationFlags = 0;
      LPDWORD noThreadID = NULL;

      HANDLE m_hThreadHandle = CreateThread(attr, stackSize, threadCallbackFunction,
            this, dwCreationFlags, noThreadID);
}

void Render::internalRunInteractor()
{
      // Called in background thread.
      pIRen->Initialize();
      pIRen->Start();
}

void Render::setBackground(float r, float g, float b) {
	pRen->SetBackground( r, g, b );
}

void Render::addActor(vtkActor* actor) {
	pRen->AddActor( actor );
}

void Render::setWindow(HWND handle) {
	this->windowID = handle;
	pRenWin->SetParentId( handle );
}

void Render::setWindowSize(int x, int y, int width, int height) {
	SetWindowPos(this->windowID, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW);
	pRenWin->SetSize( width, height );
}

void Render::runTest()
{	
	pIRen = vtkWin32RenderWindowInteractor::New();
	pIRen->SetRenderWindow(pRenWin);

	vtkInteractorStyleTrackballCamera *style =
		vtkInteractorStyleTrackballCamera::New();
	pIRen->SetInteractorStyle(style);

	pStartInteractionCommand = vtkCommandDelegator<Render>::New();
	pStartInteractionCommand->RegisterCallback(this, &Render::lockCriticalSection);
	pEndInteractionCommand = vtkCommandDelegator<Render>::New();
	pEndInteractionCommand->RegisterCallback(this, &Render::unlockCriticalSection);
	style->AddObserver(vtkCommand::StartInteractionEvent,pStartInteractionCommand);
	style->AddObserver(vtkCommand::EndInteractionEvent, pEndInteractionCommand);
	
	runInBackground();
}