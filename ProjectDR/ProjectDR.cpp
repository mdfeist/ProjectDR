// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include "ClientHandler.h"
#include "MainFormController.h"

#include "Render.h"

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
	Render* render = new Render();
	render->RunTest();

	// Create the main window and run it
	Application::Run(mainForm);
	return 0;
}
