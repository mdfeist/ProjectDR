#pragma once

#include "Debug.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <exception>
#include <msclr\marshal_cppstd.h>

#include "ClientHandler.h"
#include "RigidBody.h"
#include "CameraCalibrationFormController.h"
#include "VolumeRenderManager.h"

#include "ProgressSpinner.h"

namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace msclr::interop;

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
	private: System::Windows::Forms::TabPage^  VolumeTab;

	private: System::Windows::Forms::SplitContainer^  optiTrackSubSplitContainer;
	private: System::Windows::Forms::TextBox^  optiTrackLocalIpAddressTextBox;
	private: System::Windows::Forms::Label^  optiTrackLocalIpAddressLabel;
	private: System::Windows::Forms::Label^  optiTrackLocalTitle;
	private: System::Windows::Forms::ComboBox^  optiTrackConnectionTypeComboBox;
	private: System::Windows::Forms::Label^  optiTrackConnectionTypeLabel;
	private: System::Windows::Forms::TextBox^  optiTrackDataPortTextBox;
	private: System::Windows::Forms::Label^  optiTrackDataPortLabel;
	private: System::Windows::Forms::TextBox^  optiTrackCmdPortTextBox;
	private: System::Windows::Forms::Label^  optiTrackCmdPortLabel;
	private: System::Windows::Forms::TextBox^  optiTrackSeverIpAddressTextBox;
	private: System::Windows::Forms::Label^  optiTrackSeverIpAddressLabel;
	private: System::Windows::Forms::Label^  optiTrackServerTitleLabel;
	private: System::Windows::Forms::Label^  optiTrackPropertiesLabel;
	private: System::Windows::Forms::Button^  optiTrackDisConnect;
	private: System::Windows::Forms::Button^  optiTrackConnectBtn;
	private: System::Windows::Forms::DataGridView^  optiTrackDataGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyIDColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyNameColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyPositionXColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyPositionYColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyPositionZColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyRotationXColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyRotationYColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyRotationZColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  optiTrackRigidBodyRotationWColumn;
	private: System::Windows::Forms::TextBox^  optiTrackOutputLogTextBox;
	private: System::Windows::Forms::Label^  optiTrackOutputLogLabel;
	private: System::Windows::Forms::ToolStripMenuItem^  calibrationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cameraCalibrationToolStripMenuItem;
	private: System::Windows::Forms::Label^  volumePathLabel;

	private: System::Windows::Forms::TextBox^  volumePathTextBox;
	private: System::Windows::Forms::Button^  loadVolumeBtn;
	private: System::Windows::Forms::Button^  browseForVolumeBtn;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  volumeRemoveBtn;



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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->projectDRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calibrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cameraCalibrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->optiTrackPage = (gcnew System::Windows::Forms::TabPage());
			this->optiTrackMainSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->optiTrackSubSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->optiTrackDataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->optiTrackRigidBodyIDColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyPositionXColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyPositionYColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyPositionZColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyRotationXColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyRotationYColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyRotationZColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackRigidBodyRotationWColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->optiTrackOutputLogTextBox = (gcnew System::Windows::Forms::TextBox());
			this->optiTrackOutputLogLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackDisConnect = (gcnew System::Windows::Forms::Button());
			this->optiTrackConnectBtn = (gcnew System::Windows::Forms::Button());
			this->optiTrackLocalIpAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->optiTrackLocalIpAddressLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackLocalTitle = (gcnew System::Windows::Forms::Label());
			this->optiTrackConnectionTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->optiTrackConnectionTypeLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackDataPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->optiTrackDataPortLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackCmdPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->optiTrackCmdPortLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackSeverIpAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->optiTrackSeverIpAddressLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackServerTitleLabel = (gcnew System::Windows::Forms::Label());
			this->optiTrackPropertiesLabel = (gcnew System::Windows::Forms::Label());
			this->VolumeTab = (gcnew System::Windows::Forms::TabPage());
			this->volumeRemoveBtn = (gcnew System::Windows::Forms::Button());
			this->loadVolumeBtn = (gcnew System::Windows::Forms::Button());
			this->browseForVolumeBtn = (gcnew System::Windows::Forms::Button());
			this->volumePathTextBox = (gcnew System::Windows::Forms::TextBox());
			this->volumePathLabel = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->optiTrackPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackMainSplitContainer))->BeginInit();
			this->optiTrackMainSplitContainer->Panel1->SuspendLayout();
			this->optiTrackMainSplitContainer->Panel2->SuspendLayout();
			this->optiTrackMainSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackSubSplitContainer))->BeginInit();
			this->optiTrackSubSplitContainer->Panel1->SuspendLayout();
			this->optiTrackSubSplitContainer->Panel2->SuspendLayout();
			this->optiTrackSubSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackDataGridView))->BeginInit();
			this->VolumeTab->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip->GripMargin = System::Windows::Forms::Padding(0);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->projectDRToolStripMenuItem, 
				this->calibrationToolStripMenuItem});
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
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->cameraCalibrationToolStripMenuItem});
			this->calibrationToolStripMenuItem->ForeColor = System::Drawing::SystemColors::MenuText;
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(77, 20);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			// 
			// cameraCalibrationToolStripMenuItem
			// 
			this->cameraCalibrationToolStripMenuItem->Name = L"cameraCalibrationToolStripMenuItem";
			this->cameraCalibrationToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->cameraCalibrationToolStripMenuItem->Text = L"Camera Calibration";
			this->cameraCalibrationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cameraCalibrationToolStripMenuItem_Click);
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->optiTrackPage);
			this->tabControl->Controls->Add(this->VolumeTab);
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
			this->optiTrackPage->ForeColor = System::Drawing::SystemColors::Window;
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
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackDisConnect);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackConnectBtn);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackLocalIpAddressTextBox);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackLocalIpAddressLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackLocalTitle);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackConnectionTypeComboBox);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackConnectionTypeLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackDataPortTextBox);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackDataPortLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackCmdPortTextBox);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackCmdPortLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackSeverIpAddressTextBox);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackSeverIpAddressLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackServerTitleLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->optiTrackPropertiesLabel);
			this->optiTrackMainSplitContainer->Panel2MinSize = 225;
			this->optiTrackMainSplitContainer->Size = System::Drawing::Size(792, 548);
			this->optiTrackMainSplitContainer->SplitterDistance = 515;
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
			this->optiTrackSubSplitContainer->Panel1->Controls->Add(this->optiTrackDataGridView);
			// 
			// optiTrackSubSplitContainer.Panel2
			// 
			this->optiTrackSubSplitContainer->Panel2->BackColor = System::Drawing::Color::LightGray;
			this->optiTrackSubSplitContainer->Panel2->Controls->Add(this->optiTrackOutputLogTextBox);
			this->optiTrackSubSplitContainer->Panel2->Controls->Add(this->optiTrackOutputLogLabel);
			this->optiTrackSubSplitContainer->Panel2MinSize = 100;
			this->optiTrackSubSplitContainer->Size = System::Drawing::Size(515, 548);
			this->optiTrackSubSplitContainer->SplitterDistance = 411;
			this->optiTrackSubSplitContainer->TabIndex = 0;
			// 
			// optiTrackDataGridView
			// 
			this->optiTrackDataGridView->AllowUserToAddRows = false;
			this->optiTrackDataGridView->AllowUserToDeleteRows = false;
			this->optiTrackDataGridView->AllowUserToResizeColumns = false;
			this->optiTrackDataGridView->AllowUserToResizeRows = false;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(234)), 
				static_cast<System::Int32>(static_cast<System::Byte>(234)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::Black;
			this->optiTrackDataGridView->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->optiTrackDataGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->optiTrackDataGridView->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->optiTrackDataGridView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->optiTrackDataGridView->CausesValidation = false;
			this->optiTrackDataGridView->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::Disable;
			this->optiTrackDataGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->optiTrackDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->optiTrackDataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {this->optiTrackRigidBodyIDColumn, 
				this->optiTrackRigidBodyNameColumn, this->optiTrackRigidBodyPositionXColumn, this->optiTrackRigidBodyPositionYColumn, this->optiTrackRigidBodyPositionZColumn, 
				this->optiTrackRigidBodyRotationXColumn, this->optiTrackRigidBodyRotationYColumn, this->optiTrackRigidBodyRotationZColumn, this->optiTrackRigidBodyRotationWColumn});
			this->optiTrackDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->optiTrackDataGridView->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->optiTrackDataGridView->EnableHeadersVisualStyles = false;
			this->optiTrackDataGridView->Location = System::Drawing::Point(0, 0);
			this->optiTrackDataGridView->Name = L"optiTrackDataGridView";
			this->optiTrackDataGridView->ReadOnly = true;
			this->optiTrackDataGridView->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->optiTrackDataGridView->RowHeadersWidth = 25;
			this->optiTrackDataGridView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
			this->optiTrackDataGridView->RowsDefaultCellStyle = dataGridViewCellStyle2;
			this->optiTrackDataGridView->ShowCellErrors = false;
			this->optiTrackDataGridView->ShowCellToolTips = false;
			this->optiTrackDataGridView->ShowEditingIcon = false;
			this->optiTrackDataGridView->ShowRowErrors = false;
			this->optiTrackDataGridView->Size = System::Drawing::Size(515, 411);
			this->optiTrackDataGridView->TabIndex = 2;
			// 
			// optiTrackRigidBodyIDColumn
			// 
			this->optiTrackRigidBodyIDColumn->HeaderText = L"ID";
			this->optiTrackRigidBodyIDColumn->Name = L"optiTrackRigidBodyIDColumn";
			this->optiTrackRigidBodyIDColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyNameColumn
			// 
			this->optiTrackRigidBodyNameColumn->HeaderText = L"Name";
			this->optiTrackRigidBodyNameColumn->Name = L"optiTrackRigidBodyNameColumn";
			this->optiTrackRigidBodyNameColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyPositionXColumn
			// 
			this->optiTrackRigidBodyPositionXColumn->HeaderText = L"Position X";
			this->optiTrackRigidBodyPositionXColumn->Name = L"optiTrackRigidBodyPositionXColumn";
			this->optiTrackRigidBodyPositionXColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyPositionYColumn
			// 
			this->optiTrackRigidBodyPositionYColumn->HeaderText = L"Position Y";
			this->optiTrackRigidBodyPositionYColumn->Name = L"optiTrackRigidBodyPositionYColumn";
			this->optiTrackRigidBodyPositionYColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyPositionZColumn
			// 
			this->optiTrackRigidBodyPositionZColumn->HeaderText = L"Position Z";
			this->optiTrackRigidBodyPositionZColumn->Name = L"optiTrackRigidBodyPositionZColumn";
			this->optiTrackRigidBodyPositionZColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyRotationXColumn
			// 
			this->optiTrackRigidBodyRotationXColumn->HeaderText = L"Rotation X";
			this->optiTrackRigidBodyRotationXColumn->Name = L"optiTrackRigidBodyRotationXColumn";
			this->optiTrackRigidBodyRotationXColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyRotationYColumn
			// 
			this->optiTrackRigidBodyRotationYColumn->HeaderText = L"Rotation Y";
			this->optiTrackRigidBodyRotationYColumn->Name = L"optiTrackRigidBodyRotationYColumn";
			this->optiTrackRigidBodyRotationYColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyRotationZColumn
			// 
			this->optiTrackRigidBodyRotationZColumn->HeaderText = L"Rotation Z";
			this->optiTrackRigidBodyRotationZColumn->Name = L"optiTrackRigidBodyRotationZColumn";
			this->optiTrackRigidBodyRotationZColumn->ReadOnly = true;
			// 
			// optiTrackRigidBodyRotationWColumn
			// 
			this->optiTrackRigidBodyRotationWColumn->HeaderText = L"Rotation W";
			this->optiTrackRigidBodyRotationWColumn->Name = L"optiTrackRigidBodyRotationWColumn";
			this->optiTrackRigidBodyRotationWColumn->ReadOnly = true;
			// 
			// optiTrackOutputLogTextBox
			// 
			this->optiTrackOutputLogTextBox->AcceptsReturn = true;
			this->optiTrackOutputLogTextBox->AcceptsTab = true;
			this->optiTrackOutputLogTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackOutputLogTextBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->optiTrackOutputLogTextBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackOutputLogTextBox->Location = System::Drawing::Point(3, 18);
			this->optiTrackOutputLogTextBox->Multiline = true;
			this->optiTrackOutputLogTextBox->Name = L"optiTrackOutputLogTextBox";
			this->optiTrackOutputLogTextBox->ReadOnly = true;
			this->optiTrackOutputLogTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->optiTrackOutputLogTextBox->Size = System::Drawing::Size(509, 112);
			this->optiTrackOutputLogTextBox->TabIndex = 3;
			// 
			// optiTrackOutputLogLabel
			// 
			this->optiTrackOutputLogLabel->AutoSize = true;
			this->optiTrackOutputLogLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackOutputLogLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackOutputLogLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->optiTrackOutputLogLabel->Location = System::Drawing::Point(5, 2);
			this->optiTrackOutputLogLabel->Name = L"optiTrackOutputLogLabel";
			this->optiTrackOutputLogLabel->Size = System::Drawing::Size(67, 13);
			this->optiTrackOutputLogLabel->TabIndex = 2;
			this->optiTrackOutputLogLabel->Text = L"Output Log";
			// 
			// optiTrackDisConnect
			// 
			this->optiTrackDisConnect->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackDisConnect->BackColor = System::Drawing::Color::Gainsboro;
			this->optiTrackDisConnect->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackDisConnect->Location = System::Drawing::Point(192, 520);
			this->optiTrackDisConnect->Name = L"optiTrackDisConnect";
			this->optiTrackDisConnect->Size = System::Drawing::Size(76, 23);
			this->optiTrackDisConnect->TabIndex = 43;
			this->optiTrackDisConnect->Text = L"Disconnect";
			this->optiTrackDisConnect->UseVisualStyleBackColor = false;
			this->optiTrackDisConnect->Click += gcnew System::EventHandler(this, &MainForm::optiTrackDisConnect_Click);
			// 
			// optiTrackConnectBtn
			// 
			this->optiTrackConnectBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->optiTrackConnectBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->optiTrackConnectBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackConnectBtn->Location = System::Drawing::Point(9, 520);
			this->optiTrackConnectBtn->Name = L"optiTrackConnectBtn";
			this->optiTrackConnectBtn->Size = System::Drawing::Size(76, 23);
			this->optiTrackConnectBtn->TabIndex = 42;
			this->optiTrackConnectBtn->Text = L"Connect";
			this->optiTrackConnectBtn->UseVisualStyleBackColor = false;
			this->optiTrackConnectBtn->Click += gcnew System::EventHandler(this, &MainForm::optiTrackConnectBtn_Click);
			// 
			// optiTrackLocalIpAddressTextBox
			// 
			this->optiTrackLocalIpAddressTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackLocalIpAddressTextBox->Location = System::Drawing::Point(124, 58);
			this->optiTrackLocalIpAddressTextBox->Name = L"optiTrackLocalIpAddressTextBox";
			this->optiTrackLocalIpAddressTextBox->Size = System::Drawing::Size(144, 22);
			this->optiTrackLocalIpAddressTextBox->TabIndex = 41;
			this->optiTrackLocalIpAddressTextBox->Text = L"127.0.0.1";
			// 
			// optiTrackLocalIpAddressLabel
			// 
			this->optiTrackLocalIpAddressLabel->AutoSize = true;
			this->optiTrackLocalIpAddressLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackLocalIpAddressLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->optiTrackLocalIpAddressLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackLocalIpAddressLabel->Location = System::Drawing::Point(6, 61);
			this->optiTrackLocalIpAddressLabel->Name = L"optiTrackLocalIpAddressLabel";
			this->optiTrackLocalIpAddressLabel->Size = System::Drawing::Size(63, 13);
			this->optiTrackLocalIpAddressLabel->TabIndex = 40;
			this->optiTrackLocalIpAddressLabel->Text = L"IP Address:";
			// 
			// optiTrackLocalTitle
			// 
			this->optiTrackLocalTitle->AutoSize = true;
			this->optiTrackLocalTitle->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackLocalTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackLocalTitle->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackLocalTitle->Location = System::Drawing::Point(6, 38);
			this->optiTrackLocalTitle->Name = L"optiTrackLocalTitle";
			this->optiTrackLocalTitle->Size = System::Drawing::Size(85, 13);
			this->optiTrackLocalTitle->TabIndex = 39;
			this->optiTrackLocalTitle->Text = L"Local Machine:";
			// 
			// optiTrackConnectionTypeComboBox
			// 
			this->optiTrackConnectionTypeComboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackConnectionTypeComboBox->FormattingEnabled = true;
			this->optiTrackConnectionTypeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Multicast", L"Unicast"});
			this->optiTrackConnectionTypeComboBox->Location = System::Drawing::Point(124, 204);
			this->optiTrackConnectionTypeComboBox->Name = L"optiTrackConnectionTypeComboBox";
			this->optiTrackConnectionTypeComboBox->Size = System::Drawing::Size(144, 21);
			this->optiTrackConnectionTypeComboBox->TabIndex = 38;
			this->optiTrackConnectionTypeComboBox->Text = L"Multicast";
			// 
			// optiTrackConnectionTypeLabel
			// 
			this->optiTrackConnectionTypeLabel->AutoSize = true;
			this->optiTrackConnectionTypeLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackConnectionTypeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->optiTrackConnectionTypeLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackConnectionTypeLabel->Location = System::Drawing::Point(6, 204);
			this->optiTrackConnectionTypeLabel->Name = L"optiTrackConnectionTypeLabel";
			this->optiTrackConnectionTypeLabel->Size = System::Drawing::Size(96, 13);
			this->optiTrackConnectionTypeLabel->TabIndex = 37;
			this->optiTrackConnectionTypeLabel->Text = L"Connection Type:";
			// 
			// optiTrackDataPortTextBox
			// 
			this->optiTrackDataPortTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackDataPortTextBox->Location = System::Drawing::Point(124, 172);
			this->optiTrackDataPortTextBox->Name = L"optiTrackDataPortTextBox";
			this->optiTrackDataPortTextBox->Size = System::Drawing::Size(144, 22);
			this->optiTrackDataPortTextBox->TabIndex = 36;
			this->optiTrackDataPortTextBox->Text = L"1511";
			// 
			// optiTrackDataPortLabel
			// 
			this->optiTrackDataPortLabel->AutoSize = true;
			this->optiTrackDataPortLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackDataPortLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackDataPortLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackDataPortLabel->Location = System::Drawing::Point(6, 175);
			this->optiTrackDataPortLabel->Name = L"optiTrackDataPortLabel";
			this->optiTrackDataPortLabel->Size = System::Drawing::Size(58, 13);
			this->optiTrackDataPortLabel->TabIndex = 35;
			this->optiTrackDataPortLabel->Text = L"Data Port:";
			// 
			// optiTrackCmdPortTextBox
			// 
			this->optiTrackCmdPortTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackCmdPortTextBox->Location = System::Drawing::Point(124, 144);
			this->optiTrackCmdPortTextBox->Name = L"optiTrackCmdPortTextBox";
			this->optiTrackCmdPortTextBox->Size = System::Drawing::Size(144, 22);
			this->optiTrackCmdPortTextBox->TabIndex = 34;
			this->optiTrackCmdPortTextBox->Text = L"1510";
			// 
			// optiTrackCmdPortLabel
			// 
			this->optiTrackCmdPortLabel->AutoSize = true;
			this->optiTrackCmdPortLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackCmdPortLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackCmdPortLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackCmdPortLabel->Location = System::Drawing::Point(6, 147);
			this->optiTrackCmdPortLabel->Name = L"optiTrackCmdPortLabel";
			this->optiTrackCmdPortLabel->Size = System::Drawing::Size(86, 13);
			this->optiTrackCmdPortLabel->TabIndex = 33;
			this->optiTrackCmdPortLabel->Text = L"Command Port:";
			// 
			// optiTrackSeverIpAddressTextBox
			// 
			this->optiTrackSeverIpAddressTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->optiTrackSeverIpAddressTextBox->Location = System::Drawing::Point(124, 116);
			this->optiTrackSeverIpAddressTextBox->Name = L"optiTrackSeverIpAddressTextBox";
			this->optiTrackSeverIpAddressTextBox->Size = System::Drawing::Size(144, 22);
			this->optiTrackSeverIpAddressTextBox->TabIndex = 32;
			this->optiTrackSeverIpAddressTextBox->Text = L"127.0.0.1";
			// 
			// optiTrackSeverIpAddressLabel
			// 
			this->optiTrackSeverIpAddressLabel->AutoSize = true;
			this->optiTrackSeverIpAddressLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackSeverIpAddressLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->optiTrackSeverIpAddressLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackSeverIpAddressLabel->Location = System::Drawing::Point(6, 119);
			this->optiTrackSeverIpAddressLabel->Name = L"optiTrackSeverIpAddressLabel";
			this->optiTrackSeverIpAddressLabel->Size = System::Drawing::Size(63, 13);
			this->optiTrackSeverIpAddressLabel->TabIndex = 31;
			this->optiTrackSeverIpAddressLabel->Text = L"IP Address:";
			// 
			// optiTrackServerTitleLabel
			// 
			this->optiTrackServerTitleLabel->AutoSize = true;
			this->optiTrackServerTitleLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackServerTitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackServerTitleLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackServerTitleLabel->Location = System::Drawing::Point(6, 96);
			this->optiTrackServerTitleLabel->Name = L"optiTrackServerTitleLabel";
			this->optiTrackServerTitleLabel->Size = System::Drawing::Size(94, 13);
			this->optiTrackServerTitleLabel->TabIndex = 30;
			this->optiTrackServerTitleLabel->Text = L"OptiTrack Server:";
			// 
			// optiTrackPropertiesLabel
			// 
			this->optiTrackPropertiesLabel->AutoSize = true;
			this->optiTrackPropertiesLabel->BackColor = System::Drawing::Color::Transparent;
			this->optiTrackPropertiesLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->optiTrackPropertiesLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->optiTrackPropertiesLabel->Location = System::Drawing::Point(3, 10);
			this->optiTrackPropertiesLabel->Name = L"optiTrackPropertiesLabel";
			this->optiTrackPropertiesLabel->Size = System::Drawing::Size(71, 17);
			this->optiTrackPropertiesLabel->TabIndex = 29;
			this->optiTrackPropertiesLabel->Text = L"Properties";
			// 
			// VolumeTab
			// 
			this->VolumeTab->BackColor = System::Drawing::Color::WhiteSmoke;
			this->VolumeTab->Controls->Add(this->volumeRemoveBtn);
			this->VolumeTab->Controls->Add(this->loadVolumeBtn);
			this->VolumeTab->Controls->Add(this->browseForVolumeBtn);
			this->VolumeTab->Controls->Add(this->volumePathTextBox);
			this->VolumeTab->Controls->Add(this->volumePathLabel);
			this->VolumeTab->Location = System::Drawing::Point(4, 24);
			this->VolumeTab->Name = L"VolumeTab";
			this->VolumeTab->Padding = System::Windows::Forms::Padding(3);
			this->VolumeTab->Size = System::Drawing::Size(792, 548);
			this->VolumeTab->TabIndex = 1;
			this->VolumeTab->Text = L"Volume";
			// 
			// volumeRemoveBtn
			// 
			this->volumeRemoveBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->volumeRemoveBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->volumeRemoveBtn->Location = System::Drawing::Point(9, 83);
			this->volumeRemoveBtn->Name = L"volumeRemoveBtn";
			this->volumeRemoveBtn->Size = System::Drawing::Size(76, 23);
			this->volumeRemoveBtn->TabIndex = 45;
			this->volumeRemoveBtn->Text = L"Remove";
			this->volumeRemoveBtn->UseVisualStyleBackColor = false;
			this->volumeRemoveBtn->Click += gcnew System::EventHandler(this, &MainForm::volumeRemoveBtn_Click);
			// 
			// loadVolumeBtn
			// 
			this->loadVolumeBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->loadVolumeBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->loadVolumeBtn->Location = System::Drawing::Point(8, 54);
			this->loadVolumeBtn->Name = L"loadVolumeBtn";
			this->loadVolumeBtn->Size = System::Drawing::Size(76, 23);
			this->loadVolumeBtn->TabIndex = 44;
			this->loadVolumeBtn->Text = L"Load";
			this->loadVolumeBtn->UseVisualStyleBackColor = false;
			this->loadVolumeBtn->Click += gcnew System::EventHandler(this, &MainForm::loadVolumeBtn_Click);
			// 
			// browseForVolumeBtn
			// 
			this->browseForVolumeBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->browseForVolumeBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->browseForVolumeBtn->Location = System::Drawing::Point(400, 15);
			this->browseForVolumeBtn->Name = L"browseForVolumeBtn";
			this->browseForVolumeBtn->Size = System::Drawing::Size(76, 23);
			this->browseForVolumeBtn->TabIndex = 43;
			this->browseForVolumeBtn->Text = L"Browse";
			this->browseForVolumeBtn->UseVisualStyleBackColor = false;
			this->browseForVolumeBtn->Click += gcnew System::EventHandler(this, &MainForm::browseForVolumeBtn_Click);
			// 
			// volumePathTextBox
			// 
			this->volumePathTextBox->Location = System::Drawing::Point(102, 16);
			this->volumePathTextBox->Name = L"volumePathTextBox";
			this->volumePathTextBox->Size = System::Drawing::Size(292, 22);
			this->volumePathTextBox->TabIndex = 1;
			// 
			// volumePathLabel
			// 
			this->volumePathLabel->AutoSize = true;
			this->volumePathLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->volumePathLabel->Location = System::Drawing::Point(6, 19);
			this->volumePathLabel->Name = L"volumePathLabel";
			this->volumePathLabel->Size = System::Drawing::Size(90, 13);
			this->volumePathLabel->TabIndex = 0;
			this->volumePathLabel->Text = L"Path To Volume:";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker1_RunWorkerCompleted);
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
			this->optiTrackMainSplitContainer->Panel2->ResumeLayout(false);
			this->optiTrackMainSplitContainer->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackMainSplitContainer))->EndInit();
			this->optiTrackMainSplitContainer->ResumeLayout(false);
			this->optiTrackSubSplitContainer->Panel1->ResumeLayout(false);
			this->optiTrackSubSplitContainer->Panel2->ResumeLayout(false);
			this->optiTrackSubSplitContainer->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackSubSplitContainer))->EndInit();
			this->optiTrackSubSplitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->optiTrackDataGridView))->EndInit();
			this->VolumeTab->ResumeLayout(false);
			this->VolumeTab->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Local Variables
	private: std::vector<RigidBody*>* optiTrackRigidBodyVector;
	private: ProgressSpinner^ spinner;
	// Abstract Delegate
	private: delegate System::Void SetDelegate();
	// Abstract Delegate to change text
	private: delegate System::Void SetTextDelegate(String^ value);
	// Abstract Delegate to change integer value
	private: delegate System::Void SetIntDelegate(int value);
	// Abstract Delegate to change unsigned integer value
	private: delegate System::Void SetUIntDelegate(unsigned int value);
	// MainForm Load
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
				 //this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
				 this->SetStyle(ControlStyles::UserPaint, true);
				 this->SetStyle(ControlStyles::AllPaintingInWmPaint, true); 
				 this->SetStyle(ControlStyles::DoubleBuffer, true);
				 this->SetStyle(ControlStyles::ResizeRedraw, true);

				 this->optiTrackDataGridView->CellValueNeeded += gcnew
					 DataGridViewCellValueEventHandler( this, &MainForm::optiTrackDataGridView_CellValueNeeded );

				 for (int i = 0; i < this->optiTrackDataGridView->ColumnCount; i++)
				 {
					 this->optiTrackDataGridView->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
				 }

				 this->optiTrackDataGridView->VirtualMode = true;

				 this->spinner = gcnew ProgressSpinner();
				 this->spinner->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left));
				 this->spinner->Location = System::Drawing::Point(100, 60);
				 this->spinner->Enable = false;
				 this->VolumeTab->Controls->Add(this->spinner);

				 this->volumeRemoveBtn->Enabled = false;
			 }

	// OptiTrack Getters/Setters
	public: System::Void setOptiTrackLocalIpAddressTextBox(System::String^ text) {
				this->optiTrackLocalIpAddressTextBox->Text = text;
			}

	public: System::String^ getOptiTrackLocalIpAddressTextBox() {
				return this->optiTrackLocalIpAddressTextBox->Text;
			}

	public: System::Void setOptiTrackSeverIpAddressTextBox(System::String^ text) {
				this->optiTrackSeverIpAddressTextBox->Text = text;
			}

	public: System::String^ getOptiTrackSeverIpAddressTextBox() {
				return this->optiTrackSeverIpAddressTextBox->Text;
			}

	public: System::Void setOptiTrackCmdPortTextBox(System::String^ text) {
				this->optiTrackCmdPortTextBox->Text = text;
			}

	public: System::String^ getOptiTrackCmdPortTextBox() {
				return this->optiTrackCmdPortTextBox->Text;
			}

	public: System::Void setOptiTrackDataPortTextBox(System::String^ text) {
				this->optiTrackDataPortTextBox->Text = text;
			}

	public: System::String^ getOptiTrackDataPortTextBox() {
				return this->optiTrackDataPortTextBox->Text;
			}

	public: System::Void setOptiTrackConnectionTypeComboBox(System::String^ text) {
				this->optiTrackConnectionTypeComboBox->SelectedItem = text;
			}

	public: System::String^ getOptiTrackConnectionTypeComboBox() {
				return (System::String^)this->optiTrackConnectionTypeComboBox->SelectedItem;
			}

	// OptiTrack Output Log
	public: System::Void optiTrackOutputLog(System::String^ text) {
				if (this->optiTrackOutputLogTextBox->InvokeRequired) 
				{
					SetTextDelegate^ d = gcnew SetTextDelegate(this, &MainForm::optiTrackOutputLog);
					this->Invoke(d, gcnew array<Object^> { text });
				} 
				else 
				{
					// Determine if the text being appended to dikablisOutputLogTextBox exceeds the MaxLength property.
					if((unsigned int)(this->optiTrackOutputLogTextBox->TextLength + text->Length) > 
						(unsigned int)this->optiTrackOutputLogTextBox->MaxLength) 
					{
						int over = (this->optiTrackOutputLogTextBox->TextLength + text->Length + 1) - 
							this->optiTrackOutputLogTextBox->MaxLength;
						this->optiTrackOutputLogTextBox->Text = this->optiTrackOutputLogTextBox->Text->Substring(over);
					}

					// Append the text
					this->optiTrackOutputLogTextBox->AppendText(text->Replace("\n", Environment::NewLine));
				}
			}

	public: System::Void getOptiTrackInfo() {
				 msclr::interop::marshal_context context;

				 // Local Ip Address
				 String^ localIP = this->getOptiTrackLocalIpAddressTextBox();
				 ClientHandler::getInstance()->setLocalIpAddress( context.marshal_as<std::string>(localIP).c_str() );

				 // Server Ip Address
				 String^ serverIP = this->getOptiTrackSeverIpAddressTextBox();
				 ClientHandler::getInstance()->setOptiTrackServerIpAddress( context.marshal_as<std::string>(serverIP).c_str() );

				 // Command Port
				 String^ commandPort = this->getOptiTrackCmdPortTextBox();
				 ClientHandler::getInstance()->setOptiTrackServerCommandPort(System::Int32::Parse(commandPort));

				 // Data Port
				 String^ dataPort = this->getOptiTrackDataPortTextBox();
				 ClientHandler::getInstance()->setOptiTrackServerDataPort(System::Int32::Parse(dataPort));

				 // Connection Type
				 String^ connectionType = this->getOptiTrackConnectionTypeComboBox();
				 if (!String::Compare(connectionType, "Multicast"))
					 ClientHandler::getInstance()->setOptiTrackServerConnectionType(ConnectionType_Multicast);
				 else if (!String::Compare(connectionType, "Unicast"))
					 ClientHandler::getInstance()->setOptiTrackServerConnectionType(ConnectionType_Unicast);
			 }

	public: System::Void setOptiTrackInfo() {

				char buf[128];
				// Local Ip Address
				ClientHandler::getInstance()->getLocalIpAddress(buf);
				this->setOptiTrackLocalIpAddressTextBox( gcnew String(buf) );

				// Server Ip Address
				ClientHandler::getInstance()->getOptiTrackServerIpAddress(buf);
				this->setOptiTrackSeverIpAddressTextBox( gcnew String(buf) );

				// Command Port
				String ^cmdPort = Convert::ToString(ClientHandler::getInstance()->getOptiTrackServerCommandPort());
				this->setOptiTrackCmdPortTextBox( cmdPort );

				// Data Port
				String ^dataPort = Convert::ToString(ClientHandler::getInstance()->getOptiTrackServerDataPort());
				this->setOptiTrackDataPortTextBox( dataPort );

				// Connection Type
				if (ClientHandler::getInstance()->getOptiTrackServerConnectionType() == ConnectionType_Multicast)
					this->setOptiTrackConnectionTypeComboBox( "Multicast" );
				else if (ClientHandler::getInstance()->getOptiTrackServerConnectionType() == ConnectionType_Unicast)
					this->setOptiTrackConnectionTypeComboBox( "Unicast" );
			}

	// Connect to OptiTrack
	private: System::Void optiTrackConnectBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				getOptiTrackInfo();
				ClientHandler::getInstance()->connect();
			 }

	// Disconnect to OptiTrack
	private: System::Void optiTrackDisConnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 ClientHandler::getInstance()->disconnect();
			 }

	// OptiTrack Data View
	public: System::Void optiTrackInitDataView() {
				if (this->optiTrackRigidBodyVector)
					delete this->optiTrackRigidBodyVector;

				this->optiTrackRigidBodyVector = new std::vector<RigidBody*>();

				if (!ClientHandler::getInstance()->lock())
					return;
				
				RigidBodyMap bodyMap = ClientHandler::getInstance()->getRigidBodyMap();
				this->optiTrackDataGridView->RowCount = (unsigned int)bodyMap.size();

				for (RigidBody_iterator it = bodyMap.begin(); it != bodyMap.end(); ++it) {
					this->optiTrackRigidBodyVector->push_back(it->second);
				}

				ClientHandler::getInstance()->unlock();
			}

	public: System::Void optiTrackUpdateData() {
				static bool isUpdating = false;
				
				if (isUpdating)
					return;

				isUpdating = true;

				static float fps = (1000.f/10.f);
				static float dwCurrentTime = 0.f;
				static float dwElapsedTime = 0.f;
				static float dwLastUpdateTime = 0.f;

				// Get Current Time
				SYSTEMTIME time;
				GetSystemTime(&time);
				dwCurrentTime = (float)(time.wHour*60.f*60.f*1000.f + time.wMinute*60.f*1000.f + time.wSecond*1000.f + time.wMilliseconds);
				// Calculate time Elapsed time
				dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
				
				// If the elapsed time is less then the fps
				if (dwElapsedTime > fps)
				{
					// Start update
					// Check if the main tab control needs invoke.
					// If not then check to see if the OptiTrack tab
					// is selected.
					if (this->tabControl->InvokeRequired) {
						SetDelegate^ d = gcnew SetDelegate(this, &MainForm::optiTrackUpdateData);
						BeginInvoke(d, nullptr);
					} else if (this->tabControl->SelectedIndex == 0) {
						// Check if the OptiTrack DataGridView needs invoke.
						// If not then update the view.
						if (this->optiTrackDataGridView->InvokeRequired) {
							SetDelegate^ d = gcnew SetDelegate(this, &MainForm::optiTrackUpdateData);
							BeginInvoke(d, nullptr);
						} else {
							// Lock the client
							if (!ClientHandler::getInstance()->lock())
								return;

							// Try to update the view
							try {
								this->optiTrackDataGridView->SuspendLayout();
								this->optiTrackDataGridView->Invalidate();
								this->optiTrackDataGridView->ResumeLayout();

								// Set LastUpdateTime to CurrentTime
								dwLastUpdateTime = dwCurrentTime;
							}
							catch(Exception^) {
								Debug::WriteLine("Error: Exception when trying to redraw the OptiTrack DataGridView.");
							}

							// Unlock client
							ClientHandler::getInstance()->unlock();
						}
					}
				} // End of update

				isUpdating = false;
			}

	private: System::Void optiTrackDataGridView_CellValueNeeded(System::Object^ /*sender*/,
       System::Windows::Forms::DataGridViewCellValueEventArgs^ e )
			{
				if (this->optiTrackRigidBodyVector)
				{
					if ((int)e->RowIndex >= (int)this->optiTrackRigidBodyVector->size())
						return;

					RigidBody* body = this->optiTrackRigidBodyVector->at(e->RowIndex);

					int id = body->getID();
					String^ name = gcnew String(body->getName());
					
					switch(e->ColumnIndex)
					{
					case 0:
						e->Value = Convert::ToString(id);
						break;
					case 1 :
						e->Value = name;
						break;
					case 2:
						e->Value = Convert::ToString(body->x());
						break;
					case 3:
						e->Value = Convert::ToString(body->y());
						break;
					case 4:
						e->Value = Convert::ToString(body->z());
						break;
					case 5:
						e->Value = Convert::ToString(body->qx());
						break;
					case 6:
						e->Value = Convert::ToString(body->qy());
						break;
					case 7:
						e->Value = Convert::ToString(body->qz());
						break;
					case 8:
						e->Value = Convert::ToString(body->qw());
						break;
					}
				}
				
			}
