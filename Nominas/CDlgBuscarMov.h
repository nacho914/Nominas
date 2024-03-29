#pragma once


// CDlgBuscarMov dialog

class CDlgBuscarMov : public CDialog
{
	DECLARE_DYNAMIC(CDlgBuscarMov)

public:
	CDlgBuscarMov( CWnd* pParent = nullptr);
	CDlgBuscarMov(int iID, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgBuscarMov();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUSCAMOV};
#endif

protected:
	int iID;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listMov;
	CDateTimeCtrl m_fechaInicio;
	CDateTimeCtrl m_fechaFin;

	

	virtual BOOL OnInitDialog();
	bool CargarMovimientos(int iOpcionCargar);
	afx_msg void OnBnClickedBtnbuscar();
	afx_msg void OnBnClickedBtnborrar();
	afx_msg void OnNMDblclkListmov(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddexcel();
};
