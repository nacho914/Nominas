#pragma once


// CDlgAcerca dialog

class CDlgAcerca : public CDialog
{
	DECLARE_DYNAMIC(CDlgAcerca)

public:
	CDlgAcerca(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgAcerca();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
