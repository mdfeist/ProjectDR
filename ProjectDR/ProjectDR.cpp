// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include <Windows.h>

#include "ClientHandler.h"
#include "MainFormController.h"

#include "RenderWindow.h"

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h" 

#include "Render.h"

#pragma comment(lib, "user32.lib")

using namespace System::Drawing;
using namespace System::Windows::Forms;

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

	RenderWindow^ renderWin = gcnew RenderWindow();
	renderWin->Show();
	
	// Render Test
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight( 3.0 );
	cone->SetRadius( 1.0 );
	cone->SetResolution( 10 );
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );

	Render* render = new Render();
	render->addActor( coneActor );
	render->setWindow(renderWin->GetWindowID());
	render->setBackground( 0.0, 0.0, 0.0 );

	for each (Screen^ screen in Screen::AllScreens) {
		if (!screen->Primary) {
			System::Drawing::Rectangle rect = screen->WorkingArea;
			render->setWindowSize(rect.X, rect.Y, rect.Width, rect.Height);
		}
	}

	render->runTest();

	// Create the main window and run it
	Application::Run(mainForm);
	return 0;
}
