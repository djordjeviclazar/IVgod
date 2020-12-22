
// LV4-OpenGL-Transformacije.h : main header file for the LV4-OpenGL-Transformacije application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV4OpenGLTransformacijeApp:
// See LV4-OpenGL-Transformacije.cpp for the implementation of this class
//

class CLV4OpenGLTransformacijeApp : public CWinApp
{
public:
	CLV4OpenGLTransformacijeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV4OpenGLTransformacijeApp theApp;
