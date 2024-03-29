// CDlgMovimientos.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgMovimientos.h"
#include "afxdialogex.h"
#include "sysNominas.h"


// CDlgMovimientos dialog

IMPLEMENT_DYNAMIC(CDlgMovimientos, CDialog)

CDlgMovimientos::CDlgMovimientos(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MOVIMIENTOS, pParent)
{
	iRol = 0;
	iTipo = 0;
	idMov = 0;
	idEmp = 0;

}

CDlgMovimientos::CDlgMovimientos(int iDlgS, CWnd* pParent /*=nullptr*/)
	: CDialog(iDlgS,pParent)//IDD_MOVIMIENTOS, pParent)
{
	iDlg = iDlgS;
	iRol = 0;
	iTipo = 0;
	idMov = 0;
	idEmp = 0;

}

CDlgMovimientos::~CDlgMovimientos()
{
}

void CDlgMovimientos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXTNUM, m_numemp);
	DDX_Control(pDX, IDC_NOMBRE, m_nombre);
	DDX_Control(pDX, IDC_TIPO, m_tipo);
	DDX_Control(pDX, IDC_ROL, m_rol);

	DDX_Control(pDX, IDC_CUBRIO, m_cuadro);
	DDX_Control(pDX, IDC_CHOFER, m_radChofer);
	DDX_Control(pDX, IDC_CARGA, m_radCarga);
	DDX_Control(pDX, IDC_RADCUB, m_radCubrio);
	DDX_Control(pDX, IDC_DTPFECHA, m_fecha);
	DDX_Control(pDX, IDC_TXTENTREGAS, m_cantEntregas);
	DDX_Control(pDX, IDADDMOVIMIENTO, m_btnPrincipal);
}


BEGIN_MESSAGE_MAP(CDlgMovimientos, CDialog)
ON_BN_CLICKED(IDADDMOVIMIENTO, &CDlgMovimientos::OnBnClickedAddmovimiento)
ON_WM_CREATE()
ON_BN_CLICKED(IDC_BTNCARGAR, &CDlgMovimientos::OnBnClickedBtnCargar)
END_MESSAGE_MAP()


// CDlgMovimientos message handlers



//Al oprimir el boton de addMovimientos se actualizara o inseraran datos dependiendo de la variable idMov
void CDlgMovimientos::OnBnClickedAddmovimiento()
{
	CString sNumeroEmp, sEntregas,sFecha, sConsulta;
	int iPuestoCubrio = 0,iResultado=0;


	m_numemp.GetWindowTextW(sNumeroEmp);
	
	if(!sNumeroEmp.IsEmpty())
	{
		if (CargarDatos(1))
		{
			iPuestoCubrio = regresaPuestoCubierto();

			m_cantEntregas.GetWindowTextW(sEntregas);
			m_fecha.GetWindowTextW(sFecha);

			if (sEntregas.IsEmpty())
				sEntregas = "0";

			if (idMov == 0)
				sConsulta.Format(_T("SELECT insertaMovimiento(%Ts,%d,%d,%d,%Ts,'%Ts') AS resultado"), sNumeroEmp, iRol, iPuestoCubrio, iTipo, sEntregas, sFecha);
			else
				sConsulta.Format(_T("SELECT ActualizaMovimiento(%Ts,%d,%d,%d,%Ts,'%Ts',%d) AS resultado"), sNumeroEmp, iRol, iPuestoCubrio, iTipo, sEntregas, sFecha, idMov);


			SACommand cmd(&con, SAString(sConsulta));

			cmd.Execute();

			while (cmd.FetchNext())
			{
				iResultado = int(cmd.Field("resultado").asLong());
			}

			if (iResultado == 1)
			{
				if (idMov == 0)
					AfxMessageBox(_T("El movimiento ha sido agregado"), MB_ICONINFORMATION);
				else
				{
					AfxMessageBox(_T("El movimiento ha sido modificado"), MB_ICONINFORMATION);
					OnOK();
				}
			}
			else if (iResultado == -1)
				AfxMessageBox(_T("El empleado ya tiene un movimiento registrado ese dia!"), MB_ICONSTOP);
		}
		else
			AfxMessageBox(_T("Favor de ingresar un numero de empleado valido"), MB_ICONSTOP);
	}
	else
		AfxMessageBox(_T("Favor de ingresar un numero de empleado valido"), MB_ICONSTOP);
}

