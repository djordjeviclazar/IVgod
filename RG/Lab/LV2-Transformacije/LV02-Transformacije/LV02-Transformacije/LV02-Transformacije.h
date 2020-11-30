
// LV02-Transformacije.h : main header file for the LV02-Transformacije application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV02TransformacijeApp:
// See LV02-Transformacije.cpp for the implementation of this class
//

class CLV02TransformacijeApp : public CWinAppEx
{
public:
	CLV02TransformacijeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV02TransformacijeApp theApp;
