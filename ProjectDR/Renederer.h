#pragma once
#include <windows.h>
#include <GL/gl.h>    

using namespace System::Windows::Forms;

public ref class Renederer : 
      public System::Windows::Forms::NativeWindow
{
public:
	Renederer(System::Windows::Forms::Form ^ parentForm, 
            GLsizei iWidth, GLsizei iHeight);

	virtual System::Void Render(System::Void);
	System::Void SwapOpenGLBuffers(System::Void);

private:
    HDC m_hDC;
    HGLRC m_hglrc;
protected:
    ~Renederer(System::Void);

	GLint SetPixelFormat(HDC hdc);
};

