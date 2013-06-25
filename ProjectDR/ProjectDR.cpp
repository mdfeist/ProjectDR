// ProjectDR.cpp : main project file.

#include "stdafx.h"
#include "MainFormController.h"

using namespace ProjectDR;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the MainForm using MainFormController
	MainForm^ mainForm = MainFormController::getInstance()->createForm();

	MainFormController::getInstance()->createCallbacks();

	// Create the main window and run it
	Application::Run(mainForm);
	return 0;
}
