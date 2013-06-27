#include "StdAfx.h"
#include "MainFormController.h"

#include "ClientHandler.h"

using namespace System;

MainFormController* FormController<MainFormController, ProjectDR::MainForm>::m_pInstance = NULL;

void MainFormController::optiTrackOutputLogCallback(void* msg) {
	this->form->optiTrackOutputLog(gcnew String((char*)msg));
}

void MainFormController::optiTrackInitDataViewCallback(void*) {
	this->optiTrackInitDataView();
}

void MainFormController::optiTrackUpdateDataCallback(void*) {
	this->optiTrackUpdateData();
}

void MainFormController::setOptiTrackInfo() {
	this->form->setOptiTrackInfo();
}

void MainFormController::getOptiTrackInfo() {
	this->form->getOptiTrackInfo();
}

void MainFormController::optiTrackOutputLog(const std::string msg) {
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

