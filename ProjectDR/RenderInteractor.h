#pragma once

#include "Render.h"
#include "vtkCommandDelegator.h"

class vtkWin32RenderWindowInteractor;

class RenderInteractor : public Render
{
public:
	RenderInteractor(void);
	~RenderInteractor(void);

	void lockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);
	void unlockCriticalSection(vtkObject *caller, unsigned long eventID, void *callData);
protected:
	virtual DWORD runThread();
private:
	vtkSmartPointer<vtkCommandDelegator<RenderInteractor>> pStartInteractionCommand;
	vtkSmartPointer<vtkCommandDelegator<RenderInteractor>> pEndInteractionCommand;
};


