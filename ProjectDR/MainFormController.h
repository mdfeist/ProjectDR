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
/*
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
*/
public class MainFormController :
	public FormController<MainFormController, ProjectDR::MainForm>
{
public:
	void setOptiTrackInfo();
	void getOptiTrackInfo();

	// Prints to the Output window in the OptiTrack Tab of the MainForm
	void optiTrackOutputLog(std::string msg);
	// List the Rigid Bodies in a grid view
	void optiTrackInitDataView();
	void optiTrackUpdateData();
	// Connect to OptiTrack
	void optiTrackConnect();

	virtual void init() override;
};

