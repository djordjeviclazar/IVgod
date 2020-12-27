
// LV5-OpenGL-Osvetljenje.h : main header file for the LV5-OpenGL-Osvetljenje application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV5OpenGLOsvetljenjeApp:
// See LV5-OpenGL-Osvetljenje.cpp for the implementation of this class
//

class CLV5OpenGLOsvetljenjeApp : public CWinApp
{
public:
	CLV5OpenGLOsvetljenjeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV5OpenGLOsvetljenjeApp theApp;
