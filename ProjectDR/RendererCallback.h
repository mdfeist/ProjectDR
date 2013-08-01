#pragma once

class RendererCallback
{
public:
	static int Callback_ID;
	RendererCallback(void) { id = Callback_ID++; }
	int getID() { return id; }
	virtual void Execute(void) {}
private:
	int id;
};
