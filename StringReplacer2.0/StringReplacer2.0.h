
// StringReplacer2.0.h : main header file for the StringReplacer2.0 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CApp:
// See StringReplacer2.0.cpp for the implementation of this class
//

class CApp : public CWinApp
{
public:
	CApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;
