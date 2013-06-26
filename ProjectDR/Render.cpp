#include "StdAfx.h"
#include "Render.h"

Render::Render(void)
{
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
      fprintf(stderr,"Interactor about to render\n");
}

void Render::UnlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData)
{
      fprintf(stderr,"Interactor done rendering\n");
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
      fprintf(stderr, "About to rotate camera\n");
      pCam->Azimuth(rot);
      pRenWin->Render();
      fprintf(stderr,"Done rotating camera\n");
      CS->Unlock();

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
	pRenWin = vtkRenderWindow::New();
	pRenWin->AddRenderer( pRen );
	pRenWin->SetSize( 300, 300 );

	pIRen = vtkRenderWindowInteractor::New();
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