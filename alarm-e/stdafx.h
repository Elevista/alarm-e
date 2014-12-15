
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#define UM_TRAYICON (WM_USER + 101) 
#define UM_BANWORD WM_USER+5



#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
#include <afxdb.h>

#include <afx.h>


#include <gdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

#include <afxcontrolbars.h>
#include <afxdhtml.h>
#include <afxdb.h>
#include <iostream>
#include "JSHook.h"
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
extern "C" bool isAltHook();

extern "C" void Delete_Hook();
extern "C" void Delete_UnHook();
extern "C" bool isDelHook();

extern "C" void sendDB(vector<CString> dbData);
extern "C" void keyStrInit();
extern "C" void hWndSend(HWND hWnd);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


INT DrawTextEx(HDC hDC, WCHAR * szText, RECT * rc, BOOL bBold, INT nSize, DWORD dwColor, UINT uDTOptions);
INT DrawTextEx(HDC hDC, WCHAR * szText, int nCol, int nRow, BOOL bBold, INT nSize, DWORD dwColor);

void GetFillLogFont(LOGFONT * logFont, BOOL bSystem = TRUE, INT nSize = 0, BOOL bBold = FALSE);
void DrawImageBitBlt(HDC hdc, HBITMAP hBitmap, INT nX, INT nY);

BOOL OnOdbcAutoSetup();
UINT GetScreenWidth();
UINT GetScreenHeight();

void MoveDlgCenter(HWND hWnd, int nDlgWidth, int nDlgHeight);

extern CString g_szUserName;
extern BOOL g_bTest;
extern CJSHook g_JSHook;

CString GetTypedWord();
void ClearTypedWord();