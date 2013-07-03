#pragma once
#include "stdafx.h"

namespace ProjectDR {
		
using namespace System;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::ComponentModel::Design;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class WizardPages : TabControl
{
protected: 
	virtual void WndProc(Message% m) override
    {
        // Hide tabs by trapping the TCM_ADJUSTRECT message
        if (m.Msg == 0x1328 && !DesignMode) 
			m.Result = (IntPtr)1;
        else 
			TabControl::WndProc(m);
    }        

	
    virtual void OnKeyDown(KeyEventArgs^ ke) override
    {
        // Block Ctrl+Tab and Ctrl+Shift+Tab hotkeys
        if (ke->Control && ke->KeyCode == Keys::Tab) 
            return;
        TabControl::OnKeyDown(ke);
    }
};
}