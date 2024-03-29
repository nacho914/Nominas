#pragma once


// CDlgReporte dialog

class CDlgReporte : public CDialog
{
	DECLARE_DYNAMIC(CDlgReporte)

public:
	CDlgReporte(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgReporte();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORTE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool CargarNomina(int iOpcion);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listRep;
	CComboBox m_cmes;
//	afx_msg void OnCbnSelchangeCombomes();
	afx_msg void OnBnClickedBtnbuscar();
	CEdit m_anio;
	afx_msg void OnBnClickedBtnexel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
