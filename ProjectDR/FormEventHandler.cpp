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