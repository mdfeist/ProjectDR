#pragma once

namespace ProjectDR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CalibrationGrid
	/// </summary>
	public ref class CalibrationGrid : public System::Windows::Forms::Form
	{
	public:
		CalibrationGrid(void)
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
		~CalibrationGrid()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox;
	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CalibrationGrid::typeid));
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox.Image")));
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(530, 395);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			// 
			// CalibrationGrid
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(530, 395);
			this->Controls->Add(this->pictureBox);
			this->Name = L"CalibrationGrid";
			this->Text = L"CalibrationGrid";
			this->Load += gcnew System::EventHandler(this, &CalibrationGrid::CalibrationGrid_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CalibrationGrid::CalibrationGrid_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		BOOL fullScreen;
		System::Void CalibrationGrid_Load(System::Object^  sender, System::EventArgs^  e) {
			fullScreen = false;
		}

		System::Void CalibrationGrid_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			switch (e->KeyChar) {
			case (char)27 :
				{
					fullScreen = false;
					FullScreen(fullScreen);
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
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->WindowState = FormWindowState::Maximized;
			}
			else
			{
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
				this->WindowState = FormWindowState::Normal;
			}

			this->ResumeLayout();
		}
};
}
