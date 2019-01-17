#pragma once


// CDlgEmpleado dialog

class CDlgEmpleado : public CDialog
{
	DECLARE_DYNAMIC(CDlgEmpleado)

public:
	CDlgEmpleado(CWnd* pParent = nullptr);   // standard constructor
	CDlgEmpleado(int iDlgS, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgEmpleado();

// Dialog Data

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPLEADO};
#endif


private:
	BOOL ObtenerDatosCaptura(int &iRol, int &iTipo);
	BOOL soloLetras(CString letras);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void limpiarDialogo();
	BOOL ValidaDatos();
	int iIdEmp;
	int iDlg;
	CEdit m_nombre;
	CEdit m_paterno;
	CEdit m_materno;
	CButton m_chofer;
	CButton m_cargador;
	CComboBox m_tipo;
	virtual BOOL OnInitDialog();
	CButton m_interno;
	CButton m_externo;
	CButton m_aux;
	CButton m_btnprincipal;
	CEdit m_idemp;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddempleado();
};
