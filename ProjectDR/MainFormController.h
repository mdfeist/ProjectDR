/**
 * MainFormController.h
 * Created By: Michael Feist
 *
 * This a controller class to help bridge the model/data
 * with the GUI in the MainForm.
 */

#pragma once
#include "stdafx.h"
#include <string>

#include "FormController.h"
#include "MainForm.h"

public class MainFormController :
	public FormController<MainFormController, ProjectDR::MainForm>
{
public:
	void setOptiTrackInfo();
	void getOptiTrackInfo();

	// Callbacks
	void optiTrackOutputLogCallback(void* msg);
	void optiTrackInitDataViewCallback(void*);
	void optiTrackUpdateDataCallback(void*);

	// Prints to the Output window in the OptiTrack Tab of the MainForm
	void optiTrackOutputLog(std::string msg);
	// List the Rigid Bodies in a grid view
	void optiTrackInitDataView();
	void optiTrackUpdateData();
	// Connect to OptiTrack
	void optiTrackConnect();
};

