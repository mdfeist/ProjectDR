#include "StdAfx.h"
#include "Render.h"

Render::Render(void)
{
	pRenWin = vtkWin32OpenGLRenderWindow::New();
	CS = vtkCriticalSection::New();
	pCam = NULL;
}


Render::~Render(void)
{
}

static DWORD WINAPI ThreadCallbackFunction(LPVOID lpParameter)
{
      Render *This = static_cast<Render *>(lpParameter);

      // Start the render window interactor in the background
      This->InternalRunInteractor();
      return 0;
}


void Render::LockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
      CS->Lock();
}

void Render::UnlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
      CS->Unlock();
}


void Render::RunInteractorInBackground()
{
      // Start up the thread
      LPSECURITY_ATTRIBUTES attr = NULL;
      SIZE_T stackSize = 0; // default = 1 MB
      DWORD dwCreationFlags = 0;
      LPDWORD noThreadID = NULL;

      HANDLE m_hThreadHandle = CreateThread(attr, stackSize, ThreadCallbackFunction,
            this, dwCreationFlags, noThreadID);
}

void Render::InternalRunInteractor()
{
      // Called in background thread.
      pIRen->Initialize();
      pIRen->Start();
}

void Render::CameraAzimuth(double rot)
{
      // Rotate camera here. Called by main thread
      CS->Lock();
      pCam->Azimuth(rot);
      pRenWin->Render();
      CS->Unlock();
}

void Render::setWindow(HWND handle) {
	this->windowID = handle;
	pRenWin->SetParentId( handle );
}

void Render::setWindowSize(int x, int y, int width, int height) {
	SetWindowPos(this->windowID, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW);
	pRenWin->SetSize( width, height );
}

void Render::RunTest()
{
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight( 3.0 );
	cone->SetRadius( 1.0 );
	cone->SetResolution( 10 );
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	pRen = vtkRenderer::New();
	pRen->AddActor( coneActor );
	pRen->SetBackground( 0.1, 0.2, 0.4 );
	
	pRenWin->AddRenderer( pRen );
	
	pIRen = vtkWin32RenderWindowInteractor::New();
	pIRen->SetRenderWindow(pRenWin);

	vtkInteractorStyleTrackballCamera *style =
		vtkInteractorStyleTrackballCamera::New();
	pIRen->SetInteractorStyle(style);

	pCam = pRen->GetActiveCamera();

	pStartInteractionCommand = vtkCommandDelegator<Render>::New();
	pStartInteractionCommand->RegisterCallback(this, &Render::LockCriticalSection);
	pEndInteractionCommand = vtkCommandDelegator<Render>::New();
	pEndInteractionCommand->RegisterCallback(this, &Render::UnlockCriticalSection);
	style->AddObserver(vtkCommand::StartInteractionEvent,pStartInteractionCommand);
	style->AddObserver(vtkCommand::EndInteractionEvent, pEndInteractionCommand);

	RunInteractorInBackground();
}