#pragma once

#include "WizardPages.h"
#include "CameraCalibration.h"

#pragma unmanaged
#include "ClientHandler.h"
#include "RigidBody.h"
#pragma managed

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

	private: System::Windows::Forms::Button^  cancelBtn;
	private: System::Windows::Forms::Button^  nextBtn;
	private: System::Windows::Forms::Button^  backBtn;
	private: System::Windows::Forms::TabPage^  calculatingOffsetPage;
	private: System::Windows::Forms::TextBox^  calibrationOffsetOutputLogLabel;


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
	private: System::Windows::Forms::TabPage^  cameraSelectPage;
	private: System::Windows::Forms::Label^  cameraSelectedLabel;

	private: System::Windows::Forms::Button^  selectAsCameraBtn;
	private: System::Windows::Forms::Label^  cameraSelectLabel;
	private: System::Windows::Forms::ListView^  cameraListView;
	private: System::Windows::Forms::TabPage^  cameraOffsetPage;
	private: System::Windows::Forms::Label^  cameraOffsetLabel;
	private: System::Windows::Forms::PictureBox^  cameraOffsetImage;
	private: System::Windows::Forms::Button^  addOffsetBtn;
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
			this->cancelBtn = (gcnew System::Windows::Forms::Button());
			this->nextBtn = (gcnew System::Windows::Forms::Button());
			this->backBtn = (gcnew System::Windows::Forms::Button());
			this->calculatingOffsetPage = (gcnew System::Windows::Forms::TabPage());
			this->calibrationOffsetOutputLogLabel = (gcnew System::Windows::Forms::TextBox());
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
			this->cameraSelectPage = (gcnew System::Windows::Forms::TabPage());
			this->cameraSelectedLabel = (gcnew System::Windows::Forms::Label());
			this->selectAsCameraBtn = (gcnew System::Windows::Forms::Button());
			this->cameraSelectLabel = (gcnew System::Windows::Forms::Label());
			this->cameraListView = (gcnew System::Windows::Forms::ListView());
			this->cameraOffsetPage = (gcnew System::Windows::Forms::TabPage());
			this->addOffsetBtn = (gcnew System::Windows::Forms::Button());
			this->cameraOffsetLabel = (gcnew System::Windows::Forms::Label());
			this->cameraOffsetImage = (gcnew System::Windows::Forms::PictureBox());
			this->calculatingOffsetPage->SuspendLayout();
			this->screenSelectPage->SuspendLayout();
			this->introPage->SuspendLayout();
			this->wizardPagesTemp->SuspendLayout();
			this->cameraSelectPage->SuspendLayout();
			this->cameraOffsetPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraOffsetImage))->BeginInit();
			this->SuspendLayout();
			// 
			// cancelBtn
			// 
			this->cancelBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->cancelBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelBtn->Location = System::Drawing::Point(448, 329);
			this->cancelBtn->Name = L"cancelBtn";
			this->cancelBtn->Size = System::Drawing::Size(73, 23);
			this->cancelBtn->TabIndex = 6;
			this->cancelBtn->Text = L"Cancel";
			this->cancelBtn->UseVisualStyleBackColor = false;
			this->cancelBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::cancelBtn_Click);
			// 
			// nextBtn
			// 
			this->nextBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->nextBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nextBtn->Location = System::Drawing::Point(332, 329);
			this->nextBtn->Name = L"nextBtn";
			this->nextBtn->Size = System::Drawing::Size(73, 23);
			this->nextBtn->TabIndex = 5;
			this->nextBtn->Text = L"Next";
			this->nextBtn->UseVisualStyleBackColor = false;
			this->nextBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::nextBtn_Click);
			// 
			// backBtn
			// 
			this->backBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->backBtn->Enabled = false;
			this->backBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->backBtn->Location = System::Drawing::Point(251, 329);
			this->backBtn->Name = L"backBtn";
			this->backBtn->Size = System::Drawing::Size(73, 23);
			this->backBtn->TabIndex = 4;
			this->backBtn->Text = L"Back";
			this->backBtn->UseVisualStyleBackColor = false;
			this->backBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::backBtn_Click);
			// 
			// calculatingOffsetPage
			// 
			this->calculatingOffsetPage->Controls->Add(this->calibrationOffsetOutputLogLabel);
			this->calculatingOffsetPage->Location = System::Drawing::Point(4, 22);
			this->calculatingOffsetPage->Name = L"calculatingOffsetPage";
			this->calculatingOffsetPage->Padding = System::Windows::Forms::Padding(3);
			this->calculatingOffsetPage->Size = System::Drawing::Size(529, 295);
			this->calculatingOffsetPage->TabIndex = 4;
			this->calculatingOffsetPage->Text = L"Cal Offset";
			this->calculatingOffsetPage->UseVisualStyleBackColor = true;
			// 
			// calibrationOffsetOutputLogLabel
			// 
			this->calibrationOffsetOutputLogLabel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->calibrationOffsetOutputLogLabel->Location = System::Drawing::Point(3, 3);
			this->calibrationOffsetOutputLogLabel->Multiline = true;
			this->calibrationOffsetOutputLogLabel->Name = L"calibrationOffsetOutputLogLabel";
			this->calibrationOffsetOutputLogLabel->ReadOnly = true;
			this->calibrationOffsetOutputLogLabel->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->calibrationOffsetOutputLogLabel->Size = System::Drawing::Size(523, 289);
			this->calibrationOffsetOutputLogLabel->TabIndex = 0;
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
			this->selectAsMonitorBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->selectAsMonitorBtn->Location = System::Drawing::Point(335, 200);
			this->selectAsMonitorBtn->Name = L"selectAsMonitorBtn";
			this->selectAsMonitorBtn->Size = System::Drawing::Size(109, 23);
			this->selectAsMonitorBtn->TabIndex = 4;
			this->selectAsMonitorBtn->Text = L"Select as Monitor";
			this->selectAsMonitorBtn->UseVisualStyleBackColor = false;
			this->selectAsMonitorBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::selectAsMonitorBtn_Click);
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
			this->eyeCalibrationInstructionsLabel->Location = System::Drawing::Point(3, 41);
			this->eyeCalibrationInstructionsLabel->MaximumSize = System::Drawing::Size(524, 250);
			this->eyeCalibrationInstructionsLabel->Name = L"eyeCalibrationInstructionsLabel";
			this->eyeCalibrationInstructionsLabel->Size = System::Drawing::Size(518, 228);
			this->eyeCalibrationInstructionsLabel->TabIndex = 4;
			this->eyeCalibrationInstructionsLabel->Text = resources->GetString(L"eyeCalibrationInstructionsLabel.Text");
			// 
			// introTitleLabel
			// 
			this->introTitleLabel->AutoSize = true;
			this->introTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->introTitleLabel->Location = System::Drawing::Point(3, 3);
			this->introTitleLabel->Name = L"introTitleLabel";
			this->introTitleLabel->Size = System::Drawing::Size(275, 30);
			this->introTitleLabel->TabIndex = 0;
			this->introTitleLabel->Text = L"Camera Calibration Wizard";
			// 
			// wizardPagesTemp
			// 
			this->wizardPagesTemp->Controls->Add(this->introPage);
			this->wizardPagesTemp->Controls->Add(this->screenSelectPage);
			this->wizardPagesTemp->Controls->Add(this->cameraSelectPage);
			this->wizardPagesTemp->Controls->Add(this->cameraOffsetPage);
			this->wizardPagesTemp->Controls->Add(this->calculatingOffsetPage);
			this->wizardPagesTemp->Controls->Add(this->calibrationPage);
			this->wizardPagesTemp->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->wizardPagesTemp->Location = System::Drawing::Point(0, 0);
			this->wizardPagesTemp->Name = L"wizardPagesTemp";
			this->wizardPagesTemp->SelectedIndex = 0;
			this->wizardPagesTemp->Size = System::Drawing::Size(537, 321);
			this->wizardPagesTemp->TabIndex = 7;
			// 
			// cameraSelectPage
			// 
			this->cameraSelectPage->Controls->Add(this->cameraSelectedLabel);
			this->cameraSelectPage->Controls->Add(this->selectAsCameraBtn);
			this->cameraSelectPage->Controls->Add(this->cameraSelectLabel);
			this->cameraSelectPage->Controls->Add(this->cameraListView);
			this->cameraSelectPage->Location = System::Drawing::Point(4, 22);
			this->cameraSelectPage->Name = L"cameraSelectPage";
			this->cameraSelectPage->Padding = System::Windows::Forms::Padding(3);
			this->cameraSelectPage->Size = System::Drawing::Size(529, 295);
			this->cameraSelectPage->TabIndex = 5;
			this->cameraSelectPage->Text = L"Camera";
			this->cameraSelectPage->UseVisualStyleBackColor = true;
			// 
			// cameraSelectedLabel
			// 
			this->cameraSelectedLabel->AutoSize = true;
			this->cameraSelectedLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cameraSelectedLabel->Location = System::Drawing::Point(266, 248);
			this->cameraSelectedLabel->MaximumSize = System::Drawing::Size(250, 60);
			this->cameraSelectedLabel->Name = L"cameraSelectedLabel";
			this->cameraSelectedLabel->Size = System::Drawing::Size(217, 34);
			this->cameraSelectedLabel->TabIndex = 9;
			this->cameraSelectedLabel->Text = L"No rigid body is selected to be the camera.";
			// 
			// selectAsCameraBtn
			// 
			this->selectAsCameraBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->selectAsCameraBtn->Location = System::Drawing::Point(335, 200);
			this->selectAsCameraBtn->Name = L"selectAsCameraBtn";
			this->selectAsCameraBtn->Size = System::Drawing::Size(109, 23);
			this->selectAsCameraBtn->TabIndex = 8;
			this->selectAsCameraBtn->Text = L"Select as Camera";
			this->selectAsCameraBtn->UseVisualStyleBackColor = false;
			this->selectAsCameraBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::selectAsCameraBtn_Click);
			// 
			// cameraSelectLabel
			// 
			this->cameraSelectLabel->AutoSize = true;
			this->cameraSelectLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->cameraSelectLabel->Location = System::Drawing::Point(265, 3);
			this->cameraSelectLabel->Name = L"cameraSelectLabel";
			this->cameraSelectLabel->Size = System::Drawing::Size(254, 152);
			this->cameraSelectLabel->TabIndex = 7;
			this->cameraSelectLabel->Text = resources->GetString(L"cameraSelectLabel.Text");
			// 
			// cameraListView
			// 
			this->cameraListView->Alignment = System::Windows::Forms::ListViewAlignment::Left;
			this->cameraListView->Dock = System::Windows::Forms::DockStyle::Left;
			this->cameraListView->FullRowSelect = true;
			this->cameraListView->LabelWrap = false;
			this->cameraListView->Location = System::Drawing::Point(3, 3);
			this->cameraListView->MultiSelect = false;
			this->cameraListView->Name = L"cameraListView";
			this->cameraListView->Size = System::Drawing::Size(245, 289);
			this->cameraListView->TabIndex = 6;
			this->cameraListView->TileSize = System::Drawing::Size(100, 20);
			this->cameraListView->UseCompatibleStateImageBehavior = false;
			this->cameraListView->View = System::Windows::Forms::View::SmallIcon;
			// 
			// cameraOffsetPage
			// 
			this->cameraOffsetPage->Controls->Add(this->addOffsetBtn);
			this->cameraOffsetPage->Controls->Add(this->cameraOffsetLabel);
			this->cameraOffsetPage->Controls->Add(this->cameraOffsetImage);
			this->cameraOffsetPage->Location = System::Drawing::Point(4, 22);
			this->cameraOffsetPage->Name = L"cameraOffsetPage";
			this->cameraOffsetPage->Size = System::Drawing::Size(529, 295);
			this->cameraOffsetPage->TabIndex = 6;
			this->cameraOffsetPage->Text = L"Camera Offset";
			this->cameraOffsetPage->UseVisualStyleBackColor = true;
			// 
			// addOffsetBtn
			// 
			this->addOffsetBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->addOffsetBtn->Location = System::Drawing::Point(315, 139);
			this->addOffsetBtn->Name = L"addOffsetBtn";
			this->addOffsetBtn->Size = System::Drawing::Size(144, 23);
			this->addOffsetBtn->TabIndex = 2;
			this->addOffsetBtn->Text = L"Add Camera Position";
			this->addOffsetBtn->UseVisualStyleBackColor = false;
			this->addOffsetBtn->Click += gcnew System::EventHandler(this, &CameraCalibrationForm::addOffsetBtn_Click);
			// 
			// cameraOffsetLabel
			// 
			this->cameraOffsetLabel->AutoSize = true;
			this->cameraOffsetLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->cameraOffsetLabel->Location = System::Drawing::Point(165, 5);
			this->cameraOffsetLabel->MaximumSize = System::Drawing::Size(355, 0);
			this->cameraOffsetLabel->Name = L"cameraOffsetLabel";
			this->cameraOffsetLabel->Size = System::Drawing::Size(353, 114);
			this->cameraOffsetLabel->TabIndex = 1;
			this->cameraOffsetLabel->Text = resources->GetString(L"cameraOffsetLabel.Text");
			// 
			// cameraOffsetImage
			// 
			this->cameraOffsetImage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cameraOffsetImage->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cameraOffsetImage.Image")));
			this->cameraOffsetImage->Location = System::Drawing::Point(0, 0);
			this->cameraOffsetImage->Name = L"cameraOffsetImage";
			this->cameraOffsetImage->Size = System::Drawing::Size(529, 295);
			this->cameraOffsetImage->TabIndex = 0;
			this->cameraOffsetImage->TabStop = false;
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
			this->Name = L"CameraCalibrationForm";
			this->Text = L"Camera Calibration";
			this->Load += gcnew System::EventHandler(this, &CameraCalibrationForm::Form_Load);
			this->calculatingOffsetPage->ResumeLayout(false);
			this->calculatingOffsetPage->PerformLayout();
			this->screenSelectPage->ResumeLayout(false);
			this->screenSelectPage->PerformLayout();
			this->introPage->ResumeLayout(false);
			this->introPage->PerformLayout();
			this->wizardPagesTemp->ResumeLayout(false);
			this->cameraSelectPage->ResumeLayout(false);
			this->cameraSelectPage->PerformLayout();
			this->cameraOffsetPage->ResumeLayout(false);
			this->cameraOffsetPage->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraOffsetImage))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	 // Abstract Delegate to change text
	private: delegate void SetTextDelegate(String^ value);
	private: CameraCalibration* cameraCalibration;
