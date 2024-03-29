// CDlgPass.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgPass.h"
#include "afxdialogex.h"



// CDlgPass dialog

IMPLEMENT_DYNAMIC(CDlgPass, CDialog)

CDlgPass::CDlgPass(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PASS, pParent)
	, m_pass(_T(""))
{
	//Se inicializan variables internas.
	iCoincide = 0;

}

CDlgPass::~CDlgPass()
{
}

void CDlgPass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTRA, m_contra);
}



BEGIN_MESSAGE_MAP(CDlgPass, CDialog)
END_MESSAGE_MAP()


// CDlgPass message handlers


BOOL CDlgPass::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			//Por cada enter que se de se intentara coincidir la contraseña.
			if (CoincideContraseña())
			{
				OnOK();
			}
			else
			{
				AfxMessageBox(_T("Favor de ingresar la contraseña correcta"), MB_OK | MB_ICONSTOP);
			}

			return TRUE;                // Do not process further
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


//Funcion utilizada para tomar el valor del textbox del dialogo y compararla con la de la base de datos
BOOL CDlgPass::CoincideContraseña()
{
	bool bRegresa = false;
	CString sConsulta,sContra;

	m_contra.GetWindowTextW(sContra);
	sConsulta.Format(_T("Select contra from password WHERE contra = '%Ts'"), sContra);

	SACommand cmd( &con, SAString(sConsulta));

	cmd.Execute();
	while (cmd.FetchNext())
	{
		bRegresa = true;
		iCoincide = 1;
	}

	return bRegresa;
}