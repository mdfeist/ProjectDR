// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include <Windows.h>

#pragma unmanaged
#include "ClientHandler.h"
#pragma managed

#include "MainFormController.h"

#include "OpenGLView.h"

using namespace ProjectDR;
using namespace System::Diagnostics;
using namespace System::IO;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	FILE *stream;
	BOOL f = AllocConsole();
	freopen_s(&stream, "CONIN$", "r", stdin);
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);

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
	//OpenGLView^ glView = gcnew OpenGLView();
	//glView->Show();

	// Create the main window and run it
	Application::Run(mainForm);

	return 0;
}
