
// LV1-GDI-Tangram.h : main header file for the LV1-GDI-Tangram application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV1GDITangramApp:
// See LV1-GDI-Tangram.cpp for the implementation of this class
//

class CLV1GDITangramApp : public CWinApp
{
public:
	CLV1GDITangramApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV1GDITangramApp theApp;
