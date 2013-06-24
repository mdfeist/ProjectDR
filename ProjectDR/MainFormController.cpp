#include "StdAfx.h"
#include "MainFormController.h"

void MainFormController::showError(std::string& msg) {
	MessageBox::Show(gcnew String(msg.c_str()), "Error", 
    MessageBoxButtons::OK, MessageBoxIcon::Warning);
}

std::string MainFormController::getSpecialFolderMyDocuments() {
	msclr::interop::marshal_context context;
	return context.marshal_as<std::string>(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments));
}

void MainFormController::getFilePath(std::string& pathBuffer) {
	getFilePath(pathBuffer, "");
}

void MainFormController::getFilePath(std::string& pathBuffer, std::string defaultPath) {
	SaveFileDialog^ dialog = gcnew SaveFileDialog;

	dialog->DefaultExt = "xml";
	dialog->Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*";
	dialog->FilterIndex = 2;
	dialog->RestoreDirectory = true;

	if (defaultPath != "") {
		dialog->InitialDirectory = gcnew String(defaultPath.c_str());
	}
	
	if ( dialog->ShowDialog() == ::DialogResult::OK )
	{
		msclr::interop::marshal_context context;
		pathBuffer = context.marshal_as<std::string>(dialog->FileName);
	}
}

bool MainFormController::propt(std::string& title, std::string& msg) {
	if (MessageBox::Show(gcnew String(msg.c_str()), gcnew String(title.c_str()), MessageBoxButtons::YesNo) == DialogResult::Yes) {
		return true;
	} else {
		return false;
	}
}