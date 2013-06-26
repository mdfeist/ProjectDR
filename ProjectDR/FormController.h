/**
 * FormController.h
 * Created By: Michael Feist
 *
 * Generic FormController
 */
#pragma once
#include "stdafx.h"
#include <msclr\auto_gcroot.h>

template<class ControllerType, class FormType>
public class FormController abstract
{
public:
	static ControllerType* getInstance() {
		if(!m_pInstance) {
			m_pInstance = new ControllerType();
			m_pInstance->init();
		}
		return m_pInstance;
	}

	// Creates a form if not already created
	FormType^ createForm() {
		if (!form || form->IsDisposed) {
			form = gcnew FormType();
		}

		return form.get();
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
	FormController() { this->initialized = false; };
	~FormController() {};

	msclr::auto_gcroot<FormType^> form;

	bool initialized;
	virtual void init() { this->initialized = true; };
private:
	static ControllerType* m_pInstance;
};

