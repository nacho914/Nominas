
#include "CDlgEmpleado.h"
#include "CDlgBuscarEmp.h"
#include "CDlgMovimientos.h"
#include "CDlgBuscarMov.h"
#include "CDlgReporte.h"


#pragma once

// Cuadro de diálogo de CNominasDlg
class CNominasDlg : public CDialog
{
// Construcción
public:
	CNominasDlg(CWnd* pParent = nullptr);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOMINAS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Variable para mostrar datos
	int iOpcion;
	CString m_conexion;
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	
	CDlgEmpleado m_dlgEmpleado;
	CDlgBuscarEmp m_dlgBuscarEmp;
	CDlgMovimientos m_dlgMov;
	CDlgBuscarMov m_dlgbuscarMov;
	CDlgReporte m_dlgRepor;
	CTabCtrl m_tab;
	CWnd * m_pwnShow;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTcnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult);
	
};
