// CDlgBuscarMov.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgBuscarMov.h"
#include "afxdialogex.h"
#include "sysNominas.h"
#include "CDlgMovimientos.h"
#include "CDlgAcerca.h"
#include "xlsxio_write.h"



// CDlgBuscarMov dialog

IMPLEMENT_DYNAMIC(CDlgBuscarMov, CDialog)


CDlgBuscarMov::CDlgBuscarMov(CWnd* pParent /*=nullptr*/)
	: CDialog(iID, pParent)
{

}

CDlgBuscarMov::CDlgBuscarMov(int iID, CWnd* pParent /*=nullptr*/)
	: CDialog(iID, pParent)
{
	this->iID = iID;

}

CDlgBuscarMov::~CDlgBuscarMov()
{
}

void CDlgBuscarMov::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTMOV, m_listMov);
	DDX_Control(pDX, IDC_DTPINICIO, m_fechaInicio);
	DDX_Control(pDX, IDC_DTPFIN, m_fechaFin);
	
}


BEGIN_MESSAGE_MAP(CDlgBuscarMov, CDialog)
ON_BN_CLICKED(IDC_BTNBUSCAR, &CDlgBuscarMov::OnBnClickedBtnbuscar)
ON_BN_CLICKED(IDC_BTNBORRAR, &CDlgBuscarMov::OnBnClickedBtnborrar)
ON_NOTIFY(NM_DBLCLK, IDC_LISTMOV, &CDlgBuscarMov::OnNMDblclkListmov)
ON_BN_CLICKED(IDC_ADDEXCEL, &CDlgBuscarMov::OnBnClickedAddexcel)
END_MESSAGE_MAP()


// CDlgBuscarMov message handlers

