#pragma once


// CDlgMenu dialog

class CDlgMenu : public CDialog
{
	DECLARE_DYNAMIC(CDlgMenu)

public:
	CDlgMenu(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgMenu();
	int iOpcion;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
};
