// CDlgBuscarEmp.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgBuscarEmp.h"
#include "afxdialogex.h"
#include "sysNominas.h"
#include "CDlgEmpleado.h"
#include "CDlgMovimientos.h"
#include "xlsxio_write.h"

// CDlgBuscarEmp dialog

IMPLEMENT_DYNAMIC(CDlgBuscarEmp, CDialog)

CDlgBuscarEmp::CDlgBuscarEmp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BUSCAEMP, pParent)
{

}


CDlgBuscarEmp::~CDlgBuscarEmp()
{
}

void CDlgBuscarEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTEMPLEADOS, m_listEmpleados);
	DDX_Control(pDX, IDC_TXTBUSCAR, m_buscar);
}


BEGIN_MESSAGE_MAP(CDlgBuscarEmp, CDialog)
ON_NOTIFY(NM_DBLCLK, IDC_LISTEMPLEADOS, &CDlgBuscarEmp::OnNMDblclkListempleados)
ON_EN_CHANGE(IDC_TXTBUSCAR, &CDlgBuscarEmp::OnEnChangeTxtbuscar)
ON_BN_CLICKED(IDELIMINAR, &CDlgBuscarEmp::OnBnClickedEliminar)
ON_BN_CLICKED(ID_AGREGARMOV, &CDlgBuscarEmp::OnBnClickedAgregarmov)
ON_BN_CLICKED(IDC_ADDEXCEL, &CDlgBuscarEmp::OnBnClickedAddexcel)
END_MESSAGE_MAP()


// CDlgBuscarEmp message handlers


