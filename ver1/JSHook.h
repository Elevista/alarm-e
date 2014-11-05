#pragma once
#include "SavingStruct.h"
#include "afxtempl.h"
//#include "afxwin.h"

class CJSHook :
	public CWnd
{
public:
	CJSHook(void);
	~CJSHook(void);

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CList<SSTRT,SSTRT&> Active_List_Browser;
	CList<SSTRT,SSTRT&> Active_List_Player;
	CList<SSTRT,SSTRT&> Active_List_Games;

	CList<SSTRT,SSTRT&> Destory_List_Browser;
	CList<SSTRT,SSTRT&> Destory_List_Player;
	CList<SSTRT,SSTRT&> Destory_List_Games;
	HWND GetAddressBar(HWND hwnd);
	BOOL IsBrowser(HWND hwnd);
	BOOL HWNDCmp(HWND hwnd, CList<SStrt,SStrt&>* list);
	int nDestoryWindows(CList<SSTRT,SSTRT&>* list, BOOL bCheck);
	CString texts;
	int WritingText(CList<SSTRT,SSTRT&>* DestList);
	afx_msg void OnBnClickedCancel();
	CTime Time_UsingBrowser(void);
	CTime Time_UsingPlayer(void);
	CTime Time_UsingGamed)(void);
	CTime Time_UsingTotal(void);
	CTime m_TimeStart;
	HWND BlockSites(CList<CString,CString*> blockList);
	CLIst(CString,CString&> BlockingList;
	void AddBlockURL(CString m_URL);
	void SetBlockList(CList<CString,CString&> list);
	void Test();

private:
	CList<CString,CString&> GetBlockList(void);
};
