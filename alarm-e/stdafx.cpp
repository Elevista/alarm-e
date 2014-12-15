
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// alarm-e.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

CString g_szUserName =L"";
BOOL g_bTest = FALSE;
CJSHook g_JKHook; // = new CJSHook();

UINT GetScreenWidth() {
	return GetSystemMetrics(SM_CXSCREEN);
}
UINT GetScreenHeight() {
	return GetSystemMetrics(SM_CYSCREEN);
}
INT DrawTextEx(HDC hDC, WCHAR * szText, int nCol, int nRow, BOOL bBold, INT nSize, DWORD dwColor)
{
	long mBKMode;
	TCHAR wszMsg[128]=_T("");
	RECT rt;
	HFONT hOldFont = NULL;

	wcscpy(wszMsg, szText);
	HFONT hFont;
	LOGFONT logFont;
	GetFillLogFont(&logFont,FALSE, nSize);
	if(bBold == TRUE) 
		logFont.IfWeight = FW_BOLD;
	hFont = CreateFontIndirect(&logFont);
	hOldFont =(HFONT) SelectObject(hDC,hFont);
	nBKMode = GETBkMode(hDC);
	SetBKMode(hDC, TRANSPARENT);
	SetTextColor(hDC, dwColor);
	SIZE sz;
	GetTextExtentPoint32(hDC, szText, wcslen(szText), &sz);
	rt.left = nCol;
	rt.right = rt.left + sz.cx;
	rt.top = nRow;
	rt.bottom = rt.top + sz.cy;
	::DrawText(hDC, wszMsg,wcslen(wczMsg),&rt,DT_LEFT | DT_TOP);
	SetBKMode(hDC,nBKMode);
}