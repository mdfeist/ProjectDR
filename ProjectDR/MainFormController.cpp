#include "StdAfx.h"
#include "MainFormController.h"

#include "ClientHandler.h"

using namespace System;

MainFormController* FormController<MainFormController, ProjectDR::MainForm>::m_pInstance = NULL;

void OptiTrackOutputLogCallback(const std::string& msg, void* pointer) {
	MainFormController* self = static_cast<MainFormController*>(pointer);
	self->optiTrackOutputLog(msg);
}

void OptiTrackInitDataViewCallback(void* pointer) {
	MainFormController* self = static_cast<MainFormController*>(pointer);
	self->optiTrackInitDataView();
}

void OptiTrackUpdateDatawCallback(void* pointer) {
	MainFormController* self = static_cast<MainFormController*>(pointer);
	self->optiTrackUpdateData();
}

void MainFormController::init(void) {
	if (!this->initialized) {
		createForm();
		ClientHandler::getInstance()->setOutputLogCallback(OptiTrackOutputLogCallback, this);
		ClientHandler::getInstance()->setInitDataCallback(OptiTrackInitDataViewCallback, this);
		ClientHandler::getInstance()->setUpdateDataCallback(OptiTrackUpdateDatawCallback, this);
	}

	FormController::init();
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

