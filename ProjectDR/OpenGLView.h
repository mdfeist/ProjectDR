#pragma once

#include "Renderer.h"
#include <iostream>

namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OpenGLView
	/// </summary>
	public ref class OpenGLView : public System::Windows::Forms::Form
	{
	public:
		OpenGLView(void)
		{
			InitializeComponent();
			renderer = gcnew Renderer(this, this->Size.Width, this->Size.Height);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OpenGLView()
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
		Renderer^ renderer;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// OpenGLView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"OpenGLView";
			this->Text = L"OpenGL View";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &OpenGLView::OpenGLView_FormClosing);
			this->Load += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Load);
			this->Shown += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Shown);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OpenGLView::OpenGLView_Paint);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &OpenGLView::OpenGLView_KeyPress);
			this->Resize += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		Renderer^ GetRenderer() {
			return renderer;
		}

	private:
		BOOL fullScreen;
		System::Void OpenGLView_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);

			fullScreen = false;

			if ( renderer == nullptr )
				renderer = gcnew Renderer(this, this->Size.Width, this->Size.Height);

			renderer->Active = true;

			renderer->Resize(this->Size.Width, this->Size.Height);
			MoveWindow((HWND)renderer->Handle.ToPointer(), 0, 0, this->Size.Width, this->Size.Height, true);
		}

		System::Void OpenGLView_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			renderer->Running = false;

			while(!renderer->IsThreadDone())
				Sleep(100);

			delete renderer;
			renderer = nullptr;
		}

		System::Void OpenGLView_Shown(System::Object^  sender, System::EventArgs^  e) {
			renderer->Active = true;
		}

		System::Void OpenGLView_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
		}

		System::Void OpenGLView_Resize(System::Object^  sender, System::EventArgs^  e) {
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			if ( WindowState == FormWindowState::Minimized )
			{
				renderer->Active = false;
			} else {
				renderer->Active = true;
				renderer->Resize(this->Size.Width, this->Size.Height);
				MoveWindow(
					(HWND)renderer->Handle.ToPointer(), 
					0, 
					0, 
					this->Size.Width, 
					this->Size.Height, 
					true);
			}
		}

		System::Void OpenGLView_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			switch (e->KeyChar) {
			case (char)27 :
				{
					fullScreen = false;
					FullScreen(fullScreen);
					renderer->Active = false;
					this->Hide();
					break;
				}
			case 'f' :
				{
					fullScreen = !fullScreen;
					FullScreen(fullScreen);
					break;
				}
			}
		}

		System::Void FullScreen(BOOL Enable)
		{
			fullScreen = Enable;

			this->SuspendLayout();

			if (Enable)
			{
				this->FormBorderStyle = ::FormBorderStyle::None;
				this->WindowState = FormWindowState::Maximized;
			}
			else
			{
				this->FormBorderStyle = ::FormBorderStyle::Sizable;
				this->WindowState = FormWindowState::Normal;
			}

			this->ResumeLayout();
		}
};
}
