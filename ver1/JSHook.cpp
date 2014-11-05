
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
void CJSHook::QnTimer(UINT_PTR niDEvent)
{

	HWND currentHwnd;
	TCHAR str[MAX_PATH] = {0,};
	CString message;
	switch(niDEvent)
	{
	case 1 :
		currentHwnd = GetDesktopWindow()->GetSafeHwnd(); 
		currentHwnd = ::GetWindow(currentHwnd, GW_CHILD);

		if(!Active_List_Browser.lsEmpty())
			initCheckList(&Active_List_Browser,FALSE);

		while(currentHwnd !=NULL)
		{
			TCHAR className[MAX_PATH] = {O,};
			TCHAR programName[MAX_PATH] = {0,};

			/*if(!GetCiassName(hwnd, className , sizeof(className)) &&
			GetLastError() != ERROR_SUCCESS)
			return; */
			if(lsBrowser(currentHwnd) && !HwndCmp(currentHwnd,&Active_List_Browser))
			{
				SStrt temp;
				temp.m_hwnd = currentHwnd;
				::GetWindowText(currentHwnd, temp.m_Name, sizeof(temp.m_Name)); 
				//::GetWindowText(GetAddressBar(current Hwnd),temp->m_URL,sizeof(temp->m_URL));
				HWND returnHwnd ;
				::SendMessage(returnHwnd = GetAddressBar(currentHwnd), WM_GETTEXT , MAX_PATH, (LPARAM)
					temp.m_URL);
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
		n_Destory_Browser += nDestroyWindows(&Active_List_Browser ,&Destory_List_Browser);

		WritingText(&Destory_List_Browser);

		break;

		//case 2:
		//KiIITimer(1);
		//KillTimer(2);
		// break:
	}

	//CWnd::QnTimer(nIDEvent);

}

HWND CJSHook::GetAd9ressBar(HWND hwnd)
{
	TCHAR buf[MAX_PATH] = {0,};
	::GetClassName(hwnd, buf, sizeof(buf));
	if(_tcsicmp(buf, _T("IEFrame")) == 0)
	{
		hwnd = ::Getwindow(hwnd, GW_CHILD);
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
	else if(_tcsicmp(buf, _T("Chrome_Windowlmpl _O")) == 0 || _tcsicmp(buf, _T("Chrome_WidgetW n_O")) == 0)
	{
		hwnd = ::GetWindow(hwnd, GW_CHILD); 
		//addressWnd = ::GetWindow(currenthWnd, GW_CHILD);
		while(hwnd != NULL)
		{
			hwnd = ::GetWindow(hwnd, GW_HWNDNEXT); //WorkerW
			//::GetWindowTextA(hwnd, windowName, sizeof(windowName));
			::GetCiassName(hwnd, buf, sizeof(buf));
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

BOOL CJSHook::lsBrowser(HWND hwnd)
{
	TCHAR className[MAX_PATH];
	GetClassName(hwnd, className, sizeof(className));
	if(_tcsicmp(className, _T("IEFrame")) == 0 ||
		_tcsicmp(className, _T("Chrome_Windowlmpi_O")) == 0 ||
		_tcsicmp(className, _T("Chrome_WidgetWin_O")) == 0 ||
		_tcsicmp(className, _T( "Mozi I laUIWindowCiass")) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CJSHook::HwndCmp(HWND hwnd, CList<SStrt,SStrt&>* Iist)
{
	SStrt* temp;
	if(Iist->lsEmpty())
		return FALSE;

	INT_PTR n_Num = 0, n_Size = Iist->GetSize();
	POSITION pos = Iist->GetHeadPosition();

	while(n_Num < n_Size)
	{
		temp= &list->GetNext(pos);
		if(temp->m_hwnd == hwnd)
		{
			temp-> IsCheck = TRUE; 
			::SendMessage(GetAddressBar(hwnd), WM_GETTEXT, MAX_PATH, (LPARAM) temp->m_URL) ;

			return TRUE;
		}

		n_Num++;

		/*if(pos != list->GetTailPosition())
		{
		temp = &Iist ->GetNext(pos);
		pos++;
		}
		else
		{
		temp = NULL;
		}*/
	}
	return FALSE;
}

int CJSHook::nDestroyWindows(CList<SStrt,SStrt&>* orginaiList, CList<SStrt,SStrt&>* returnList)
{
	//CList<SStrt,SStrt&> returnValue;

	///////////////////////////

	int count =O;
	POSITION pos = orginallist->GetHeadPosition();
	int i =O;

	while(i<orginallist->GetCount())
	{
		POSITION tempPos = pos;
		SStrt temp= orginallist->GetNext(pos); 
		if(temp.!sCheck ==FALSE)
		{
			temp.m_EndTime = CTime::GetCurrentTime() ;
			returnlist->AddHead(temp);
			orginallist->RemoveAt(tempPos);
			count++;
		}
		i++;
	}

	return count;
}

void CJSHook::initChecklist(CList<SStrt,SStrt&>* Iist , BOOL bCheck)
{
	int nltems = list->GetCount();
	POSITION pos = Iist->GetHeadPosition();
	for (int i=0; i<nItems; i++)
	{
		Iist->GetNext(pos).IsCheck= bCheck;
	}
}

int CJSHook::WritingText(CList<SStrt,SStrt&>* Destlist) 
{
	int nltems = Destlist->GetCount();
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
			data.m_EndT me.GetMonth(),
			data.m_EndT me.GetDay(),
			data.m_EndT me.Format("%A"),
			data.m_EndT me.GetHour(),
			data.m_EndT me.GetMinute(),
			data.m_EndT me.GetSecond()) ;
		if(texts.Find(message))
		{
			texts += message;
			UpdateData();
		}
		UpdateData();
	}
	return O;
}



CJSHook::Time_UsingBrowser(void)
{
	int nltems = Active_List_Browser.GetCount();
	CTime timeTotal = O;
	if(nItems ! = 0)
	{
		POSITION pos = Active_List_Browser .GetHeadPosition() ;
		for(int i=0; i<nItems; i++)
		{
			timeTotal += CTime::GetCurrentTime()  - Active_List_Browser.GetNext(pos).m_StartTime;
		}
	}

	nltems = Destory_List_Browser.GetCount();

	if(nItems ! = 0)
	{
		POSITION pos = Destory_List_Browser .GetHeadPosit ion();
		for(int i=0; i<nItems; i++)
		{
			timeTotal += Destory_List_Browser.GetNext(pos).m_EndTime - Destory_List_Browser.GetNext 
				(pos).m_StartTime;
		}
	}
	return timeTotal;
}

CJSHook::Time_UsingPiayer(void)
{
	int nltems = Active_List_Player.GetCount();
	CTime timeTotal = O;
	if(nItems ! = 0)
	{
		POSITION pos = Active_List_Player.GetHeadPosition();
		for(int i =0; i<nItems; i++)
		{
			timeTotal += CTime::GetCurrentTime() - Active_List_Player.GetNext(pos) .m_StartTime;
		}

		/////////////////////////////////
	}
	nltems = Destory_List_Piayer.GetCount();
	if(nItems ! = 0)
	{
		POSITION pos = Destory_List_Piayer .GetHeadPosition() ;
		for(int i =0; i<nItems; i++)
		{
			timeTotal += Destory_List_Player.GetNext(pos).m_EndTime - Destory_List_Player.GetNext 
				(pos).m_StartTime:
		}
	}
	return timeTotal;

	CTime CJSHook::Time_UsingGame(void)
	{
		int nltems = Active_List_Games.GetCount();
		Clime timeTotal = O;
		if(nItems ! = 0)
		{
			POSITION pos = Active_List_Games.GetHeadPosition();
			for(int i=O; i<nltems; i++)
			{
				timeTotal +=Clime::GetCurrentrime() - Active_List_Games.GetNext(pos).m_StartTime:
			}
			nltems = Destory_List_Games.GetCount();
			if(nItems ! = 0)
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
			Clime timeTotal = O;
			timeTotal +=Clime::GetCurrentTime() - m_TimeStart:

			/////////////////////////////////////////
			return timeTotal;
		}

		HWND CJSHook::BiockSites(CList<CString,CString&> blacklist)
		{
			int nltems = Active_List_Browser .GetCount();
			int nBicoks = blocklist.GetCount();

			POSITION blockPos = blocklist.GetHeadPosition();
			POSITION pos = Active_List_Browser .GetHeadPosition();

			for(int i=O; i<nBlcoks; i++)
			{
				//TCHAR b I_URL[ MAX_PATH ];
				CString bi_URL = blocklist.GetNext(blockPos);
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

		void CJSHook::AddBiockURL(CString m_URL)
		{
			Blockinglist.AddHead(m_URL);
		}

		void CJSHook::SetBiocklist(CList<CString,CString&> Iist)
		{
			Blockinglist.AddHead(&list) ;
		}
