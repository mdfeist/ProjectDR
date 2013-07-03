/**
 * CameraCalibrationFormController.h
 * Created By: Michael Feist
 *
 * This a controller class to help bridge the model/data
 * with the GUI in the CameraCalibrationForm.
 */

#pragma once
#include "stdafx.h"
#include <string>

#include "FormController.h"
#include "CameraCalibrationForm.h"

public class CameraCalibrationFormController :
	public FormController<CameraCalibrationFormController, ProjectDR::CameraCalibrationForm>
{
public:
	// Prints to the Output window in the Calculating Window
	void offsetCalibrationOutputLog(std::string msg) {
		if (form && !form->IsDisposed)
			this->form->offsetCalibrationOutputLog(gcnew System::String(msg.c_str()));
	}
};
