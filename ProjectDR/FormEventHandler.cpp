#include "StdAfx.h"
#include "FormEventHandler.h"

#include "MainFormController.h"
#include "ClientHandler.h"

void FormEventHandler::connectToOptiTrack() {
	MainFormController::getInstance()->getOptiTrackInfo();
	ClientHandler::getInstance()->connect();
}

void FormEventHandler::disconnectFromOptiTrack() {
	ClientHandler::getInstance()->disconnect();
}

void FormEventHandler::optiTrackInitDataView() {
	MainFormController::getInstance()->optiTrackInitDataView();
}

void FormEventHandler::optiTrackUpdateData() {
	MainFormController::getInstance()->optiTrackUpdateData();
}