// WordFilterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"


// CWordFilterDlg ��ȭ �����Դϴ�.

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


// CWordFilterDlg �޽��� ó�����Դϴ�.
