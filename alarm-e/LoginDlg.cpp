// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg ��ȭ �����Դϴ�.

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


// CLoginDlg �޽��� ó�����Դϴ�.


void CLoginDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(!loginDB.Open()){	//DB���� ���� ���н�
		AfxMessageBox(_T("DB���� ���� ����"));
		return;
	}
	if(m_PW.Compare((CString)loginDB.m_PW)==0){	//�н����尡 ������
		::SetAuthority(true);	//��������
		AfxMessageBox(_T("������ �α��� �Ǿ����ϴ�."));
		loginDB.Close();
	}else{
		AfxMessageBox(_T("��й�ȣ�� Ʋ�Ƚ��ϴ�."));
		loginDB.Close();
		return;
	}

	CDialogEx::OnOK();
}
