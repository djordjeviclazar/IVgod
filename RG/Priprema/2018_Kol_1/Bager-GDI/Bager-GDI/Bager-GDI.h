
// Bager-GDI.h : main header file for the Bager-GDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBagerGDIApp:
// See Bager-GDI.cpp for the implementation of this class
//

class CBagerGDIApp : public CWinApp
{
public:
	CBagerGDIApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBagerGDIApp theApp;