private: System::Void cameraCalibrationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 CameraCalibrationFormController::getInstance()->Show();
		 }

private: System::Void browseForVolumeBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 OpenFileDialog^ dialog = gcnew OpenFileDialog;

			 dialog->DefaultExt = "raw";
			 dialog->Filter = "raw files (*.raw)|*.xml|All files (*.*)|*.*";
			 dialog->FilterIndex = 2;
			 dialog->RestoreDirectory = true;

			 if ( dialog->ShowDialog() == ::DialogResult::OK )
			 {
				 this->volumePathTextBox->Text = dialog->FileName;
			 }
		 }

private: System::Void loadVolumeBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->loadVolumeBtn->Enabled = false;
			 this->spinner->Enable = true;

			 this->backgroundWorker1->RunWorkerAsync();
		 }

private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 msclr::interop::marshal_context context;
			 std::string pathBuffer = context.marshal_as<std::string>(this->volumePathTextBox->Text);

			 VolumeRenderManager::getInstance()->loadVolume(pathBuffer.c_str());
		 }

private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 OpenGLView^ view = VolumeRenderManager::getInstance()->createForm();
			 VolumeRenderManager::getInstance()->addVolumeToScene();
			 VolumeRenderManager::getInstance()->Show();
			 view->Invalidate();
			 view->Refresh();

			 this->spinner->Enable = false;
			 this->volumeRemoveBtn->Enabled = true;
		 }
private: System::Void volumeRemoveBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			  this->loadVolumeBtn->Enabled = true;
			  this->volumeRemoveBtn->Enabled = false;
			  VolumeRenderManager::getInstance()->removeVolumeFromScene();

			  VolumeRenderManager::getInstance()->Refresh();
		 }
};
}

