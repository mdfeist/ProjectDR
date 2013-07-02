#pragma once
namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CameraCalibrationForm
	/// </summary>
	public ref class CameraCalibrationForm : public System::Windows::Forms::Form
	{
	public:
		CameraCalibrationForm(void)
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
		~CameraCalibrationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::Button^  cancelBtn;
	private: System::Windows::Forms::Button^  nextBtn;
	private: System::Windows::Forms::Button^  backBtn;
	private: System::Windows::Forms::TabPage^  calculatingPage;
	private: System::Windows::Forms::TextBox^  calibrationOutputLogLabel;
	private: System::Windows::Forms::TabPage^  calibrationPage;



	private: System::Windows::Forms::TabPage^  screenSelectPage;
	private: System::Windows::Forms::Label^  monitorSelectedLabel;

	private: System::Windows::Forms::Button^  selectAsMonitorBtn;
	private: System::Windows::Forms::Label^  monitorSelectLabel;
	private: System::Windows::Forms::ListView^  monitorListView;


	private: System::Windows::Forms::TabPage^  introPage;
	private: System::Windows::Forms::Label^  eyeCalibrationInstructionsLabel;
	private: System::Windows::Forms::Label^  introTitleLabel;
	private: System::Windows::Forms::TabControl^  wizardPagesTemp;
	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CameraCalibrationForm::typeid));
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->cancelBtn = (gcnew System::Windows::Forms::Button());
			this->nextBtn = (gcnew System::Windows::Forms::Button());
			this->backBtn = (gcnew System::Windows::Forms::Button());
			this->calculatingPage = (gcnew System::Windows::Forms::TabPage());
			this->calibrationOutputLogLabel = (gcnew System::Windows::Forms::TextBox());
			this->calibrationPage = (gcnew System::Windows::Forms::TabPage());
			this->screenSelectPage = (gcnew System::Windows::Forms::TabPage());
			this->monitorSelectedLabel = (gcnew System::Windows::Forms::Label());
			this->selectAsMonitorBtn = (gcnew System::Windows::Forms::Button());
			this->monitorSelectLabel = (gcnew System::Windows::Forms::Label());
			this->monitorListView = (gcnew System::Windows::Forms::ListView());
			this->introPage = (gcnew System::Windows::Forms::TabPage());
			this->eyeCalibrationInstructionsLabel = (gcnew System::Windows::Forms::Label());
			this->introTitleLabel = (gcnew System::Windows::Forms::Label());
			this->wizardPagesTemp = (gcnew System::Windows::Forms::TabControl());
			this->calculatingPage->SuspendLayout();
			this->screenSelectPage->SuspendLayout();
			this->introPage->SuspendLayout();
			this->wizardPagesTemp->SuspendLayout();
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->Location = System::Drawing::Point(0, 0);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(0, 0);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// cancelBtn
			// 
			this->cancelBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelBtn->Location = System::Drawing::Point(448, 329);
			this->cancelBtn->Name = L"cancelBtn";
			this->cancelBtn->Size = System::Drawing::Size(73, 23);
			this->cancelBtn->TabIndex = 6;
			this->cancelBtn->Text = L"Cancel";
			this->cancelBtn->UseVisualStyleBackColor = true;
			// 
			// nextBtn
			// 
			this->nextBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nextBtn->Location = System::Drawing::Point(332, 329);
			this->nextBtn->Name = L"nextBtn";
			this->nextBtn->Size = System::Drawing::Size(73, 23);
			this->nextBtn->TabIndex = 5;
			this->nextBtn->Text = L"Next";
			this->nextBtn->UseVisualStyleBackColor = true;
			// 
			// backBtn
			// 
			this->backBtn->Enabled = false;
			this->backBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->backBtn->Location = System::Drawing::Point(251, 329);
			this->backBtn->Name = L"backBtn";
			this->backBtn->Size = System::Drawing::Size(73, 23);
			this->backBtn->TabIndex = 4;
			this->backBtn->Text = L"Back";
			this->backBtn->UseVisualStyleBackColor = true;
			// 
			// calculatingPage
			// 
			this->calculatingPage->Controls->Add(this->calibrationOutputLogLabel);
			this->calculatingPage->Location = System::Drawing::Point(4, 22);
			this->calculatingPage->Name = L"calculatingPage";
			this->calculatingPage->Padding = System::Windows::Forms::Padding(3);
			this->calculatingPage->Size = System::Drawing::Size(529, 295);
			this->calculatingPage->TabIndex = 4;
			this->calculatingPage->Text = L"Calculating";
			this->calculatingPage->UseVisualStyleBackColor = true;
			// 
			// calibrationOutputLogLabel
			// 
			this->calibrationOutputLogLabel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->calibrationOutputLogLabel->Location = System::Drawing::Point(3, 3);
			this->calibrationOutputLogLabel->Multiline = true;
			this->calibrationOutputLogLabel->Name = L"calibrationOutputLogLabel";
			this->calibrationOutputLogLabel->ReadOnly = true;
			this->calibrationOutputLogLabel->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->calibrationOutputLogLabel->Size = System::Drawing::Size(523, 289);
			this->calibrationOutputLogLabel->TabIndex = 0;
			// 
			// calibrationPage
			// 
			this->calibrationPage->Location = System::Drawing::Point(4, 22);
			this->calibrationPage->Name = L"calibrationPage";
			this->calibrationPage->Padding = System::Windows::Forms::Padding(3);
			this->calibrationPage->Size = System::Drawing::Size(529, 295);
			this->calibrationPage->TabIndex = 3;
			this->calibrationPage->Text = L"Calibration";
			this->calibrationPage->UseVisualStyleBackColor = true;
			// 
			// screenSelectPage
			// 
			this->screenSelectPage->Controls->Add(this->monitorSelectedLabel);
			this->screenSelectPage->Controls->Add(this->selectAsMonitorBtn);
			this->screenSelectPage->Controls->Add(this->monitorSelectLabel);
			this->screenSelectPage->Controls->Add(this->monitorListView);
			this->screenSelectPage->Location = System::Drawing::Point(4, 22);
			this->screenSelectPage->Name = L"screenSelectPage";
			this->screenSelectPage->Padding = System::Windows::Forms::Padding(3);
			this->screenSelectPage->Size = System::Drawing::Size(529, 295);
			this->screenSelectPage->TabIndex = 1;
			this->screenSelectPage->Text = L"Monitor";
			this->screenSelectPage->UseVisualStyleBackColor = true;
			// 
			// monitorSelectedLabel
			// 
			this->monitorSelectedLabel->AutoSize = true;
			this->monitorSelectedLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->monitorSelectedLabel->Location = System::Drawing::Point(266, 248);
			this->monitorSelectedLabel->MaximumSize = System::Drawing::Size(250, 60);
			this->monitorSelectedLabel->Name = L"monitorSelectedLabel";
			this->monitorSelectedLabel->Size = System::Drawing::Size(234, 34);
			this->monitorSelectedLabel->TabIndex = 5;
			this->monitorSelectedLabel->Text = L"No monitor is selected to be the main display.";
			// 
			// selectAsMonitorBtn
			// 
			this->selectAsMonitorBtn->Location = System::Drawing::Point(335, 200);
			this->selectAsMonitorBtn->Name = L"selectAsMonitorBtn";
			this->selectAsMonitorBtn->Size = System::Drawing::Size(109, 23);
			this->selectAsMonitorBtn->TabIndex = 4;
			this->selectAsMonitorBtn->Text = L"Select as Monitor";
			this->selectAsMonitorBtn->UseVisualStyleBackColor = true;
			// 
			// monitorSelectLabel
			// 
			this->monitorSelectLabel->AutoSize = true;
			this->monitorSelectLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->monitorSelectLabel->Location = System::Drawing::Point(265, 3);
			this->monitorSelectLabel->Name = L"monitorSelectLabel";
			this->monitorSelectLabel->Size = System::Drawing::Size(260, 114);
			this->monitorSelectLabel->TabIndex = 3;
			this->monitorSelectLabel->Text = resources->GetString(L"monitorSelectLabel.Text");
			// 
			// monitorListView
			// 
			this->monitorListView->Alignment = System::Windows::Forms::ListViewAlignment::Left;
			this->monitorListView->Dock = System::Windows::Forms::DockStyle::Left;
			this->monitorListView->FullRowSelect = true;
			this->monitorListView->LabelWrap = false;
			this->monitorListView->Location = System::Drawing::Point(3, 3);
			this->monitorListView->MultiSelect = false;
			this->monitorListView->Name = L"monitorListView";
			this->monitorListView->Size = System::Drawing::Size(245, 289);
			this->monitorListView->TabIndex = 2;
			this->monitorListView->TileSize = System::Drawing::Size(100, 20);
			this->monitorListView->UseCompatibleStateImageBehavior = false;
			this->monitorListView->View = System::Windows::Forms::View::SmallIcon;
			// 
			// introPage
			// 
			this->introPage->Controls->Add(this->eyeCalibrationInstructionsLabel);
			this->introPage->Controls->Add(this->introTitleLabel);
			this->introPage->Location = System::Drawing::Point(4, 22);
			this->introPage->Name = L"introPage";
			this->introPage->Padding = System::Windows::Forms::Padding(3);
			this->introPage->Size = System::Drawing::Size(529, 295);
			this->introPage->TabIndex = 0;
			this->introPage->Text = L"Intro";
			this->introPage->UseVisualStyleBackColor = true;
			// 
			// eyeCalibrationInstructionsLabel
			// 
			this->eyeCalibrationInstructionsLabel->AutoSize = true;
			this->eyeCalibrationInstructionsLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->eyeCalibrationInstructionsLabel->Location = System::Drawing::Point(6, 64);
			this->eyeCalibrationInstructionsLabel->MaximumSize = System::Drawing::Size(500, 250);
			this->eyeCalibrationInstructionsLabel->Name = L"eyeCalibrationInstructionsLabel";
			this->eyeCalibrationInstructionsLabel->Size = System::Drawing::Size(479, 152);
			this->eyeCalibrationInstructionsLabel->TabIndex = 4;
			this->eyeCalibrationInstructionsLabel->Text = resources->GetString(L"eyeCalibrationInstructionsLabel.Text");
			// 
			// introTitleLabel
			// 
			this->introTitleLabel->AutoSize = true;
			this->introTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->introTitleLabel->Location = System::Drawing::Point(8, 16);
			this->introTitleLabel->Name = L"introTitleLabel";
			this->introTitleLabel->Size = System::Drawing::Size(275, 30);
			this->introTitleLabel->TabIndex = 0;
			this->introTitleLabel->Text = L"Camera Calibration Wizard";
			// 
			// wizardPagesTemp
			// 
			this->wizardPagesTemp->Controls->Add(this->introPage);
			this->wizardPagesTemp->Controls->Add(this->screenSelectPage);
			this->wizardPagesTemp->Controls->Add(this->calibrationPage);
			this->wizardPagesTemp->Controls->Add(this->calculatingPage);
			this->wizardPagesTemp->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->wizardPagesTemp->Location = System::Drawing::Point(-1, 2);
			this->wizardPagesTemp->Name = L"wizardPagesTemp";
			this->wizardPagesTemp->SelectedIndex = 0;
			this->wizardPagesTemp->Size = System::Drawing::Size(537, 321);
			this->wizardPagesTemp->TabIndex = 7;
			// 
			// CameraCalibrationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(534, 362);
			this->Controls->Add(this->wizardPagesTemp);
			this->Controls->Add(this->cancelBtn);
			this->Controls->Add(this->nextBtn);
			this->Controls->Add(this->backBtn);
			this->Controls->Add(this->listView1);
			this->Name = L"CameraCalibrationForm";
			this->Text = L"CameraCalibrationForm";
			this->Load += gcnew System::EventHandler(this, &CameraCalibrationForm::Form_Load);
			this->calculatingPage->ResumeLayout(false);
			this->calculatingPage->PerformLayout();
			this->screenSelectPage->ResumeLayout(false);
			this->screenSelectPage->PerformLayout();
			this->introPage->ResumeLayout(false);
			this->introPage->PerformLayout();
			this->wizardPagesTemp->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->monitorListView->Items->Clear();

				 for each (Screen^ screen in Screen::AllScreens) {
					 String^ text = Convert::ToString(screen->DeviceName);

					 text += " " + Convert::ToString(screen->WorkingArea.Width) + "x" 
						 + Convert::ToString(screen->WorkingArea.Height);

					 if (screen->Primary)
						 text += " (Primary)";

					 ListViewItem^ listViewItem = gcnew ListViewItem(text); 
					 this->monitorListView->Items->Add(listViewItem);
				 }
			 }
	};
}
