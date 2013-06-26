#pragma once
#include "vtkCommand.h"

template <class Class>
class vtkCommandDelegator : public vtkCommand
{
public:
	 static vtkCommandDelegator *New()
		{return new vtkCommandDelegator;};

	 void RegisterCallback(Class* object, void (Class::*callback)(vtkObject*, unsigned long, void*)) {
		 this->object = object;
		 this->callback = callback;
	 }

	 virtual void Execute(vtkObject *caller, unsigned long eid, void *callData) {
		 if (object && callback) {
			 (object->*callback)(caller, eid, callData);
		 }
	 }

private:
	Class* object;
	void (Class::*callback)(vtkObject*, unsigned long, void*);
};