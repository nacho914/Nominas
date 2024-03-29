// CDlgEmpleado.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgEmpleado.h"
#include "afxdialogex.h"
#include "sysNominas.h"


// CDlgEmpleado dialog

IMPLEMENT_DYNAMIC(CDlgEmpleado, CDialog)

CDlgEmpleado::CDlgEmpleado(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EMPLEADO, pParent)
{
	iIdEmp = 0;
}

CDlgEmpleado::CDlgEmpleado(int iDlgS, CWnd* pParent /*=nullptr*/)
	: CDialog(iDlgS, pParent)
{
	iIdEmp = 0;
	iDlg = iDlgS;
}

CDlgEmpleado::~CDlgEmpleado()
{
}

void CDlgEmpleado::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXTNOMBRE, m_nombre);
	DDX_Control(pDX, IDC_TXTPATERNO, m_paterno);
	DDX_Control(pDX, IDC_TXTMATERNO, m_materno);
	DDX_Control(pDX, IDC_RBChofer, m_chofer);
	DDX_Control(pDX, IDC_RBCARGADOR, m_cargador);
	DDX_Control(pDX, IDC_INTERNO, m_interno);
	DDX_Control(pDX, IDC_EXTERNO, m_externo);
	DDX_Control(pDX, IDC_RBAUX, m_aux);
	DDX_Control(pDX, IDC_TXTNUM, m_idemp);
}


BEGIN_MESSAGE_MAP(CDlgEmpleado, CDialog)
ON_BN_CLICKED(ID_ADDEmpleado, &CDlgEmpleado::OnBnClickedAddempleado)
END_MESSAGE_MAP()

//Funcion unicamente creada para devolver los datos de los radio buttons

BOOL CDlgEmpleado::ObtenerDatosCaptura( int &iRol, int &iTipo)
{
	
	if (m_chofer.GetCheck())
	{
		iRol = 1;
	}
	else if (m_cargador.GetCheck())
	{
		iRol = 2;
	}
	else if (m_aux.GetCheck())
	{
		iRol = 3;
	}

	if (m_interno.GetCheck())
	{
		iTipo = 1;
	}
	else if (m_externo.GetCheck())
	{
		iTipo = 2;
	}
	return false;
}

