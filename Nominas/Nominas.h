#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif
#include "resource.h"		// Símbolos principales
#include <SQLAPI.h> // main SQLAPI++ header

class CNominasApp : public CWinApp
{
public:
	CNominasApp();
	

public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CNominasApp theApp;
