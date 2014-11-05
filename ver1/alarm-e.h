//alarm-e.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
#pragma once

#ifndef __AFXWIN_H__
#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'f를 포함합니다."
#endif

#include "resource.h"  //주 기호입니다.
#include "afxtempl.h"
#include "DBDataForm.h"
#include "MessageForm.h"

// CalarmeApp:
// 이 클래스의 구현에 대해서는 alarm-e.cpp를 참조하십시오.

class CalarmeApp : public CWinAppEx
{
public:
	CalarmeApp();
	~CalarmeApp();

	//재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	HANDLE m_hThreadHook;
	enum INPUTTYPE{e_BROWSER =0,e_PLAYER,e_GAME,e_URL,e_Word,e_Img};
	void HookStartingThread();
	static DWORD WINAPI HookThreadFunction(LPVOID pParent);
	void HookFinishThreadFunction();

	ULONG_PTR m_gpToken;

	CList<SStrt,SStrt&> Active_List_Browser;
	CList<SStrt,SStrt&> Active_List_Player;
	CList<SStrt,SStrt&> Active_List_Games;

	CList<SStrt,SStrt&> Destroy_List_Browser;
	CList<SStrt,SStrt&> Destroy_List_Player;
	CList<SStrt,SStrt&> Destroy_List_Games;

	CList<CDBDataForm,CDBDataForm&> videoClipInfo;
	Clist<CDBDataForm,CDBDataForm&> gameInfo;
	Clist<CDBDataForm,CDBDataForm&> internetInfo;
	Clist<CDBDataForm,CDBDataForm&> BlockingWordInfo;
	Clist<CDBDataForm,CDBDataForm&> BlockingURLInfo;
	Clist<CDBDataForm,CDBDataForm&> EduListInfo;
	Clist<CDBDataForm,CDBDataForm&> captureInfo;
	//Clist<CString,CString&> BlockingURLList;

	Clist<CDBDataForm,CDBDataForm&> videoDayInfo;
	Clist<CDBDataForm,CDBDataForm&> gameDayInfo;
	Clist<CDBDataForm,CDBDataForm&> internetDayInfo;

	Clist<CDBDataForm,CDBDataForm&> videoMonthInfo;
	Clist<CDBDataForm,CDBDataForm&> gameMonthInfo;
	Clist<CDBDataForm,CDBDataForm&> internetMonthInfo;

	HWND GetAddressBar(HWND hwnd);
	BOOL IsBrowser(HWND hwnd);
	BOOL IsPlayer(HWND hwnd);
	BOOL IsGame(HWND hwnd);
	BOOL IsspectEduURL(CString url);
	BOOL HwndCmp(HWND hwnd, CList<SStrt,SStrt&>* list);
	int nDestroyWindows(CList<SStrt,SStrt&>* orginalList, CList<SStrt,SStrt&>* returnList);
	int n_Destory_Browser, n_Destroy_Player, n_Destory_Game;
	void initCheckList(CList<SStrt,SStrt&>* list, BOOL bCheck);
	CString texts;
	int WritingText(CList<SStrt,SStrt&>* DestList);

	CTime Time_UsingBrower(void);
	CTime Time_UsingPlayer(void);
	CTime Time_UsingGame(void);
	CTime Time_UsingTotal(void);
	CTime m_TimeStart;
	CTime Time_Boot;
	CTime Time_AfterCapture;
	CTime Time_ShutDown;

	HWND BlockSites(CList<CString,CString&> blockList);

	void AddBlockURL(CString m_URL, CString m_date);
	void AddCaptureImg(CString m_URL, Cstring m_date);
	//void SetBlockLIst(CList<CString,CString&> list);
private:
	CList<CString,CString*> GetBlockList(void);
	// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL Insert4PrmTable(INPUTTYPE type);
	BOOL Insert3PrmTable(INPUTTYPE type, CString word);
	BOOL DBinputForm(CString szQurryString);
	BOOL inspectURL(CString url);

	void Capture();

	void LoadVideoDB(void);
	void LoadGameDB(void);
	void LoadUsingURLDB(void);
	void LoadBanWordDB(void);
	void LoadImageDB(void);
	void LoadBanURLDB(void);

	void LoadVideoDB(int year, int month, int day);
	void LoadGameDB(int year, int month, int day);
	void LoadUsingURLDB(int year, int month, int day);

	void LoadVideoDB(int year, int month);
	void LoadGameDB(int year, int month);
	void LoadUsingURLDB(int year, int month);
	void PopupEcampus(int nMode);

	int n_captureTime, n_captureLevel;
	CString m_captureDirectory,m_captureFileName;
	BOOL isInthe3List(CDBDataForm cmpType, CList<CDBDataForm,CDBDataForm&>* list);
	BOOL isInthe4List(CDBDataForm cmpType, CList<CDBDataForm,CDBDataForm&>* list);
	int m_limitedTimeFrom, m_LimitedTimeTo;
	int m_limitedTimeUsingCom;
	HWND m_h0ldhWnd;

	void LoadRcvMessages(int nMode);
	void LoadEcampusList();
	BOOL inspectSameMSG(CMessageForm cmpType, CList<CMessageForm,CMessageForm&>* list);

	CList<CMessageForm,CMessageForm&> m_ListToParent, m_ListToChild, m_ListEcampus;
	CList<CMessageForm,CMessageForm&> m_RCVLIST, m_WILLSENDLIST, m_SENDEDLIST;

	void GetTimeSetData();
	void PrintMessage(int nMode);
	void InitForReLoad();
	void LoadEduURLDB(void);

	int m_editTimeUseHour;
	int m_editTimeMinute;
	int m_editTimeBanHour1;
	int m_editTimeBanMinute1;
	int m_editTimeBanHour2;
	int m_editTimeBanMinute2;

	int ReAlaramTime,ReAlaramTime2,ReAlaramTime3;
	BOOL m_bIsAlram, m_blsAlaram2, m_blsAlaram3;

	BOOL m_blsBanDay;

	CString m_szCaptureDirectory;

	int m_DayOfWeek;

	BOOL m_blsChild;
};

HANDLE DDBToDIB(CBitmap& bitmap, DWORD dwCompression, CPalette* pPal); // DDB에서 DIB로 변환
static HANDLE		m_hDIB;
static BITMAPINFO	m_bmpinfo;
BOOL	WriteToDIB(CRect &rect, CSize &destSize, HANDLE &hDIB); // DIB에 쓰기

extern CalarmeApp theApp;







