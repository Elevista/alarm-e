#include "stdafx.h "
#include "alarm-e.h"
#include "alarm-eDig .h"
#include "Alarm_UILogin.h"
#include "Ala rm_UICh i ld.h"
#include "Alarm_UIParent . h"
#include "JKRegistry.h"
#include "Jpeg.h"
#include <GdiPlus.h>
#include "DBDataForm.h "
#include "Alarm_UIPopup.h"
using namespace Gdiplus;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern CJSHook g_JSHook;

// CalarmeApp

BEGIN_MESSAGE_MAP(CalarmeApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()
//CalarmeApp 생성

CalarmeApp::CalarmeApp()
	: n_captureTime()
	, m_captureDirectory(L " ..WWcaptureWW")
{
	time_Boot = time_AfterCapture = CTime::GetCurrentTime();
	m_hOidhWnd = NULL ;
}

CalarmeApp::~CalarmeApp()
{
	time_ShutDown = CTime::GetCurrentTime();
}
// 유일한 CalarmeApp 개체입니다.
CalarmeApp theApp;
//CalarmeApp 초기화.
BOOL CaIarmeApp::InitInstance()
{
	WNDCLASS wClass;
	::GetCiasslnfo(AfxGet lnstanceHandle(), _T("#32770"), &wClass);
	wClass.lpszCiassName = _T("CAiarm_UIChild");


	bool bOk = AfxRegisterClass(&wCiass);


	INITCOMMONCONTROLSEX lnitCtrls;
	lnitCtrls.dwSize = sizeof(lnitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이항목을 설정하십시오.
	lnitCtrls.dwlCC = ICC_WIN95_CLASSES;
	lnitCommonControlsEx(&lnitCtrls);

	CWinAppEx::lnitlnstance();

	AfxEnableControlContainer();

	GdiplusStartuplnput gpsi;
	if (GdiplusStartup(&m_gpToken,&gpsi,NULL) != Ok) {
		AfxMessageBox(TEXT("GD|+ 라이브러리를 초기화할 수 없습니다.")); // 메세지 상자를 표시
		return FALSE;
	}

	JKRegistry reg;
	reg.SetHKey(HKEY_LOCAL_MACHINE);
	reg.SetPath(TEXT("SoftwareWWAIarmE")) ;
	reg.SetName(TEXT("IsSetupODBC"));
	int nAutoStart = O;
	nAutoStart = reg.Getlnteger();
	if(nAutoStart == 0) //자동설치하십쇼
	{
		OnOdbcAutoSetup();
		reg.Setlnteger(1);
	}

	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램")); 

	RECT rect = {0,0,1,1};

	CAlarm_UILogin dig;
	dIg.DoModaI();


	return FALSE;

}
void CalarmeApp::lnitForReLoad()
{
	JKRegistry reg;
	reg.SetHKey(HKEY_CURRENT_USER);
	reg.SetPath(TEXT("Software\\AiarmE\\Mode"));
	reg.SetName(TEXT("IsChild"));
	m_bIsChiId = reg.GetInteger();

	m_blsAiram =false;
	m_blsAiram2 =false;
	m_blsAiram3 =false;
	theApp.m_szCaptureDirectory = " .. //capture//";
	GetTimeSetData();
	theApp.LoadRcvMessages(1);  //자녀모드
	theApp.LoadRcvMessages(0); //부모님 모드




	ReAlramTime = O;
	ReAlramTime2 = O;
	ReAlramTime3 = O;

	HookFinishThreadFunction();
	HookStartingThread();
}

int CalarmeApp::ExitInstance()
{
	GdiplusShutdown(m_gpToken);

	return CWinApp::ExiInstance();
}
void CalarmeApp::HookStartingThread()
{
	if (m_hThreadHook !=NULL) HookFinishThreadFunction();
	m_hThreadHook = ::CreateThread(NULL, 0, HookThreadFunction , (PVOID)this, 0, NULL);
}


// 실 프로시져
DWORD WINAPI CalarmeApp::HookThreadFunction(LPVOID pParent)
{
	CalarmeApp * pAlarmApp = (CalarmeApp *)pParent;

	CreateDirectory(pAlarmApp->m_captureDirectory, NULL);

	JKRegistry reg;
	reg.SetHKey(HKEY_CURRENT_USER);
	reg.SetPath(TEXT("Software\\AlarmE\\Parent\\Capture"));
	reg.SetName(TEXT("LevelSetting"));

	pAlarmApp->n_captureLevel = reg.Getlnteger() ;
	reg.SetName(TEXT("CaptureTime"));


	pAlarmApp->n_captureTime = reg.Getlnteger();
	if(pAlarmApp->n_captureTime == 0) pAlarmApp->n_captureTime = 60;

	//Capture();
	//작업끝난뒤 주석풀기
	//pAlarmApp->Capture();

	whiIe(1)
	{
		HWND currentHwnd ;
		TCHAR str[MAX_PATH] = {0,};
		CString message;


		//GetDesktopWindow
		currentHwnd = GetDesktopWindow();
		//GetDesktopWindow() ->GetSafeHwnd( ); //가장 상위의 핸들
		currentHwnd = ::GetWindow(currentHwnd, GW_CHILD);

		if(!pAIarmApp->Active_List_Browser.IsEmpty())
		{
			pAlarmApp->initCheckList(&pAiarmApp->Active_List_Browser,FALSE);
		}
		if(lpAlarmApp->Active_List_Piayer.lsEmpty()) 
		{
			pAlarmApp->initCheckList(&pAlarmApp->Active_List_Piayer ,FALSE);
		}
		if( !pAlarmApp->Active_List_Games.lsEmpty())
		{
			pAlarmApp->initChecklist(&pAlarmApp->Active_List_Games,FALSE);
		}
		int n_startTime, n_nowTime;

		CTimeSpan timeDifference;
		CTime timeNow = CTime::GetCurrentTime();
		timeDifference = timeNow - theApp.time_Boot;
		int minutes = timeDifference.GetMinutes();
		int nowMinute = timeNow.GetHour() * 60 + timeNow.GetMinute();

		while(currentHwnd != NULL)
		{
			TCHAR className[MAX_PATH] = {0,};
			TCHAR programName[MAX_PATH] = {0,};
			// 인터넷 브라우저일 경우 찾아내기
			if(pAlarmApp->lsBrowser(currentHwnd)
				&& !pAlarmApp->HwndCmp(currentHwnd ,&pAlarmApp->Active_List_Browser) && pAlarmApp->m_blsChi ld ==TRUE)
			{
				HWND currHWnd = GetForegroundWindow();
				SStrt temp;
				temp.m_hwnd = currentHwnd;
				::GetWindowText(currentHwnd, temp.m_Name,sizeof(temp.m_Name));


				HWND returnHwnd;
				::SendMessage(returnHwnd = pAlarmApp->GetAddressBar(currentHwnd), WM_GETTEXT,MAX_PATH, (LPARAM) temp.m_URL); 
				temp.m_StartTime = CTime: :GetCurrentTime() ;
				temp.IsCheck= TRUE;


				if(currHWnd != pAlarmApp->m_hOldhWnd && theApp.m_blsChild)
				{
					if(isHook() == false && isArtHook() == false)
					{
						if(isDeiHook() == false)
							Hook();
					}
				}
				//차단 URL일 경우만 저장
				BOOL isBlockedURL = pAlarmApp->inspectURL((CString)temp.m_URL);
				if(returnHwnd !=NULL && isBlockedURL && pAlarmApp->m_blsChild ==TRUE)
				{

					theApp.ReAiramTime3 = nowMinute + 2;
					theApp.m_blsAfram3 = true;

					CAlarm_UIPopup dlg2;
					dlg2 .SetMessage(L "이 사이트는 접근이 금지된 사이트입니다.Wn");


				}
				//dlg2.SetPosition() ;
				dlg2.DoModal ();
				//강의목록일경우 추가
				BOOL isEduURL = pAlarmApp->inspectEduURL((CString)temp.m_URL) ;
				if(returnHwnd !=NULL && isEduURL && pAlarmApp->m_blsChild ==TRUE)
				{
					pAlarmApp->Active_List_Browser.AddHead(temp);
				}
				pAlarmApp->m_hOidhWnd = currHWnd;
			}
			else if(currentHwnd == pAlarmApp->m_hOidhWnd)
			{
				if(pAlarmApp->m_blsChild ==TRUE)
				{

					if(isHook())
					{

						OutputDebugString(L"Hook - Stop Wn");
						UnHook();
						keyStrInit();
					}
				}
			}
			//동영상 플레이어일 경우 찾아내기
			if(pAlarmApp->lsPlayer(currentHwnd))
			{
				if(!pAlarmApp->HwndCmp(currentHwnd,&pAlarmApp->Active_List_Player))
				{
					SStrttemp ;
					temp.m_hwnd = current Hwnd ; 
					::GetWindowText(currentHwnd, temp.m_Name ,sizeof(temp.m_Name));

					if(StrStrW(temp.m_Name, _T( "곰플레이어")) |I StrStrW(_T("곰플레이어"),temp.m_Name)) 
					{
						HWND returnHwnd ;
						::SendMessage(returnHwnd = pAlarmApp->GetAddressBar(currentHwnd), WM_GETTEXT,
							MAX_PATH ,(LPARAM) temp.m_URL);
						temp.m_StartTime = CTime::GetCurrentTime();
						temp.IsCheck =TRUE;
						if(returnHwnd !=NULL)
						{
							pAlarmApp->Active_List_Piayer.AddHead(temp) ;
						}
					}
				}
			}

			if(pAlarmApp->lsGame(currentHwnd))
			{
				if( !pAlarmApp->HwndCmp(currentHwnd,&pAlarmApp->Active_List_Games))
				{
					SStrt temp;
					temp.m_hwnd = currentHwnd; 
					::GetWindowText(currentHwnd, temp.m_Name , sizeof (temp . m_Name))


						HWND returnHwnd;
					::SendMessage(returnHwnd = pAlarmApp->GetAddressBar(currentHwnd), WM_GETTEXT,
						MAX_PATH, (LPARAM) temp.m_URL);

					temp.m_StartTime = CTime::GetCurrentTime();
					temp.IsCheck = TRUE;
					if(returnHwnd !=NULL)
					{
						pAlarmApp->Active_List_Games.AddHead(temp);
					}}}

			currentHwnd = ::GetWindow(currentHwnd, GW_HWNDNEXT);
		}

		pAlarmApp->n_Destory_Browser += pAlarmApp->nDestroyWindows(&pAlarmApp->Active_List_Browserl,& ~
			pAlarmApp->Destory_List_Browser);
		pAlarmApp->n_Destroy_Game += pAiarmApp->nDestroyWindows(&pA!armApp->Active_List_Games ,& ~
			pAiarmApp->Destory_List_Games);
		pAlarmApp->lnsert4PrmTable(e_BROWSER);
		pAlarmApp->lnsert4PrmTable(e_PLAYER);
		pAlarmApp->lnsert4PrmTable(e_GAME);

		if(theApp.m_blsBanDay ==TRUE && theApp.m_limitedTimeUsingCom != 0 && minutes> theApp.
			m_limitedTimeUsingCom && pAlarmApp->m_blsChild ==TRUE)
		{

			theApp.ReAlramTime = nowMinute + 5;
			theApp.m_blsAlram =true;

			CAlarm_UlPopup dlg2;
			CString szMessage;
			szMessage.Format(L "%d시간 %02d분의 \n컴퓨터 사용 가능 시간이 모두 지났습니다,",
				theApp.m_editTimeUseHour, theApp.m_editTimeUseMinute);
			dlg2.SetMessage(szMessage);
			dIg2 . DoModaI () ;
		}

		if(theApp.m_blsBanDay ==TRUE && theApp.m_l imitedTimeFrom < nowMinute
		{
			&& theApp.m_limitedTimeTo > nowMinute && pA!armApp->m_blsChi ld ==TRUE)
				theApp.ReAiramTime2 = nowMinute + 5;
			theApp.m_blsA!ram2 =true;
			CAlarm_U!Popup dlg2;
			CString dayArr[7] = {L"일",L"일월",L"화",L"수",L"목",L"금",L"토"};
			CString message;
			message.Format(L " PC사용 금지 시간입니다\\ %s요일 \n\n%02d:%02d부터 %02d:%02d까지"/,
				dayArr[theApp .m_nDayOfWeek-1],
				theApp.m_editTimeBanHour1, theApp.m_editTimeBanMinute1,
				theApp.m_editTimeBanHour2, theApp.m_editTimeBanMinute2
				) ;
			dlg2.SetMessage(message);
			dlg2.DoModal();

			pAlarmApp->PrintMessage(theApp.m_blsChild);
			pAlarmApp->PopupEcampus(theApp.m_blsChild);



			CTimeSpan span ;
			span= timeNow- pAlarmApp->time_AfterCapture;
			LONG min= span.GetMinutes();
			if(min !=0 && min>=1)
			{
				pAlarmApp->Capture();
				pAlarmApp->time_AfterCapture = timeNow ;
			}
			if(!isHook) Sleep(1000) ;
		}
		return 1;
	}
	void CalarmeApp: :HookFinishThreadFunction()
	{

		if (m_hThreadHook ==NULL) return;
		TerminateThread(m_hThreadHook, 0);
		CloseHandle(m_hThreadHook);
		m_hThreadHook = NULL;
	}
	//주소가져온다.

	HWND CalarmeApp::GetAddressBar(HWND hwnd)
	{
		TCHAR buf[MAX_PATH] = {0 ,};
		HWND t_hwnd = hwnd;
		::GetCiassName(hwnd, buf, sizeof(buf));
		if(_tcsicmp(buf, _T("IEFrame")) == 0)
		{
			hwnd = ::GetWindow(hwnd ,GW_CHILD); 
			hwnd = ::GetWindow(hwnd ,GW_HWNDNEXT); 
			hwnd = ::GetWindow(hwnd, GW_CHILD); 
			hwnd = ::GetWindow(hwnd, GW_CHILD) ; 
			hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); 
			hwnd = ::GetWindow(hwnd, GW_CHILD); 
			hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); 
			::GetCiassName(hwnd, buf, sizeof(buf)) ;
			if(_tcsicmp(buf _T("Edit")) != 0)
			{
				hwnd = t_hwnd ;
				hwnd = ::GetWindow(hwnd, GW_CHILD); 
				hwnd = ::GetWindow(hwnd ,GW_CHILD); 
				hwnd = ::GetWindow(hwnd, GW_CHILD);
				hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); 
				hwnd = ::GetWindow(hwnd, GW_CHILD); 
				hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); 
				hwnd = ::GetWindow(hwnd, GW_CHILD);
				::GetCiassName(hwnd , buf, sizeof(buf));

				if(_tcsicmp(buf, _T("Edit")) != 0)
					return NULL;
			}
			return hwnd ;
		}
		/////////////////////////////////////////////////////
	}
	else if(_tcsicmp(buf, _T("Chrome_Windowlmpi_O")) == 0 II _tcsicmp(buf, _T("Chrome_WidgetWin_O ")) == 0)
	{
		hwnd = ::GetWindow(hwnd, GW_CHILD); 
		while(hwnd !=NULL)
		{

			hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); 

			::GetClassName(hwnd, buf, sizeof(buf));

			if(_tcsicmp(buf, _T("Chrome_AutocompleteEditView")) == 0)
			{
				return hwnd;
			}
		}
		return NULL;
	}
	else if(_tcsicmp(buf, _T("GomPlayer1.x")) == 0)
	{
		return hwnd;
	}
	else if(_tcsicmp(buf, _T("Winamp v1.x" )) == 0)
	{
		return hwnd;
	}
	else if(_tcsicmp(buf, _T("지뢰 찾기")) == 0 II _tcsicmp(buf, _T("Minesweeper")) == 0)
	{
		return hwnd;
	}
	else
	{
		return NULL;
	}

	BOOL CalarmeApp::lsBrowser(HWND hwnd)
	{
		TCHAR className[MAX_PATH];
		GetClassName(hwnd, className, sizeof(className));
		if(_tcsicmp(className, _T("IEFrame")) == 0 II
			_tcsicmp(className , _T("Chrome_Windowlmpi_O ")) == 0II
			_tcsicmp(className, _T("Chrome_WidgetWin_O ")) == 0II
			_tcsicmp(className, _T("MoziIlaUIWindowCiass")) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}}

	BOOL CalarmeApp::lsPlayer(HWND hwnd)
	{
		TCHAR className[MAX_PATH];
		GetClassName(hwnd, className, sizeof(className));
		if(_tcsicmp(className, _T( "GomPlayer1.x")) == 0II
			_tcsicmp(className, _T( "Winamp v1 .x")) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	// 게임 확인부분
	BOOL CalarmeApp::lsGame(HWND hwnd)
	{
		TCHAR className[MAX_PATH];
		GetClassName(hwnd, className, sizeof(className));
		if(_tcsicmp(className, _T("Minesweeper")) == 0II
			_tcsicmp(className, _T("지뢰 찾기" )) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	//리스트 중복검사
	BOOL CalarmeApp::HwndCmp(HWND hwnd, CList<SStrt,SStrt&>* Iist)
	{
		SStr * temp;
		if(Iist-> IsEmpty())
			return FALSE;
		INT_PTR n_Num = 0, n_Size = Iist->GetSize();
		POSITION pos = Iist->GetHeadPosition();
		POSITION tempPos;

		while(n_Num < n_Size)
		{
			tempPos = pos;
			temp= &Iist->GetNext(pos);
			if(temp->m_hwnd == hwnd)
			{
				temp->lsCheck =TRUE; 

				if(IsBrowser(hwnd)) 
				{
					::SendMessage(GetAddressBar(hwnd), WM_GETTEXT, MAX_PATH, (LPARAM) temp->m_URL);
				}
				else if(lsPiayer(hwnd))
				{
					TCHAR uri[MAX_PATH];
					::SendMessage(GetAddressBar(hwnd), WM_GETTEXT, MAX_PATH, (LPARAM)url);
					if(_tcsicmp(temp->m_URL,url) != 0) 
					{
						temp->m_EndTime = CTime::GetCurrentTime();
						temp->lsCheck =FALSE;
						this->Destory_List_Piayer.AddHead(*temp);
						Iist->RemoveA t ( tempPos);

						SStrt newNode;
						newNode.m_hwnd = hwnd;
						::GetWindowText(hwnd,newNode.m_Name,sizeof(newNode.m_Name));

						HWND returnHwnd;
						::SendMessage(returnHwnd = this->GetAddressBar(hwnd), WM_GETTEXT, MAX_PATH,
							(LPARAM) newNode.m_URL); 

						newNode.m_StartTime = CTime::GetCurrentTime();
						newNode.IsCheck = TRUE;

						if(returnHwnd != NULL)
						{
							this->Active_List_Piayer.AddHead(newNode);
						}
					}
				}
				return TRUE ;
			}
			n_Num++;
		}
		return FALSE;
	}
	//종료된 목록 받아오기
	int CalarmeApp::nDestroyWindows(CList<SStrt,SStrt&>* orginalList, CList<SStrt,SStrt&>* returnList)
	{
		int count =O;

		POSITION pos = orginalList->GetHeadPosition();
		int i=O;

		whiIe( <orginaIList->GetCount())
		{
			POSITION tempPos = pos;
			SStrt temp= orginalList->GetNext(pos);
			if(temp.IsCheck == FALSE)
			{
				temp.m_EndTime = CTime::GetCurrentTime();
				returnList->AddHead(temp);
				orginalList->RemoveAt(tempPos);
				count++;
			}
			i++;
			return count;
		}
	}
	//체크 초기화
	void CalarmeApp::initCheckList(CList<SStrt ,SStrt&>* Iist, BOOL bCheck)
	{
		int nltems = list->GetCount();
		POSITION pos = Iist->GetHeadPosition();
		for (int i=0; i<nItems; i++)
		{
			Iist->GetNext(pos).IsCheck= bCheck;
		}
	}
	//브라우저 사용시간
	CTime CalarmeApp::Time_UsingBrowser(void)
	{
		int nltems = Active_List_Browser.GetCount();
		CTime timeTotal = O;

		if(nItems !=0)
		{
			POSITION pos = Active_List_Browser.GetHeadPosition();
			for (int i=0; i<nItems; i++)
			{
				timeTotal += CTime::GetCurrentTime() - Active_List_Browser.GetNext(pos).m_StartTime;
			}
		}
		nltems = Destory_List_Browser.GetCount();
		if(nItems ! = 0)
		{
			POSITION pos = Destory_List_Browser .GetHeadPosition();
			for (int i =0; i<nItems; i++)
			{
				timeTotal += Destory_List_Browser.GetNext(pos).m_EndTime - Destory_List_Browser.GetNext(pos).m_StartTime;
			}
		}
		return timeTotal;
	}
	//플레이어 사용시간
	CTime CalarmeApp::Time_UsingPlayer(void)
	{
		int nltems = Active_List_Player.GetCount();
		CTime timeTotal = O;

		if(nItems != 0)
		{
			POSITION pos = Active_List_Player.GetHeadPosition();
			for (int i=0; i<nItems; i++)
			{
				timeTotal += CTime::GetCurrentTime() - Active_List_Piayer.GetNext(pos).m_StartTime;
			}
		}
		nltems = Destory_List_Piayer.GetCount();
		if(nItems ! = 0)
		{
			POSITION pos = Destory_List_Piayer.GetHeadPosition();
			for(int i=0; i<nItems; i++)
			{
				timeTotal += Destory_List_Piayer.GetNext(pos).m_EndTime- Destory_List_Player.GetNext(pos).m_StartTime;
			}
		}
		return timeTotal;
	}
	CTime CalarmeApp::Time_UsingGame(void)
	{
		int nltems = Active_List_Games.GetCount();
		CTime timeTotal = O;
		if(nItems ! = 0)
		{
			POSITION pos = Active_List_Games.GetHeadPosition();
			for (int i=0; i<nItems; i++)
			{
				timeTotal += CTime::GetCurrentTime() - Active_List_Games.GetNext(pos).m_StartTime;
			}
		}
		nltems = Destory_List_Games.GetCount();
		if(nItems ! = 0)
		{
			POSITION pos = Destory_List_Games.GetHeadPosition();
			for (int i=0; i<nItems; i++)
			{
				timeTotal += Destory_List_Games.GetNext(pos).m_EndTime- Destory_List_Games.GetNext(pos).m_StartTime;
			}
		}
		return timeTotal;
		//컴퓨터의 총사용시간
		CTime CalarmeApp::Time_UsingTotal(void)
		{
			CTime timeTotal = O;
			timeTotal += CTime::GetCurrentTime() - m_TimeStart;
			return timeTotaI;
		}
		//차단 사이트 알아오기
		HWND CalarmeApp::BlockSites(CList<CString,CString&> blocklist)
		{
			int nltems = Active_List_Browser.GetCount();
			int nBlcoks = blocklist.GetCount();

			POSITION blockPos = blocklist.GetHeadPosition();
			POSITION pos = Active_List_Browser .GetHeadPosition();
			for( int i=O; i<nBlcoks; i++)
			{
			}
			CString bl_URL = blocklist.GetNext(blockPos);
			for(int j=O; j<nltems; j++)
			{
				SStrt temp= Active_List_Browser.GetNext(pos);
				if(bl_URL.Find((CString)(temp.m_URL)))
				{
					return temp.m_hwnd;
				}
			}
		}
		return NULL;
	}
	///////////////////////////
	//차단사이트 추가
	void CalarmeApp::AddBlockURL(CString m_URL, CString m_date)
	{
		CDBDataForm temp;
		temp.m_Url = m_URL;
		temp.m_Date = m_date;
		BlockingURLinfo.AddHead(temp);
	}
	void CalarmeApp::AddCapturelmg(CString m_URL, CString m_date)
	{
		CDBDataForm temp;
		temp.m_Url = m_URL;
		temp.m_Date = m_date;
		capturelnfo.AddHead(temp);
	}
	BOOL CalarmeApp: :DBinputForm(CString szQurryString)
	{
		CDatabase db;
		if(!db.OpenEx(L"DSN=AlarmEducation", 0))
		{
			OutputDebugString(L"Failed - ODBC Open\n");
			return FALSE;
		}
		db.ExecuteSQL(szQurryString);
		db. CIose() ;
		return TRUE;
	}

	BOOL CalarmeApp::lnsert4PrmTable(INPUTTYPE type)
	{
		CString dBAddress, str_URL, saveDate, usedTime, szlnsert;

		CString szQurryString;
		CTime timeStart, timeEnd;
		CTimeSpan timeDifference;

		POSITION pos;
		CList<SStrt ,SStrt&>* pList;

		int count =O;

		switch( type)
		{
		case e_BROWSER :
			dBAddress = L"user lnfolnternet";
			pos = this->Destory_List_Browser .GetHeadPosition() ;
			pList = &this->Destory_List_Browser;
			szlnsert.Format(L"INSERT INTO %s (savedDate, internetURL, usedTime) VALUES (", dBAddress);
			break;
		case e_PLAYER:
			dBAddress = L"user lnfoMovie";

			pos = this->Destory_List_Piayer.GetHeadPosition();
			pList = &this->Destory_List_Piayer;
			szlnsert.Format(L"INSERT INTO %s (savedDate, movieName, usedTime) VALUES(" ,dBAddress);
			break;
		case e_GAME:
			dBAddress = L"user lnfoGame";
			pos = this->Destory_List_Games.GetHeadPosition();
			pList = &this->Destory_List_Games;
			szlnsert.Format(L"INSERT INTO %s (savedDate, gameName, usedTime) VALUES(" ,dBAddress);
			break;
		}
		int i =O;

		while(i<pList->GetCount())
		{
			POSITION tempPos = pos;
			SStrt temp= pList->GetNext(pos); 
			if(temp.IsCheck ==FALSE)
			{
				timeStart = temp.m_StartTime;
				timeEnd = temp.m_EndTime;
				timeDifference = timeEnd - timeStart;

				saveDate.Format(L"%d-%02d-%02d" ,timeStart.GetYear(), timeStart.GetMonth(), timeStart.Get Day()) ;

				str_URL = temp.m_URL;

				long l_seconds, l_minutes, l_hours;
				l_seconds= timeDifference.GetSeconds();
				l_minutes= l_secondsl60;
				l_seconds = l_seconds%60;
				l_hours = l_minutes/60;
				l_minutes= l_minutes%60;

				usedTime.Format(L"%d:%02d :%02d ",l_hours, l_minutes, l_seconds);
				switch(type)
				{
				case e_BROWSER:
					szInsert.Format (L"INSERT INTO %s (savedDate , internetURL, usedTime) VALUES (",dBAddress) ;
					break;
				case e_PLAYER:
					szlnsert.Format(L"INSERT INTO %s (savedDate, movieName, usedTime) VALUES(",dBAddress);
					break;
				case e_GAME:
					szlnsert.Format(L"INSERT INTO %s (savedDate , gameName, usedTime) VALUES( " ,dBAddress);
					break;
				}
				szQurryString.Format(L "%s '%s', '%s ', '%s ' )", szlnsert, saveDate, str_URL, usedTime);

				if(DBinputForm(szQurryString) ==FALSE)
				{
					return FALSE;
				}

				//////////////////
				pList->RemoveAt(tempPos);
				count++;
			}
			i++;
		}
		return TRUE;
	}

	BOOL CalarmeApp::lnsert3PrmTable(INPUTTYPE type,CString word)
	{
		CString szlnsert, saveDate, dBAddress;
		saveDate. Format(L "%d-%02d-%02d", CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(),
			CTime::GetCurrentTime().GetDay());
		switch(type)
		{
		case e_URL:
			dBAddress = L"banURL";
			szInsert.Format(L"INSERT INTO %s (banURLPath , savedDate) VALUES ( '%s', '%s')" ,dBAddress, word, saveDate);
			break;
		case e_Word:
			// dBAddress = L"banWord";
			// szlnsert.Fo rmat(L "INSE RT INTO %s (word, savedDate) VALUES ('%s', '%s')",dBAddress, word ,saveDate);
			break;
		case e_lmg:
			dBAddress = L"capturelmg" ;
			szlnsert.Format(L"INSERT INTO %s (imgPath ,savedDate) VALUES ('%s', '%s')" ,dBAddress, word, saveDate);
			break;
		}

		if(DBinputForm(szlnsert))
		{
			switch( type)
			{
			case e_URL:
				theApp.AddBiockURL(word,saveDate);
				break;
			case e_Word:

				break;
			case e_lmg:
				theApp.AddCapturelmg(word,saveDate);
				break;
			}
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	BOOL CaIarmeApp::inspectURL(CString urI)
	{
		int nltems = this->BiockingURLinfo.GetCount();

		//////////////////////////////////

		POSITION pos = BlockingURLInfo.GetHeadPosition() ;
		for (int i=0; i<nItems; i++)
		{
		}
		CDBDataForm dataform ;
		dataform = BlockingURLinfo.GetNext(pos) ;
		CString temp= dataform.m_Url ;
		temp.MakeLower() ;
		urI.MakeLower () ;
		if(temp == urI)
			return TRUE ;
		// if(temp == uri.Mid( O, uri.Getlengt h()-1))
		// return TRUE;
		if(StrStrW(temp, urI))
		{
			return TRUE;
		}
		else if(StrStrW(url, temp))
		{
			return TRUE ;
		}
		return FALSE ;
	}
	BOOL CalarmeApp::inspectEduURL(CString url)
	{
		int nltems = this->Edulistlnfo .GetCount() ;
		POSITION pos = EduListlnfo.GetHeadPosition() ;
		for( int i=O; i<nl terns ; i++)
		{
			CDBDataForm dataform ;
			dataform = Edulistlnfo.GetNext(pos);
			if(g_szUserName == dataform.m_Url)
			{
				CString temp= dataform.m_Date;
				temp.MakeLower();
				uri.MakeLower();
				if(temp == urI)
					return TRUE;
				//i f(temp == uri.Mid(O, uri.Getlength()-1))
				// return TR UE;
				if(StrStrW(temp,urI))
				{
					return TRUE ;
				}
				else if(StrStrW(url , temp))
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	void CalarmeApp::Capture()
		//////
	{
		double cx,cy;
		cx= GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);

		CSize destSize;
		double dSize = 1;

		destSize.cx = (int)(cx * dSize);
		destSize.cy = (int)(cy * dSize);

		cx = destSize.cx;
		cy = destSize.cy;

		CRect m_rect(O, 0, ex, cy);

		if(m_hDIB) {
			GlobaiFree(m_hDIB);
		}


		WriteToDIB(m_rect, destSize, m_hDIB);

		CTime t = CTime::GetCurrentTime();
		CString szTime;

		szTime .Format(L"%d_%02d_%02d_%02d_%02d_%02d ", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
		CJpeg jpg;
		jpg.LoadMemDIB(m_bmpinfo, (BYTE*)m_hDIB , CX*CY*3);

		CString stFileName;
		stFiIeName.Format(szTime+(T(".jpg")));
		CString filename;

		TCHAR programpath[MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, programpath) ;
		//filename.Format(L "%sWW%s" ,programpath, stFi leName);
		filename.Format(L "%s%s", m_szCaptureDirectory, stFileName);

		jpg.SaveJpg(filename);

		lnsert3PrmTable(e_lmg,stFileName);

		BOOL WriteToDIB(CRect &rect, CSize &destSize, HANDLE &hDIB)
		{
			CDC memDC;
			CDC ScreenDC;
			CBitmap m_Bitmap;

			UCHAR t;
			UCHAR temp[17*3] ;
			UCHAR *tt;
			UINT m_width, h;
			UINT m_height ;
			m_width = rect.Width() ;
			m_height = rect.Height();


			ScreenDC .CreateDC(L"DISPLAY", NULL , NULL , NULL);

			memDC.CreateCompatibleDC(&ScreenDC);

			m_Bitmap.CreateCompatibleBitmap(&ScreenDC, destSize.cx, destSize.cy) ;

			CBitmap* pOldBitmap = memDC.SelectObject(&m_Bitmap);

			memDC.BitBit(O, 0, destSize.cx, destSize.cy, &ScreenDC, 0, 0, SRCCOPY) ;

			CPalette m_Pal;

			if(ScreenDC.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
			{
				UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
				LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
				pLP->paiVersion = Ox300;
				pLP->paiNumEntries = GetSystemPaletteEntries(ScreenDC, 0, 255 , pLP->paiPaiEntry) ;

				m_Pal .CreatePalette( pLP ) ;
				delete[] pLP;
			}
			memDC .SelectObject(pOidBitmap);
			m_hDIB = DDBToDIB(m_Bitmap , BI_RGB , &m_Pal);
			ScreenDC.DeleteDC();
			if (hDIB ==NULL) {

				return FALSE;

			}
			tt = new UCHAR[m_width * 3];
			for(h = 1; h < (UINT)m_height; h++)
			{
				memcpy(temp, (UCHAR*)hDIB + (h * (m_width * 3)), 13 * 3);
				memcpy(tt, (UCHAR*)hDIB + (h * (m_width * 3)), m_width * 3);
				memcpy((UCHAR*)hDIB +((h) * (m_width * 3)), tt + (13 * 3), m_width * 3- (13 * 3) ) ;
				memcpy((UCHAR*)hDIB + ((h- 1) * (m_width * 3)) + ((m_width * 3) - 13 * 3), temp, 13 * 3) ;
			}

			memcpy(temp, (UCHAR*)hDIB , 13 * 3) ;
			memcpy(tt, (UCHAR*)hDIB, m_width * 3) ;
			memcpy((UCHAR*)hDIB, tt + (13 * 3), m_width * 3- (13 * 3) ) ;

			delete tt ;

			for( h = 0 ; h < m_width * m_height * 3 ; h+=3)
			{

				memcpy(&t , ((UCHAR*)hDIB+h+1), 1);
				memcpy(((UCHAR*)hDIB+h+1), ((UCHAR*)hDIB+h+2), 1);
				memcpy(((UCHAR*)hDIB+h+2), &t, 1);
				memcpy(&t , ((UCHAR*)hDIB+h), 1);
				memcpy(((UCHAR*)hDIB+h), ((UCHAR*)hDIB+h+2), 1);

				////

				memcpy(((UCHAR*)hDIB+h+2), &t , 1);
			}
			return TRUE ;
		}

		HANDLE DDBToDIB (CBitmap &bitmap , DWORD dwCompression , CPalette *pPal)
		{
			BITMAP bm ;
			// BITMAPINFOHEADER bi ;
			LPBITMAPINFOHEADER lpbi ;
			DWORD dwLen ;
			HANDLE hDIB ;
			HANDLE handle;
			HOC hOC ;
			HPALETTE hPal;
			//Return Value A HANDLE to the attached Windows GDI object
			ASSERT( bitmap.GetSafeHandle() );
			//The functio n has no arg for bitfields
			if( dwCompression == BI_BITFIELDS)
				return NULL;
			//It a palet te has not been supplied use defaul palette
			hPal = (HPALETTE) pPal->GetSafeHandle();
			if(hPaI ==NULL)
				hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE) ;

			// Get bitmap information
			bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

			//Initialize the bitmapinfoheader
			m_bmpinfo.bmiHeader.biSize = sizeof( BITMAPINFOHEADER);
			m_bmpinfo.bmiHeader.biWidth = bm.bmWidth ;
			m_bmpinfo.bmiHeader.biHeight = bm.bmHeight;
			m_bmpinfo.bmiHeader.biPlanes = 1;

			m_bmpinfo.bmiHeader .biBitCount = 24 ;
			m_bmpinfo.bmiHeader .biCompression = dwCompression;
			m_bmpinfo.bmiHeader .biSizelmage = bm.bmWidth * bm.bmHeight *3;
			m_bmpinfo.bmiHeader .biXPelsPerMeter = O;

			( Bitmap Information)

				m_bmpinfo .bmiHeader . biYPelsPerMeter = O;
			m_b mpinfo.bmiHeader . biCirUsed = O;
			m_bmpinfo.bmiHeader .biCirlmportant = O;

			// Compute the size of the info header and the color table
			int nColors = (1 << m_bmpinfo.bmiHeader.biBitCount);
			if( nColors > 256 )
				nColors = O;
			dwLen = m_bmpinfo.bmiHeader.biSize + nColors * sizeof(RGBQUAD);

			//We need a device context to get the DIB from
			hDC= ::GetDC(NULL) ;
			hPal = SelectPalette(hDC,hPal,FALSE) ;
			RealizePalette(hDC) ;

			//AI locate enough memory to hold bitmapinfoh eader and color table
			hDIB = GlobalAIloc(GMEM_FIXED ,dwLen);

			if (!hDIB){
				SelectPalette(hDC,hPal,FALSE);
				::ReleaseDC(NULL,hDC);

				return NULL;
			}

			lpbi = (LPBITMAPINFOHEADER)hDIB;

			*lpbi = m_bmpinfo.bmiHeader;

			// Call GetDIBits with a NULL lpBits param, so the device driver
			// wiII calculate the biSizelmage field

			GetDIBits(hDC,
				(HBITMAP)bitmap.GetSafeHandle(),
				OL,
				(DWORD)m_bmpinfo .bmiHeader .biHeight ,
				(LPBYTE)NULL,
				(LPBITMAPINFO) lpbi,
				(DWORD)DIB_RGB_COLORS);

			m_bmp info.bmiHeader = *lpbi;

			//If the driver did not fill in the biSizelmage field, then compute it
			// Each scan I ine of the image is aligned on a DWORD (32bit) bounda ry
			if(m_bmpinfo.bmiHeader .biSizelmage == 0)
			{
				m_bmpinfo.bmiHeader.biSizelmage =
					( ( ( (m_bmpinfo.bmiHeader.biWidth * m_bmpinfo.bmiHeader.biBitCount) + 31)
					& -31) / 8) * m_bmpinfo.bmiHeader.biHeight;

				// If a compression scheme is used the result may infact be larger
				// Increase the s ize to account for this .
				if (dwCompression != BI_RGB)
					m_bmpinfo.bmiHeader.biSizelmage = (m_bmp info.bmiHeader .biSizelmage * 3); 

				// Realloc the bu ff er so that it can hold all the bi ts
				dwLen += m_bmpinfo.bmiHeader .biSizelmage;
				if (handle= GlobalReAI loc(hDIB, dwLen, GMEM_MOVEABLE))
					hDIB = handle;
				else{
					GlobaiFree(hDIB);

					// Reselect the original palette
					SelectPalette(hDC,hPal ,FALSE);
					::ReleaseDC(NULL,hDC);
					return NULL;
				}
				//Get the b i t map b i t s
				lpbi = (LPBITMAPINFOHEADER)hDIB;

				//FINALLY get the DIB
				BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle() ,
					OL, // Start scan line
					(DWORD)m_bmpinfo.bmiHeader.biHeight, //# of scan lines
					(LPBYTE) lpbi //address for bitmap bits
					+ (m_bmpinfo .bmiHeader .biSize + nColors * si zeof(RGBQUAD)),
					( LPB I TMAP INFO) I pb i , // address of bitmapinfo
					(DWORD)DIB_RGB_COLORS) ; // Use RGB for color table

				if(!bGotBits)
				{
					GlobaiFree(hDIB);
					///
					SelectPalette(hDC,hPal,FALSE);
					::ReleaseDC(NULL,hDC) ;
					return NULL ;
					SelectPalette(hDC,hPal,FALSE) ;
					::ReleaseDC(NULL,hDC) ;
					//size = dwLen;
					return hDIB ;
				}

				void CalarmeApp::LoadVideoDB(void)
				{
					CDatabase db;
					if(!db.OpenEx(L"DSN=A iarmEducat ion",0))
					{
						OutputDebugStr ing(L"Fai led- ODBC OpenWn");
					}

					CString szlnsert = L"Select savedDate, movieName, usedTime from user lnfoMovie";
					//szQurryString .Format(L "%s '%s ' and password= '%s'", szlnsert, szName, szPassWord);

					CRecordset rs(&db);
					if(!rs.Open(CRecordset::dynaset,szInsert))
					{
						OutputDebugStr ing(L "Fai led - ODBC QurryWn" );
					}

					if(!rs.IsBOF()) rs.MoveFirst();

					//rs.GetFieldValue(short(O), temp);
					whiIe(!rs.IsEOF())
					{
						CDBDataForm temp ;
						//blsLogin ~ tr ue;
						rs.GetFieldValue(short(O), temp .m_Date) ;
						rs.GetF ieldValue(short(1), temp.m_Url ) ;
						rs.GetFieldValue( short(2), temp .m_UsedTime) ;

						if(!isInthe4List(temp,&videoCIipInfo)) videoCIipInfo.AddHead(temp) ;
						rs.MoveNext() ;
					}
					rs.Ciose();
					db.Ciose();
				}
				void CalarmeApp::LoadGameDB(void)
				{
					CDatabase db;
					if(!db.OpenEx(L "DSN=AlarmEducation" , 0))
					{
						OutputDebugString(L "Failed- ODBCOpen\n") ;
					}
					CString szlnsert = L"Select savedDate, gameNarne, usedTime from userlnfoGarne ;
						//szQurryString. Forrnat(L"%s '%s' and password= '%s' ', szlnsert , szName , szPassWord);

						CRecordset rs(&db) ;

					///
					if(!rs.Open(CRecordset::dynaset, szlnsert))
					{
						OutputDebugString(L "Failed- ODBC QurryWn ");
					}

					if(! rs.lsBOF()) rs.MoveFi rst();

					//rs.GetFieldValue(short(O), temp);
					whiIe (!rs.IsEOF())
					{
						CDBDataForm temp;
						//blslogin = true;
						rs.GetFieldValue(short(O), temp.m_Date);
						rs.GetFieldValue(short(1), temp.m_Url);
						rs.GetFieldValue(short(2), temp.m_UsedTime);


						if(!islnthe4List(temp,&gamelnfo)) gamelnfo.AddHead(temp);
						rs.MoveNext();
					}
					rs.Close();
					db.Close();
				}

				void CalarmeApp::LoadUsingURLDB(void)
				{
				}
				CDatabase db;
				if(!db.OpenEx(L"DSN=AIarmEducation", 0))
				{
					OutputDebugString(L "Failed - ODBC OpenWn");
				}
				CString szlnsert = L"Select savedDate, internetURL, usedTime from userlnfolnternet";
				//szQurryStr ing .Format(L"%s '%s ' and password = '%s"', szlnsert, szName, szPassWord);

				CRecordset rs(&db);
				if(!rs .Open(CRecordset : :dynaset, szlnsert))
				{ 
					OutputDebugStr ing(L"Fai led- ODBC QurryWn");
				}
				if(!rs.lsBOF()) rs.MoveFirst(); 


				//rs.GetFieldValue(short(O), temp) ;
				whiIe(!rs.IsEOF() )
				{
					CDBDataForm temp;
					//blslog in =true;
					rs.GetFieldValue(short(O), temp.m_Date);
					rs.GetFieldValue(short(1), temp.m_Url);
					rs.GetFieldValue(short(2) , temp .m_UsedTime);

					if(!islnthe4List(temp,&internetlnfo)) internetlnfo.AddHead(temp);
					rs.MoveNext();
				}
				rs.Close();
				db.Close();
			}
			void CalarmeApp::LoadBanWordDB(void)
			{

				CDatabase db;
				if(!db.OpenEx(L"DSN=AIarmEducation", 0))
				{
					OutputDebugString(L"Failed - ODBC OpenWn");
				}

				CString szlnsert = L"Select word, savedOate from banWord ";
				//szQurryString .Format(L "%s '%s ' and password= '%s ' ", szlnsert, szName , szPassWord):

				CRecordset rs(&db);
				if(!rs.Open(CRecordset: :dynaset, szlnsert))
				{
					OutputOebugString(L"Failed- OOBC QurryWn");
				}
				if(!rs.IsBOF())rs.MoveFirst();
				//rs.GetFieldValue(short(O) , temp);
				whiIe(!rs.IsEOF())
				{
					COBSDataForm temp;
					//blslogin = true;
					rs.GetFieldValue(short(O), temp.m_Url);
					rs.GetFieldValue(short(1) , temp.m_Date);

					if(!islnthe3List(temp,&BiockingWordlnfo)) BlockingWordlnfo.AddHead(temp);
					rs.MoveNext();
				}
				rs.Close();
				db.CIose();

				//sendOB(BiockingWordlnfo);
			}

			void CalarmeApp::LoadlmageOB(void)
			{
				CList<CString, CString&> fi filelist;
				COatabase db;
				if(!db.OpenEx(L "OSN=AiarmEducation ", 0))
				{
					OutputDebugStr ing(L"Fai led - OOBC OpenWn");
				}

				CString szlnsert = L"Select lmgPath , savedDate from capturelmg ";
				//szQurryStr ing.Format(L "%s '%s' and password = '%s'", szlnsert , szName , szPassWord):
				CRecordset rs(&db);
				if(!rs.Open(CRecordset: :dynaset, szlnsert))
				{
					OutputDebugStr ing(L"Fai led - OOBC QurryWn ");
				}

				if(!rs.IsBOF())rs.MoveFirst(); 

				CFileFind finder;
				BOOL bWorking = finder.FindFiIe(_T("..//capture]]*.*"));
				while(bWorking)
				{

					bWorking =finder .FindNextFileW();
					CString fiIeInDir;
					fiIeInDir = finder.GetFiIeName();

					if(!finder.lsDirectory()) filelist.AddHead(filelnDir);
				}

				whiIe(!rs.IsEOF())
				{
					CDBDataForm temp;
					//blslogin = true ;
					rs.GetFieldValue(short(O), temp.m_Url);
					rs.GetFieldValue(short(1), temp.m_Date);
					if(!fiIelist.Find(temp.m_UrI))
					{
						CDatabase deleteDb;
						if(!deleteDb.OpenEx(L "DSN=AiarmEd ucation", 0))
						{
							OutputDebugString(L "Failed- ODBC Open\n") ;
						}
						CString szDelete ;
						szDelete.Format(L "Delete from capture lmg WHERE lmgPath = '%s'", temp.m_Url);

						deleteDb.ExecuteSQL(szDelete) ;
						deleteDb.Ciose() ;
					}
					else if(!islnthe3List(temp,&capturelnfo))
					{
						capturelnfo .AddHead(temp) ;
					}
					rs.MoveNext() ;
				}
				rs.Close();
				db.Close();
			}
			void CalarmeApp::LoadBanURLDB(void)
			{
				CDatabase db;
				if (!db .OpenEx(L "DSN=Alar mEducation", 0))
				{
					OutputDebugStr ing(L "Failed - ODBC OpenWn '' ) ;
				}

				CString szlnsert = L"Select banURLPath , savedDate from banURL" ;
				// szQurryString .Format(L''%s '%s' and password = '%s'", szlnsert, szName, szPassWord);

				CRecordset rs(&db);
				if(!rs.Open(CRecordset::dynaset,szInsert))
				{
					OutputDebugString(L "Failed - ODBC QurryWn");
				}
				if(Irs.IsBOF())rs.MoveFirst(); 
				//rs.GetFieldValue(short(O), temp) ;
				whiIe(!rs.IsEOF())
				{
					CDBDataForm temp;
					//blslogin = tr ue;
					rs.GetFieldValue(short(O), temp.m_Url);
					rs.GetFieldValue(short(1), temp.m_Date);


					if(!islnthe3List(temp,&BiockingURLinfo))
						rs.MoveNex t () ;
				}
				rs.Close();
				db.Close();
				BlockingURLinfo.AddHead(temp) ;
				void CalarmeApp::LoadEduURLDB(void)
				{

					CDatabase db;
					if (!db.OpenEx(L "DSN =Ai ar mEdu cat ion", 0))
					{
						OutputDebugString(L"Failed- ODBC Op en\n");
					}

					CString szlnsert = L"Select userID , urI from ecampusURL" ;
					//szQurryString.Format(L"%s'%s'and password = '%s' " , szlnsert , szName , szPassWord);

					CRecordset rs(&db) ;
					if(!rs.Open(CRecordset::dynaset, szlnsert))
					{
						OutputDebugString(L "Failed - ODBC Qurry\n") ;
					}
					if(!rs.IsBOF())rs.MoveFirst();
					//rs.GetFieldValue(short(O), temp) ;
					whiIe(!rs.IsEOF())
					{
						CDBDataForm temp;
						//blslogin = true;
						rs.GetFieldValue(short(O),temp.m_Url);
						rs.GetFieldValue(short(1),temp.m_Date);
						if(!islnthe3List(temp,&Edulistlnto)) Edulistlnfo.AddHead(temp);
						rs.MoveNext();
					}
					rs.Close();
					db.Close();
				}


				void CalarmeApp::LoadVideoDB(int year,int month,int day)
				{
					CDatabase db;
					if(!db.OpenEx(L"DSN =AlarmEducation", 0))
					{
						OutputDebugString(L "Failed- ODBC Open\n") ;
					}

					CString szlnsert;
					szlnsert.Format(L"Select movieName, usedTime from user lnfo Movie where save dDate = '%d-%02d-& 02d '",year ,month,day) ;
					//szQurryString. Format( L"%s '%s' and password == '%s'", sz lnsert , szName , szPassWord);

					CRecordset rs(&db);
					if(!rs.Open(CRecordset::dynaset, szlnsert))
					{

						OutputDebugString(L"Failed- ODBC Qurry\n");
					}

					if(!rs.lsBOF()) rs.MoveFirst(); 

					//rs.GetFieldValue(short(O), temp);
					whiIe(!rs.IsEOF())
					{
						CDBDataForm temp;
						//blslogin = true;
						//rs.GetFieIdVaIue(short(0) ,temp.m_Date);
						rs.GetFieldValue(short(O), temp.m_Url);
						rs.GetFieldValue(short(1), temp.m_UsedTime) ;
						temp.m_Date.Format(L"%d-%02d-&02d " ,year ,month,day);

						thisDaylist.AddHead(temp);
						rs.MoveNext();
					}
					rs.Ciose();
					db.Ciose();
				}
				void CalarmeApp::LoadGameDB( int year, int month, int day)
				{
					CDatabase db;
					if(!db.OpenEx(L"DSN=AiarmEducation ", 0))
					{
						OutputDebugString(L"Failed - ODBC OpenWn ');
					}

					CString szlnsert;
					szlnsert.Format(L"Select gameName , usedTime from userlnfoGame where savedDate = '%d-%02d-&02d'",year ,month ,day);
					//szQurryString.Format(L"%s '%s" and password= '%s"', szlnsert, szName, szPassWord);

					CRecordset rs(&db);
					if(!rs. Open(CRecordset::dynaset, szInsert))
					{
						OutputDebugString(L "Failed - ODBC QurryWn");
					}
					if(!rs.IsBOF())rs.MoveFirst();

					//rs.GetFieldValue(short(O), temp);
					whiIe(!rs.IsEOF())
					{
						CDBDataForm temp;
						//blslogin = true;
						//rs.GetFieldValue(short(O) , temp.m_Date);
						rs.GetFieldValue(short(O), temp.m_Url);
						rs.GetFieldValue(short(1), temp.m_UsedTime);
						temp.m_Date.Format(L "%d-%02d-&02d" ,year ,month, day);

						gamelnfo.AddHead(temp);
						rs.MoveNext();
					}
					rs.Ciose();
					db.Ciose();
				}

				void CalarmeApp::LoadUsingURLDB(int year,int month,int day)
				{
					CDatabase db;
					if(!db.OpenEx(L "DSN=A iarmEducation", 0))
					{
						OutputDebugString(L"Failed- ODBC Open\n ");
					}

					CString szlnsert;
					szlnsert.Format(L"Select in ternetURL, usedTime from userlnfolnternet where savedDate = ' %d-%02d - &02d'",year ,month,day);
					//szQurryString.Format(L"%s '%s ' and password'= '%s ' ", szlnsert, szName, szPassWord);
					CRecordset rs(&db);
					if(!rs.Open(CRecordset::dynaset, szlnsert))
					{
						OutputDebugString(L "Failed - ODBC QurryWn");
					}
					if(!rs.IsBOF()) rs.MoveFirst(); 

					whiIe(!rs.IsEOF())
					{
						CDBDataForm temp;
						// blslogin =true;
						//rs.GetFieldValue(short(O), temp.m_Date) ;
						rs.GetFieldValue(short(O), temp.m_Url) ;
						rs.GetFieldValue(short(1), temp .m_UsedTime);
						temp.m_Date.Format(L "%d-%02d-&02d" ,year,month,day);
						internetlnfo.AddHead(temp);
						rs.MoveNext();
					}
					rs.Close();
					db.Close();
				}

				void CalarmeApp::LoadVideoDB(int year, int month)
				{
					//videoCIipInfo
					int nltems = videoCiiplnfo.GetCount();

					CString yearMonth;
					yearMonth.Format(L"%d-%02d-" ,year ,month);

					POSITION pos = videoCIiplnfo.GetHeadPosition();

					for(int i=O; i<nltems; i++)
					{
						CDBDataForm temp= videoCIiplnfo .GetNext(pos) ;
						if(StrStrW(temp.m_Date,yearMonth) && ! islnthe4List(temp,&videoMonthlnfo))
						{
							videoMonthlnfo.AddHead(temp);
						}
						else if(StrStrW(yearMonth, temp.m_Date) && ! islnthe4List(temp,&videoMonthlnfo))
						{
							videoMonthlnfo.AddHead(temp);
						}
					}
				}
				void CalarmeApp::LoadGameDB( int year, int month)
				{
					int nltems = gamelnfo.GetCount();

					CString yearMonth;
					yearMonth.Format(L "%d-%02d-", year,month);

					POSITION pos = gamelnfo .GetHeadPosition();

					for(int i=O; i<nltems; i++)
					{
						CDBDataForm temp= gamelnfo . GetNext(pos);
						if(StrStrW(temp.m_Date,yearMonth) && ! islnthe4List(temp,&gameMonthlnfo))
						{
							gameMonthlnfo.AddHead(temp);
						}
						else if(StrStrW(yearMonth, temp.m_Date) && ! islnthe4List(temp,&gameMonthlnfo))
						{
							gameMonthlnfo.AddHead(temp);
						}
					}
				}
				void CalarmeApp::LoadUsingURLDB(int year ,int month)
				{
					int nltems = internetlnfo .GetCount();

					CString yearMonth;
					yearMonth.Format(L"%d-%02d-" ,year ,month);

					POSITION pos = internetlnfo.GetHeadPosition();

					for (int i=0; i<nItems; i++)
					{
						CDBDataForm temp= internetlnfo.GetNext(pos) ;
						if(StrStrW(temp.m_Date,yearMonth) && ! islnthe4List(temp,&internetMonthlnfo))
						{
							theApp.
								internetMonthlnfo.AddHead(temp);
						}
						else if(StrStrW(yearMonth , temp .m_Date) && ! islnthe4List(temp,&internetMonthlnfo))
						{
							internetMonthlnfo.AddHead(temp) ;
						}

					}
				}
				BOOL CalarmeApp::islnthe4List(CDBDataForm cmpType, CList<CDBDataForm,CDBDataForm&>* Iist)
				{
					int nltems = Iist->GetCount();

					POSITION pos = Iist->GetHeadPosition();

					for(int i=O; i<nltems ; i++)
					{
						CDBDataForm temp = I ist->GetNext(pos);
						if(StrCmpW(temp . m_Date,cmpType . m_Date) ==0
							&& StrCmpW(temp . m_Url ,cmpType.m_Url) ==0
							&& StrCmpW(temp .m_UsedTime,cmpType.m_UsedTime) ==0)
						{
							return TRUE;
						}

					}
					return FALSE;
				}
				BOOL CalarmeApp::islnthe3List(CDBDataForm cmpType, CList<CDBDataForm,CDBDataForm&>* Iist)
				{
					int nltems = list->GetCount();

					POSITION pos = Iist->GetHeadPosition();

					for (int i =0; i<nItems; i++)
					{
						CDBDataForm temp= I ist->GetNext(pos);
						if(StrCmpW(temp.m_Date,cmpType.m_Date) ==0
							&& StrCmpW(temp.m_Url ,cmpType.m_Url) ==0)
						{
							return TRUE;
						}
					}
					return FALSE;
				}
				void CalarmeApp::LoadRcvMessages(int nMode)
				{
					if(nMode == 1) m_ListToChild.RemoveAII();
					else m_ListToParent.RemoveAII();

					CDatabase db;
					if(!db.OpenEx(L"DSN=AiarmEducation", O))
					{
						OutputDebugString(L"Fai led- ODBC Open\n");
					}

					CString szlnsert, dbAddress:
					//(alarmTime, isCheck, isResendMode, contents , savedUseriD, savedDate)


					if(nMode == 1) dbAddress = L"MSGT oChiId";
					else dbAddress = L"MSGToParent";
					szlnsert.Format(L"Select alarmTime, isCheck, isResendMode, contents, savedUseriD, savedDate from%s", dbAddress) ;
					//szQurryString.Format(L"%s '%s' and password= '%s'", szlnsert, szName, szPassWord);
					CRecordset rs(&db);
					if(!rs.Open(CRecordset::dynaset, szlnsert))
					{
						OutputDebugString(L "Failed- ODBC Qurry\n" );
					}
					if(!rs.IsBOF())rs.MoveFirst();
					//rs.GetFieldValue(short(O), temp);
					whiIe(!rs.IsEOF())
					{
						CMessageForm temp;
						//blslogin = true;
						rs.GetFeldValue(short(O), temp.m_Airam);
						rs.GetFeldValue(short(1), temp.m_isCheck);
						rs.GetFeldValue(short(2), temp.m_ReSendMode);
						rs.GetFeldValue(short(3), temp.m_Contents) ;
						rs.GetFeldValue(short(4), temp.m_Sender);
						rs.GetFeldValue(short(5), temp.m_SendingTime) ;
						if(nMode == 1)
						{
							if(!inspectSameMSG(temp,&m_ListToChi ld)) m_ListToChild.AddHead(temp);
						}
						else
						{
							if(!inspectSameMSG(temp,&m_ListToParent)) m_ListToParent.AddHead(temp);
						}
						rs.MoveNext();
					}
				}

				void CalarmeApp: :LoadEcampuslist()
				{
					//if  nMode == 1)
					{
						m_ListEcampus.RemoveAII();

						CDatabase db;

						if(!db.OpenEx(L"DSN=AiarmEducat ion", 0))
						{
							OutputDebugString(L"Failed- ODBC Open\n");
						}
						CString szlnsert, dbAddress;
						//useriD, uri, day_, Time1
						//sz Insert.Format(L"Select alarmTime, isCheck, isResendMode, contents, savedUser ID, savedDate from %s" ,dbAddress);

						szlnsert.Format(L"Select Time1, uri, day_ ,userID from ecampusURL");

						//szQurryString.Format(L "%s '%s ' and password = '%s'", szlnsert, szName, szPassWord);

						CRecordset rs(&db);
						if(!rs.Open(CRecordset::dynaset, szlnsert))
						{
							OutputDebugString(L"Failed - ODBC Qurry\n");
						}

						if(!rs. IsBOF())rs.MoveFirst();

						//rs.GetFieldValue(short(O), temp);
						while (!rs.lsEOF())
						{
							CMessageForm temp;
							//blslogin = true ;
							rs.GetFieldValue(short(O), temp.m_Airam);
							rs.GetFieldValue(short(1), temp.m_Contents);
							rs.GetFieldValue(short(2), temp.m_isCheck);
							rs.GetFieldValue(short(3), temp.m_Sender);


							if(!inspectSameMSG(temp,&m_ListEcampus))
								m_ListEcampus.AddHead(temp);
							rs.MoveNext();
						}
					}
				}

				BOOL CalarmeApp::inspectSameMSG(CMessageForm cmpType,CList<CMessageForm,CMessageForm&>* Iist)
				{
					int nltems= I ist->GetCount();

					POSITION pos = Iist->GetHeadPosition();

					for(int i=0; i<nItems; i++)
					{
						CMessageForm temp = Iist->GetNext(pos);
						if(StrCmpW(temp.m_Contents,cmpType.m_Contents) ==0
							&& StrCmpW(temp .m_Airam,cmpType.m_Airam) == 0)
						{
							return TRUE;
						}
					}
					return FALSE;
				}
				void CalarmeApp : :GetTimeSetData()
				{
					JKRegistry reg;
					reg.SetHKey(HKEY_LOCAL_MACHINE);
					reg.SetPath(TEXT("SoftwareWWAiarmEWWParent1")) ;

					//CString szUseHour, szUseMinute, szBanHour1, szBanMinute1, szBanHour2. szBanMinute2;
					WCHAR szUseHour[16] = L"" ;
					WCHAR szUseMinute[16] = L"";
					WCHAR szBanHour1[16] = L"";
					WCHAR szBanMinute1[16] = L"";
					WCHAR szBanHour2[16] = L"";
					WCHAR szBanMinute2[16] = L"";
					theApp.m_blsBanDay = FALSE;


					reg.SetName(TEXT("UseHour"));
					reg.GetString(szUseHour);

					reg.SetName(TEXT("UseMinute")) ;
					reg.GetString(szUseMinute) ;

					reg.SetName(TEXT("BanHour1"));
					reg.GetString(szBanHour1) ;

					reg.SetName(TEXT("BanMinute1"));
					reg.GetString(szBanMinute1);

					reg.SetName(TEXT("BanHour2"));
					reg.GetString(szBanHour2) ;

					reg.SetName(TEXT("BanMinute2"));
					reg.GetString(szBanMinute2);

					reg.SetName(TEXT("IsMon"));
					int nMonCheck = reg.Getlnteger();

					reg. Set Name( TEXT("IsTUE"));
					int nTUECheck = reg.Getlnteger();

					reg.SetName(TEXT("IsWED"));
					int nWEDCheck = reg.Getlnteger();

					reg.SetName(TEXT("IsTHU"));
					int nTHUCheck = reg.Getlnteger();
					reg.SetName(TEXT("IsFRI"));
					int nFRICheck = reg.Getlnteger();
					reg.SetName(TEXT("IsSAT"));
					int nSATCheck = reg.Getlnteger();
					reg.SetName(TEXT("IsSUN"));
					int nSUNCheck = reg.Getlnteger();

					m_ed tTimeUseHour = _ttoi(szUseHour);
					m_ed tTimeUseMinute = _ttoi(szUseMinute);
					m_ed tTimeBanHour1 = _ttoi(szBanHour1);
					m_ed tTimeBanMinute1 = _ttoi(szBanMinute1);
					m_ed tTimeBanHour2 = _ttoi(szBanHour2) ;
					m_ed tTimeBanMinute2 = _ttoi(szBanMinute2);



					BOOL arr[7];
					arr[1] = nMonCheck;
					arr[2] = nTUECheck;
					arr[3] = nWEDCheck;
					arr[4] = nTHUCheck;
					arr[5] = nFRICheck;
					arr[6] = nSATCheck;
					arr[O] = nSUNCheck;
					CTime ct;
					ct = CTime::GetCurrentTime();
					theApp.m_nDayOfWeek = ct.GetDayOfWeek();

					if(arr[theApp.m_nDayOfWeek-1])
						theApp.m_blsBanDay =TRUE;

					m_limitedTimeFrom = m_editTimeBanHour1 * 60 + m_editTimeBanMinute1;
					m_limitedTimeTo = m_editTimeBanHour2 * 60 + m_editTimeBanMinute2;

					m_limitedTimeUsingCom = m_editTimeUseHour* 60 + m_editTimeUseMinute;
				}

				void CalarmeApp::PrintMessage(int nMode)
				{
					CTime timeNow = CTime::GetCurrentTime();


					CList<CMessageForm, CMessageForm&>* savinglist;
					if(nMode == 1) savinglist = &theApp.m_ListToChild;
					else savinglist = &theApp.m_ListToParent;

					int nltems = savinglist->GetCount();

					POSITION pos = savinglist->GetHeadPosition();
					for ( in t i =0; i <n I t ems; i ++)
					{
						POSITION tempPos = pos;
						CMessageForm temp= savinglist->GetNext(pos);
						CStr ing szCurrentTime;

						CString szCurrentDate;

						szCurrentTime.Format(L"%02d:%02d",timeNow.GetHour(), timeNow.GetMinute());

						CString szSendingDate = temp.m_SendingTime;

						szCurrentDate.Format(L"%d%02d%02d",
							CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(),CTime::GetCurrentTime().GetDay());

						szSendingDate.Remove('-');
						int nCurrentDate = _ttoi(szCurrentDate);
						int nSendingDate = _ttoi(szSendingDate);

						int nCurrentTime = _ttoi(szCurrentTime);
						int nAiramTime = _ttoi(temp.m_Airam);

						if(szCurrentTime == temp .m_Airam && nCurrentDate == nSendingDate && temp.m_isCheck == L'O')
						{
							OutputDebugString(L "Success Wn");
						}

						//if(StrCmpW(szCurrentTime, temp.m_Airam) == 0 && nCurrentDate == nSendingDate && temp. m_ i sCheck == '0' )
						if(StrCmpW(szCurrentTime, temp .m_Airam) == 0 && nCurrentDate == nSendingDate && temp. m_isCheck == L'O')
						{
							OutputDebugString(L"Success 2Wn");

							int cxlcon = GetSystemMetrics(SM_CXICON);
							int cylcon = GetSystemMetrics(SM_CYICON);

							CAlarm_UIPopup dlg2;
							dlg2.SetMessage(temp.m_Contents);
							//dlg2.SetPosition(cxlconl2 ,cylcon/2);
							dIg2.DoModaI();

							temp.m_isCheck = "1";
							savinglist->lnsertAfter(tempPos, temp);
							savinglist->RemoveAt(tempPos);


							CDatabase db;
							if( !db.OpenEx(L"DSN=AiarmEducati on" , 0)) OutputDebugStr ing(L"Fai led- ODBC OpenWn '');

								CString szlnsert;
							i f ( nMode == 1)
							{
								szlnsert.Format(L "UPDATE MSGToChild set isCheck =true WHERE alarmTime = '%s' and contents= '%s '"
									, temp.m_Airam, temp.m_Contents);
							}
							else
							{
								szlnsert.Format(L"UPDATE MSGToParent set isCheck =true WHERE alarmTime = '%s' and contents = '%s'"
									, temp.m_Airam , temp.m_Contents);
							}
							db.ExecuteSQL(szlnsert);
							db.Close();


						}
						else if((nCurrentDate > nSendingDate && temp.m_ReSendMode == '1' && temp.m_isCheck == '0' )
							II(nCurrentDate == nSendingDate && nCurrentTime > nAiramTime && temp .m_ReSendMode == '1' && temp .m_isCheck =='0'))
						{
							int cxlcon = GetSystemMetrics(SM_CXICON) ;
							int cylcon = GetSystemMetrics(SM_CYICON) ;

							CAlarm_UIPopup dlg2 ;
							dlg2.SetMessage(temp .m_Contents);
							dlg2 .SetPosition(cxlcon/2 ,cylcon /2);
							dlg2 .DoModal();

							temp.m_isCheck = "1" ;
							savinglist->lnsertAfter(tempPos , temp);
							savinglist->RemoveAt(tempPos);

							CDatabase db;
							CString szQurryString = L"";
							if(!db.OpenEx(L"DSN=AiarmEducation ", 0))  OutputDebugString(L "Failed - ODBC Open\n);
								CString szlnsert;
							if(nMode == 1)
							{
								CString szlnsert ,szQurryString;
								szlnsert.Format(L"UPDATE MSGToChi ld set isCheck ==true WHERE alarmTime ='%s' and contents= '%s '"
									, temp.m_Airam, temp.m_Contents);
								db.ExecuteSQL(szlnsert) ;
								db.CIose() ;
							}
						}
						else
						{

							CString szlnsert , szQurryString;
							szlnsert.Format(L "UPDATE MSGToParent set isCheck =true WHERE alarmTime = '%s' and contents= '%s' "
								, temp.m_Airam, temp.m_Contents);
							db.ExecuteSQL(szlnsert) ;
							db.CIose() ;
						}
					}
				else if((nCurrentDate > nSendingDate && temp.m_ReSendMode == '0' )
					II(nCurrentDate == nSendingDate && nCurrentTime > nAiramTime && temp .m_ReSendMode == '0' ))
				{
					savinglist->RemoveAt(tempPos);
				}
				}
			}
			void CalarmeApp::PopupEcampus(int nMode)
			{
				if(nMode == 1)
				{
					CTime timeNow = CTime::GetCurrentTime();
					////////////////////////////
					//pAlarmApp->m_ListToChild.'
					CList<CMessageForm, CMessageForm&>* savingList;

					savingList = &theApp.m_ListEcampus;

					int nltems = savingList->GetCount();

					POSITION pos = savingList->GetHeadPosition();
					for(int i=0; i<n Items; i++)
					{
						POSITION tempPos = pos;
						CMessageForm temp= savingList->GetNext(pos);
						CString szCurrentTime;
						CString szCurrentDate;

						szCurrentTime .Format(L "%02d:%02d'',timeNow.GetHour() ,timeNow.GetMinute());

							/*
							//CString szSendingDate = temp.m_SendingTime;
							szCurrentDate.Format(L"%d%02d%02d",
							CTime::GetCurrentTime().GetYear(), CTime::GetCurrentTime().GetMonth(),
							CTime::GetCurrentTime().GetDay());

							szSendingDate.Remove('-');
							int nCurrentDate = _ttoi(szCurrentDate);
							int nSendingDate = _ttoi(szSendingDate);

							int nCurrentTime = _ttoi(szCurrentTime);
							int nAlramTime = _ttoi(temp .m_Airam);

							if(szCur rentTime == temp.m_Alram && nCurrentDate == nSendingDate && temp.m isCheck == L 'O')
							{
							OutputDebugString(L"Success Wn");
							}
							*/

							CStr ing dayArr[7] = {L "월" ,L "화" ,L"수" ,L"목" ,L"금" ,L "토" , L "일"};

						//message. Format( L"PC사용 금지 시간입니다\n\n %s요일 \n\n%02d:%02d부터 %02d:%02d까지",

						//if(StrCmpW(szCurrentTime, temp.m_Airam) == 0 && nCurrentDate == nSendingDate && temp.m_isCheck == '0')

						if(StrCmpW(szCurrentTime, temp.m_Airam) == 0 && StrCmpW(dayArr[theApp.m_nDayOfWeek-1], 
							temp.m_isCheck) && g_szUserName == temp.m_Sender)
						{
							OutputDebugString(L"Success 2Wn");

							int cxlcon = GetSystemMetrics(SM_CXICON);
							int cylcon = GetSystemMetrics(SM_CYICON);

							CAlarm_UIPopup dlg2;
							dIg2.SetMessage(L"인처넷 강의를 들을 시간입니다.");
							//dlg2.SetPosition(cxlcon/2 ,cylcon/2);
							dlg2.DoModal();

							ShellExecute(NULL, L"open " , L" iexplore", temp.m_Contents, NULL, SW_SHOWNORMAL);
						}
						else
						{
							savingList->RemoveAt(temPos);
						}
					}
				}
			}