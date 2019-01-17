#pragma once

#include "sysNominas.h"

// CDlgPass dialog

class CDlgPass : public CDialog
{
	DECLARE_DYNAMIC(CDlgPass)



public:
	CDlgPass(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgPass();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASS };
#endif

private:
	BOOL CoincideContraseña();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual BOOL OnInitDialog();
	
	int iCoincide;
	CString m_pass;
	CEdit m_contra;
};
