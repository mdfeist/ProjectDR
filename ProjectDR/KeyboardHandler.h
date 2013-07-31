#pragma once
ref class KeyboardHandler
{
public:
	KeyboardHandler(void);
	~KeyboardHandler(void);

	void KeyPress( System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ ex );
	void KeyUp( System::Object^ sender, System::Windows::Forms::KeyEventArgs^ ex );
	void KeyDown( System::Object^ sender, System::Windows::Forms::KeyEventArgs^ ex );

	BOOL IfKeyIsDown(int keyCode);

private:
	array< BOOL >^ keys;
};

