
// LV6-OpenGL-Teksture1.1.h : main header file for the LV6-OpenGL-Teksture1.1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV6OpenGLTeksture11App:
// See LV6-OpenGL-Teksture1.1.cpp for the implementation of this class
//

class CLV6OpenGLTeksture11App : public CWinApp
{
public:
	CLV6OpenGLTeksture11App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV6OpenGLTeksture11App theApp;
