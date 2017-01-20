// demo_lzh.h : main header file for the demo_lzh DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cdemo_lzhApp
// See demo_lzh.cpp for the implementation of this class
//

class Cdemo_lzhApp : public CWinApp
{
public:
	Cdemo_lzhApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
