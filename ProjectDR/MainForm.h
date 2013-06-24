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
	private: System::Windows::Forms::SplitContainer^  optiTrackMainSplitContainer;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::SplitContainer^  optiTrackSubSplitContainer;

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
			this->optiTrackMainSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->optiTrackSubSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->optiTrackPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackMainSplitContainer))->BeginInit();
			this->optiTrackMainSplitContainer->Panel1->SuspendLayout();
			this->optiTrackMainSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackSubSplitContainer))->BeginInit();
			this->optiTrackSubSplitContainer->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip->GripMargin = System::Windows::Forms::Padding(0);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->projectDRToolStripMenuItem});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(800, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// projectDRToolStripMenuItem
			// 
			this->projectDRToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			this->projectDRToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->projectDRToolStripMenuItem->ForeColor = System::Drawing::SystemColors::MenuText;
			this->projectDRToolStripMenuItem->Name = L"projectDRToolStripMenuItem";
			this->projectDRToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->projectDRToolStripMenuItem->Text = L"ProjectDR";
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->optiTrackPage);
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl->HotTrack = true;
			this->tabControl->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->tabControl->ItemSize = System::Drawing::Size(80, 20);
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Margin = System::Windows::Forms::Padding(0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->Padding = System::Drawing::Point(0, 0);
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(800, 576);
			this->tabControl->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl->TabIndex = 2;
			// 
			// optiTrackPage
			// 
			this->optiTrackPage->BackColor = System::Drawing::Color::Gainsboro;
			this->optiTrackPage->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->optiTrackPage->Controls->Add(this->optiTrackMainSplitContainer);
			this->optiTrackPage->Location = System::Drawing::Point(4, 24);
			this->optiTrackPage->Margin = System::Windows::Forms::Padding(0);
			this->optiTrackPage->Name = L"optiTrackPage";
			this->optiTrackPage->Size = System::Drawing::Size(792, 548);
			this->optiTrackPage->TabIndex = 0;
			this->optiTrackPage->Text = L"OptiTrack";
			// 
			// optiTrackMainSplitContainer
			// 
			this->optiTrackMainSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->optiTrackMainSplitContainer->Location = System::Drawing::Point(0, 0);
			this->optiTrackMainSplitContainer->Name = L"optiTrackMainSplitContainer";
			// 
			// optiTrackMainSplitContainer.Panel1
			// 
			this->optiTrackMainSplitContainer->Panel1->BackColor = System::Drawing::Color::Gainsboro;
			this->optiTrackMainSplitContainer->Panel1->Controls->Add(this->optiTrackSubSplitContainer);
			// 
			// optiTrackMainSplitContainer.Panel2
			// 
			this->optiTrackMainSplitContainer->Panel2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->optiTrackMainSplitContainer->Panel2MinSize = 273;
			this->optiTrackMainSplitContainer->Size = System::Drawing::Size(792, 548);
			this->optiTrackMainSplitContainer->SplitterDistance = 502;
			this->optiTrackMainSplitContainer->TabIndex = 0;
			// 
			// optiTrackSubSplitContainer
			// 
			this->optiTrackSubSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->optiTrackSubSplitContainer->Location = System::Drawing::Point(0, 0);
			this->optiTrackSubSplitContainer->Name = L"optiTrackSubSplitContainer";
			this->optiTrackSubSplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// optiTrackSubSplitContainer.Panel1
			// 
			this->optiTrackSubSplitContainer->Panel1->BackColor = System::Drawing::Color::White;
			// 
			// optiTrackSubSplitContainer.Panel2
			// 
			this->optiTrackSubSplitContainer->Panel2->BackColor = System::Drawing::Color::White;
			this->optiTrackSubSplitContainer->Panel2MinSize = 100;
			this->optiTrackSubSplitContainer->Size = System::Drawing::Size(502, 548);
			this->optiTrackSubSplitContainer->SplitterDistance = 411;
			this->optiTrackSubSplitContainer->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage1->Location = System::Drawing::Point(4, 24);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(792, 548);
			this->tabPage1->TabIndex = 1;
			this->tabPage1->Text = L"tabPage1";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::Window;
			this->MainMenuStrip = this->menuStrip;
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MainForm";
			this->Text = L"ProjectDR";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->optiTrackPage->ResumeLayout(false);
			this->optiTrackMainSplitContainer->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackMainSplitContainer))->EndInit();
			this->optiTrackMainSplitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackSubSplitContainer))->EndInit();
			this->optiTrackSubSplitContainer->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
			 
		 }
};
}

