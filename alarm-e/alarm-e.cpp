
// alarm-e.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CalarmeApp 생성

CalarmeApp::CalarmeApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CalarmeApp 개체입니다.

CalarmeApp theApp;
CManager loginDB;
CwordFilter filterDB;	//전역
HANDLE hMapFile;//전역
HANDLE hMapFile2;//전역
CString ID;	//전역

// CalarmeApp 초기화

BOOL CalarmeApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	if(SetRunning()) return 0; //중복 실행중이면 
	
	SetRegistryKey(_T("Alarm-e"));	//Software 폴더아래 폴더이름
	free( ( void* )m_pszProfileName );
	m_pszProfileName = _tcsdup(_T("Alarm-e v1.0")) ;	//Alarm-e폴더아래의 폴더
	


	if(!loginDB.Open()){	//DB파일 열기 실패시
		AfxMessageBox(_T("DB파일 열기 실패"));
		return 0;
	}
	

	if(loginDB.GetRecordCount()==0){	//아이디가 생성되어있지 않음
		loginDB.Close();
		AfxMessageBox(_T("첫 실행시 아이디 암호 생성"));
		CRegistDlg rdlg;	//회원가입 다이얼로그
		INT_PTR nResponse=rdlg.DoModal();
	}else{
		ID=loginDB.m_ID;
		loginDB.Close();
	}
	
	
	if(!loginDB.IsOpen())loginDB.Open();	
	if(loginDB.GetRecordCount()==0){	//관리자가 등록이 되지 않았단 소리
		AfxMessageBox(_T("관리자 가입 필수"));
		loginDB.Close();
		return 0;	//고로 끔
	}
	if(loginDB.IsOpen())loginDB.Close();
	
	CalarmeDlg dlg; //메인 다이얼로그
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


//~~~~~전역함수들~~~~~~
bool SetRunning()	//실행중 설정값이 true면 true리턴. 아니면 false리턴
{
	hMapFile2=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_running"));
	bool running(false);
	bool *mem=(bool*)MapViewOfFile(hMapFile2,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&running,mem,sizeof(bool));
	if(running) return true;		
	else{
		running=true;
		memcpy(mem,&running,sizeof(bool));
		return false;
	}
}

void SetAuthority(bool Authority)//권한 설정. true=관리자,false=유저.
{
	if(hMapFile==NULL){
		//전역변수에 메모리 매핑 생성 이름은 Alarme_authority
		hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_authority"));
	}
	//권한을 저장할 메모리맵의 포인터를 받아옴
	bool* auth=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(auth,&Authority,sizeof(bool));	//메모리에 값쓰기
	UnmapViewOfFile(auth);//파일닫기
	//핸들 닫기는 alarm-eDlg destroy할때. 핸들닫으면 메모리에서 사라짐
}



bool GetAuthority(void)	//권한 가져오기
{
	if(hMapFile==NULL) return false;
	bool Authority(false);
	bool* auth=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&Authority,auth,sizeof(bool));	//메모리에 값읽어오기
	return Authority;
}