#if Debug
	private: System::Windows::Forms::TabControl^ wizardPages;
#else
	private: WizardPages^ wizardPages;
#endif

	private: System::Void Form_Load(System::Object^  sender, System::EventArgs^  e) {
				 if (!cameraCalibration)
					 cameraCalibration = new CameraCalibration();

				 cameraCalibration->init();

#if Debug
				 this->wizardPages = this->wizardPagesTemp;
#else
				 this->Controls->Remove(this->wizardPagesTemp);

				 this->wizardPages = gcnew WizardPages();

				 this->wizardPages->SuspendLayout();
				 this->wizardPages->Controls->Add(this->introPage);
				 this->wizardPages->Controls->Add(this->screenSelectPage);
				 this->wizardPages->Controls->Add(this->cameraSelectPage);
				 this->wizardPages->Controls->Add(this->cameraOffsetPage);
				 this->wizardPages->Controls->Add(this->calculatingOffsetPage);
				 this->wizardPages->Controls->Add(this->calibrationPage);
				 this->wizardPages->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->wizardPages->Location = System::Drawing::Point(0, 0);
				 this->wizardPages->Name = L"wizardPages";
				 this->wizardPages->SelectedIndex = 0;
				 this->wizardPages->Size = System::Drawing::Size(537, 321);
				 this->wizardPages->TabIndex = 7;
				  this->wizardPages->SelectedIndexChanged += gcnew System::EventHandler(this, &CameraCalibrationForm::pageChanged);

				 this->Controls->Add(this->wizardPages);
				 this->wizardPages->ResumeLayout(false);
#endif

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

				 this->cameraListView->View = View::Details;
				 this->cameraListView->Columns->Add("Id", 50, HorizontalAlignment::Left ); 
				 this->cameraListView->Columns->Add("Name", 150, HorizontalAlignment::Left ); 

				 RigidBodyMap bodyMap = ClientHandler::getInstance()->getRigidBodyMap();

				 // Clear any previous entries in the list view
				 this->cameraListView->Items->Clear();
				 
				 // Loop through all Rigid Body's
				 for (RigidBody_iterator it = bodyMap.begin(); it != bodyMap.end(); ++it)
				 {
					 { // Add Rigid Body's for Camera
						 String^ rigidBodyID = Convert::ToString(it->second->getID());
						 String^ rigidBodyName = gcnew String(it->second->getName());
						 ListViewItem^ listViewItem = gcnew ListViewItem(rigidBodyID); 
						 listViewItem->SubItems->Add(rigidBodyName);
						 this->cameraListView->Items->Add(listViewItem);
					 }
				 }
			 }
	private: System::Void pageChanged(System::Object^  sender, System::EventArgs^  e) {
				 // Check Valid information for each page
				 if (this->wizardPages->SelectedTab == this->screenSelectPage &&
					 this->cameraCalibration->getHeight() == 0) {
						 this->nextBtn->Enabled = false;
				 } else if (this->wizardPages->SelectedTab == this->cameraSelectPage &&
					 this->cameraCalibration->getCameraId() < 0) {
						 this->nextBtn->Enabled = false;
				 } else if (this->wizardPages->SelectedTab == this->calculatingOffsetPage) {
					 this->nextBtn->Enabled = false;
				 } else {
					 this->nextBtn->Enabled = true;
				 }

				 // Calculate Calibration Points
				 if (this->wizardPages->SelectedTab == this->calculatingOffsetPage) {
					 if (!this->cameraCalibration->calculateOffset()) {
						 this->nextBtn->Enabled = true;
					 }
				 }

				 // Done and change text in the next button to finished
				 if (this->wizardPages->SelectedIndex == this->wizardPages->TabCount - 1)
					 this->nextBtn->Text = "Finish";
				 else
					 this->nextBtn->Text = "Next";

				 // First page so set enabled to false for the back button
				 if (this->wizardPages->SelectedIndex == 0)
					 this->backBtn->Enabled = false;
				 else
					 this->backBtn->Enabled = true;
			 }

	private: System::Void backBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->wizardPages->SelectedIndex > 0)
					this->wizardPages->SelectedIndex--;
			 }
	private: System::Void nextBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 // Check if at last index and if so close Wizard
				 if (this->wizardPages->SelectedIndex < this->wizardPages->TabCount - 1)
					 this->wizardPages->SelectedIndex++;
				 else if (this->wizardPages->SelectedIndex == this->wizardPages->TabCount - 1)
					 this->Close();
			 }
	private: System::Void cancelBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	private: System::Void selectAsCameraBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->cameraListView->SelectedItems->Count > 0) {
					 int cameraId = System::Int32::Parse(this->cameraListView->SelectedItems[0]->Text);
					 this->cameraCalibration->setCameraId(cameraId);

					 String^ message = gcnew String(this->cameraCalibration->getCameraName());
					 message = message + " is the rigid body selected as the camera.";

					 this->cameraSelectedLabel->Text = message;
					 this->nextBtn->Enabled = true;
				 }
				 else {
					 this->cameraSelectedLabel->Text = "No rigid body is selected to be the head.";
				 }
			 }
	private: System::Void addOffsetBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->cameraCalibration->addCameraOffset();
		 }
	public: System::Void offsetCalibrationOutputLog(System::String^ value) {
				 if (this->calibrationOffsetOutputLogLabel->InvokeRequired)
				 {
					 SetTextDelegate^ d = gcnew SetTextDelegate(this, &ProjectDR::CameraCalibrationForm::offsetCalibrationOutputLog);
					 this->Invoke(d, gcnew array<Object^> { value });
				 } else {
					 // Update Value
					 // Determine if the text being appended to calibrationOutputLogLabel exceeds the MaxLength property.
					 if((unsigned int)(calibrationOffsetOutputLogLabel->TextLength + value->Length) > (unsigned int)calibrationOffsetOutputLogLabel->MaxLength)
					 {
						 int over = (calibrationOffsetOutputLogLabel->TextLength + value->Length) - calibrationOffsetOutputLogLabel->MaxLength;
						 calibrationOffsetOutputLogLabel->Text = calibrationOffsetOutputLogLabel->Text->Substring(over);
					 }
					 // Append the text
					 this->calibrationOffsetOutputLogLabel->AppendText(value->Replace("\n", Environment::NewLine));
				 }
			 }
	private: System::Void selectAsMonitorBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->monitorListView->SelectedItems->Count > 0) {
					 Screen^ screen = Screen::AllScreens[this->monitorListView->Items->IndexOf(this->monitorListView->SelectedItems[0])];
					 this->cameraCalibration->setWorkingArea(screen->WorkingArea.X, screen->WorkingArea.Y,
						 screen->WorkingArea.Width, screen->WorkingArea.Height);

					 String^ message = screen->DeviceName + " is selected to be the main display.";

					 this->monitorSelectedLabel->Text = message;
					 this->nextBtn->Enabled = true;
				 }
				 else {
					 this->monitorSelectedLabel->Text = "No monitor is selected to be the main display.";
				 }
			 }
};
}
