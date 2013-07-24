#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Windows::Forms;
using namespace System::Timers;

public ref class ProgressSpinner : Control
{
public:
	property bool Spinning
	{
		bool get() { return _timer->Enabled; }
		void set(bool value) { _timer->Enabled = value; }
	}

	property bool EnsureVisible
	{
		bool get() { return _ensureVisible; }
		void set(bool value) { _ensureVisible = value; Refresh(); }
	}

	property float Speed
	{
		float get() { return _speed; }
		void set(float value)
		{
			if (value <= 0 || value > 10)
				throw gcnew ArgumentOutOfRangeException("Speed value must be > 0 and <= 10.");
			_speed = value;
		}
	}

	property bool Backwards
	{
		bool get() { return _backwards; }
		void set(bool value) { _backwards = value; Refresh(); }
	}

	property bool Enable
	{
		bool get() { return _enabled; }
		void set(bool value)
		{
			_enabled = value;

			if (value)
			{
				_timer->Start();
				_ensureVisible = true;
			}
			else
			{
				_timer->Stop();
				_ensureVisible = false;
			}

			Refresh();
		}
	}
	
	ProgressSpinner()
	{
		components = nullptr;

		InitializeComponent();

		_enabled = true;

		_timer = gcnew System::Timers::Timer();
		_timer->Interval = 100;
		_timer->Elapsed += gcnew ElapsedEventHandler( this, &ProgressSpinner::OnTimedEvent );
		_timer->Enabled = true;

		Width = 16;
		Height = 16;
		this->_speed = 10;
		DoubleBuffered = true;
		ForeColor = SystemColors::Highlight;

		_rotation = 270;
		_numberOfCircles = 16;
		_spacing = 6;
		_circleSize = 1.0f;
		_ensureVisible = true;
	}

	void Reset()
	{
		_rotation = 270;
		Refresh();
	}

	void OnTimedEvent(Object^ sender, ElapsedEventArgs^ e)
	{
		_rotation += 0.05f * _speed * (_backwards ? -1 : 1);
		Invalidate();
		Refresh();
	}

protected: 
	System::Void OnPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		float angle = 6.28318530718F / (_numberOfCircles + _spacing);

		GraphicsState^ oldState = e->Graphics->Save();
		
		e->Graphics->InterpolationMode = InterpolationMode::HighQualityBicubic;
		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;

		for (int i = 1; i <= _numberOfCircles; i++)
		{
			int alphaValue = 255.0F * (i / (float)_numberOfCircles);
			int alpha = _ensureVisible ? alphaValue : 0;

			Color drawColor = Color::FromArgb(alpha, 0, 0, 0);

			SolidBrush^ brush = gcnew SolidBrush(drawColor);

			float sizeRate = 4.5F / _circleSize;
			float size = Width / sizeRate;

			float diffX = Width/2.0F - size;
			float diffY = Height/2.0F - size;

			float x = diffX + diffX*cosf(i*angle + _rotation);
			float y = diffY + diffY*sinf(i*angle + _rotation);
			e->Graphics->FillEllipse(brush, x, y, size, size);

		}

		e->Graphics->Restore(oldState);
	}

private: 
	void InitializeComponent()
	{
		components = gcnew System::ComponentModel::Container();
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ProgressSpinner::OnPaint);
	}

	System::ComponentModel::IContainer^ components;

	System::Timers::Timer^ _timer;
	bool _enabled;
	float _rotation;
	bool _ensureVisible;
	float _speed;
	bool _backwards;
	int _numberOfCircles;
	int _spacing;
	float _circleSize;
};

