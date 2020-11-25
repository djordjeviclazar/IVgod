
// MFCApplicationсExample1.h : main header file for the MFCApplicationсExample1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplicationсExample1App:
// See MFCApplicationсExample1.cpp for the implementation of this class
//

class CMFCApplicationсExample1App : public CWinApp
{
public:
	CMFCApplicationсExample1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationсExample1App theApp;
