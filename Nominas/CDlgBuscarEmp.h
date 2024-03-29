#pragma once


// CDlgBuscarEmp dialog

class CDlgBuscarEmp : public CDialog
{
	DECLARE_DYNAMIC(CDlgBuscarEmp)

public:
	CDlgBuscarEmp(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgBuscarEmp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUSCAEMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	

public:
	CListCtrl m_listEmpleados;
	virtual BOOL OnInitDialog();
//	afx_msg void OnHdnItemdblclickListempleados(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListempleados(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTxtbuscar();
	CEdit m_buscar;
	afx_msg void OnBnClickedEliminar();
	BOOL CargarEmpleados(int iOpcion);

	afx_msg void OnBnClickedAgregarmov();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddexcel();
};
