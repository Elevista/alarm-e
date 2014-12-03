#pragma once
#include "SavingStruct.h"
#include "afxtempl.h"
#include "afxwin.h"

//#include "afxwin.h"

class CJSHook :	public CWnd {
public:
	CJSHook(void);
	~CJSHook(void);

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CList<SStrt,SStrt&> Active_List_Browser;
	CList<SStrt,SStrt&> Active_List_Player;
	CList<SStrt,SStrt&> Active_List_Games;

	CList<SStrt,SStrt&> Destory_List_Browser;
	CList<SStrt,SStrt&> Destory_List_Player;
	CList<SStrt,SStrt&> Destory_List_Games;
	
	HWND GetAddressBar(HWND hwnd);
	BOOL IsBrowser(HWND hwnd);
	
	BOOL HwndCmp(HWND hwnd, CList<SStrt,SStrt&>* list);
	BOOL Hwnd(HWND hwnd, CList<SStrt,SStrt&>* list);
	int nDestoryWindows(CList<SStrt,SStrt&>* list, CList<SStrt,SStrt&>* returnlist);
	int n_Destory_Browser;
	CString texts;
	int WritingText(CList<SStrt,SStrt&>* DestList);
	afx_msg void OnBnClickedCancel();

	void initChecklist(CList<SStrt,SStrt&>* list , BOOL bCheck);
	CTime Time_UsingBrowser(void);
	CTime Time_UsingPlayer(void);
	CTime Time_UsingGamed(void);
	CTime Time_UsingTotal(void);
	CTime m_TimeStart;

	HWND BlockSites(CList<CString,CString&> blockList);
	CList<CString,CString&> BlockingList;

	void AddBlockURL(CString m_URL);
	void SetBlockList(CList<CString,CString&> list);
	void Test();

private:
	CList<CString,CString&> GetBlockList(void);
};
