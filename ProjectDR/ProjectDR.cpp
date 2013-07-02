// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include <Windows.h>

#include "ClientHandler.h"
#include "MainFormController.h"

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkPNGReader.h"
#include "vtkActor.h"
#include "vtkCamera.h"

#include "RenderInteractor.h"

using namespace ProjectDR;
using namespace System::Diagnostics;
using namespace System::IO;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the MainForm using MainFormController
	MainForm^ mainForm = MainFormController::getInstance()->createForm();

	// Create MainForm Callbacks
	ClientHandlerDelegator<MainFormController>* outputLogDelegate = new ClientHandlerDelegator<MainFormController>();
	outputLogDelegate->RegisterCallback(MainFormController::getInstance(), ClientHandlerCallbackID::OUTPUT_LOG, &MainFormController::optiTrackOutputLogCallback);
	ClientHandler::getInstance()->addObserver(outputLogDelegate);

	ClientHandlerDelegator<MainFormController>* initDelegate = new ClientHandlerDelegator<MainFormController>();
	initDelegate->RegisterCallback(MainFormController::getInstance(), ClientHandlerCallbackID::INIT_DATA, &MainFormController::optiTrackInitDataViewCallback);
	ClientHandler::getInstance()->addObserver(initDelegate);

	ClientHandlerDelegator<MainFormController>* updateDelegate = new ClientHandlerDelegator<MainFormController>();
	updateDelegate->RegisterCallback(MainFormController::getInstance(), ClientHandlerCallbackID::UPDATE_DATA, &MainFormController::optiTrackUpdateDataCallback);
	ClientHandler::getInstance()->addObserver(updateDelegate);
	
	// Render Test
	/*
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight( 1.5 );
	cone->SetRadius( 0.5 );
	cone->SetResolution( 10 );
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );
	*/

	vtkSmartPointer<vtkImageData> imageData;
	vtkPNGReader* pngReader = vtkPNGReader::New();
	pngReader->SetFileName("images/CalibrationDot.png");
	pngReader->Update();

	imageData = pngReader->GetOutput();

	vtkImageActor* imgActor = vtkImageActor::New();
	imgActor->SetInputData(imageData);

	if (!File::Exists(L"images/CalibrationDot.png"))
		Debug::WriteLine(L"File not found.");

	Render* render = new Render();
	//RenderInteractor* render = new RenderInteractor();

	double aspect = 1.0;

	for each (Screen^ screen in Screen::AllScreens) {
		if (!screen->Primary) {
			render->setFullScreen(screen);
			aspect = (double)screen->WorkingArea.Width/screen->WorkingArea.Height;
		}
	}

	render->start();
	
	double origin[3];
	double spacing[3];
	int extent[6];
	imageData->GetOrigin( origin );
	imageData->GetSpacing( spacing );
	imageData->GetExtent( extent );

	vtkCamera* camera = render->getCamera();
	camera->ParallelProjectionOn();
 
	double xc = origin[0] + 0.5*(extent[0] + extent[1])*spacing[0];
	double yc = origin[1] + 0.25*(extent[2] + extent[3])*spacing[1];
	double xd = (extent[1] - extent[0] + 1)*spacing[0];
	double yd = (extent[3] - extent[2] + 1)*spacing[1];
	double d = camera->GetDistance();

	camera->SetParallelScale(0.5*yd);
	camera->SetFocalPoint(xc, yc, 0.0);
	camera->SetPosition(xc, yc, d);

	render->setBackground( 0.0, 0.0, 0.0 );
	render->addActor( imgActor );

	// Create the main window and run it
	Application::Run(mainForm);
	return 0;
}