//Funcion que regresa el valor del puesto seleccionado en los radiobuttons unicamente si el empleado tiene el rol 3
int CDlgMovimientos::regresaPuestoCubierto()
{
	int iPuesto = 0;

	if (iRol == 3)
	{
		if (m_radChofer.GetCheck())
			iPuesto = 1;
		
		else if(m_radCarga.GetCheck())
			iPuesto = 2;			
	}
	
	return iPuesto;
}

int CDlgMovimientos::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

//Funcion que se carga al inicializar el dialogo en este caso seran dos opciones
//Si el valor de idMov es diferente de cero indicara que se mostraran los datos de un movimiento anterior
//Si el valor de idEmp es diferente de cero indicara que se mostraran los datos de un cliente.

BOOL CDlgMovimientos::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_cantEntregas.SetWindowTextW(_T("0"));
	
	if (idMov != 0)
	{
		CargarDatos(2);
	}
	else if (idEmp != 0)
	{
		CargarDatos(3);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Funcion que traera tres diferentes consultas dependiendo de la situacion
//Opcion 1 Cargara los datos del cliente que se hayan seleccionado dentro del textbox
//Opcion 2 Cargara los datos del movimiento seleccionado en la pantalla de buscar movimiento
//Opcion 3 Cargara los datos del cliente seleccionado en la pantalla de buscar cliente

BOOL CDlgMovimientos::CargarDatos(int iOpcion)
{
	CString sConsulta, sValor;
	SYSTEMTIME sysTime;
	memset(&sysTime, 0, sizeof(sysTime));
	int iRolCubierto = 0, iRolMovimiento = 0;
	bool bRegresa= true;
	
	if (iOpcion == 1)
	{
		m_numemp.GetWindowTextW(sValor);
		sConsulta.Format(_T("SELECT a.id::text as idemp,(TRIM(a.nombre)||' '|| trim(a.apellidopaterno) || ' '||TRIM(a.apellidoMaterno))::text as nombre,b.descripcion as puesto,c.descripcion as tipo, b.idrol as idrol, c.idtipo as idtipo from empleados as a inner join rol as b on a.puesto = b.idrol inner join tipo as c on a.tipoempleado = idtipo WHERE a.status = 1 AND a.id = %Ts"), sValor);

	}
	else if(iOpcion == 2)
	{
		m_btnPrincipal.SetWindowTextW(_T("Actualiza Movimiento"));
		sConsulta.Format(_T("SELECT a.idempleado::text as idemp,a.fechamovimiento as fechamov, (TRIM(b.nombre)||' '|| trim(b.apellidopaterno) || ' '||TRIM(b.apellidoMaterno))::text as nombre, TRIM(c.descripcion) as puesto, TRIM(d.descripcion) as tipo, TRIM(e.descripcion) as puestoc, a.cantidadentregas as cant,a.puesto as idrol,a.puestocubrio as idrolc,a.tipoempleado as idtipo  from movimientos as a inner join empleados as b ON a.idempleado = b.id inner join rol as c on a.puesto = c.idrol inner join tipo as d  ON a.tipoempleado =d.idtipo LEFT join rol as e on a.puestocubrio = e.idrol WHERE a.idmovimiento = %d order by a.fechamovimiento"), idMov);
	}
	else if (iOpcion == 3)
	{

		sConsulta.Format(_T("SELECT a.id::text as idemp, (TRIM(a.nombre)||' '|| trim(a.apellidopaterno) || ' '||TRIM(a.apellidoMaterno))::text as nombre,TRIM(b.descripcion) as puesto,TRIM(c.descripcion) as tipo, b.idrol as idrol, c.idtipo as idtipo from empleados as a inner join rol as b on a.puesto = b.idrol inner join tipo as c on a.tipoempleado = idtipo where a.id = %d"), idEmp);

	}

	SACommand cmd(&con, SAString(sConsulta));

	cmd.Execute();

	if (cmd.FetchNext())
	{
		sValor = cmd.Field("idemp").asString();
		m_numemp.SetWindowTextW(sValor);
		
		if(iOpcion!=1)
			m_numemp.SetReadOnly();

		sValor = cmd.Field("nombre").asString();
		m_nombre.SetWindowTextW(sValor);

		sValor = cmd.Field("puesto").asString();
		m_rol.SetWindowTextW(sValor);

		sValor = cmd.Field("tipo").asString();
		m_tipo.SetWindowTextW(sValor);
		
		iRol = cmd.Field("idrol").asLong();
		iTipo = cmd.Field("idtipo").asLong();
		
		//Solo mostrara los radiobuttons en caso que sea un empleado auxiliar.

		if (iRol == 3)
		{
			m_radCarga.ShowWindow(SW_SHOW);
			m_radChofer.ShowWindow(SW_SHOW);
			m_cuadro.ShowWindow(SW_SHOW);
			m_radCubrio.ShowWindow(SW_SHOW);
		}
		else
		{
			m_radCarga.ShowWindow(SW_HIDE);
			m_radChofer.ShowWindow(SW_HIDE);
			m_cuadro.ShowWindow(SW_HIDE);
			m_radCubrio.ShowWindow(SW_HIDE);
		}

		if(iOpcion == 2)
		{

			iRolCubierto = cmd.Field("idrolc").asLong();

			sValor = cmd.Field("cant").asString();
			m_cantEntregas.SetWindowTextW(sValor);

			sysTime.wYear = cmd.Field("fechamov").asDateTime().GetYear();
			sysTime.wMonth = cmd.Field("fechamov").asDateTime().GetMonth();
			sysTime.wDay = cmd.Field("fechamov").asDateTime().GetDay();

			m_fecha.SetTime(&sysTime);

			iRol = cmd.Field("idrol").asLong();
			iRolCubierto = cmd.Field("idrolc").asLong();
			iTipo = cmd.Field("idtipo").asLong();

			switch (iRolCubierto)
			{
			case 0:
				m_radCubrio.SetCheck(1);
				m_radChofer.SetCheck(0);
				m_radCarga.SetCheck(0);
				break;
			case 1:
				m_radChofer.SetCheck(1);
				m_radCubrio.SetCheck(0);
				m_radCarga.SetCheck(0);
				break;
			case 2:
				m_radCarga.SetCheck(1);
				m_radChofer.SetCheck(0);
				m_radCubrio.SetCheck(0);
				break;

			}
		}

	}
	else if (iOpcion == 1)
	{
		bRegresa = false;
		LimpiarDatos();

	}


	return bRegresa;
}

//Funcion que pone vacios los datos del dialogo
void CDlgMovimientos::LimpiarDatos()
{

	m_numemp.SetWindowTextW(_T(""));
	m_nombre.SetWindowTextW(_T(""));
	m_rol.SetWindowTextW(_T(""));
	m_tipo.SetWindowTextW(_T(""));
	iRol = 0;
	iTipo = 0;
	m_radCubrio.SetCheck(1);
	m_cantEntregas.SetWindowTextW(_T("0"));

}

//Funcion que se mandara a llamar cuando de click en cargar empleado
void CDlgMovimientos::OnBnClickedBtnCargar()
{
	CString sValor;
	m_numemp.GetWindowTextW(sValor);
	if (!sValor.IsEmpty())
	{
		if(!CargarDatos(1))
			AfxMessageBox(_T("Favor de colocar un id de empleado valido"), MB_ICONSTOP);
	}
	else
		AfxMessageBox(_T("Favor de colocar un id de empleado"), MB_ICONSTOP);
}



BOOL CDlgMovimientos::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			//Solo permitira salir del sistema por enter o Escape cuando el movimiento sea por modificacion
			if (idMov != 0 || idEmp != 0)
				OnOK();
			else
				return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
