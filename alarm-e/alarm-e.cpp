
// alarm-e.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "RegistDlg.h"
#include "alarm-eDlg.h"
#include "DBconsumer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CalarmeApp

BEGIN_MESSAGE_MAP(CalarmeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CalarmeApp ����

CalarmeApp::CalarmeApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CalarmeApp ��ü�Դϴ�.

CalarmeApp theApp;
CManager loginDB;
CwordFilter filterDB;	//����
HANDLE hMapFile;//����
CString ID;	//����

// CalarmeApp �ʱ�ȭ

BOOL CalarmeApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	
	/*
	SetRegistryKey(_T("Alarm-e"));	//Software �����Ʒ� �����̸�
	free( ( void* )m_pszProfileName );
	m_pszProfileName = _tcsdup(_T("Alarm-e v1.0")) ;	//Alarm-e�����Ʒ��� ����
	*/


	if(!loginDB.Open()){	//DB���� ���� ���н�
		AfxMessageBox(_T("DB���� ���� ����"));
		return 0;
	}
	

	if(loginDB.GetRecordCount()==0){	//���̵� �����Ǿ����� ����
		AfxMessageBox(_T("ù ����� ���̵� ��ȣ ����"));
		CRegistDlg rdlg;	//ȸ������ ���̾�α�
		INT_PTR nResponse=rdlg.DoModal();
	}else{
		ID=loginDB.m_ID;
	}
	if(loginDB.IsOpen())loginDB.Close();
	

	loginDB.Open();
	if(loginDB.GetRecordCount()==0){	//�����ڰ� ����� ���� �ʾҴ� �Ҹ�
		AfxMessageBox(_T("������ ���� �ʼ�"));
		loginDB.Close();
		return 0;	//��� ��
	}
	if(loginDB.IsOpen())loginDB.Close();
	
	CalarmeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}



void SetAuthority(bool Authority)//���� ����. true=������,false=����.
{
	if(hMapFile==NULL){
		//���������� �޸� ���� ���� �̸��� Alarme_authority
		hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_authority"));
	}
	//������ ������ �޸𸮸��� �����͸� �޾ƿ�
	bool* auth=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(auth,&Authority,sizeof(bool));	//�޸𸮿� ������
	UnmapViewOfFile(auth);//���ϴݱ�
	//�ڵ� �ݱ�� alarm-eDlg destroy�Ҷ�. �ڵ������ �޸𸮿��� �����
}


bool GetAuthority(void)
{
	if(hMapFile==NULL) return false;
	bool Authority(false);
	bool* auth=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&Authority,auth,sizeof(bool));	//�޸𸮿� ���о����
	return Authority;
}
