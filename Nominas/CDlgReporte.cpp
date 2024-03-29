// CDlgReporte.cpp : implementation file
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgReporte.h"
#include "afxdialogex.h"
#include "sysNominas.h"
#include "xlsxio_write.h"

#include <chrono>
#include <ctime>



// CDlgReporte dialog

IMPLEMENT_DYNAMIC(CDlgReporte, CDialog)

CDlgReporte::CDlgReporte(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_REPORTE, pParent)
{

}

CDlgReporte::~CDlgReporte()
{
}

void CDlgReporte::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTREP, m_listRep);

	DDX_Control(pDX, IDC_COMBOMES, m_cmes);
	DDX_Control(pDX, IDC_ANIO, m_anio);
}


BEGIN_MESSAGE_MAP(CDlgReporte, CDialog)
//	ON_CBN_SELCHANGE(IDC_COMBOMES, &CDlgReporte::OnCbnSelchangeCombomes)
	ON_BN_CLICKED(IDC_BTNBUSCAR, &CDlgReporte::OnBnClickedBtnbuscar)
	ON_BN_CLICKED(ID_BTNEXEL, &CDlgReporte::OnBnClickedBtnexel)
END_MESSAGE_MAP()


// CDlgReporte message handlers

//Funcion que inicializa los controles del dialogo
BOOL CDlgReporte::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sAnio;
	typedef std::chrono::system_clock Clock;

	auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	struct tm *parts = std::localtime(&now_c);

	//Se pone el año actual al txt del año
	sAnio.Format(_T("%d"), (parts->tm_year+1900));
	m_anio.SetWindowTextW(sAnio);

	m_listRep.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 30);
	m_listRep.InsertColumn(1, _T("Nombre"), LVCFMT_CENTER, 190);
	m_listRep.InsertColumn(2, _T("Sueldo"), LVCFMT_CENTER, 50);
	m_listRep.InsertColumn(3, _T("Extra"), LVCFMT_CENTER, 50);
	m_listRep.InsertColumn(4, _T("Bono"), LVCFMT_CENTER, 50);
	m_listRep.InsertColumn(5, _T("ISR"), LVCFMT_CENTER, 50);
	m_listRep.InsertColumn(6, _T("Vales"), LVCFMT_CENTER, 50);
	m_listRep.InsertColumn(7, _T("Sueldo Final"), LVCFMT_CENTER, 80);

	m_cmes.AddString(_T("Enero"));
	m_cmes.SetItemData(0, 1);
	m_cmes.AddString(_T("Febrero"));
	m_cmes.SetItemData(1, 2);
	m_cmes.AddString(_T("Marzo"));
	m_cmes.SetItemData(2, 3);
	m_cmes.AddString(_T("Abril"));
	m_cmes.SetItemData(3, 4);
	m_cmes.AddString(_T("Mayo"));
	m_cmes.SetItemData(4, 5);
	m_cmes.AddString(_T("Junio"));
	m_cmes.SetItemData(5, 6);
	m_cmes.AddString(_T("Julio"));
	m_cmes.SetItemData(6, 7);
	m_cmes.AddString(_T("Agosto"));
	m_cmes.SetItemData(7, 8);
	m_cmes.AddString(_T("Septiembre"));
	m_cmes.SetItemData(8, 9);
	m_cmes.AddString(_T("Octubre"));
	m_cmes.SetItemData(9, 10);
	m_cmes.AddString(_T("Noviembre"));
	m_cmes.SetItemData(10, 11);
	m_cmes.AddString(_T("Diciembre"));
	m_cmes.SetItemData(11,12);

	m_listRep.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_listRep.SetExtendedStyle(m_listRep.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CargarNomina(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Carga los datos de la nomina dependiendo de la opcion
//iOpcion = 1 carga la nomina de todos los empleado de toda la vida
//iOpcion = 1 carga la nomina de los empleados trabajandos el mes seleccionado
bool CDlgReporte::CargarNomina(int iOpcion)
{
	bool bRegresa = false;

	CString sConsulta, sValor, sFechaIni, sFechaFin, sFecha;
	int i = 0, iValor = 0;

	m_listRep.DeleteAllItems();

	if(iOpcion == 1)
		sConsulta = "SELECT idempleado::text,TRIM(nombre)as nombre,sueldo::text,bono::text,extra::text,isr::text,vale::text, sueldoTotal::text from obtenerNomina()";
	else
	{
		iValor = m_cmes.GetCurSel();
		iValor = m_cmes.GetItemData(iValor);

		m_anio.GetWindowTextW(sValor);

		sFecha.Format(_T("%Ts/%d/01"), sValor, iValor);

		sConsulta.Format(_T("SELECT idempleado::text,TRIM(nombre)as nombre,sueldo::text,bono::text,extra::text,isr::text,vale::text,sueldoTotal::text from obtenerNomina('%Ts')"), sFecha);

	}

	SACommand cmd(&con, SAString(sConsulta));

	cmd.Execute();

	while (cmd.FetchNext())
	{
		bRegresa = true;

		sValor = cmd.Field("idempleado").asString();
		m_listRep.InsertItem(i, LPCTSTR(sValor));

		m_listRep.SetItemText(i, 0, LPCTSTR(sValor));

		sValor = cmd.Field("nombre").asString();
		m_listRep.SetItemText(i, 1, LPCTSTR(sValor));

		sValor = cmd.Field("sueldo").asString();
		m_listRep.SetItemText(i, 2, LPCTSTR(sValor));

		sValor = cmd.Field("extra").asString();
		m_listRep.SetItemText(i, 3, LPCTSTR(sValor));

		sValor = cmd.Field("bono").asString();
		m_listRep.SetItemText(i, 4, LPCTSTR(sValor));

		sValor = cmd.Field("isr").asString();
		m_listRep.SetItemText(i, 5, LPCTSTR(sValor));

		sValor = cmd.Field("vale").asString();
		m_listRep.SetItemText(i, 6, LPCTSTR(sValor));

		sValor = cmd.Field("sueldoTotal").asString();
		m_listRep.SetItemText(i, 7, LPCTSTR(sValor));

		i++;
	}
	return bRegresa;

}


//Funcion que carga los datos del mes seleccionado a menos que algun dato esta vacio, cargara los datos de toda la vida.
void CDlgReporte::OnBnClickedBtnbuscar()
{
	CString sValor;
	int iValor = 0;

	iValor = m_cmes.GetCurSel();
	m_anio.GetWindowTextW(sValor);

	if(iValor == -1 || sValor == "0" || sValor.IsEmpty())
		CargarNomina(1);
	else
		CargarNomina(2);
}

//Boton que genera un archivo excel en base a lo mostrado en el control list
void CDlgReporte::OnBnClickedBtnexel()
{
	xlsxiowriter handle;
	int iTotal;
	CString sValor;

	if (!(handle = xlsxiowrite_open("Nomina.xlsx", "Reporte de nomina")) == NULL)
	{

		xlsxiowrite_add_column(handle, "ID", 16);
		xlsxiowrite_add_column(handle, "Nombre", 30);
		xlsxiowrite_add_column(handle, "Sueldo", 30);
		xlsxiowrite_add_column(handle, "Extra", 30);
		xlsxiowrite_add_column(handle, "Bono", 30);
		xlsxiowrite_add_column(handle, "ISR", 30);
		xlsxiowrite_add_column(handle, "Vales", 30);
		xlsxiowrite_add_column(handle, "Sueldo total", 50);
		xlsxiowrite_next_row(handle);

		//write data
		iTotal = m_listRep.GetItemCount();

		for (int i = 0; i < iTotal; i++)
		{
			for(int j = 0; j <= 7;j++)
			{
				sValor = m_listRep.GetItemText(i, j);
				xlsxiowrite_add_cell_string(handle, SAString(sValor));
			
			}
			xlsxiowrite_next_row(handle);
		}


		xlsxiowrite_close(handle);

		AfxMessageBox(_T("El reporte fue creado"), MB_ICONINFORMATION);

	}
	else
	{
		AfxMessageBox(_T("Favor de cerrar el archivo o crear la ruta de destino del reporte de nomina"), MB_ICONSTOP);
	}

}


BOOL CDlgReporte::PreTranslateMessage(MSG* pMsg)
{
	
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
				return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