//Funcion que se manda a llamar al inicializar el dialogo
BOOL CDlgEmpleado::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString sConsulta,sValor;
	int iRol=0, iIipoempleado=0;
	m_nombre.SetFocus();

	//Esta variable nos indica si es o no modificion,
	//En el caso que lo sea cargara los datos que ya tenga el cliente al dialogo

	if (iIdEmp != 0)
	{

		sValor.Format(_T("%d"), iIdEmp);
		m_idemp.SetWindowTextW(sValor);

		sConsulta.Format(_T("SELECT TRIM(nombre) as nom, trim(apellidopaterno) as paterno, trim(apellidoMaterno) as materno, puesto, tipoempleado FROM EMPLEADOS WHERE id = %d"), iIdEmp);

		SACommand cmd(&con, SAString(sConsulta));

		cmd.Execute();

		while (cmd.FetchNext())
		{
			// Se asignan los valores a los controles.

			sValor = cmd.Field("nom").asString();
			m_nombre.SetWindowTextW(sValor);
			sValor = cmd.Field("paterno").asString();
			m_paterno.SetWindowTextW(sValor);
			sValor = cmd.Field("materno").asString();
			m_materno.SetWindowTextW(sValor);

			iRol = cmd.Field("puesto").asLong();
			iIipoempleado = cmd.Field("tipoempleado").asLong();

			switch (iRol)
			{
			case 1:
				m_chofer.SetCheck(1);
				break;
			case 2:
				m_cargador.SetCheck(1);
				break;
			case 3:
				m_aux.SetCheck(1);
				break;
			}

			if (iIipoempleado == 1)
				m_interno.SetCheck(1);

			else if (iIipoempleado == 2)
				m_externo.SetCheck(1);

		}

	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Funcion que se utiliza para dejar vacios los controles
void CDlgEmpleado::limpiarDialogo()
{

	m_nombre.SetWindowTextW(_T(""));
	m_paterno.SetWindowTextW(_T(""));
	m_materno.SetWindowTextW(_T(""));
	
	m_chofer.SetCheck(0);
	m_cargador.SetCheck(0);
	m_aux.SetCheck(0);
	m_interno.SetCheck(0);
	m_externo.SetCheck(0);

}

//Funcion utulizada para validar el nombre del empleado y sus puestos
BOOL CDlgEmpleado::ValidaDatos()
{
	bool bRegresa = true;
	CString sValor;

	m_nombre.GetWindowTextW(sValor);
	if (sValor.Trim().IsEmpty() || !soloLetras(sValor))
		return false;

	
	m_paterno.GetWindowTextW(sValor);
	if (sValor.Trim().IsEmpty() || !soloLetras(sValor))
		return false;

	m_materno.GetWindowTextW(sValor);
	if (!soloLetras(sValor))
		return false;

	if (m_chofer.GetCheck() == 0 && m_cargador.GetCheck() == 0 && m_aux.GetCheck() == 0)
		return false;
	

	if (m_interno.GetCheck() == 0 && m_externo.GetCheck() == 0)
		return false;
	
	return bRegresa;

}

//Funcion que validad caracter por caracter que sea un caracter alfabetico o bien un espacio en blanco
BOOL CDlgEmpleado::soloLetras(CString letras)
{
	bool bRegresa = true;

	for (int i = 0; i < letras.GetLength(); i++) {
		if (!isalpha(letras[i]) && letras[i] != 32 )
			return false;
	}

	return bRegresa;
}

BOOL CDlgEmpleado::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			//Esto indicara que solo salga en caso de que sea llamado por modificacion con las teclas ESC o Enter
			if (iIdEmp != 0)
				OnOK();
			else
				return TRUE;                
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


//Funcion que actualiza o inserta datos del empleado.
void CDlgEmpleado::OnBnClickedAddempleado()
{
	CString sNombre, sPaterno, sMaterno, sConsulta;
	int iRol = 0, iTipo = 0, iValorRegresa = 0;

	if (ValidaDatos())
	{
		m_nombre.GetWindowTextW(sNombre);
		m_paterno.GetWindowTextW(sPaterno);
		m_materno.GetWindowTextW(sMaterno);

		ObtenerDatosCaptura(iRol, iTipo);

		//En caso de que la variable iIdEmp este en cero nos indica que el caso sera una insercion caso contrario se tomara como una actualizacion
		if (iIdEmp == 0)
			sConsulta.Format(_T("SELECT insertaEmpleado('%Ts','%Ts','%Ts',%d, %d) AS resultado"), sNombre, sPaterno, sMaterno, iRol, iTipo);
		else
			sConsulta.Format(_T("SELECT ActualizaEmpleado('%Ts','%Ts','%Ts',%d, %d, %d) AS resultado"), sNombre, sPaterno, sMaterno, iRol, iTipo, iIdEmp);



		SACommand cmd(&con, SAString(sConsulta));

		cmd.Execute();

		while (cmd.FetchNext())
		{
			//Se toma el valor del resultado que si es una insercion sera el id del nuevo empleado.
			iValorRegresa = int(cmd.Field("resultado").asLong());

		}

		if (iValorRegresa != -1)
		{
			if (iIdEmp == 0)
			{
				sConsulta.Format(_T("Su ID de empleado es: %d"), iValorRegresa);
				AfxMessageBox(sConsulta, MB_ICONINFORMATION);
				limpiarDialogo();

			}
			else
			{
				AfxMessageBox(_T("El empleado se ha actualizado"), MB_ICONINFORMATION);
				OnOK();
			}
		}
		else
		{

			AfxMessageBox(_T("Ya existe un empleado con ese nombre"), MB_ICONSTOP);

		}
	}
	else
		AfxMessageBox(_T("Favor de verificar los datos de nuevo"), MB_ICONSTOP);
}
