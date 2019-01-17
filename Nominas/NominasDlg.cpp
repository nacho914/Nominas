
// NominasDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Nominas.h"
#include "NominasDlg.h"
#include "afxdialogex.h"
#include <SQLAPI.h> // main SQLAPI++ header

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CNominasDlg



CNominasDlg::CNominasDlg(CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_NOMINAS_DIALOG, pParent)
	, m_conexion(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNominasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CNominasDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDOK, &CNominasDlg::OnBnClickedOk)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CNominasDlg::OnTcnSelchangeTab1)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CNominasDlg::OnTcnSelchangeTab)
//ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, &CNominasDlg::OnTcnSelchangingTab)
END_MESSAGE_MAP()


// Controladores de mensajes de CNominasDlg

BOOL CNominasDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional


	//A partir de la iOpcion opcion seran los dialogos que se mostraran en los tabs.
	
	//Con la variable rect se definira la posicion de los dialogos dentro del grid
	CRect rect;
	m_tab.GetClientRect(&rect);
	
	if(iOpcion == 1)
	{
		m_tab.InsertItem(0, _T("Nuevo empleado"));
		m_tab.InsertItem(2, _T("Buscar empleado"), 2);
		
		m_dlgEmpleado.Create(IDD_EMPLEADO, &m_tab);
		m_dlgEmpleado.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

		m_dlgBuscarEmp.Create(IDD_BUSCAEMP, &m_tab);
		m_dlgBuscarEmp.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_HIDEWINDOW | SWP_NOZORDER);
		
		m_pwnShow = &m_dlgEmpleado;
	}
	else if (iOpcion == 2)
	{
		m_tab.InsertItem(0, _T("Nuevo movimiento"));
		m_tab.InsertItem(2, _T("Buscar movimiento"), 2);

		m_dlgMov.Create(IDD_MOVIMIENTOS, &m_tab);
		m_dlgMov.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
		
		m_dlgbuscarMov.Create(IDD_BUSCAMOV, &m_tab);
		m_dlgbuscarMov.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_HIDEWINDOW | SWP_NOZORDER);
		
		m_pwnShow = &m_dlgMov;

	}

	else if (iOpcion == 3)
	{
		m_tab.InsertItem(0, _T("Reporte de nomina"));
		
		m_dlgRepor.Create(IDD_REPORTE, &m_tab);
		m_dlgRepor.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

		m_pwnShow = &m_dlgRepor;
	}

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CNominasDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CNominasDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CNominasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//Este metodo hara que se muestren los dialogos elegidos cada vez que se cambie de tab
void CNominasDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iIndex = 0;

	if (m_pwnShow != NULL)
	{
		m_pwnShow->ShowWindow(SW_HIDE);
		m_pwnShow = NULL;
	}
	
	iIndex = m_tab.GetCurSel();

	switch (iIndex)
	{
		case 0:
			if(iOpcion == 1)
			{
				m_dlgEmpleado.m_nombre.SetFocus();
				m_dlgEmpleado.ShowWindow(SW_SHOW);				
				m_pwnShow = &m_dlgEmpleado;
			}
			else if(iOpcion == 2)
			{
				m_dlgMov.m_numemp.SetFocus();
				m_dlgMov.ShowWindow(SW_SHOW);
				m_pwnShow = &m_dlgMov;
			}
			break;

		case 1:
			if (iOpcion == 1)
			{
				m_dlgBuscarEmp.CargarEmpleados(1);
				m_dlgBuscarEmp.m_buscar.SetFocus();
				m_dlgBuscarEmp.ShowWindow(SW_SHOW);
				m_pwnShow = &m_dlgBuscarEmp;
			}
			else
			{
				m_dlgbuscarMov.CargarMovimientos(1);
				m_dlgbuscarMov.ShowWindow(SW_SHOW);
				m_pwnShow = &m_dlgbuscarMov;
			}
			break;

	}

	*pResult = 0;
}


