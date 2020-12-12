
// LV03-GDI-Bitmape.h : main header file for the LV03-GDI-Bitmape application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV03GDIBitmapeApp:
// See LV03-GDI-Bitmape.cpp for the implementation of this class
//

class CLV03GDIBitmapeApp : public CWinApp
{
public:
	CLV03GDIBitmapeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV03GDIBitmapeApp theApp;
