#pragma once

#include "Debug.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <exception>
#include <msclr\marshal_cppstd.h>

#pragma unmanaged
#include "ClientHandler.h"
#include "RigidBody.h"
#pragma managed

#include "CalibrationGrid.h"
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
	private: System::Windows::Forms::TabPage^  SceneTab;



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





	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;





	private: System::Windows::Forms::Label^  flipYZLabel;
	private: System::Windows::Forms::Button^  flipYZBtn;
	private: System::Windows::Forms::GroupBox^  loadVolumeGroupBox;

	private: System::Windows::Forms::Button^  showOpenGLViewBtn;
	private: System::Windows::Forms::Button^  volumeRemoveBtn;
	private: System::Windows::Forms::Button^  loadVolumeBtn;
	private: System::Windows::Forms::Button^  browseForVolumeBtn;
	private: System::Windows::Forms::TextBox^  volumePathTextBox;
	private: System::Windows::Forms::Label^  volumePathLabel;
	private: System::Windows::Forms::GroupBox^  volumePropertiesGroupBox;
	private: System::Windows::Forms::Label^  minIsoValueLabel;
	private: System::Windows::Forms::Label^  minIsoValueTitleLabel;
	private: System::Windows::Forms::TrackBar^  minIsoValueTrackBar;
	private: System::Windows::Forms::Label^  volumeScaleLabel;
	private: System::Windows::Forms::Label^  volumeScaleTitleLabel;
	private: System::Windows::Forms::TrackBar^  volumeScaleTrackBar;
	private: System::Windows::Forms::Label^  positionTitleLabel;
	private: System::Windows::Forms::Label^  positionXLabel;
	private: System::Windows::Forms::Label^  positionXTitleLabel;


	private: System::Windows::Forms::TrackBar^  positionXTrackBar;
	private: System::Windows::Forms::Label^  rotationZLabel;

	private: System::Windows::Forms::Label^  rotationZTitleLabel;
	private: System::Windows::Forms::TrackBar^  rotationZTrackBar;
	private: System::Windows::Forms::Label^  rotationYLabel;



	private: System::Windows::Forms::Label^  rotationYTitleLabel;
private: System::Windows::Forms::TrackBar^  rotationYTrackBar;


private: System::Windows::Forms::Label^  rotationTitleLabel;
private: System::Windows::Forms::Label^  rotationXLabel;


private: System::Windows::Forms::Label^  rotationXTitleLabel;
private: System::Windows::Forms::TrackBar^  rotationXTrackBar;


private: System::Windows::Forms::Label^  positionZLabel;

private: System::Windows::Forms::Label^  positionZTitleLabel;
private: System::Windows::Forms::TrackBar^  positionZTrackBar;
private: System::Windows::Forms::Label^  positionYLabel;



private: System::Windows::Forms::Label^  positionYTitleLabel;
private: System::Windows::Forms::TrackBar^  positionYTrackBar;
private: System::Windows::Forms::GroupBox^  rigidBodyGroupBox;
private: System::Windows::Forms::ListView^  rigidBodyListView;
private: System::Windows::Forms::Label^  volumeSelectedLabel;

private: System::Windows::Forms::Button^  selectRigidBodyAsVolumeBtn;
private: System::Windows::Forms::Label^  volumeSelectLabel;
private: System::Windows::Forms::GroupBox^  dicomConverterGroupBox;
private: System::Windows::Forms::Button^  browseOutputBtn;
private: System::Windows::Forms::TextBox^  outputTextBox;
private: System::Windows::Forms::Label^  pathToOutputLabel;
private: System::Windows::Forms::Button^  convertDICOMBtn;
private: System::Windows::Forms::Button^  browseDICOMBtn;
private: System::Windows::Forms::TextBox^  DICOMTextBox;
private: System::Windows::Forms::Label^  pathToDICOMLabel;
private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
private: System::Windows::Forms::TabPage^  cameraPage;
private: System::Windows::Forms::GroupBox^  cameraGroupBox;
private: System::Windows::Forms::Button^  showGridBtn;
private: System::Windows::Forms::Label^  fovLabel;
private: System::Windows::Forms::Label^  fovTitleLabel;
private: System::Windows::Forms::TrackBar^  fovTrackBar;
private: System::Windows::Forms::Label^  cameraZLabel;
private: System::Windows::Forms::Label^  cameraZTitleLabel;
private: System::Windows::Forms::TrackBar^  cameraZTrackBar;
private: System::Windows::Forms::Label^  cameraYLabel;
private: System::Windows::Forms::Label^  cameraYTitleLabel;
private: System::Windows::Forms::TrackBar^  cameraYTrackBar;
private: System::Windows::Forms::Label^  cameraPositionLabel;
private: System::Windows::Forms::Label^  cameraXLabel;
private: System::Windows::Forms::Label^  cameraXTitleLabel;
private: System::Windows::Forms::TrackBar^  cameraXTrackBar;
private: System::Windows::Forms::Button^  toggleGridBtn;
private: System::Windows::Forms::Label^  gridSelectedLabel;
private: System::Windows::Forms::Button^  selectRigidBodyAsGridBtn;
private: System::Windows::Forms::CheckBox^  useKMatrixCheckBox;
















private: System::Windows::Forms::Label^  kMatrixLabel;

private: System::Windows::Forms::Label^  pPointYLabel;

private: System::Windows::Forms::Label^  pPointYTitleLabel;
private: System::Windows::Forms::TrackBar^  pPointYTrackBar;
private: System::Windows::Forms::Label^  pPointXLabel;



private: System::Windows::Forms::Label^  pPointXTitleLabel;
private: System::Windows::Forms::TrackBar^  pPointXTrackBar;
private: System::Windows::Forms::Label^  skewLabel;



private: System::Windows::Forms::Label^  skewTitleLabel;
private: System::Windows::Forms::TrackBar^  skewTrackBar;
private: System::Windows::Forms::Label^  betaLabel;



private: System::Windows::Forms::Label^  betaTitleLabel;
private: System::Windows::Forms::TrackBar^  betaTrackBar;
private: System::Windows::Forms::Label^  alphaLabel;



private: System::Windows::Forms::Label^  alphaTitleLabel;
private: System::Windows::Forms::TrackBar^  alphaTrackBar;
private: System::Windows::Forms::Label^  farLabel;



private: System::Windows::Forms::Label^  farTitleLabel;
private: System::Windows::Forms::TrackBar^  farTrackBar;
private: System::Windows::Forms::Label^  nearLabel;



