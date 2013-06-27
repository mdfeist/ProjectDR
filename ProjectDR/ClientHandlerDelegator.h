#pragma once

#include "ClientHandlerCallback.h"

template <class Class>
class ClientHandlerDelegator : public ClientHandlerCallback
{
public:
	ClientHandlerDelegator(void) : ClientHandlerCallback() {
		this->object = NULL;
		this->callback = NULL;
	}

	void RegisterCallback(Class* object, unsigned int callID, void (Class::*callback)(void*)) {
		this->object = object;
		this->callID = callID;
		this->callback = callback;
	}

	virtual void Execute(void *callData) {
		if (object && callback) {
			(object->*callback)(callData);
		}
	}

private:
	Class* object;
	void (Class::*callback)(void*);
};