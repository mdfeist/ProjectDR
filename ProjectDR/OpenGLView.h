#pragma once

#include "Renderer.h"

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
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OpenGLView::OpenGLView_Paint);
			this->Resize += gcnew System::EventHandler(this, &OpenGLView::OpenGLView_Resize);
			this->ResumeLayout(false);
		}
#pragma endregion
	private: System::Void OpenGLView_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 UNREFERENCED_PARAMETER(sender);
				 UNREFERENCED_PARAMETER(e);
				 renderer->Render();
				 renderer->SwapOpenGLBuffers();
			 }

	private: System::Void OpenGLView_Resize(System::Object^  sender, System::EventArgs^  e) {
				 UNREFERENCED_PARAMETER(sender);
				 UNREFERENCED_PARAMETER(e);
				 renderer->Resize(this->Size.Width, this->Size.Height);
				 MoveWindow((HWND)renderer->Handle.ToPointer(), 0, 0, this->Size.Width, this->Size.Height, true);
				 Invalidate();
				 Refresh();
			 }

	public: Renderer^ GetRenderer() {
				return renderer;
			}
	};
}