private: System::Windows::Forms::Label^  nearTitleLabel;
private: System::Windows::Forms::TrackBar^  nearTrackBar;
















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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
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
			this->flipYZLabel = (gcnew System::Windows::Forms::Label());
			this->flipYZBtn = (gcnew System::Windows::Forms::Button());
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
			this->SceneTab = (gcnew System::Windows::Forms::TabPage());
			this->dicomConverterGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->browseOutputBtn = (gcnew System::Windows::Forms::Button());
			this->outputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->pathToOutputLabel = (gcnew System::Windows::Forms::Label());
			this->convertDICOMBtn = (gcnew System::Windows::Forms::Button());
			this->browseDICOMBtn = (gcnew System::Windows::Forms::Button());
			this->DICOMTextBox = (gcnew System::Windows::Forms::TextBox());
			this->pathToDICOMLabel = (gcnew System::Windows::Forms::Label());
			this->rigidBodyGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->gridSelectedLabel = (gcnew System::Windows::Forms::Label());
			this->selectRigidBodyAsGridBtn = (gcnew System::Windows::Forms::Button());
			this->volumeSelectedLabel = (gcnew System::Windows::Forms::Label());
			this->selectRigidBodyAsVolumeBtn = (gcnew System::Windows::Forms::Button());
			this->volumeSelectLabel = (gcnew System::Windows::Forms::Label());
			this->rigidBodyListView = (gcnew System::Windows::Forms::ListView());
			this->volumePropertiesGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->rotationZLabel = (gcnew System::Windows::Forms::Label());
			this->rotationZTitleLabel = (gcnew System::Windows::Forms::Label());
			this->rotationZTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->rotationYLabel = (gcnew System::Windows::Forms::Label());
			this->rotationYTitleLabel = (gcnew System::Windows::Forms::Label());
			this->rotationYTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->rotationTitleLabel = (gcnew System::Windows::Forms::Label());
			this->rotationXLabel = (gcnew System::Windows::Forms::Label());
			this->rotationXTitleLabel = (gcnew System::Windows::Forms::Label());
			this->rotationXTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->positionZLabel = (gcnew System::Windows::Forms::Label());
			this->positionZTitleLabel = (gcnew System::Windows::Forms::Label());
			this->positionZTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->positionYLabel = (gcnew System::Windows::Forms::Label());
			this->positionYTitleLabel = (gcnew System::Windows::Forms::Label());
			this->positionYTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->positionTitleLabel = (gcnew System::Windows::Forms::Label());
			this->positionXLabel = (gcnew System::Windows::Forms::Label());
			this->positionXTitleLabel = (gcnew System::Windows::Forms::Label());
			this->positionXTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->volumeScaleLabel = (gcnew System::Windows::Forms::Label());
			this->volumeScaleTitleLabel = (gcnew System::Windows::Forms::Label());
			this->volumeScaleTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->minIsoValueLabel = (gcnew System::Windows::Forms::Label());
			this->minIsoValueTitleLabel = (gcnew System::Windows::Forms::Label());
			this->minIsoValueTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->loadVolumeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->showOpenGLViewBtn = (gcnew System::Windows::Forms::Button());
			this->volumeRemoveBtn = (gcnew System::Windows::Forms::Button());
			this->loadVolumeBtn = (gcnew System::Windows::Forms::Button());
			this->browseForVolumeBtn = (gcnew System::Windows::Forms::Button());
			this->volumePathTextBox = (gcnew System::Windows::Forms::TextBox());
			this->volumePathLabel = (gcnew System::Windows::Forms::Label());
			this->cameraPage = (gcnew System::Windows::Forms::TabPage());
			this->cameraGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->farLabel = (gcnew System::Windows::Forms::Label());
			this->farTitleLabel = (gcnew System::Windows::Forms::Label());
			this->farTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->nearLabel = (gcnew System::Windows::Forms::Label());
			this->nearTitleLabel = (gcnew System::Windows::Forms::Label());
			this->nearTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->pPointYLabel = (gcnew System::Windows::Forms::Label());
			this->pPointYTitleLabel = (gcnew System::Windows::Forms::Label());
			this->pPointYTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->pPointXLabel = (gcnew System::Windows::Forms::Label());
			this->pPointXTitleLabel = (gcnew System::Windows::Forms::Label());
			this->pPointXTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->skewLabel = (gcnew System::Windows::Forms::Label());
			this->skewTitleLabel = (gcnew System::Windows::Forms::Label());
			this->skewTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->betaLabel = (gcnew System::Windows::Forms::Label());
			this->betaTitleLabel = (gcnew System::Windows::Forms::Label());
			this->betaTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->alphaLabel = (gcnew System::Windows::Forms::Label());
			this->alphaTitleLabel = (gcnew System::Windows::Forms::Label());
			this->alphaTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->useKMatrixCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->kMatrixLabel = (gcnew System::Windows::Forms::Label());
			this->toggleGridBtn = (gcnew System::Windows::Forms::Button());
			this->cameraZLabel = (gcnew System::Windows::Forms::Label());
			this->cameraZTitleLabel = (gcnew System::Windows::Forms::Label());
			this->cameraZTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->cameraYLabel = (gcnew System::Windows::Forms::Label());
			this->cameraYTitleLabel = (gcnew System::Windows::Forms::Label());
			this->cameraYTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->cameraPositionLabel = (gcnew System::Windows::Forms::Label());
			this->cameraXLabel = (gcnew System::Windows::Forms::Label());
			this->cameraXTitleLabel = (gcnew System::Windows::Forms::Label());
			this->cameraXTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->showGridBtn = (gcnew System::Windows::Forms::Button());
			this->fovLabel = (gcnew System::Windows::Forms::Label());
			this->fovTitleLabel = (gcnew System::Windows::Forms::Label());
			this->fovTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
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
			this->SceneTab->SuspendLayout();
			this->dicomConverterGroupBox->SuspendLayout();
			this->rigidBodyGroupBox->SuspendLayout();
			this->volumePropertiesGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationZTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationYTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationXTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionZTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionYTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionXTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->volumeScaleTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minIsoValueTrackBar))->BeginInit();
			this->loadVolumeGroupBox->SuspendLayout();
			this->cameraPage->SuspendLayout();
			this->cameraGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->farTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nearTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pPointYTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pPointXTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->skewTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->betaTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->alphaTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraZTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraYTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraXTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fovTrackBar))->BeginInit();
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
			this->tabControl->Controls->Add(this->SceneTab);
			this->tabControl->Controls->Add(this->cameraPage);
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
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->flipYZLabel);
			this->optiTrackMainSplitContainer->Panel2->Controls->Add(this->flipYZBtn);
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
			// flipYZLabel
			// 
			this->flipYZLabel->AutoSize = true;
			this->flipYZLabel->BackColor = System::Drawing::Color::Transparent;
			this->flipYZLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->flipYZLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->flipYZLabel->Location = System::Drawing::Point(121, 243);
			this->flipYZLabel->Name = L"flipYZLabel";
			this->flipYZLabel->Size = System::Drawing::Size(41, 13);
			this->flipYZLabel->TabIndex = 45;
			this->flipYZLabel->Text = L"Z is up";
			// 
			// flipYZBtn
			// 
			this->flipYZBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->flipYZBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->flipYZBtn->Location = System::Drawing::Point(9, 239);
			this->flipYZBtn->Name = L"flipYZBtn";
			this->flipYZBtn->Size = System::Drawing::Size(76, 23);
			this->flipYZBtn->TabIndex = 44;
			this->flipYZBtn->Text = L"Flip Y and Z";
			this->flipYZBtn->UseVisualStyleBackColor = false;
			this->flipYZBtn->Click += gcnew System::EventHandler(this, &MainForm::flipYZBtn_Click);
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
			// SceneTab
			// 
			this->SceneTab->BackColor = System::Drawing::Color::WhiteSmoke;
			this->SceneTab->Controls->Add(this->dicomConverterGroupBox);
			this->SceneTab->Controls->Add(this->rigidBodyGroupBox);
			this->SceneTab->Controls->Add(this->volumePropertiesGroupBox);
			this->SceneTab->Controls->Add(this->loadVolumeGroupBox);
			this->SceneTab->Location = System::Drawing::Point(4, 24);
			this->SceneTab->Name = L"SceneTab";
			this->SceneTab->Padding = System::Windows::Forms::Padding(3);
			this->SceneTab->Size = System::Drawing::Size(792, 548);
			this->SceneTab->TabIndex = 1;
			this->SceneTab->Text = L"Scene";
			// 
			// dicomConverterGroupBox
			// 
			this->dicomConverterGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dicomConverterGroupBox->Controls->Add(this->browseOutputBtn);
			this->dicomConverterGroupBox->Controls->Add(this->outputTextBox);
			this->dicomConverterGroupBox->Controls->Add(this->pathToOutputLabel);
			this->dicomConverterGroupBox->Controls->Add(this->convertDICOMBtn);
			this->dicomConverterGroupBox->Controls->Add(this->browseDICOMBtn);
			this->dicomConverterGroupBox->Controls->Add(this->DICOMTextBox);
			this->dicomConverterGroupBox->Controls->Add(this->pathToDICOMLabel);
			this->dicomConverterGroupBox->Location = System::Drawing::Point(331, 6);
			this->dicomConverterGroupBox->Name = L"dicomConverterGroupBox";
			this->dicomConverterGroupBox->Size = System::Drawing::Size(453, 114);
			this->dicomConverterGroupBox->TabIndex = 51;
			this->dicomConverterGroupBox->TabStop = false;
			this->dicomConverterGroupBox->Text = L"DICOM Converter";
			// 
			// browseOutputBtn
			// 
			this->browseOutputBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseOutputBtn->BackColor = System::Drawing::Color::Transparent;
			this->browseOutputBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"browseOutputBtn.BackgroundImage")));
			this->browseOutputBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->browseOutputBtn->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->browseOutputBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->browseOutputBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->browseOutputBtn->Location = System::Drawing::Point(415, 39);
			this->browseOutputBtn->Name = L"browseOutputBtn";
			this->browseOutputBtn->Size = System::Drawing::Size(32, 32);
			this->browseOutputBtn->TabIndex = 57;
			this->browseOutputBtn->UseVisualStyleBackColor = false;
			this->browseOutputBtn->Click += gcnew System::EventHandler(this, &MainForm::browseOutputBtn_Click);
			// 
			// outputTextBox
			// 
			this->outputTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->outputTextBox->Location = System::Drawing::Point(136, 43);
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->Size = System::Drawing::Size(273, 22);
			this->outputTextBox->TabIndex = 56;
			// 
			// pathToOutputLabel
			// 
			this->pathToOutputLabel->AutoSize = true;
			this->pathToOutputLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pathToOutputLabel->Location = System::Drawing::Point(6, 46);
			this->pathToOutputLabel->Name = L"pathToOutputLabel";
			this->pathToOutputLabel->Size = System::Drawing::Size(69, 13);
			this->pathToOutputLabel->TabIndex = 55;
			this->pathToOutputLabel->Text = L"Output File:";
			// 
			// convertDICOMBtn
			// 
			this->convertDICOMBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->convertDICOMBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->convertDICOMBtn->Location = System::Drawing::Point(6, 82);
			this->convertDICOMBtn->Name = L"convertDICOMBtn";
			this->convertDICOMBtn->Size = System::Drawing::Size(76, 23);
			this->convertDICOMBtn->TabIndex = 54;
			this->convertDICOMBtn->Text = L"Convert";
			this->convertDICOMBtn->UseVisualStyleBackColor = false;
			this->convertDICOMBtn->Click += gcnew System::EventHandler(this, &MainForm::convertDICOMBtn_Click);
			// 
			// browseDICOMBtn
			// 
			this->browseDICOMBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseDICOMBtn->BackColor = System::Drawing::Color::Transparent;
			this->browseDICOMBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"browseDICOMBtn.BackgroundImage")));
			this->browseDICOMBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->browseDICOMBtn->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->browseDICOMBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->browseDICOMBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->browseDICOMBtn->Location = System::Drawing::Point(415, 11);
			this->browseDICOMBtn->Name = L"browseDICOMBtn";
			this->browseDICOMBtn->Size = System::Drawing::Size(32, 32);
			this->browseDICOMBtn->TabIndex = 53;
			this->browseDICOMBtn->UseVisualStyleBackColor = false;
			this->browseDICOMBtn->Click += gcnew System::EventHandler(this, &MainForm::browseDICOMBtn_Click);
			// 
			// DICOMTextBox
			// 
			this->DICOMTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->DICOMTextBox->Location = System::Drawing::Point(136, 15);
			this->DICOMTextBox->Name = L"DICOMTextBox";
			this->DICOMTextBox->Size = System::Drawing::Size(273, 22);
			this->DICOMTextBox->TabIndex = 52;
			// 
			// pathToDICOMLabel
			// 
			this->pathToDICOMLabel->AutoSize = true;
			this->pathToDICOMLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pathToDICOMLabel->Location = System::Drawing::Point(6, 18);
			this->pathToDICOMLabel->Name = L"pathToDICOMLabel";
			this->pathToDICOMLabel->Size = System::Drawing::Size(124, 13);
			this->pathToDICOMLabel->TabIndex = 51;
			this->pathToDICOMLabel->Text = L"Path To DICOM Folder:";
			// 
			// rigidBodyGroupBox
			// 
			this->rigidBodyGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->rigidBodyGroupBox->Controls->Add(this->gridSelectedLabel);
			this->rigidBodyGroupBox->Controls->Add(this->selectRigidBodyAsGridBtn);
			this->rigidBodyGroupBox->Controls->Add(this->volumeSelectedLabel);
			this->rigidBodyGroupBox->Controls->Add(this->selectRigidBodyAsVolumeBtn);
			this->rigidBodyGroupBox->Controls->Add(this->volumeSelectLabel);
			this->rigidBodyGroupBox->Controls->Add(this->rigidBodyListView);
			this->rigidBodyGroupBox->Location = System::Drawing::Point(323, 126);
			this->rigidBodyGroupBox->Name = L"rigidBodyGroupBox";
			this->rigidBodyGroupBox->Size = System::Drawing::Size(461, 377);
			this->rigidBodyGroupBox->TabIndex = 50;
			this->rigidBodyGroupBox->TabStop = false;
			this->rigidBodyGroupBox->Text = L"Rigid Body";
			// 
			// gridSelectedLabel
			// 
			this->gridSelectedLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridSelectedLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gridSelectedLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->gridSelectedLabel->Location = System::Drawing::Point(5, 337);
			this->gridSelectedLabel->MaximumSize = System::Drawing::Size(450, 60);
			this->gridSelectedLabel->Name = L"gridSelectedLabel";
			this->gridSelectedLabel->Size = System::Drawing::Size(450, 31);
			this->gridSelectedLabel->TabIndex = 54;
			this->gridSelectedLabel->Text = L"No rigid body is selected to be the grid.";
			this->gridSelectedLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// selectRigidBodyAsGridBtn
			// 
			this->selectRigidBodyAsGridBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->selectRigidBodyAsGridBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->selectRigidBodyAsGridBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->selectRigidBodyAsGridBtn->Location = System::Drawing::Point(120, 303);
			this->selectRigidBodyAsGridBtn->Name = L"selectRigidBodyAsGridBtn";
			this->selectRigidBodyAsGridBtn->Size = System::Drawing::Size(221, 23);
			this->selectRigidBodyAsGridBtn->TabIndex = 53;
			this->selectRigidBodyAsGridBtn->Text = L"Use Selected Rigid Body As Grid";
			this->selectRigidBodyAsGridBtn->UseVisualStyleBackColor = false;
			this->selectRigidBodyAsGridBtn->Click += gcnew System::EventHandler(this, &MainForm::selectRigidBodyAsGridBtn_Click);
			// 
			// volumeSelectedLabel
			// 
			this->volumeSelectedLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->volumeSelectedLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->volumeSelectedLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->volumeSelectedLabel->Location = System::Drawing::Point(5, 269);
			this->volumeSelectedLabel->MaximumSize = System::Drawing::Size(450, 60);
			this->volumeSelectedLabel->Name = L"volumeSelectedLabel";
			this->volumeSelectedLabel->Size = System::Drawing::Size(450, 31);
			this->volumeSelectedLabel->TabIndex = 52;
			this->volumeSelectedLabel->Text = L"No rigid body is selected to be the volume.";
			this->volumeSelectedLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// selectRigidBodyAsVolumeBtn
			// 
			this->selectRigidBodyAsVolumeBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->selectRigidBodyAsVolumeBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->selectRigidBodyAsVolumeBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->selectRigidBodyAsVolumeBtn->Location = System::Drawing::Point(120, 235);
			this->selectRigidBodyAsVolumeBtn->Name = L"selectRigidBodyAsVolumeBtn";
			this->selectRigidBodyAsVolumeBtn->Size = System::Drawing::Size(221, 23);
			this->selectRigidBodyAsVolumeBtn->TabIndex = 51;
			this->selectRigidBodyAsVolumeBtn->Text = L"Use Selected Rigid Body As Volume";
			this->selectRigidBodyAsVolumeBtn->UseVisualStyleBackColor = false;
			this->selectRigidBodyAsVolumeBtn->Click += gcnew System::EventHandler(this, &MainForm::selectRigidBodyAsVolumeBtn_Click);
			// 
			// volumeSelectLabel
			// 
			this->volumeSelectLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->volumeSelectLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->volumeSelectLabel->ForeColor = System::Drawing::SystemColors::MenuText;
			this->volumeSelectLabel->Location = System::Drawing::Point(217, 18);
			this->volumeSelectLabel->Name = L"volumeSelectLabel";
			this->volumeSelectLabel->Size = System::Drawing::Size(239, 209);
			this->volumeSelectLabel->TabIndex = 50;
			this->volumeSelectLabel->Text = resources->GetString(L"volumeSelectLabel.Text");
			// 
			// rigidBodyListView
			// 
			this->rigidBodyListView->Alignment = System::Windows::Forms::ListViewAlignment::Left;
			this->rigidBodyListView->FullRowSelect = true;
			this->rigidBodyListView->LabelWrap = false;
			this->rigidBodyListView->Location = System::Drawing::Point(6, 20);
			this->rigidBodyListView->MultiSelect = false;
			this->rigidBodyListView->Name = L"rigidBodyListView";
			this->rigidBodyListView->Size = System::Drawing::Size(205, 207);
			this->rigidBodyListView->TabIndex = 49;
			this->rigidBodyListView->TileSize = System::Drawing::Size(100, 20);
			this->rigidBodyListView->UseCompatibleStateImageBehavior = false;
			this->rigidBodyListView->View = System::Windows::Forms::View::SmallIcon;
			// 
			// volumePropertiesGroupBox
			// 
			this->volumePropertiesGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->volumePropertiesGroupBox->Controls->Add(this->rotationZLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationZTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationZTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationYLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationYTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationYTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationXLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationXTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->rotationXTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->positionZLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionZTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionZTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->positionYLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionYTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionYTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->positionTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionXLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionXTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->positionXTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->volumeScaleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->volumeScaleTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->volumeScaleTrackBar);
			this->volumePropertiesGroupBox->Controls->Add(this->minIsoValueLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->minIsoValueTitleLabel);
			this->volumePropertiesGroupBox->Controls->Add(this->minIsoValueTrackBar);
			this->volumePropertiesGroupBox->Location = System::Drawing::Point(8, 126);
			this->volumePropertiesGroupBox->Name = L"volumePropertiesGroupBox";
			this->volumePropertiesGroupBox->Size = System::Drawing::Size(312, 414);
			this->volumePropertiesGroupBox->TabIndex = 48;
			this->volumePropertiesGroupBox->TabStop = false;
			this->volumePropertiesGroupBox->Text = L"Volume Properties";
			// 
			// rotationZLabel
			// 
			this->rotationZLabel->AutoSize = true;
			this->rotationZLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationZLabel->Location = System::Drawing::Point(263, 343);
			this->rotationZLabel->Name = L"rotationZLabel";
			this->rotationZLabel->Size = System::Drawing::Size(28, 13);
			this->rotationZLabel->TabIndex = 77;
			this->rotationZLabel->Text = L"0.00";
			// 
			// rotationZTitleLabel
			// 
			this->rotationZTitleLabel->AutoSize = true;
			this->rotationZTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationZTitleLabel->Location = System::Drawing::Point(79, 332);
			this->rotationZTitleLabel->Name = L"rotationZTitleLabel";
			this->rotationZTitleLabel->Size = System::Drawing::Size(16, 13);
			this->rotationZTitleLabel->TabIndex = 76;
			this->rotationZTitleLabel->Text = L"Z:";
			// 
			// rotationZTrackBar
			// 
			this->rotationZTrackBar->LargeChange = 10;
			this->rotationZTrackBar->Location = System::Drawing::Point(102, 332);
			this->rotationZTrackBar->Maximum = 720;
			this->rotationZTrackBar->Minimum = -720;
			this->rotationZTrackBar->Name = L"rotationZTrackBar";
			this->rotationZTrackBar->Size = System::Drawing::Size(158, 45);
			this->rotationZTrackBar->TabIndex = 75;
			this->rotationZTrackBar->TickFrequency = 120;
			this->rotationZTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::rotationZTrackBar_ValueChanged);
			// 
			// rotationYLabel
			// 
			this->rotationYLabel->AutoSize = true;
			this->rotationYLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationYLabel->Location = System::Drawing::Point(263, 297);
			this->rotationYLabel->Name = L"rotationYLabel";
			this->rotationYLabel->Size = System::Drawing::Size(28, 13);
			this->rotationYLabel->TabIndex = 74;
			this->rotationYLabel->Text = L"0.00";
			// 
			// rotationYTitleLabel
			// 
			this->rotationYTitleLabel->AutoSize = true;
			this->rotationYTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationYTitleLabel->Location = System::Drawing::Point(79, 287);
			this->rotationYTitleLabel->Name = L"rotationYTitleLabel";
			this->rotationYTitleLabel->Size = System::Drawing::Size(15, 13);
			this->rotationYTitleLabel->TabIndex = 73;
			this->rotationYTitleLabel->Text = L"Y:";
			// 
			// rotationYTrackBar
			// 
			this->rotationYTrackBar->LargeChange = 10;
			this->rotationYTrackBar->Location = System::Drawing::Point(102, 287);
			this->rotationYTrackBar->Maximum = 720;
			this->rotationYTrackBar->Minimum = -720;
			this->rotationYTrackBar->Name = L"rotationYTrackBar";
			this->rotationYTrackBar->Size = System::Drawing::Size(158, 45);
			this->rotationYTrackBar->TabIndex = 72;
			this->rotationYTrackBar->TickFrequency = 120;
			this->rotationYTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::rotationYTrackBar_ValueChanged);
			// 
			// rotationTitleLabel
			// 
			this->rotationTitleLabel->AutoSize = true;
			this->rotationTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationTitleLabel->Location = System::Drawing::Point(4, 225);
			this->rotationTitleLabel->Name = L"rotationTitleLabel";
			this->rotationTitleLabel->Size = System::Drawing::Size(90, 13);
			this->rotationTitleLabel->TabIndex = 71;
			this->rotationTitleLabel->Text = L"Rotation Offset:";
			// 
			// rotationXLabel
			// 
			this->rotationXLabel->AutoSize = true;
			this->rotationXLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationXLabel->Location = System::Drawing::Point(263, 255);
			this->rotationXLabel->Name = L"rotationXLabel";
			this->rotationXLabel->Size = System::Drawing::Size(28, 13);
			this->rotationXLabel->TabIndex = 70;
			this->rotationXLabel->Text = L"0.00";
			// 
			// rotationXTitleLabel
			// 
			this->rotationXTitleLabel->AutoSize = true;
			this->rotationXTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->rotationXTitleLabel->Location = System::Drawing::Point(80, 245);
			this->rotationXTitleLabel->Name = L"rotationXTitleLabel";
			this->rotationXTitleLabel->Size = System::Drawing::Size(16, 13);
			this->rotationXTitleLabel->TabIndex = 69;
			this->rotationXTitleLabel->Text = L"X:";
			// 
			// rotationXTrackBar
			// 
			this->rotationXTrackBar->LargeChange = 10;
			this->rotationXTrackBar->Location = System::Drawing::Point(102, 245);
			this->rotationXTrackBar->Maximum = 720;
			this->rotationXTrackBar->Minimum = -720;
			this->rotationXTrackBar->Name = L"rotationXTrackBar";
			this->rotationXTrackBar->Size = System::Drawing::Size(158, 45);
			this->rotationXTrackBar->TabIndex = 68;
			this->rotationXTrackBar->TickFrequency = 120;
			this->rotationXTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::rotationXTrackBar_ValueChanged);
			// 
			// positionZLabel
			// 
			this->positionZLabel->AutoSize = true;
			this->positionZLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionZLabel->Location = System::Drawing::Point(263, 207);
			this->positionZLabel->Name = L"positionZLabel";
			this->positionZLabel->Size = System::Drawing::Size(46, 13);
			this->positionZLabel->TabIndex = 67;
			this->positionZLabel->Text = L"0.000 m";
			// 
			// positionZTitleLabel
			// 
			this->positionZTitleLabel->AutoSize = true;
			this->positionZTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionZTitleLabel->Location = System::Drawing::Point(79, 196);
			this->positionZTitleLabel->Name = L"positionZTitleLabel";
			this->positionZTitleLabel->Size = System::Drawing::Size(16, 13);
			this->positionZTitleLabel->TabIndex = 66;
			this->positionZTitleLabel->Text = L"Z:";
			// 
			// positionZTrackBar
			// 
			this->positionZTrackBar->LargeChange = 1000;
			this->positionZTrackBar->Location = System::Drawing::Point(102, 196);
			this->positionZTrackBar->Maximum = 5000;
			this->positionZTrackBar->Minimum = -5000;
			this->positionZTrackBar->Name = L"positionZTrackBar";
			this->positionZTrackBar->Size = System::Drawing::Size(158, 45);
			this->positionZTrackBar->TabIndex = 65;
			this->positionZTrackBar->TickFrequency = 1000;
			this->positionZTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::positionZTrackBar_ValueChanged);
			// 
			// positionYLabel
			// 
			this->positionYLabel->AutoSize = true;
			this->positionYLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionYLabel->Location = System::Drawing::Point(263, 161);
			this->positionYLabel->Name = L"positionYLabel";
			this->positionYLabel->Size = System::Drawing::Size(46, 13);
			this->positionYLabel->TabIndex = 64;
			this->positionYLabel->Text = L"0.000 m";
			// 
			// positionYTitleLabel
			// 
			this->positionYTitleLabel->AutoSize = true;
			this->positionYTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionYTitleLabel->Location = System::Drawing::Point(79, 151);
			this->positionYTitleLabel->Name = L"positionYTitleLabel";
			this->positionYTitleLabel->Size = System::Drawing::Size(15, 13);
			this->positionYTitleLabel->TabIndex = 63;
			this->positionYTitleLabel->Text = L"Y:";
			// 
			// positionYTrackBar
			// 
			this->positionYTrackBar->LargeChange = 1000;
			this->positionYTrackBar->Location = System::Drawing::Point(102, 151);
			this->positionYTrackBar->Maximum = 5000;
			this->positionYTrackBar->Minimum = -5000;
			this->positionYTrackBar->Name = L"positionYTrackBar";
			this->positionYTrackBar->Size = System::Drawing::Size(158, 45);
			this->positionYTrackBar->TabIndex = 62;
			this->positionYTrackBar->TickFrequency = 1000;
			this->positionYTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::positionYTrackBar_ValueChanged);
			// 
			// positionTitleLabel
			// 
			this->positionTitleLabel->AutoSize = true;
			this->positionTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionTitleLabel->Location = System::Drawing::Point(9, 90);
			this->positionTitleLabel->Name = L"positionTitleLabel";
			this->positionTitleLabel->Size = System::Drawing::Size(87, 13);
			this->positionTitleLabel->TabIndex = 61;
			this->positionTitleLabel->Text = L"Position Offset:";
			// 
			// positionXLabel
			// 
			this->positionXLabel->AutoSize = true;
			this->positionXLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionXLabel->Location = System::Drawing::Point(263, 119);
			this->positionXLabel->Name = L"positionXLabel";
			this->positionXLabel->Size = System::Drawing::Size(46, 13);
			this->positionXLabel->TabIndex = 60;
			this->positionXLabel->Text = L"0.000 m";
			// 
			// positionXTitleLabel
			// 
			this->positionXTitleLabel->AutoSize = true;
			this->positionXTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->positionXTitleLabel->Location = System::Drawing::Point(80, 109);
			this->positionXTitleLabel->Name = L"positionXTitleLabel";
			this->positionXTitleLabel->Size = System::Drawing::Size(16, 13);
			this->positionXTitleLabel->TabIndex = 59;
			this->positionXTitleLabel->Text = L"X:";
			// 
			// positionXTrackBar
			// 
			this->positionXTrackBar->LargeChange = 1000;
			this->positionXTrackBar->Location = System::Drawing::Point(102, 109);
			this->positionXTrackBar->Maximum = 5000;
			this->positionXTrackBar->Minimum = -5000;
			this->positionXTrackBar->Name = L"positionXTrackBar";
			this->positionXTrackBar->Size = System::Drawing::Size(158, 45);
			this->positionXTrackBar->TabIndex = 58;
			this->positionXTrackBar->TickFrequency = 1000;
			this->positionXTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::positionXTrackBar_ValueChanged);
			// 
			// volumeScaleLabel
			// 
			this->volumeScaleLabel->AutoSize = true;
			this->volumeScaleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->volumeScaleLabel->Location = System::Drawing::Point(263, 68);
			this->volumeScaleLabel->Name = L"volumeScaleLabel";
			this->volumeScaleLabel->Size = System::Drawing::Size(46, 13);
			this->volumeScaleLabel->TabIndex = 57;
			this->volumeScaleLabel->Text = L"1.000 m";
			// 
			// volumeScaleTitleLabel
			// 
			this->volumeScaleTitleLabel->AutoSize = true;
			this->volumeScaleTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->volumeScaleTitleLabel->Location = System::Drawing::Point(60, 58);
			this->volumeScaleTitleLabel->Name = L"volumeScaleTitleLabel";
			this->volumeScaleTitleLabel->Size = System::Drawing::Size(36, 13);
			this->volumeScaleTitleLabel->TabIndex = 56;
			this->volumeScaleTitleLabel->Text = L"Scale:";
			// 
			// volumeScaleTrackBar
			// 
			this->volumeScaleTrackBar->LargeChange = 1000;
			this->volumeScaleTrackBar->Location = System::Drawing::Point(102, 58);
			this->volumeScaleTrackBar->Maximum = 5000;
			this->volumeScaleTrackBar->Minimum = 1;
			this->volumeScaleTrackBar->Name = L"volumeScaleTrackBar";
			this->volumeScaleTrackBar->Size = System::Drawing::Size(158, 45);
			this->volumeScaleTrackBar->TabIndex = 55;
			this->volumeScaleTrackBar->TickFrequency = 1000;
			this->volumeScaleTrackBar->Value = 1000;
			this->volumeScaleTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::volumeScaleTrackBar_ValueChanged);
			// 
			// minIsoValueLabel
			// 
			this->minIsoValueLabel->AutoSize = true;
			this->minIsoValueLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->minIsoValueLabel->Location = System::Drawing::Point(263, 28);
			this->minIsoValueLabel->Name = L"minIsoValueLabel";
			this->minIsoValueLabel->Size = System::Drawing::Size(22, 13);
			this->minIsoValueLabel->TabIndex = 54;
			this->minIsoValueLabel->Text = L"0.0";
			// 
			// minIsoValueTitleLabel
			// 
			this->minIsoValueTitleLabel->AutoSize = true;
			this->minIsoValueTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->minIsoValueTitleLabel->Location = System::Drawing::Point(19, 18);
			this->minIsoValueTitleLabel->Name = L"minIsoValueTitleLabel";
			this->minIsoValueTitleLabel->Size = System::Drawing::Size(77, 13);
			this->minIsoValueTitleLabel->TabIndex = 53;
			this->minIsoValueTitleLabel->Text = L"Min IsoValue:";
			// 
			// minIsoValueTrackBar
			// 
			this->minIsoValueTrackBar->LargeChange = 100;
			this->minIsoValueTrackBar->Location = System::Drawing::Point(102, 18);
			this->minIsoValueTrackBar->Maximum = 1000;
			this->minIsoValueTrackBar->Name = L"minIsoValueTrackBar";
			this->minIsoValueTrackBar->Size = System::Drawing::Size(158, 45);
			this->minIsoValueTrackBar->TabIndex = 0;
			this->minIsoValueTrackBar->TickFrequency = 100;
			this->minIsoValueTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::minIsoValueTrackBar_ValueChanged);
			// 
			// loadVolumeGroupBox
			// 
			this->loadVolumeGroupBox->Controls->Add(this->showOpenGLViewBtn);
			this->loadVolumeGroupBox->Controls->Add(this->volumeRemoveBtn);
			this->loadVolumeGroupBox->Controls->Add(this->loadVolumeBtn);
			this->loadVolumeGroupBox->Controls->Add(this->browseForVolumeBtn);
			this->loadVolumeGroupBox->Controls->Add(this->volumePathTextBox);
			this->loadVolumeGroupBox->Controls->Add(this->volumePathLabel);
			this->loadVolumeGroupBox->Location = System::Drawing::Point(8, 6);
			this->loadVolumeGroupBox->Name = L"loadVolumeGroupBox";
			this->loadVolumeGroupBox->Size = System::Drawing::Size(312, 114);
			this->loadVolumeGroupBox->TabIndex = 47;
			this->loadVolumeGroupBox->TabStop = false;
			this->loadVolumeGroupBox->Text = L"Load Volume";
			// 
			// showOpenGLViewBtn
			// 
			this->showOpenGLViewBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->showOpenGLViewBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->showOpenGLViewBtn->Location = System::Drawing::Point(8, 82);
			this->showOpenGLViewBtn->Name = L"showOpenGLViewBtn";
			this->showOpenGLViewBtn->Size = System::Drawing::Size(76, 23);
			this->showOpenGLViewBtn->TabIndex = 52;
			this->showOpenGLViewBtn->Text = L"Show View";
			this->showOpenGLViewBtn->UseVisualStyleBackColor = false;
			this->showOpenGLViewBtn->Click += gcnew System::EventHandler(this, &MainForm::showOpenGLViewBtn_Click);
			// 
			// volumeRemoveBtn
			// 
			this->volumeRemoveBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->volumeRemoveBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->volumeRemoveBtn->Location = System::Drawing::Point(222, 53);
			this->volumeRemoveBtn->Name = L"volumeRemoveBtn";
			this->volumeRemoveBtn->Size = System::Drawing::Size(76, 23);
			this->volumeRemoveBtn->TabIndex = 51;
			this->volumeRemoveBtn->Text = L"Remove";
			this->volumeRemoveBtn->UseVisualStyleBackColor = false;
			this->volumeRemoveBtn->Click += gcnew System::EventHandler(this, &MainForm::volumeRemoveBtn_Click);
			// 
			// loadVolumeBtn
			// 
			this->loadVolumeBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->loadVolumeBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->loadVolumeBtn->Location = System::Drawing::Point(8, 53);
			this->loadVolumeBtn->Name = L"loadVolumeBtn";
			this->loadVolumeBtn->Size = System::Drawing::Size(76, 23);
			this->loadVolumeBtn->TabIndex = 50;
			this->loadVolumeBtn->Text = L"Load";
			this->loadVolumeBtn->UseVisualStyleBackColor = false;
			this->loadVolumeBtn->Click += gcnew System::EventHandler(this, &MainForm::loadVolumeBtn_Click);
			// 
			// browseForVolumeBtn
			// 
			this->browseForVolumeBtn->BackColor = System::Drawing::Color::Transparent;
			this->browseForVolumeBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"browseForVolumeBtn.BackgroundImage")));
			this->browseForVolumeBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->browseForVolumeBtn->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->browseForVolumeBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->browseForVolumeBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->browseForVolumeBtn->Location = System::Drawing::Point(266, 11);
			this->browseForVolumeBtn->Name = L"browseForVolumeBtn";
			this->browseForVolumeBtn->Size = System::Drawing::Size(32, 32);
			this->browseForVolumeBtn->TabIndex = 49;
			this->browseForVolumeBtn->UseVisualStyleBackColor = false;
			this->browseForVolumeBtn->Click += gcnew System::EventHandler(this, &MainForm::browseForVolumeBtn_Click);
			// 
			// volumePathTextBox
			// 
			this->volumePathTextBox->Location = System::Drawing::Point(102, 15);
			this->volumePathTextBox->Name = L"volumePathTextBox";
			this->volumePathTextBox->Size = System::Drawing::Size(158, 22);
			this->volumePathTextBox->TabIndex = 48;
			// 
			// volumePathLabel
			// 
			this->volumePathLabel->AutoSize = true;
			this->volumePathLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->volumePathLabel->Location = System::Drawing::Point(6, 18);
			this->volumePathLabel->Name = L"volumePathLabel";
			this->volumePathLabel->Size = System::Drawing::Size(90, 13);
			this->volumePathLabel->TabIndex = 47;
			this->volumePathLabel->Text = L"Path To Volume:";
			// 
			// cameraPage
			// 
			this->cameraPage->Controls->Add(this->cameraGroupBox);
			this->cameraPage->Location = System::Drawing::Point(4, 24);
			this->cameraPage->Name = L"cameraPage";
			this->cameraPage->Padding = System::Windows::Forms::Padding(3);
			this->cameraPage->Size = System::Drawing::Size(792, 548);
			this->cameraPage->TabIndex = 2;
			this->cameraPage->Text = L"Camera";
			this->cameraPage->UseVisualStyleBackColor = true;
			// 
			// cameraGroupBox
			// 
			this->cameraGroupBox->Controls->Add(this->farLabel);
			this->cameraGroupBox->Controls->Add(this->farTitleLabel);
			this->cameraGroupBox->Controls->Add(this->farTrackBar);
			this->cameraGroupBox->Controls->Add(this->nearLabel);
			this->cameraGroupBox->Controls->Add(this->nearTitleLabel);
			this->cameraGroupBox->Controls->Add(this->nearTrackBar);
			this->cameraGroupBox->Controls->Add(this->pPointYLabel);
			this->cameraGroupBox->Controls->Add(this->pPointYTitleLabel);
			this->cameraGroupBox->Controls->Add(this->pPointYTrackBar);
			this->cameraGroupBox->Controls->Add(this->pPointXLabel);
			this->cameraGroupBox->Controls->Add(this->pPointXTitleLabel);
			this->cameraGroupBox->Controls->Add(this->pPointXTrackBar);
			this->cameraGroupBox->Controls->Add(this->skewLabel);
			this->cameraGroupBox->Controls->Add(this->skewTitleLabel);
			this->cameraGroupBox->Controls->Add(this->skewTrackBar);
			this->cameraGroupBox->Controls->Add(this->betaLabel);
			this->cameraGroupBox->Controls->Add(this->betaTitleLabel);
			this->cameraGroupBox->Controls->Add(this->betaTrackBar);
			this->cameraGroupBox->Controls->Add(this->alphaLabel);
			this->cameraGroupBox->Controls->Add(this->alphaTitleLabel);
			this->cameraGroupBox->Controls->Add(this->alphaTrackBar);
			this->cameraGroupBox->Controls->Add(this->useKMatrixCheckBox);
			this->cameraGroupBox->Controls->Add(this->kMatrixLabel);
			this->cameraGroupBox->Controls->Add(this->toggleGridBtn);
			this->cameraGroupBox->Controls->Add(this->cameraZLabel);
			this->cameraGroupBox->Controls->Add(this->cameraZTitleLabel);
			this->cameraGroupBox->Controls->Add(this->cameraZTrackBar);
			this->cameraGroupBox->Controls->Add(this->cameraYLabel);
			this->cameraGroupBox->Controls->Add(this->cameraYTitleLabel);
			this->cameraGroupBox->Controls->Add(this->cameraYTrackBar);
			this->cameraGroupBox->Controls->Add(this->cameraPositionLabel);
			this->cameraGroupBox->Controls->Add(this->cameraXLabel);
			this->cameraGroupBox->Controls->Add(this->cameraXTitleLabel);
			this->cameraGroupBox->Controls->Add(this->cameraXTrackBar);
			this->cameraGroupBox->Controls->Add(this->showGridBtn);
			this->cameraGroupBox->Controls->Add(this->fovLabel);
			this->cameraGroupBox->Controls->Add(this->fovTitleLabel);
			this->cameraGroupBox->Controls->Add(this->fovTrackBar);
			this->cameraGroupBox->Location = System::Drawing::Point(3, 6);
			this->cameraGroupBox->Name = L"cameraGroupBox";
			this->cameraGroupBox->Size = System::Drawing::Size(781, 381);
			this->cameraGroupBox->TabIndex = 53;
			this->cameraGroupBox->TabStop = false;
			this->cameraGroupBox->Text = L"Camera";
			// 
			// farLabel
			// 
			this->farLabel->AutoSize = true;
			this->farLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->farLabel->Location = System::Drawing::Point(277, 337);
			this->farLabel->Name = L"farLabel";
			this->farLabel->Size = System::Drawing::Size(40, 13);
			this->farLabel->TabIndex = 119;
			this->farLabel->Text = L"100.00";
			// 
			// farTitleLabel
			// 
			this->farTitleLabel->AutoSize = true;
			this->farTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->farTitleLabel->Location = System::Drawing::Point(73, 326);
			this->farTitleLabel->Name = L"farTitleLabel";
			this->farTitleLabel->Size = System::Drawing::Size(24, 13);
			this->farTitleLabel->TabIndex = 118;
			this->farTitleLabel->Text = L"far:";
			// 
			// farTrackBar
			// 
			this->farTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->farTrackBar->LargeChange = 100;
			this->farTrackBar->Location = System::Drawing::Point(116, 326);
			this->farTrackBar->Maximum = 100000;
			this->farTrackBar->Name = L"farTrackBar";
			this->farTrackBar->Size = System::Drawing::Size(158, 45);
			this->farTrackBar->TabIndex = 117;
			this->farTrackBar->TickFrequency = 10000;
			this->farTrackBar->Value = 10000;
			this->farTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::farTrackBar_ValueChanged);
			// 
			// nearLabel
			// 
			this->nearLabel->AutoSize = true;
			this->nearLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->nearLabel->Location = System::Drawing::Point(277, 297);
			this->nearLabel->Name = L"nearLabel";
			this->nearLabel->Size = System::Drawing::Size(28, 13);
			this->nearLabel->TabIndex = 116;
			this->nearLabel->Text = L"0.10";
			// 
			// nearTitleLabel
			// 
			this->nearTitleLabel->AutoSize = true;
			this->nearTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->nearTitleLabel->Location = System::Drawing::Point(64, 286);
			this->nearTitleLabel->Name = L"nearTitleLabel";
			this->nearTitleLabel->Size = System::Drawing::Size(33, 13);
			this->nearTitleLabel->TabIndex = 115;
			this->nearTitleLabel->Text = L"near:";
			// 
			// nearTrackBar
			// 
			this->nearTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->nearTrackBar->LargeChange = 100;
			this->nearTrackBar->Location = System::Drawing::Point(116, 286);
			this->nearTrackBar->Maximum = 100000;
			this->nearTrackBar->Name = L"nearTrackBar";
			this->nearTrackBar->Size = System::Drawing::Size(158, 45);
			this->nearTrackBar->TabIndex = 114;
			this->nearTrackBar->TickFrequency = 10000;
			this->nearTrackBar->Value = 100;
			this->nearTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::nearTrackBar_ValueChanged);
			// 
			// pPointYLabel
			// 
			this->pPointYLabel->AutoSize = true;
			this->pPointYLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pPointYLabel->Location = System::Drawing::Point(277, 259);
			this->pPointYLabel->Name = L"pPointYLabel";
			this->pPointYLabel->Size = System::Drawing::Size(34, 13);
			this->pPointYLabel->TabIndex = 113;
			this->pPointYLabel->Text = L"0.000";
			// 
			// pPointYTitleLabel
			// 
			this->pPointYTitleLabel->AutoSize = true;
			this->pPointYTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pPointYTitleLabel->Location = System::Drawing::Point(3, 248);
			this->pPointYTitleLabel->Name = L"pPointYTitleLabel";
			this->pPointYTitleLabel->Size = System::Drawing::Size(94, 13);
			this->pPointYTitleLabel->TabIndex = 112;
			this->pPointYTitleLabel->Text = L"principal point y:";
			// 
			// pPointYTrackBar
			// 
			this->pPointYTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->pPointYTrackBar->LargeChange = 1000;
			this->pPointYTrackBar->Location = System::Drawing::Point(116, 248);
			this->pPointYTrackBar->Maximum = 20000;
			this->pPointYTrackBar->Minimum = -20000;
			this->pPointYTrackBar->Name = L"pPointYTrackBar";
			this->pPointYTrackBar->Size = System::Drawing::Size(158, 45);
			this->pPointYTrackBar->TabIndex = 111;
			this->pPointYTrackBar->TickFrequency = 1000;
			this->pPointYTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::pPointYTrackBar_ValueChanged);
			// 
			// pPointXLabel
			// 
			this->pPointXLabel->AutoSize = true;
			this->pPointXLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pPointXLabel->Location = System::Drawing::Point(280, 220);
			this->pPointXLabel->Name = L"pPointXLabel";
			this->pPointXLabel->Size = System::Drawing::Size(34, 13);
			this->pPointXLabel->TabIndex = 110;
			this->pPointXLabel->Text = L"0.000";
			// 
			// pPointXTitleLabel
			// 
			this->pPointXTitleLabel->AutoSize = true;
			this->pPointXTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->pPointXTitleLabel->Location = System::Drawing::Point(6, 209);
			this->pPointXTitleLabel->Name = L"pPointXTitleLabel";
			this->pPointXTitleLabel->Size = System::Drawing::Size(94, 13);
			this->pPointXTitleLabel->TabIndex = 109;
			this->pPointXTitleLabel->Text = L"principal point x:";
			// 
			// pPointXTrackBar
			// 
			this->pPointXTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->pPointXTrackBar->LargeChange = 1000;
			this->pPointXTrackBar->Location = System::Drawing::Point(119, 209);
			this->pPointXTrackBar->Maximum = 20000;
			this->pPointXTrackBar->Minimum = -20000;
			this->pPointXTrackBar->Name = L"pPointXTrackBar";
			this->pPointXTrackBar->Size = System::Drawing::Size(158, 45);
			this->pPointXTrackBar->TabIndex = 108;
			this->pPointXTrackBar->TickFrequency = 1000;
			this->pPointXTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::pPointXTrackBar_ValueChanged);
			// 
			// skewLabel
			// 
			this->skewLabel->AutoSize = true;
			this->skewLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->skewLabel->Location = System::Drawing::Point(280, 179);
			this->skewLabel->Name = L"skewLabel";
			this->skewLabel->Size = System::Drawing::Size(34, 13);
			this->skewLabel->TabIndex = 107;
			this->skewLabel->Text = L"0.000";
			// 
			// skewTitleLabel
			// 
			this->skewTitleLabel->AutoSize = true;
			this->skewTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->skewTitleLabel->Location = System::Drawing::Point(64, 168);
			this->skewTitleLabel->Name = L"skewTitleLabel";
			this->skewTitleLabel->Size = System::Drawing::Size(36, 13);
			this->skewTitleLabel->TabIndex = 106;
			this->skewTitleLabel->Text = L"skew:";
			// 
			// skewTrackBar
			// 
			this->skewTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->skewTrackBar->LargeChange = 1000;
			this->skewTrackBar->Location = System::Drawing::Point(119, 168);
			this->skewTrackBar->Maximum = 20000;
			this->skewTrackBar->Minimum = -20000;
			this->skewTrackBar->Name = L"skewTrackBar";
			this->skewTrackBar->Size = System::Drawing::Size(158, 45);
			this->skewTrackBar->TabIndex = 105;
			this->skewTrackBar->TickFrequency = 1000;
			this->skewTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::skewTrackBar_ValueChanged);
			// 
			// betaLabel
			// 
			this->betaLabel->AutoSize = true;
			this->betaLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->betaLabel->Location = System::Drawing::Point(280, 133);
			this->betaLabel->Name = L"betaLabel";
			this->betaLabel->Size = System::Drawing::Size(34, 13);
			this->betaLabel->TabIndex = 104;
			this->betaLabel->Text = L"1.000";
			// 
			// betaTitleLabel
			// 
			this->betaTitleLabel->AutoSize = true;
			this->betaTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->betaTitleLabel->Location = System::Drawing::Point(67, 126);
			this->betaTitleLabel->Name = L"betaTitleLabel";
			this->betaTitleLabel->Size = System::Drawing::Size(33, 13);
			this->betaTitleLabel->TabIndex = 103;
			this->betaTitleLabel->Text = L"beta:";
			// 
			// betaTrackBar
			// 
			this->betaTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->betaTrackBar->LargeChange = 1000;
			this->betaTrackBar->Location = System::Drawing::Point(119, 123);
			this->betaTrackBar->Maximum = 20000;
			this->betaTrackBar->Minimum = -20000;
			this->betaTrackBar->Name = L"betaTrackBar";
			this->betaTrackBar->Size = System::Drawing::Size(158, 45);
			this->betaTrackBar->TabIndex = 102;
			this->betaTrackBar->TickFrequency = 1000;
			this->betaTrackBar->Value = 1000;
			this->betaTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::betaTrackBar_ValueChanged);
			// 
			// alphaLabel
			// 
			this->alphaLabel->AutoSize = true;
			this->alphaLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->alphaLabel->Location = System::Drawing::Point(280, 91);
			this->alphaLabel->Name = L"alphaLabel";
			this->alphaLabel->Size = System::Drawing::Size(34, 13);
			this->alphaLabel->TabIndex = 101;
			this->alphaLabel->Text = L"1.000";
			// 
			// alphaTitleLabel
			// 
			this->alphaTitleLabel->AutoSize = true;
			this->alphaTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->alphaTitleLabel->Location = System::Drawing::Point(67, 81);
			this->alphaTitleLabel->Name = L"alphaTitleLabel";
			this->alphaTitleLabel->Size = System::Drawing::Size(39, 13);
			this->alphaTitleLabel->TabIndex = 100;
			this->alphaTitleLabel->Text = L"alpha:";
			// 
			// alphaTrackBar
			// 
			this->alphaTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->alphaTrackBar->LargeChange = 1000;
			this->alphaTrackBar->Location = System::Drawing::Point(119, 81);
			this->alphaTrackBar->Maximum = 20000;
			this->alphaTrackBar->Minimum = -20000;
			this->alphaTrackBar->Name = L"alphaTrackBar";
			this->alphaTrackBar->Size = System::Drawing::Size(158, 45);
			this->alphaTrackBar->TabIndex = 99;
			this->alphaTrackBar->TickFrequency = 1000;
			this->alphaTrackBar->Value = 1000;
			this->alphaTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::alphaTrackBar_ValueChanged);
			// 
			// useKMatrixCheckBox
			// 
			this->useKMatrixCheckBox->ForeColor = System::Drawing::SystemColors::MenuText;
			this->useKMatrixCheckBox->Location = System::Drawing::Point(433, 210);
			this->useKMatrixCheckBox->Name = L"useKMatrixCheckBox";
			this->useKMatrixCheckBox->Size = System::Drawing::Size(110, 34);
			this->useKMatrixCheckBox->TabIndex = 97;
			this->useKMatrixCheckBox->Text = L"Use K Matrix";
			this->useKMatrixCheckBox->UseVisualStyleBackColor = true;
			this->useKMatrixCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::useKMatrixCheckBox_CheckedChanged);
			// 
			// kMatrixLabel
			// 
			this->kMatrixLabel->AutoSize = true;
			this->kMatrixLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->kMatrixLabel->Location = System::Drawing::Point(6, 50);
			this->kMatrixLabel->Name = L"kMatrixLabel";
			this->kMatrixLabel->Size = System::Drawing::Size(51, 13);
			this->kMatrixLabel->TabIndex = 79;
			this->kMatrixLabel->Text = L"K Matrix:";
			// 
			// toggleGridBtn
			// 
			this->toggleGridBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->toggleGridBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->toggleGridBtn->Location = System::Drawing::Point(563, 175);
			this->toggleGridBtn->Name = L"toggleGridBtn";
			this->toggleGridBtn->Size = System::Drawing::Size(76, 23);
			this->toggleGridBtn->TabIndex = 78;
			this->toggleGridBtn->Text = L"Toggle Grid";
			this->toggleGridBtn->UseVisualStyleBackColor = false;
			this->toggleGridBtn->Click += gcnew System::EventHandler(this, &MainForm::toggleGridBtn_Click);
			// 
			// cameraZLabel
			// 
			this->cameraZLabel->AutoSize = true;
			this->cameraZLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraZLabel->Location = System::Drawing::Point(614, 135);
			this->cameraZLabel->Name = L"cameraZLabel";
			this->cameraZLabel->Size = System::Drawing::Size(50, 13);
			this->cameraZLabel->TabIndex = 77;
			this->cameraZLabel->Text = L"-1.000 m";
			// 
			// cameraZTitleLabel
			// 
			this->cameraZTitleLabel->AutoSize = true;
			this->cameraZTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraZTitleLabel->Location = System::Drawing::Point(430, 124);
			this->cameraZTitleLabel->Name = L"cameraZTitleLabel";
			this->cameraZTitleLabel->Size = System::Drawing::Size(16, 13);
			this->cameraZTitleLabel->TabIndex = 76;
			this->cameraZTitleLabel->Text = L"Z:";
			// 
			// cameraZTrackBar
			// 
			this->cameraZTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->cameraZTrackBar->LargeChange = 1000;
			this->cameraZTrackBar->Location = System::Drawing::Point(453, 124);
			this->cameraZTrackBar->Maximum = 5000;
			this->cameraZTrackBar->Minimum = -5000;
			this->cameraZTrackBar->Name = L"cameraZTrackBar";
			this->cameraZTrackBar->Size = System::Drawing::Size(158, 45);
			this->cameraZTrackBar->TabIndex = 75;
			this->cameraZTrackBar->TickFrequency = 1000;
			this->cameraZTrackBar->Value = -1000;
			this->cameraZTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::cameraZTrackBar_ValueChanged);
			// 
			// cameraYLabel
			// 
			this->cameraYLabel->AutoSize = true;
			this->cameraYLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraYLabel->Location = System::Drawing::Point(614, 89);
			this->cameraYLabel->Name = L"cameraYLabel";
			this->cameraYLabel->Size = System::Drawing::Size(46, 13);
			this->cameraYLabel->TabIndex = 74;
			this->cameraYLabel->Text = L"0.000 m";
			// 
			// cameraYTitleLabel
			// 
			this->cameraYTitleLabel->AutoSize = true;
			this->cameraYTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraYTitleLabel->Location = System::Drawing::Point(430, 79);
			this->cameraYTitleLabel->Name = L"cameraYTitleLabel";
			this->cameraYTitleLabel->Size = System::Drawing::Size(15, 13);
			this->cameraYTitleLabel->TabIndex = 73;
			this->cameraYTitleLabel->Text = L"Y:";
			// 
			// cameraYTrackBar
			// 
			this->cameraYTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->cameraYTrackBar->LargeChange = 1000;
			this->cameraYTrackBar->Location = System::Drawing::Point(453, 79);
			this->cameraYTrackBar->Maximum = 5000;
			this->cameraYTrackBar->Minimum = -5000;
			this->cameraYTrackBar->Name = L"cameraYTrackBar";
			this->cameraYTrackBar->Size = System::Drawing::Size(158, 45);
			this->cameraYTrackBar->TabIndex = 72;
			this->cameraYTrackBar->TickFrequency = 1000;
			this->cameraYTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::cameraYTrackBar_ValueChanged);
			// 
			// cameraPositionLabel
			// 
			this->cameraPositionLabel->AutoSize = true;
			this->cameraPositionLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraPositionLabel->Location = System::Drawing::Point(360, 18);
			this->cameraPositionLabel->Name = L"cameraPositionLabel";
			this->cameraPositionLabel->Size = System::Drawing::Size(87, 13);
			this->cameraPositionLabel->TabIndex = 71;
			this->cameraPositionLabel->Text = L"Position Offset:";
			// 
			// cameraXLabel
			// 
			this->cameraXLabel->AutoSize = true;
			this->cameraXLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraXLabel->Location = System::Drawing::Point(614, 47);
			this->cameraXLabel->Name = L"cameraXLabel";
			this->cameraXLabel->Size = System::Drawing::Size(46, 13);
			this->cameraXLabel->TabIndex = 70;
			this->cameraXLabel->Text = L"0.000 m";
			// 
			// cameraXTitleLabel
			// 
			this->cameraXTitleLabel->AutoSize = true;
			this->cameraXTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->cameraXTitleLabel->Location = System::Drawing::Point(431, 37);
			this->cameraXTitleLabel->Name = L"cameraXTitleLabel";
			this->cameraXTitleLabel->Size = System::Drawing::Size(16, 13);
			this->cameraXTitleLabel->TabIndex = 69;
			this->cameraXTitleLabel->Text = L"X:";
			// 
			// cameraXTrackBar
			// 
			this->cameraXTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->cameraXTrackBar->LargeChange = 1000;
			this->cameraXTrackBar->Location = System::Drawing::Point(453, 37);
			this->cameraXTrackBar->Maximum = 5000;
			this->cameraXTrackBar->Minimum = -5000;
			this->cameraXTrackBar->Name = L"cameraXTrackBar";
			this->cameraXTrackBar->Size = System::Drawing::Size(158, 45);
			this->cameraXTrackBar->TabIndex = 68;
			this->cameraXTrackBar->TickFrequency = 1000;
			this->cameraXTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::cameraXTrackBar_ValueChanged);
			// 
			// showGridBtn
			// 
			this->showGridBtn->BackColor = System::Drawing::Color::Gainsboro;
			this->showGridBtn->ForeColor = System::Drawing::SystemColors::MenuText;
			this->showGridBtn->Location = System::Drawing::Point(434, 174);
			this->showGridBtn->Name = L"showGridBtn";
			this->showGridBtn->Size = System::Drawing::Size(76, 23);
			this->showGridBtn->TabIndex = 61;
			this->showGridBtn->Text = L"Grid View";
			this->showGridBtn->UseVisualStyleBackColor = false;
			this->showGridBtn->Click += gcnew System::EventHandler(this, &MainForm::showGridBtn_Click);
			// 
			// fovLabel
			// 
			this->fovLabel->AutoSize = true;
			this->fovLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->fovLabel->Location = System::Drawing::Point(286, 28);
			this->fovLabel->Name = L"fovLabel";
			this->fovLabel->Size = System::Drawing::Size(28, 13);
			this->fovLabel->TabIndex = 60;
			this->fovLabel->Text = L"45.0";
			// 
			// fovTitleLabel
			// 
			this->fovTitleLabel->AutoSize = true;
			this->fovTitleLabel->ForeColor = System::Drawing::SystemColors::InfoText;
			this->fovTitleLabel->Location = System::Drawing::Point(68, 18);
			this->fovTitleLabel->Name = L"fovTitleLabel";
			this->fovTitleLabel->Size = System::Drawing::Size(32, 13);
			this->fovTitleLabel->TabIndex = 59;
			this->fovTitleLabel->Text = L"FOV:";
			// 
			// fovTrackBar
			// 
			this->fovTrackBar->BackColor = System::Drawing::SystemColors::Window;
			this->fovTrackBar->LargeChange = 10;
			this->fovTrackBar->Location = System::Drawing::Point(125, 18);
			this->fovTrackBar->Maximum = 2000;
			this->fovTrackBar->Minimum = 1;
			this->fovTrackBar->Name = L"fovTrackBar";
			this->fovTrackBar->Size = System::Drawing::Size(158, 45);
			this->fovTrackBar->TabIndex = 58;
			this->fovTrackBar->TickFrequency = 100;
			this->fovTrackBar->Value = 450;
			this->fovTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::fovTrackBar_ValueChanged);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker2_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker2_RunWorkerCompleted);
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
			this->SceneTab->ResumeLayout(false);
			this->dicomConverterGroupBox->ResumeLayout(false);
			this->dicomConverterGroupBox->PerformLayout();
			this->rigidBodyGroupBox->ResumeLayout(false);
			this->volumePropertiesGroupBox->ResumeLayout(false);
			this->volumePropertiesGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationZTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationYTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rotationXTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionZTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionYTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->positionXTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->volumeScaleTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minIsoValueTrackBar))->EndInit();
			this->loadVolumeGroupBox->ResumeLayout(false);
			this->loadVolumeGroupBox->PerformLayout();
			this->cameraPage->ResumeLayout(false);
			this->cameraGroupBox->ResumeLayout(false);
			this->cameraGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->farTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nearTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pPointYTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pPointXTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->skewTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->betaTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->alphaTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraZTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraYTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cameraXTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fovTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
			// Local Variables
	private: std::vector<RigidBody*>* optiTrackRigidBodyVector;
	private: ProgressSpinner^ spinner;
	private: ProgressSpinner^ spinner2;
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
				 this->spinner->Location = 
					 System::Drawing::Point(
					 this->loadVolumeBtn->Location.X + this->loadVolumeBtn->Size.Width + 10, 
					 this->loadVolumeBtn->Location.Y + 5);
				 this->spinner->Enable = false;
				 this->loadVolumeGroupBox->Controls->Add(this->spinner);

				 this->spinner2 = gcnew ProgressSpinner();
				 this->spinner2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left));
				 this->spinner2->Location = 
					 System::Drawing::Point(
					 this->convertDICOMBtn->Location.X + this->convertDICOMBtn->Size.Width + 10, 
					 this->convertDICOMBtn->Location.Y + 5);
				 this->spinner2->Enable = false;
				 this->dicomConverterGroupBox->Controls->Add(this->spinner2);

				 this->volumeRemoveBtn->Enabled = false;

				 VolumeRenderManager::getInstance()->init();
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
			 // Disconnect from OptiTrack
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

				 this->rigidBodyListView->View = View::Details;
				 this->rigidBodyListView->Columns->Add("ID", 50, HorizontalAlignment::Left ); 
				 this->rigidBodyListView->Columns->Add("Name", 150, HorizontalAlignment::Left ); 

				 // Clear any previous entries in the list view
				 this->rigidBodyListView->Items->Clear();
				 
				 // Loop through all Rigid Body's
				 for (RigidBody_iterator it = bodyMap.begin(); it != bodyMap.end(); ++it)
				 {
					 { // Add Rigid Body's for Camera
						 String^ rigidBodyID = Convert::ToString(it->second->getID());
						 String^ rigidBodyName = gcnew String(it->second->getName());
						 ListViewItem^ listViewItem = gcnew ListViewItem(rigidBodyID); 
						 listViewItem->SubItems->Add(rigidBodyName);
						 this->rigidBodyListView->Items->Add(listViewItem);
					 }
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
	private: System::Void flipYZBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 ClientHandler::getInstance()->flipYZ();
				 if(ClientHandler::getInstance()->coordinateSystem())
					 this->flipYZLabel->Text = L"Y is up";
				 else
					 this->flipYZLabel->Text = L"Z is up";
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
				 VolumeRenderManager::getInstance()->createForm();
				 VolumeRenderManager::getInstance()->addVolumeToScene();
				 VolumeRenderManager::getInstance()->Show();

				 this->spinner->Enable = false;
				 this->volumeRemoveBtn->Enabled = true;
			 }
	private: System::Void volumeRemoveBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->loadVolumeBtn->Enabled = true;
				 this->volumeRemoveBtn->Enabled = false;
				 VolumeRenderManager::getInstance()->removeVolumeFromScene();
			 }
	private: System::Void showOpenGLViewBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 VolumeRenderManager::getInstance()->Show();
			 }
	private: System::Void minIsoValueTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float isoValue = 100.f*((float)this->minIsoValueTrackBar->Value/this->minIsoValueTrackBar->Maximum);
				 this->minIsoValueLabel->Text = isoValue.ToString("f1");
				 VolumeRenderManager::getInstance()->setMinIsoValue((float)this->minIsoValueTrackBar->Value/this->minIsoValueTrackBar->Maximum);
			 }
	private: System::Void volumeScaleTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float size = (float)this->volumeScaleTrackBar->Value/1000.f;
				 this->volumeScaleLabel->Text = size.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setScale(size);
			 }
	private: System::Void positionXTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->positionXTrackBar->Value/1000.f;
				 this->positionXLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setPositionX(value);
			 }
	private: System::Void positionYTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->positionYTrackBar->Value/1000.f;
				 this->positionYLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setPositionY(value);
			 }
	private: System::Void positionZTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->positionZTrackBar->Value/1000.f;
				 this->positionZLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setPositionZ(value);
			 }
	private: System::Void rotationXTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->rotationXTrackBar->Value/4.f;
				 this->rotationXLabel->Text = value.ToString("f2");
				 VolumeRenderManager::getInstance()->setRotationX(value);
			 }
	private: System::Void rotationYTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->rotationYTrackBar->Value/4.f;
				 this->rotationYLabel->Text = value.ToString("f2");
				 VolumeRenderManager::getInstance()->setRotationY(value);
			 }
	private: System::Void rotationZTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->rotationZTrackBar->Value/4.f;
				 this->rotationZLabel->Text = value.ToString("f2");
				 VolumeRenderManager::getInstance()->setRotationZ(value);
			 }
	private: System::Void selectRigidBodyAsVolumeBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->rigidBodyListView->SelectedItems->Count > 0) {
					 int id = System::Int32::Parse(this->rigidBodyListView->SelectedItems[0]->Text);

					 if (id < 0)
						 return;

					 if (!ClientHandler::getInstance()->lock())
						 return;

					 RigidBody* body = ClientHandler::getInstance()->getRigidBody(id);

					 if (body)
					 {
						 String^ message = gcnew String(body->getName());
						 message = message + " is the rigid body selected to be the volume.";

						 this->volumeSelectedLabel->Text = message;
					 }

					 ClientHandler::getInstance()->unlock();

					 VolumeRenderManager::getInstance()->setRigidBody(id);


				 }
				 else {
					 this->volumeSelectedLabel->Text = "No rigid body is selected to be the volume.";
				 }
			 }
	private: System::Void selectRigidBodyAsGridBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				  if (this->rigidBodyListView->SelectedItems->Count > 0) {
					 int id = System::Int32::Parse(this->rigidBodyListView->SelectedItems[0]->Text);

					 if (id < 0)
						 return;

					 if (!ClientHandler::getInstance()->lock())
						 return;

					 RigidBody* body = ClientHandler::getInstance()->getRigidBody(id);

					 if (body)
					 {
						 String^ message = gcnew String(body->getName());
						 message = message + " is the rigid body selected to be the grid.";

						 this->gridSelectedLabel->Text = message;
					 }

					 ClientHandler::getInstance()->unlock();

					 VolumeRenderManager::getInstance()->setGridRigidBody(id);

				 }
				 else {
					 this->gridSelectedLabel->Text = "No rigid body is selected to be the grid.";
				 }
			}
	private: System::Void browseDICOMBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 FolderBrowserDialog^ dialog = gcnew FolderBrowserDialog;

				 if ( dialog->ShowDialog() == ::DialogResult::OK )
				 {
					 this->DICOMTextBox->Text = dialog->SelectedPath;
				 }
			 }
	private: System::Void browseOutputBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveFileDialog^ dialog = gcnew SaveFileDialog;

				 dialog->DefaultExt = "raw";
				 dialog->Filter = "raw files (*.raw)|*.raw|All files (*.*)|*.*";
				 dialog->FilterIndex = 1;
				 dialog->RestoreDirectory = true;

				 if ( dialog->ShowDialog() == ::DialogResult::OK )
				 {
					 this->outputTextBox->Text = dialog->FileName;
				 }
			 }
	private: System::Void convertDICOMBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->convertDICOMBtn->Enabled = false;
				 this->spinner2->Enable = true;

				 this->backgroundWorker2->RunWorkerAsync();
			 }

	private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 ProcessStartInfo^ oStartInfo = gcnew ProcessStartInfo("DICOMConverter.exe");
				 oStartInfo->Arguments = "\"" + this->DICOMTextBox->Text + "\" \"" + this->outputTextBox->Text + "\"";
				 oStartInfo->UseShellExecute = false;
				 oStartInfo->RedirectStandardOutput = true;

				 Process^ process = Process::Start(oStartInfo);
				 process->WaitForExit();
			 }
	private: System::Void backgroundWorker2_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 this->convertDICOMBtn->Enabled = true;
				 this->spinner2->Enable = false;
			 }
	private: System::Void fovTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->fovTrackBar->Value/10.f;
				 this->fovLabel->Text = value.ToString("f1");
				 VolumeRenderManager::getInstance()->setFOV(value);
			 }
	private: System::Void showGridBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 CalibrationGrid^ grid = gcnew CalibrationGrid();
				 grid->Show();
			 }
	private: System::Void cameraXTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->cameraXTrackBar->Value/1000.f;
				 this->cameraXLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setCameraX(value);
			 }
	private: System::Void cameraYTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->cameraYTrackBar->Value/1000.f;
				 this->cameraYLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setCameraY(value);
			 }
	private: System::Void cameraZTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->cameraZTrackBar->Value/1000.f;
				 this->cameraZLabel->Text = value.ToString("f3") + " m";
				 VolumeRenderManager::getInstance()->setCameraZ(value);
			 }
	private: System::Void toggleGridBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 VolumeRenderManager::getInstance()->toggleGrid();
			 }
	private: System::Void useKMatrixCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 VolumeRenderManager::getInstance()->setUseIntrinsic(useKMatrixCheckBox->Checked);
			 }
	private: System::Void updateKMatrix() {
				 float* k = new float[16];

				 float alpha = (float)this->alphaTrackBar->Value/1000.f;
				 float beta = (float)this->betaTrackBar->Value/1000.f;
				 float skew = (float)this->skewTrackBar->Value/1000.f;
				 float pPointX = (float)this->pPointXTrackBar->Value/1000.f;
				 float pPointY = (float)this->pPointYTrackBar->Value/1000.f;
				 float znear = (float)this->nearTrackBar->Value/100.f;
				 float zfar = (float)this->farTrackBar->Value/100.f;

				 k[0] = alpha;
				 k[1] = skew;
				 k[2] = pPointX;
				 k[3] = 0.0f;

				 k[4] = 0.0f;
				 k[5] = beta;
				 k[6] = pPointY;
				 k[7] = 0.0f;

				 k[8] = 0.0f;
				 k[9] = 0.0f;
				 k[10] = (-zfar - znear)/(zfar - znear);
				 k[11] = -(2.f*zfar*znear)/(zfar - znear);

				 k[12] = 0.0f;
				 k[13] = 0.0f;
				 k[14] = -1.0f;
				 k[15] = 0.0f;

				 VolumeRenderManager::getInstance()->setIntrinsicMatrix(k);

				 delete[] k;
			 }
	private: System::Void alphaTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->alphaTrackBar->Value/1000.f;
				 this->alphaLabel->Text = value.ToString("f3");

				 updateKMatrix();
			 }
	private: System::Void betaTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->betaTrackBar->Value/1000.f;
				 this->betaLabel->Text = value.ToString("f3");

				 updateKMatrix();
			 }
	private: System::Void skewTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->skewTrackBar->Value/1000.f;
				 this->skewLabel->Text = value.ToString("f3");

				 updateKMatrix();
			 }
	private: System::Void pPointXTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->pPointXTrackBar->Value/1000.f;
				 this->pPointXLabel->Text = value.ToString("f3");

				 updateKMatrix();
			 }
	private: System::Void pPointYTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->pPointYTrackBar->Value/1000.f;
				 this->pPointYLabel->Text = value.ToString("f3");

				 updateKMatrix();
			 }
	private: System::Void nearTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->nearTrackBar->Value/100.f;
				 this->nearLabel->Text = value.ToString("f2");

				 updateKMatrix();
			 }
	private: System::Void farTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 float value = (float)this->farTrackBar->Value/100.f;
				 this->farLabel->Text = value.ToString("f2");

				 updateKMatrix();
			 }
};
}

