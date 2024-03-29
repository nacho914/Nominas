
// Nominas.cpp: define los comportamientos de las clases para la aplicación.
//

#define _MAIN_

#include <iostream>
#include <fstream>
#include <string>
#include "stdafx.h"
#include "Nominas.h"
#include "NominasDlg.h"
#include "CDlgPass.h"
#include "CDlgMenu.h"
#include "sysNominas.h"

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNominasApp

BEGIN_MESSAGE_MAP(CNominasApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Construcción de CNominasApp

CNominasApp::CNominasApp()
{
	// admite Administrador de reinicio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// Único objeto CNominasApp

CNominasApp theApp;


// Inicialización de CNominasApp

BOOL CNominasApp::InitInstance()
{
	// Windows XP requiere InitCommonControlsEx() si un manifiesto de
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales.  De lo contrario, se generará un error al crear ventanas.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Establecer para incluir todas las clases de control comunes que desee utilizar
	// en la aplicación.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Crear el administrador de shell, en caso de que el cuadro de diálogo contenga
	// alguna vista de árbol de shell o controles de vista de lista de shell.
	CShellManager *pShellManager = new CShellManager;

	// Activar el administrador visual "nativo de Windows" para habilitar temas en controles MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));

	CNominasDlg dlg;
	CDlgPass dlgpas;
	CDlgMenu dlgMenu;
	string line;
	int i = 0;
	CString sError;
	CString cIp, cUsuario, cContra;

	//En esta parte abre el archivo y obtiene los datos para conectarse a la BD//

	ifstream Archivo("C:\\Program Files (x86)\\Nominas\\configNomina.txt");
	
	if (Archivo.is_open())
	{
		while (getline(Archivo, line))
		{
			switch (i)
			{
			case 1:
				cIp = line.data();
				break;
			case 2:
				cUsuario = line.data();
				break;
			case 3:
				cContra = line.data();
				break;
			}
			i++;
		}
		Archivo.close();
	}

	
	try
	{
		//Se conecta a la base de datos con los datos del archivo.
		con.Connect(SAString(cIp), SAString(cUsuario), SAString(cContra), SA_PostgreSQL_Client);

		//Abre el dialogo que pide la contraseña
		dlgpas.DoModal();


		if (dlgpas.iCoincide == 1)
		{
			//En caso de que coincida la contraseña se mostrara el menu, y en base a eso se le dara la opcion a mostrar al objeto dlg
			//En caso de que la opcion sean salir se saldra del sistema.
			do{
			
				dlgMenu.DoModal();
			
				dlg.iOpcion = dlgMenu.iOpcion;
				
				if(dlgMenu.iOpcion == 1 || dlgMenu.iOpcion == 2 || dlgMenu.iOpcion == 3)
					dlg.DoModal();

			} while (dlgMenu.iOpcion == 1 || dlgMenu.iOpcion == 2 || dlgMenu.iOpcion == 3);

		}

	}
	catch (SAException &x)
	{
		
		AfxMessageBox(_T("Ocurrio un error al conectarse a la base de datos"), IDM_ABOUTBOX);

		sError.Format(_T("Detalle: %Ts"), x.ErrText());
		AfxMessageBox(sError, MB_ICONSTOP);
	}




	// Eliminar el administrador de shell creado anteriormente.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif


	return FALSE;
}