BOOL CDlgBuscarEmp::OnInitDialog()
{
	CDialog::OnInitDialog();
	bool bRespuesta = false;

	//se agrega las columnas a la lista.

	m_listEmpleados.InsertColumn(0, _T("ID"),LVCFMT_CENTER,30);
	m_listEmpleados.InsertColumn(1, _T("NOMBRE"), LVCFMT_CENTER, 200);
	m_listEmpleados.InsertColumn(2, _T("ROL"), LVCFMT_CENTER, 100);
	m_listEmpleados.InsertColumn(3, _T("TIPO"), LVCFMT_CENTER, 100);
	
	//Se modifica el estilo de la lista
	m_listEmpleados.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	m_listEmpleados.SetExtendedStyle(m_listEmpleados.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	//Se carga los datos de todos los empleados
	CargarEmpleados(1);
		


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Funcion que cargara los datos de los empleados a la lista la opcion 1 cargara todos 
//los datos mientras la opcion 2 cargara los datos filtrados por el nombre

BOOL CDlgBuscarEmp::CargarEmpleados(int iOpcion)
{
	bool bRegresa = false;
	CString sConsulta,sValor;
	int i = 0,iValor =0;
	
	m_listEmpleados.DeleteAllItems();

	if(iOpcion == 1)
		sConsulta = "SELECT id::text as idtex, (TRIM(nombre)||' '|| trim(apellidopaterno) || ' '||TRIM(apellidoMaterno))::text as nombre, TRIM(b.descripcion) as puesto, TRIM(c.descripcion) as tipoempleado from empleados as a inner join rol as b on a.puesto = b.idrol inner join tipo as c on a.tipoempleado = c.idtipo WHERE a.status = 1 ORDER BY a.id ";
	else if (iOpcion == 2)
	{
		m_buscar.GetWindowTextW(sValor);

		sConsulta.Format(_T("SELECT id::text as idtex, (TRIM(nombre)||' '|| trim(apellidopaterno) || ' '||TRIM(apellidoMaterno))::text as nombre, TRIM(b.descripcion) as puesto, TRIM(c.descripcion) as tipoempleado from empleados as a inner join rol as b on a.puesto = b.idrol inner join tipo as c on a.tipoempleado = c.idtipo WHERE a.status = 1 AND (TRIM(nombre)||' '|| trim(apellidopaterno) || ' '||TRIM(apellidoMaterno))::text like '%%%Ts%%' order by a.id"), sValor);

	}
	SACommand cmd(&con, SAString(sConsulta));

	cmd.Execute();

	while (cmd.FetchNext())
	{
		bRegresa = true;

		sValor = cmd.Field("nombre").asString();
		m_listEmpleados.InsertItem(i, LPCTSTR(sValor));
		m_listEmpleados.SetItemText(i, 1, LPCTSTR(sValor));
		
		sValor = cmd.Field("idtex").asString();
		m_listEmpleados.SetItemText(i, 0, LPCTSTR(sValor));

		sValor = cmd.Field("puesto").asString();
		m_listEmpleados.SetItemText(i, 2, LPCTSTR(sValor));

		sValor = cmd.Field("tipoempleado").asString();
		m_listEmpleados.SetItemText(i, 3, LPCTSTR(sValor));

		i++;
	}
	return bRegresa;
}

//Funcion que se activa al dar doble click sobre algun elemento de la lista.
void CDlgBuscarEmp::OnNMDblclkListempleados(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iId_empleado = 0, iFila=0;
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	//Se toma el dato del elemento seleccionado
	iFila = m_listEmpleados.GetSelectionMark();
	iId_empleado = _wtoi(m_listEmpleados.GetItemText(iFila, 0));

	//Se crea el objeto modemp mandando a llamar al constructor sobrecargado para que mande llamar al dialogo correcto.
	CDlgEmpleado modemp(IDD_EMPACT);
	modemp.iIdEmp = iId_empleado;

	modemp.DoModal();

	//Al finalizar el modal debe actualizar los datos de la lista para ver los cambios.
	CargarEmpleados(2);

	*pResult = 0;
}

//Funcion que se manda a llamar por cada modificacion que se haga al txtBuscar
void CDlgBuscarEmp::OnEnChangeTxtbuscar()
{
	CargarEmpleados(2);
}

//Al dar click en el boton de baja se dara un borrado logico al empleado seleccionado
void CDlgBuscarEmp::OnBnClickedEliminar()
{
	int iId_empleado=0,iFila=0;
	CString sConsulta;
	
	iFila = m_listEmpleados.GetSelectionMark();

	iId_empleado = _wtoi(m_listEmpleados.GetItemText(iFila,0) );

	
	if (iFila != -1)
	{
		sConsulta.Format(_T("UPDATE empleados SET status = 0 WHERE id = %d"), iId_empleado);

		SACommand cmd(&con, SAString(sConsulta));

		cmd.Execute();
		AfxMessageBox(_T("El empleado fue dado de baja"), MB_ICONINFORMATION);

		CargarEmpleados(2);
		m_buscar.Clear();
		
	}
	else
	{
		AfxMessageBox(_T("Favor de seleccionar algún empleado"), MB_ICONSTOP);
	}
}

//Al oprimir el boton de agregarmov te mostrara la pantalla de movimientos en base a los datos del cliente seleccionado
void CDlgBuscarEmp::OnBnClickedAgregarmov()
{

	int iId_empleado = 0, iFila = 0;
	CString sConsulta;

	iFila = m_listEmpleados.GetSelectionMark();

	if (iFila != -1)
	{
		iId_empleado = _wtoi(m_listEmpleados.GetItemText(iFila, 0));

		//Se manda a llamar al constructor sobrecargado de la clase CDlgMovimientos para asignarle el id del dialogo correcto
		CDlgMovimientos modMov(IDD_MOVACT);
		
		modMov.idEmp = iId_empleado;

		modMov.DoModal();
		
	}
	else
	{
		AfxMessageBox(_T("Favor de seleccionar algún empleado"), MB_ICONSTOP);
	}
}


BOOL CDlgBuscarEmp::PreTranslateMessage(MSG* pMsg)
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

//Al darle click al boton de generar archivo te cargara todos los datos que esten en la lista a una achivo excel.
void CDlgBuscarEmp::OnBnClickedAddexcel()
{
	CString sValor;
	int iTotalItems = 0;


	xlsxiowriter XmlCreador;
	if (!((XmlCreador = xlsxiowrite_open("empleados.xlsx", "Empleados")) == NULL))
	{
		iTotalItems = m_listEmpleados.GetItemCount();

		xlsxiowrite_add_column(XmlCreador, "Id empleado", 10);
		xlsxiowrite_add_column(XmlCreador, "Nombre", 32);
		xlsxiowrite_add_column(XmlCreador, "Puesto", 32);
		xlsxiowrite_add_column(XmlCreador, "Tipo empleado", 32);
		xlsxiowrite_next_row(XmlCreador);


		for (int i = 0; i <= iTotalItems; i++)
		{

			for (int j = 0; j <= 3; j++)
			{
				sValor = m_listEmpleados.GetItemText(i, j);
				xlsxiowrite_add_cell_string(XmlCreador, SAString(sValor));

			}
			xlsxiowrite_next_row(XmlCreador);
		}
		xlsxiowrite_close(XmlCreador);
		AfxMessageBox(_T("El reporte fue creado"), MB_ICONINFORMATION);
	}
	else
	{
		AfxMessageBox(_T("Favor de cerrar el archivo"), MB_ICONSTOP);
	}
}