//Funcion que se manda a llamar al iniciar el dialogo.
BOOL CDlgBuscarMov::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//Se agregan las columnas de la lista
	m_listMov.InsertColumn(0, _T("Mov"), LVCFMT_CENTER, 40);
	m_listMov.InsertColumn(1, _T("Fecha"), LVCFMT_CENTER, 70);
	m_listMov.InsertColumn(2, _T("Empleado"), LVCFMT_CENTER, 150);
	m_listMov.InsertColumn(3, _T("Rol"), LVCFMT_CENTER, 80);
	m_listMov.InsertColumn(4, _T("Tipo "), LVCFMT_CENTER, 80);
	m_listMov.InsertColumn(5, _T("Rol extra"), LVCFMT_CENTER, 100);
	m_listMov.InsertColumn(6, _T("Entregas"), LVCFMT_CENTER, 65);

	//Se modifican los estilos de la lista
	m_listMov.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_listMov.SetExtendedStyle(m_listMov.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	//Se cargan los datos de la BD
	CargarMovimientos(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Funcion que carga los dialogos dependiendo del caso 
//iOpcionCargar 1 carga todos los movimientos de la base de datos
//iOpcionCargar 2 carga todos los movimientos de las fechas seleccionados

bool CDlgBuscarMov::CargarMovimientos(int iOpcionCargar)
{
	bool bRegresa = false;
	CString sConsulta, sValor, sFechaIni, sFechaFin;
	int i = 0, iValor = 0;

	m_listMov.DeleteAllItems();

	if(iOpcionCargar == 1)
		sConsulta = "SELECT a.idmovimiento as idmov,TRIM(a.fechamovimiento::text) as fechamov, (TRIM(b.nombre)||' '|| trim(b.apellidopaterno) || ' '||TRIM(b.apellidoMaterno))::text as nombre, TRIM(c.descripcion) as puesto, TRIM(d.descripcion) as tipo, TRIM(e.descripcion) as puestoc, a.cantidadentregas as cant from movimientos as a inner join empleados as b ON a.idempleado = b.id inner join rol as c on a.puesto = c.idrol inner join tipo as d  ON a.tipoempleado =d.idtipo LEFT join rol as e on a.puestocubrio = e.idrol order by a.fechamovimiento";
	
	else if(iOpcionCargar == 2)
	{

		m_fechaInicio.GetWindowTextW(sFechaIni);

		m_fechaFin.GetWindowTextW(sFechaFin);

		sConsulta.Format(_T("SELECT a.idmovimiento as idmov,TRIM(a.fechamovimiento::text) as fechamov, (TRIM(b.nombre)||' '|| trim(b.apellidopaterno) || ' '||TRIM(b.apellidoMaterno))::text as nombre, TRIM(c.descripcion) as puesto, TRIM(d.descripcion) as tipo, TRIM(e.descripcion) as puestoc, a.cantidadentregas as cant from movimientos as a inner join empleados as b ON a.idempleado = b.id inner join rol as c on a.puesto = c.idrol inner join tipo as d  ON a.tipoempleado =d.idtipo LEFT join rol as e on a.puestocubrio = e.idrol WHERE A.fechamovimiento between '%Ts' and '%Ts' order by a.fechamovimiento"), sFechaIni,sFechaFin);

	}

	SACommand cmd(&con, SAString(sConsulta));

	cmd.Execute();

	while (cmd.FetchNext())
	{
		bRegresa = true;

		sValor = cmd.Field("nombre").asString();
		m_listMov.InsertItem(i, LPCTSTR(sValor));

		m_listMov.SetItemText(i, 2, LPCTSTR(sValor));

		sValor = cmd.Field("idmov").asString();
		m_listMov.SetItemText(i, 0, LPCTSTR(sValor));

		sValor = cmd.Field("fechamov").asString();
		m_listMov.SetItemText(i, 1, LPCTSTR(sValor));

		sValor = cmd.Field("puesto").asString();
		m_listMov.SetItemText(i, 3, LPCTSTR(sValor));

		sValor = cmd.Field("tipo").asString();
		m_listMov.SetItemText(i, 4, LPCTSTR(sValor));

		sValor = cmd.Field("puestoc").asString();
		m_listMov.SetItemText(i, 5, LPCTSTR(sValor));

		sValor = cmd.Field("cant").asString();
		m_listMov.SetItemText(i, 6, LPCTSTR(sValor));

		i++;
	}
	return bRegresa;
}


//Funcion que carga los datos en base a las fechas seleccionadas
void CDlgBuscarMov::OnBnClickedBtnbuscar()
{
	
	CargarMovimientos(2);

}

//Funcion que elimina el movimiento seleccionado
void CDlgBuscarMov::OnBnClickedBtnborrar()
{

	int iId_mov = 0, iFila = 0;
	CString sConsulta;

	iFila = m_listMov.GetSelectionMark();

	iId_mov = _wtoi(m_listMov.GetItemText(iFila, 0));


	if (iFila != -1)
	{
		sConsulta.Format(_T("DELETE FROM movimientos WHERE idmovimiento = %d"), iId_mov);

		SACommand cmd(&con, SAString(sConsulta));

		cmd.Execute();
		AfxMessageBox(_T("El movimiento fue eliminado"), MB_ICONINFORMATION);

		CargarMovimientos(1);

	}
	else
	{
		AfxMessageBox(_T("Favor de seleccionar algún empleado"), MB_ICONSTOP);
	}
	
}

//Funcion que se manda a llamar al hacer doble click sobre algun elemento de la lista
//Esta a su vez mandara a llamar al objeto modMov de la clase CDlgMovimientos
//mencionandole primeramente a que dialogo debe apuntar.
void CDlgBuscarMov::OnNMDblclkListmov(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int iId_movimiento = 0,iFila = 0;

	iFila = m_listMov.GetSelectionMark();
	iId_movimiento = _wtoi(m_listMov.GetItemText(iFila, 0));

	CDlgMovimientos modMov(IDD_MOVACT);
	modMov.idMov = iId_movimiento;

	modMov.DoModal();

	CargarMovimientos(2);

	*pResult = 0;
}


BOOL CDlgBuscarMov::PreTranslateMessage(MSG* pMsg)
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

//Al darle click al boton Addexcel se cargaran los datos que se encuentren en la lista a un archivo Excel.
void CDlgBuscarMov::OnBnClickedAddexcel()
{
	CString sValor;
	int iTotalItems = 0;


	xlsxiowriter XmlCreador;
	if (!((XmlCreador = xlsxiowrite_open("Movimientos.xlsx", "Movimientos")) == NULL))
	{

		iTotalItems = m_listMov.GetItemCount();

		xlsxiowrite_add_column(XmlCreador, "Id Movimiento", 10);
		xlsxiowrite_add_column(XmlCreador, "Fecha movimiento", 32);
		xlsxiowrite_add_column(XmlCreador, "Nombre", 32);
		xlsxiowrite_add_column(XmlCreador, "Puesto", 32);
		xlsxiowrite_add_column(XmlCreador, "Tipo empleado", 32);
		xlsxiowrite_add_column(XmlCreador, "Puesto cubierto", 32);
		xlsxiowrite_add_column(XmlCreador, "Cantidad entregas", 32);
		xlsxiowrite_next_row(XmlCreador);


		for (int i = 0; i <= iTotalItems; i++)
		{
			for (int j = 0; j <= 6; j++)
			{
				sValor = m_listMov.GetItemText(i, j);

				xlsxiowrite_add_cell_string(XmlCreador, SAString(sValor));

			}
			xlsxiowrite_next_row(XmlCreador);
		}
		
		xlsxiowrite_close(XmlCreador);
		AfxMessageBox(_T("El reporte fue creado"), MB_ICONINFORMATION);


	}
	else
	{
		AfxMessageBox(_T("Favor de cerrar el archivo o crear la ruta"), MB_ICONSTOP);
	}

}
