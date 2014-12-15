
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// alarm-e.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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