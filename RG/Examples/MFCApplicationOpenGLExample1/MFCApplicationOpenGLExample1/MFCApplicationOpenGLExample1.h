
// MFCApplicationOpenGLExample1.h : main header file for the MFCApplicationOpenGLExample1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplicationOpenGLExample1App:
// See MFCApplicationOpenGLExample1.cpp for the implementation of this class
//

class CMFCApplicationOpenGLExample1App : public CWinApp
{
public:
	CMFCApplicationOpenGLExample1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationOpenGLExample1App theApp;
