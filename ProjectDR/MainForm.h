#pragma once

namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  projectDRToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  optiTrackPage;

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
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->projectDRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->optiTrackPage = (gcnew System::Windows::Forms::TabPage());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->projectDRToolStripMenuItem});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(784, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// projectDRToolStripMenuItem
			// 
			this->projectDRToolStripMenuItem->Name = L"projectDRToolStripMenuItem";
			this->projectDRToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->projectDRToolStripMenuItem->Text = L"ProjectDR";
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->optiTrackPage);
			this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(784, 538);
			this->tabControl->TabIndex = 2;
			// 
			// optiTrackPage
			// 
			this->optiTrackPage->Location = System::Drawing::Point(4, 22);
			this->optiTrackPage->Name = L"optiTrackPage";
			this->optiTrackPage->Padding = System::Windows::Forms::Padding(3);
			this->optiTrackPage->Size = System::Drawing::Size(776, 512);
			this->optiTrackPage->TabIndex = 0;
			this->optiTrackPage->Text = L"OptiTrack";
			this->optiTrackPage->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->menuStrip;
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MainForm";
			this->Text = L"ProjectDR";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

