// LoginDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_ID = ID;
	m_PW = _T("");
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_ID, m_ID);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDV_MaxChars(pDX, m_ID, 20);
	DDX_Text(pDX, IDC_PW, m_PW);
	DDV_MaxChars(pDX, m_PW, 20);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기입니다.


void CLoginDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(!loginDB.Open()){	//DB파일 열기 실패시
		AfxMessageBox(_T("DB파일 열기 실패"));
		return;
	}
	
	
	if(m_PW.Compare((CString)loginDB.m_PW)!=0){
		WriteProfileInt( _T("authority"), _T("power"), 0);
	}
	
	loginDB.Close();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
