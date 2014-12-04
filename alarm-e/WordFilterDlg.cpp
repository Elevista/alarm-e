// WordFilterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"


// CWordFilterDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWordFilterDlg, CDialogEx)

CWordFilterDlg::CWordFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWordFilterDlg::IDD, pParent)
{
	SetBackgroundColor(RGB(255,255,255));
}

CWordFilterDlg::~CWordFilterDlg()
{
}

void CWordFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWordFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordFilterDlg 메시지 처리기입니다.
