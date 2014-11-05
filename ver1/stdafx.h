// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#define UM_TRAYICON (WM_USWER + 101)
#define WM_BANWORD UM_USER + 5

#ifndef VC_EXTRALEAN
#define Vc_EXTRALEAN
#endif

#include "targetver.h"

#define _ATL_ALL_WARNINGS

#include <afxwin.h>
#include <afxext.h>

#include <afxdisp.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>
#endif
#ifndef  _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif 

#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus")

#include <afxcontrolbars.h>
#include <afxdhtml.h>
#include <afxdb.h>
#include <iostream>
#include "JSHook.h:

#include <odbcinst.h>

#include <vector>
using namespace std;

extern "C" void Hook();
extern "C" void UnHook();
extern "C" bool isHook();

extern "C" void MouseHook();
extern "C" void MouseUnHook();
extern "C" bool isMouseHook();

extern "C" void AltTab_Hook();
extern "C" void AltTab_UnHook();
extern "C" bool isArtHook();

extern "C" void Delete_Hook();
extern "C" void Delete_UnHook();
extern "C" bool isDelHook();

extern "C" void sendDB(vector<CString> dbData);
extern "C" void keyStrlnit();
extern "C" void hWndSend(HWND hWnd);

#ifdef _UNICODE
#if defined _M_IX86
#pragma commnet(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture= 'x86' publickeyToken='6595b64144ccf1df' language = '*'w"")
#elif defined _M_IA64
#p0ragma commnet(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture= 'ia64' publickeyToken='6595b64144ccf1df' language = '*'w"")
#elif defined _M_X64
#pragma commnet(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture= 'amd64' publickeyToken='6595b64144ccf1df' language = '*'w"")
#else
#pragma commnet(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture= '*' publickeyToken='6595b64144ccf1df' language = '*'w"")
#endif
#endif

INT DrawTextEx(HDC hDC, WCHAR * szText, RECT * rc, BOOL bBold, INT nSize, DWORD dwColor, UINT uDTOptions);
INT DrawTextEx(HDC hDC, WCHAR * szText, int nCOl, int nRow, BOOL bBold, INT nSize, DWORD dwColor);

void GetFillLogFont(LOGFONT * logFont, BOOL bSystem = TRUE, INT nSize = 0, BOOL bBold = FALSE);
void DrawImageBitBlt(HDC hdc, HBITMAP hBitmap, INT nX, INT nY);

BOOL OnOdbcAutoSetup();
UINT GetScreenWidth();
UINT GetScreenHeight();

void MoveDIgCenter(HWND hWnd, int nDigWidth, int nDIgHeight);

extern CString g_szUserName;
extern BOOL g_bTest;
extern CJSHook g_JSHook;
