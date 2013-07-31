#include "StdAfx.h"
#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(void)
{
	keys = gcnew array< BOOL >(256);
}

KeyboardHandler::~KeyboardHandler(void)
{
	delete[] keys;
}

void KeyboardHandler::KeyPress( System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ ex )
{
	ex->Handled = true;
}

void KeyboardHandler::KeyUp( System::Object^ sender, System::Windows::Forms::KeyEventArgs^ ex )
{
	keys[ex->KeyValue] = false;
	ex->Handled = true;
}

void KeyboardHandler::KeyDown( System::Object^ sender, System::Windows::Forms::KeyEventArgs^ ex )
{
	keys[ex->KeyValue] = true;
	ex->Handled = true;
}

BOOL KeyboardHandler::IfKeyIsDown(int keyCode)
{
	return keys[keyCode];
}