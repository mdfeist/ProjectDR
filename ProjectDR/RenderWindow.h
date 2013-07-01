#pragma once
#include <Windows.h>

#include "vtkWin32OpenGLRenderWindow.h"

namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RenderWindow
	/// </summary>
	public ref class RenderWindow : public System::Windows::Forms::Form
	{
	public:
		RenderWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RenderWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// RenderWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"RenderWindow";
			this->Text = L"RenderWindow";
			this->SizeChanged += gcnew System::EventHandler(this, &RenderWindow::ResizeEnd);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: vtkWin32OpenGLRenderWindow* pRenWin;
	private: delegate void SetDelegate();
	public: System::Void FullScreen() {
				if (this->InvokeRequired) {
						SetDelegate^ d = gcnew SetDelegate(this, &ProjectDR::RenderWindow::FullScreen);
						BeginInvoke(d, nullptr);
				} else {
					this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				}
			}

	public: System::Void attachWindow(vtkWin32OpenGLRenderWindow* win) {
				pRenWin = win;
			}

	private: System::Void ResizeEnd(System::Object^ sender, System::EventArgs^ e) {
				 if (pRenWin) {
					 Control^ control = (Control^)sender;
					 pRenWin->SetSize( control->Size.Width, control->Size.Height );
				 }
			 }
	public: HWND GetWindowID() {
				 return (HWND)this->Handle.ToPointer();
			 }
	};
}

