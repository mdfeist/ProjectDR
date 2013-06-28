// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include <Windows.h>

#include "ClientHandler.h"
#include "MainFormController.h"

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h" 

#include "RenderInteractor.h"

using namespace ProjectDR;

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
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight( 1.5 );
	cone->SetRadius( 0.5 );
	cone->SetResolution( 10 );
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	RenderInteractor* render = new RenderInteractor();

	for each (Screen^ screen in Screen::AllScreens) {
		if (!screen->Primary) {
			render->setFullScreen(screen);
		}
	}

	render->start();
	render->waitForInit();
	render->setBackground( 0.0, 0.0, 0.0 );
	render->addActor( coneActor );

	// Create the main window and run it
	Application::Run(mainForm);
	return 0;
}
