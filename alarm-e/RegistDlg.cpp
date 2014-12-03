// RegistDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
#include "MultipartUpload.h"

// CRegistDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRegistDlg, CDialogEx)

CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegistDlg::IDD, pParent)
{
	m_ID = _T("");
	m_PW = _T("");
	m_PWconfirm = _T("");
}

CRegistDlg::~CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDV_MaxChars(pDX, m_ID, 20);
	DDX_Text(pDX, IDC_PW, m_PW);
	DDV_MaxChars(pDX, m_PW, 20);
	DDX_Text(pDX, IDC_PWconfirm, m_PWconfirm);
	DDV_MaxChars(pDX, m_PWconfirm, 20);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegistDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegistDlg �޽��� ó�����Դϴ�.


void CRegistDlg::OnBnClickedOk()
{
	UpdateData(TRUE); 
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//��ȿ�� �˻��ϴ� �κ�.
	if(m_ID.IsEmpty()){
		AfxMessageBox(_T("���̵� �Է��� �ּ���"));
		return;
	}else if(m_PW.IsEmpty()){
		AfxMessageBox(_T("�н����带 �Է��� �ּ���"));
		return;
	}else if(!onlyASCIIcheck(m_ID)){
		AfxMessageBox(_T("���̵�� ���� ���� ��ȣ�� ���ּ���"));
		return;
	}else if(!onlyASCIIcheck(m_PW)){
		AfxMessageBox(_T("�н������ ���� ���� ��ȣ�� ���ּ���"));
		return;
	}else if(m_PWconfirm.IsEmpty()){
		AfxMessageBox(_T("�н����� Ȯ���� �Է��� �ּ���"));
		return;
	}else if(m_PW.Compare(m_PWconfirm)){
		AfxMessageBox(_T("�н����尡 ��ġ���� �ʽ��ϴ�."));
		return;
	}
	
	/*
		�̺κп� ������ ������ ���� �� ����.
	*/
	CString response;
	response.Format(_T("������ ���ϱ�: %s"),MultipartUpload::join(m_ID,m_PW));
	AfxMessageBox(response);
	if(response.Compare(_T("������ ���ϱ�: ok"))==0){
		//��� ���
		loginDB.Open();
		loginDB.AddNew();	//�� ���ڵ� �߰�
		loginDB.m_ID=m_ID;	//���̵� �ְ�
		loginDB.m_PW=m_PW;	//�н����� �ְ�
		loginDB.Update();	//Ŀ��
		//������Ʈ���� ���
		theApp.WriteProfileString(_T("registrant"), _T("ID"), m_ID);
		::SetAuthority(true);//�α��� ����
	}else{
		loginDB.Close();
		return;
	}
	loginDB.Close();
	CDialogEx::OnOK();
}


bool CRegistDlg::onlyASCIIcheck(CString str)
{
	long nLen = str.GetLength();
 	for( long i=0 ; i < nLen ; ++i)
	{
	   BYTE tt = str.GetAt(i);

	   if( IsDBCSLeadByte(tt) )
	   {
		   return false;
	   }
	}
	return true;
}
