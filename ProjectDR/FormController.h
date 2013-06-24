/**
 * FormController.h
 * Created By: Michael Feist
 *
 * Generic FormController
 */
#pragma once
#include "stdafx.h"

using namespace System;

generic<class ControllerType, class FormType> 
where ControllerType : gcnew()
where FormType : System::Windows::Forms::Form, gcnew()
public ref class FormController abstract
{
public:
	static ControllerType getInstance() {
		if(!m_pInstance) {
			m_pInstance = gcnew ControllerType();
		}
		return m_pInstance;
	}

	// Creates a form if not already created
	FormType createForm() {
		if (!form || form->IsDisposed) {
			form = gcnew FormType();
		}

		return form;
	}

	// Create a instance of the Form if 
	// it doesn't already exist and show it
	void Show() { 
		if (!form || form->IsDisposed) {
			 form = gcnew FormType();
		}
		form->Show();
		form->BringToFront();
	}

protected:
	FormController() {};
	~FormController() {};

	FormType form;

private:
	static ControllerType m_pInstance;
};

