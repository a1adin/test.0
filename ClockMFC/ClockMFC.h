////////////////////////////////////////////////////////////////////////////////////
//
//			www.interestprograms.ru - программы, игры и их исходные коды
//
/////////////////////////////////////////////////////////////////////////////////////

// ClockMFC.h : main header file for the ClockMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CClockMFCApp:
// See ClockMFC.cpp for the implementation of this class
//

class CClockMFCApp : public CWinApp
{
public:
	CClockMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CClockMFCApp theApp;