// FullScreenDlg.cpp : 구현 파일입니다.
//



#include "stdafx.h"
#include "alarm-e.h"
#include "FullScreenDlg.h"
#include "afxdialogex.h"

// CFullScreenDlg 대화 상자입니다.

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


// CFullScreenDlg 메시지 처리기입니다.


BOOL CFullScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_MAXIMIZE);
	m_pcFullScreen.SetBitmap(hBitmap);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFullScreenDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnOK();
}
