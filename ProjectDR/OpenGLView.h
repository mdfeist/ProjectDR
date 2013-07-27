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
			delete renderer;

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
			this->Load += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OpenGLView::OpenGLView_Paint);
			this->Resize += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		Renderer^ GetRenderer() {
			return renderer;
		}

	private:
		System::Void OpenGLView_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			renderer->Resize(this->Size.Width, this->Size.Height);
			MoveWindow((HWND)renderer->Handle.ToPointer(), 0, 0, this->Size.Width, this->Size.Height, true);
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
	};
}
