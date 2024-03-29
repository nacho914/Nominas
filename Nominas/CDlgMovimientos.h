#pragma once


// CDlgMovimientos dialog

class CDlgMovimientos : public CDialog
{
	DECLARE_DYNAMIC(CDlgMovimientos)

public:
	CDlgMovimientos(CWnd* pParent = nullptr);   // standard constructor
	CDlgMovimientos(int iDlgS, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgMovimientos();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVIMIENTOS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
//	afx_msg void OnEnKillfocusTxtnum();
	
	CEdit m_numemp;
	CEdit m_nombre;
	CEdit m_tipo;
	CEdit m_rol;
	
	CStatic m_cuadro;
	CButton m_radChofer;
	CButton m_radCarga;
	CButton m_radCubrio;
	CButton m_btnPrincipal;

	CDateTimeCtrl m_fecha;
	afx_msg void OnBnClickedAddmovimiento();
	int iDlg, idMov, idEmp;

protected:
	
	int iRol;
	int iTipo;	
	BOOL CargarDatos(int iOpcion);
	
public:
	CEdit m_cantEntregas;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	void LimpiarDatos();
	afx_msg void OnBnClickedBtnCargar();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int regresaPuestoCubierto();
};
