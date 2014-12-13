// FullScreenDlg.cpp : ���� �����Դϴ�.
//



#include "stdafx.h"
#include "alarm-e.h"
#include "FullScreenDlg.h"
#include "afxdialogex.h"

// CFullScreenDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFullScreenDlg, CDialogEx)

CFullScreenDlg::CFullScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFullScreenDlg::IDD, pParent)
{

}

CFullScreenDlg::~CFullScreenDlg()
{
}

void CFullScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FULL_SCREEN, m_pcFullScreen);
}


BEGIN_MESSAGE_MAP(CFullScreenDlg, CDialogEx)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CFullScreenDlg �޽��� ó�����Դϴ�.


BOOL CFullScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_MAXIMIZE);
	m_pcFullScreen.SetBitmap(hBitmap);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CFullScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnOK();
}
