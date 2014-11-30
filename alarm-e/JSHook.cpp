
#include "StdAfx.h"
#include "JSHook.h"

CJSHook::CJSHook(void)
{
	//iSetTimer(1, 10000, NULL) ;
}

CJSHook::~CJSHook(void)
{
}

//실제 실행부
void CJSHook::OnTimer(UINT_PTR nIDEvent)
{

	HWND currentHwnd;
	TCHAR str[MAX_PATH] = {0,};
	CString message;
	switch(nIDEvent)
	{
	case 1 :
		currentHwnd = GetDesktopWindow()->GetSafeHwnd(); //가장 상위 핸들  
		currentHwnd = ::GetWindow(currentHwnd, GW_CHILD);

		if(!Active_List_Browser.IsEmpty())
			initChecklist(&Active_List_Browser,FALSE);

		while(currentHwnd != NULL)
		{
			TCHAR className[MAX_PATH] = {0,};
			TCHAR programName[MAX_PATH] = {0,};

			/*if(!GetCiassName(hwnd, className , sizeof(className)) &&
			GetLastError() != ERROR_SUCCESS)
			return; */
			if(IsBrowser(currentHwnd) && !HwndCmp(currentHwnd,&Active_List_Browser))
			{
				SStrt temp;
				temp.m_hwnd = currentHwnd;
				::GetWindowText(currentHwnd, temp.m_Name, sizeof(temp.m_Name)); 
				//::GetWindowText(GetAddressBar(current Hwnd),temp->m_URL,sizeof(temp->m_URL));
				HWND returnHwnd ;
				::SendMessage(returnHwnd = GetAddressBar(currentHwnd), WM_GETTEXT , MAX_PATH, (LPARAM)temp.m_URL);
				temp.m_StartTime = CTime::GetCurrentTime();
				temp.IsCheck= TRUE;
				if(returnHwnd !=NULL)
				{
					Active_List_Browser.AddHead(temp);
				}
			}
			//IHWND olp = currentHwnd;
			currentHwnd = ::GetWindow(currentHwnd, GW_HWNDNEXT);
		}
		////////////////////

		// CList<SStrt , SStrt&> Dest_Browser;
		n_Destory_Browser+=nDestoryWindows(&Active_List_Browser , &Destory_List_Browser);

		WritingText(&Destory_List_Browser);

		break;

		//case 2:
		//KiIITimer(1);
		//KillTimer(2);
		// break:
	}

	//CWnd::QnTimer(nIDEvent);

}

HWND CJSHook::GetAddressBar(HWND hwnd)
{
	TCHAR buf[MAX_PATH] = {0,};
	::GetClassName(hwnd, buf, sizeof(buf));
	if(_tcsicmp(buf, _T("IEFrame")) == 0)
	{
		hwnd = ::GetWindow(hwnd, GW_CHILD);
		hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); // WorkerW
		hwnd = ::GetWindow(hwnd, GW_CHILD); // ReBarWindow32
		hwnd = ::GetWindow(hwnd, GW_CHILD); // ToolbarWindow32
		hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); // ComboBoxEx32
		hwnd = ::GetWindow(hwnd, GW_CHILD); // ToolbarWindow32
		hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); // ComboBox
		//hwnd = ::GetWindow(hwnd, GW_CHILD); // Edit
		::GetClassName(hwnd, buf, sizeof(buf));
		if(_tcsicmp(buf, _T("Edit")) != 0)
			return NULL;
		return hwnd;
	}
	else if(_tcsicmp(buf, _T("Chrome_WindowImpl_0")) == 0 || _tcsicmp(buf, _T("Chrome_WidgetWin_0")) == 0)
	{
		hwnd = ::GetWindow(hwnd, GW_CHILD); 
		//addressWnd = ::GetWindow(currenthWnd, GW_CHILD);
		while(hwnd != NULL)
		{
			hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); //WorkerW
			//::GetWindowTextA(hwnd, windowName, sizeof(windowName));
			::GetClassName(hwnd, buf, sizeof(buf));
			//::SendMessage(hwnd, WM_GETTEXT, MAX_PATH, (LPARAM) windowName);
			//MessageBox((LPCTSTR)windowName);// + (LPCTSTR)className);
			if(_tcsicmp(buf, _T( "Chrome_AutocompleteEditView" )) == 0)
			{
				return hwnd;
			}
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}
//////////////////////////////////

