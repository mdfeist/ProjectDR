#include "StdAfx.h"
#include "MainFormController.h"

#include "ClientHandler.h"

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

void MainFormController::setOptiTrackInfo() {

	char buf[128];
	// Local Ip Address
	ClientHandler::getInstance()->getLocalIpAddress(buf);
	this->form->setOptiTrackLocalIpAddressTextBox( gcnew String(buf) );

	// Server Ip Address
	ClientHandler::getInstance()->getOptiTrackServerIpAddress(buf);
	this->form->setOptiTrackSeverIpAddressTextBox( gcnew String(buf) );

	// Command Port
	String ^cmdPort = Convert::ToString(ClientHandler::getInstance()->getOptiTrackServerCommandPort());
	this->form->setOptiTrackCmdPortTextBox( cmdPort );

	// Data Port
	String ^dataPort = Convert::ToString(ClientHandler::getInstance()->getOptiTrackServerDataPort());
	this->form->setOptiTrackDataPortTextBox( dataPort );

	// Connection Type
	if (ClientHandler::getInstance()->getOptiTrackServerConnectionType() == ConnectionType_Multicast)
		this->form->setOptiTrackConnectionTypeComboBox( "Multicast" );
	else if (ClientHandler::getInstance()->getOptiTrackServerConnectionType() == ConnectionType_Unicast)
		this->form->setOptiTrackConnectionTypeComboBox( "Unicast" );
}

void MainFormController::getOptiTrackInfo() {
	msclr::interop::marshal_context context;

	// Local Ip Address
	String^ localIP = this->form->getOptiTrackLocalIpAddressTextBox();
	ClientHandler::getInstance()->setLocalIpAddress( context.marshal_as<std::string>(localIP).c_str() );

	// Server Ip Address
	String^ serverIP = this->form->getOptiTrackSeverIpAddressTextBox();
	ClientHandler::getInstance()->setOptiTrackServerIpAddress( context.marshal_as<std::string>(serverIP).c_str() );

	// Command Port
	String^ commandPort = this->form->getOptiTrackCmdPortTextBox();
	ClientHandler::getInstance()->setOptiTrackServerCommandPort(System::Int32::Parse(commandPort));

	// Data Port
	String^ dataPort = this->form->getOptiTrackDataPortTextBox();
	ClientHandler::getInstance()->setOptiTrackServerDataPort(System::Int32::Parse(dataPort));

	// Connection Type
	String^ connectionType = this->form->getOptiTrackConnectionTypeComboBox();
	if (!String::Compare(connectionType, "Multicast"))
		ClientHandler::getInstance()->setOptiTrackServerConnectionType(ConnectionType_Multicast);
	else if (!String::Compare(connectionType, "Unicast"))
		ClientHandler::getInstance()->setOptiTrackServerConnectionType(ConnectionType_Unicast);
}

void MainFormController::optiTrackOutputLog(std::string msg) {
	this->form->optiTrackOutputLog(gcnew String(msg.c_str()));
}

void MainFormController::optiTrackInitDataView() {
	this->form->optiTrackInitDataView();
}

void MainFormController::optiTrackUpdateData() {
	this->form->optiTrackUpdateData(); 
}

void MainFormController::optiTrackConnect() {
	this->getOptiTrackInfo();
	ClientHandler::getInstance()->connect();
}

