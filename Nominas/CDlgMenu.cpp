// CDlgMenu.cpp : implementation file
//

#include "stdafx.h"
#include "Nominas.h"
#include "CDlgMenu.h"
#include "afxdialogex.h"


// CDlgMenu dialog

IMPLEMENT_DYNAMIC(CDlgMenu, CDialog)

CDlgMenu::CDlgMenu(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MENU, pParent)
{
	iOpcion = 0;

}

CDlgMenu::~CDlgMenu()
{
}

void CDlgMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMenu, CDialog)
END_MESSAGE_MAP()


// CDlgMenu message handlers


BOOL CDlgMenu::PreTranslateMessage(MSG* pMsg)
{
	
	if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
			case VK_F2:
				iOpcion = 1;
				OnOK();
				break;
			case VK_F3:
				iOpcion = 2;
				OnOK();
				break;
			case VK_F4:
				iOpcion = 3;
				OnOK();
				break;
			case VK_RETURN:
			case VK_ESCAPE:
				iOpcion = 4;
				OnOK();
				break;
			
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}



void CDlgMenu::OnCancel()
{
	
	iOpcion = 0;

	CDialog::OnCancel();
}
