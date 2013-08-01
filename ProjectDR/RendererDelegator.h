#pragma once

#include "RendererCallback.h"

template <class Class>
class RendererDelegator : public RendererCallback
{
public:
	RendererDelegator(void) : RendererCallback() {
		this->object = NULL;
		this->callback = NULL;
	}

	void RegisterCallback(Class* object, void (Class::*callback)(void)) {
		this->object = object;
		this->callback = callback;
	}

	virtual void Execute() {
		if (object && callback) {
			(object->*callback)();
		}
	}

private:
	Class* object;
	void (Class::*callback)(void);
};