BOOL CJSHook::IsBrowser(HWND hwnd)
{
	TCHAR className[MAX_PATH];
	GetClassName(hwnd, className, sizeof(className));
	if(_tcsicmp(className, _T("IEFrame")) == 0 ||
		_tcsicmp(className, _T("Chrome_WindowImpl_0")) == 0 ||
		_tcsicmp(className, _T("Chrome_WidgetWin_0")) == 0 ||
		_tcsicmp(className, _T( "MozillaUIWindowClass")) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CJSHook::HwndCmp(HWND hwnd, CList<SStrt,SStrt&>* list)
{
	SStrt* temp;
	if(list->IsEmpty())
		return FALSE;

	INT_PTR n_Num = 0, n_Size = list->GetSize();
	POSITION pos = list->GetHeadPosition();

	while(n_Num < n_Size)
	{
		temp= &list->GetNext(pos);
		if(temp->m_hwnd == hwnd)
		{
			temp-> IsCheck = TRUE; //리스트에 있다가 없어진 목록 체크 
			::SendMessage(GetAddressBar(hwnd), WM_GETTEXT, MAX_PATH, (LPARAM) temp->m_URL) ;

			return TRUE;
		}

		n_Num++;
	}
	return FALSE;
}

int CJSHook::nDestoryWindows(CList<SStrt,SStrt&>* orginalList, CList<SStrt,SStrt&>* returnList)
{
	//CList<SStrt,SStrt&> returnValue;

	///////////////////////////

	int count =0;
	POSITION pos = orginalList->GetHeadPosition();
	int i =0;

	while(i<orginalList->GetCount())
	{
		POSITION tempPos = pos;
		SStrt temp= orginalList->GetNext(pos); 
		if(temp.IsCheck ==FALSE)
		{
			temp.m_EndTime = CTime::GetCurrentTime() ;
			returnList->AddHead(temp);
			orginalList->RemoveAt(tempPos);
			count++;
		}
		i++;
	}

	return count;
}

void CJSHook::initChecklist(CList<SStrt,SStrt&>* list , BOOL bCheck)
{
	int nItems = list->GetCount();
	POSITION pos = list->GetHeadPosition();
	for (int i=0; i<nItems; i++)
	{
		list->GetNext(pos).IsCheck= bCheck;
	}
}

int CJSHook::WritingText(CList<SStrt,SStrt&>* Destlist) 
{
	int nItems = Destlist->GetCount();
	POSITION pos = Destlist->GetHeadPosition();
	for (int i=0; i<nItems; i++)
	{
		SStrt data= Destlist->GetNext(pos);
		//CStrings = t.Format( "%A, %B %d, %Y" );
		CString message;


		message.Format(_T( "프로그램 명 : %s \n\t시작 : %d년 %d월 %d일 %s \n %d시 %d분 %d초 \n 종료 : %d년 %d월 %d일 %s \n %d시 %d분 %d초 \n"),

			data.m_Name,
			data.m_StartTime.GetYear(),
			data.m_StartTime.GetMonth(),
			data.m_StartTime.GetDay(),
			data.m_StartTime.Format("%A") ,
			data.m_StartTime.GetHour(),
			data.m_StartTime.GetMinute(),
			data.m_StartTime.GetSecond(),

			data.m_EndTime.GetYear(),

			//////////////////////////////////////////////
			data.m_EndTime.GetMonth(),
			data.m_EndTime.GetDay(),
			data.m_EndTime.Format("%A"),
			data.m_EndTime.GetHour(),
			data.m_EndTime.GetMinute(),
			data.m_EndTime.GetSecond()) ;
		if(texts.Find(message))
		{
			texts += message;
			UpdateData();
		}
		UpdateData();
	}
	return 0;
}
CTime CJSHook::Time_UsingBrowser(void)
{
	int nItems = Active_List_Browser.GetCount();
	CTime timeTotal = 0;
	if(nItems != 0)
	{
		POSITION pos = Active_List_Browser.GetHeadPosition() ;
		for(int i=0; i<nItems; i++)
		{
			timeTotal += CTime::GetCurrentTime()-Active_List_Browser.GetNext(pos).m_StartTime;
		}
	}

	nItems = Destory_List_Browser.GetCount();

	if(nItems != 0)
	{
		POSITION pos = Destory_List_Browser .GetHeadPosition();
		for(int i=0; i<nItems; i++)
		{
			timeTotal += Destory_List_Browser.GetNext(pos).m_EndTime - Destory_List_Browser.GetNext 
				(pos).m_StartTime;
		}
	}
	return timeTotal;
}

CTime CJSHook::Time_UsingPlayer(void)
{
	int nItems = Active_List_Player.GetCount();
	CTime timeTotal = 0;
	if(nItems != 0)
	{
		POSITION pos = Active_List_Player.GetHeadPosition();
		for(int i =0; i<nItems; i++)
		{
			timeTotal += CTime::GetCurrentTime() - Active_List_Player.GetNext(pos) .m_StartTime;
		}

		/////////////////////////////////
	}
	nItems = Destory_List_Player.GetCount();
	if(nItems != 0)
	{
		POSITION pos = Destory_List_Player.GetHeadPosition() ;
		for(int i =0; i<nItems; i++)
		{
			timeTotal += Destory_List_Player.GetNext(pos).m_EndTime - Destory_List_Player.GetNext 
				(pos).m_StartTime;
		}
	}
	return timeTotal;
}

CTime CJSHook::Time_UsingGamed(void)
{
	int nItems = Active_List_Games.GetCount();
	CTime timeTotal = 0;
	if(nItems != 0)
	{
		POSITION pos = Active_List_Games.GetHeadPosition();
		for(int i=0; i<nItems; i++)
		{
			timeTotal +=CTime::GetCurrentTime() - Active_List_Games.GetNext(pos).m_StartTime;
		}
	}
	nItems = Destory_List_Games.GetCount();
	if(nItems != 0)
	{
		POSITION pos = Destory_List_Games .GetHeadPosition() ;
		for(int i =0; i<nItems; i++)
		{
			timeTotal += Destory_List_Games.GetNext(pos).m_EndTime- Destory_List_Games.GetNext(pos). 
				m_StartTime;
		}
	}
	return timeTotal;
}

CTime CJSHook::Time_UsingTotal(void)
{
	/*CTime tub = 0, tup =0 , tug =O ;;
	Cl ime ti meTo ta l = 0;
	tub = Time_UsingBrowser();
	tup = Time_UsingPlayer();
	tug = Ti me_UsingGame();
	timeTotal = timeTotal+ tub:
	timeTotal += tup;
	timeTotal += tug;
	return timeTotaI; */
	CTime timeTotal = 0;
	timeTotal +=CTime::GetCurrentTime() - m_TimeStart;

	/////////////////////////////////////////
	return timeTotal;
}

HWND CJSHook::BlockSites(CList<CString,CString*> blockList)
{
	int nItems = Active_List_Browser.GetCount();
	int nBlocks = blockList.GetCount();

	POSITION blockPos = blockList.GetHeadPosition();
	POSITION pos = Active_List_Browser.GetHeadPosition();

	for(int i=0; i<nBlocks; i++)
	{
		//TCHAR b I_URL[ MAX_PATH ];
		CString bi_URL = blockList.GetNext(blockPos);
		for (int j=0; j<nItems; j++)
		{
			SStrt temp= Active_List_Browser.GetNext(pos);
			if(bi_URL.Find((CString)(temp.m_URL)))
			{
				return temp.m_hwnd;
			}
		}
	}
	return NULL;
}

void CJSHook::AddBlockURL(CString m_URL)
{
	BlockingList.AddHead(m_URL);
}

void CJSHook::SetBlockList(CList<CString,CString&> list)
{
	BlockingList.AddHead(&list) ;
}
