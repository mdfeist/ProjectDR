#pragma once

#include "Render.h"

class RenderInteractor : public Render
{
public:
	RenderInteractor(void);
	~RenderInteractor(void);
protected:
	virtual DWORD runThread();
};


