#pragma once

namespace ClientHandlerCallbackID {
	enum CallbackID {
		UNKNOWN,
		OUTPUT_LOG,
		INIT_DATA,
		UPDATE_DATA,
	};
}

class ClientHandlerCallback
{
public:
	ClientHandlerCallback(void) { this->callID = ClientHandlerCallbackID::UNKNOWN; }

	unsigned int getCallID() {
		return this->callID;
	}

	virtual void Execute(void *callData) { }
protected:
	unsigned int callID;
};