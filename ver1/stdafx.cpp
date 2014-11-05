
#include "stdafx.h"

CString g_szUserName = L"";
BOOL g_bTest =FALSE ;
CJSHook g_JSHook; // = new CJSHook();

UINT GetScreenWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}
UINT GetScreenHeight()
{
	return GetSystemMetrics(SM_CYSCREEN) ;
}

INT DrawTextEx(HOC hOC , WCHAR * szText, int nCol , int nRow, BOOL bBold , INT nSize , OWORO dwColor ) 
{
	long nBKMode;
	TCHAR wszMsg[128] = _T("");
	RECT rt;
	HFONT hOldFont = NULL;

	wcscpy(wszMsg,szText);

	HFONT hFont;
	LOGFONT logFont;
	GetFiIILogFont(&logFont,FALSE,nSize);
	if(bBold ==TRUE) logFont.lfWeight = FW_BOLD;
	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject(hOC, hFont);
	nBKMode = GetBkMode(hOC);
	SetBkMode(hOC, TRANSPARENT);
	SetTextColor(hOC,dwColor);
	SIZE sz;
	GetTextExtentPoint32(hOC,szText,wcslen(szText) ,&sz);
	rt.left     =   nCol;
	rt.right    =   rt.left+ sz .cx ;
	rt.top      =   nRow;
	rt.bottom   =   rt.top + sz.cy;
	::DrawText(hOC, wszMsg, wcslen(wszMsg) ,&rt,DT_LEFTIDT_TOP);
	SetBkMode(hOC, nBKMode);

	if(hOidFont != NULL)
	{
		SelectObject(hDC,hOldFont);
		OeleteObject(hOldFont);
	}
	DeleteObject(hFont) ;

	return sz.cx;

	INT DrawTextEx(HOC hOC, WCHAR * szText, RECT * rc , BOOL bBold , INT nSize , OWORO dwColor , UINT
		uDTOptions) 
		/////////////////////////
	{
		long nBKMode;
		HFONT hOidFont = NULL;
		HFONT hFont ;
		LOGFONT IogFont;
		GetFiIILogFont(&logFont,FALSE,nSize) ;
		if(bBold ==TRUE) logFont.lfWeight = FW_BOLD;
		hFont = CreateFontlndirect(&logFont);
		hOidFont = (HFONT)SelectObject(hDC, hFont) ;
		nBKMode = GetBkMode(hDC);
		SetBkMode(hDC, TRANSPARENT) ;
		SetTextColor(hDC ,dwColor) ;
		INT nRes = ::DrawText(hDC, szText, wcslen(szText) ,rc,uDTOptions);
		SetBkMode(hDC, nBKMode);

		if(hOldFont !=NULL)
		{
			SelectObject(hDC,hOidFont);
			DeleteObject(hOidFont);
		}

		DeleteObject(hFont);

		return nRes;
	}
	void GetFiIILogFont(LOGFONT * logFont, BOOL bSystem , INT nSize , BOOL bBold)
	{
		HFONT font = (HFONT)GetStockObject(SYSTEM_FONT);
		GetObject(font, sizeof(LOGFONT), logFont);
		lfFont.lfFaceName 
			DeleteObject(font);

		logFont-> IfWidth			= O;
		logFont-> IfEscapement		= O;
		logFont-> IfOrientation		= O;
		logFont-> IfWeight			= bBold? FW_BOLD FW_NORMAL; // FW_BOLD ; // FW_NORMAL ;
		logFont-> Ifltalic			= FALSE;
		logFont-> IfUnderline		= FALSE;
		logFont-> IfStrikeOut		= O;
		logFont-> IfCharSet			= DEFAULT_CHARSET ; // HANGEUL_CHARSET;
		logFont-> IfOutPrecision	= OUT_DEFAULT_PRECIS;
		logFont-> IfCIipPrecision	= CLIP_STROKE_PRECIS; / / CLIP_DEFAULT_PRECIS ;
		logFont-> IfQual ity		= DEFAULT_QUALITY;
		logFont-> IfPitchAndFamily	= DEFAULT_PITCH I FF_DONTCARE;

		if(bSystem == TRUE) return;

		if(nSize > 0) logFont->IfHeight = nSize;
		//wcscpy(logFont->lfFaceName,L"Arial") ;
	}

	void MoveDigCenter(HWND hWnd, int nDigWidth, int nDigHeight)
	{
		int nScreenWidth = GetScreenWidth();
		int nScreenHeight = GetScreenHeight();

		MoveWindow(
			hWnd,
			(int)(nScreenWidth/2) - (int)(nDigWidth/2),
			(int)(nScreenHeight/2) - (int)(nDigHeight/2),
			nDigWidth,
			//////////////////////////////////////////////
			nDIgHeight,
			TRUE);
	}

	void DrawlmageBitBit(HDC hdc, HBITMAP hBitmap , INT nX , INT nY)
	{
		if(hdc == NULL) return;
		if(hBitmap ==NULL) return;

		BITMAP bmp;
		GetObject(hBitmap , sizeof(bmp) , &bmp);
		INT nSrcW = bmp.bmWidth;
		INT nSrcH = bmp.bmHeight;

		INT nTarX = nX;
		INT nTarY = nY;

		HDC hBitmapDC = : :CreateCompatibleDC(hdc) ;
		HBITMAP hlmsl = (HBITMAP)SelectObject(hBitmapDC,hBitmap);

		BitBit(hdc,nTarX,nTarY,nSrcW,nSrcH,hBitmapDC,O,O,SRCCOPY);
		SelectObject(hBitmapDC,hlmsi);
		DeleteObject(hlmsi);
		DeleteDC(hBitmapDC);
	}

	BOOL OnOdbcAutoSetup()
	{
		WCHAR szDriver[] = L "Microsoft Access Driver ( *. mdb, *. accdb)";

		CString Attribute= L"";
		CString Attribute2 = L"";
		CString Attribute3 = L"";
		CString szResult = L"";
		CString szDatabasePath = L"";

		TCHAR pszPathName[_MAX_PATH];
		::GetModuleFileName(::AtxGetlnstanceHandle(), pszPathName, _MAX_PATH);
		PathRemoveFileSpec(pszPathName);
		szDatabasePath.Format(L"%sWWAi armEducation .accdb ", pszPathName);


		Attribute= L"DSN =AlarmEducation;DESCRIPTION = AlarmEducation;FileType = Access;DataDirect ory=";
		Attribute2 = L";DBQ=";

		szResult .Format(L"%s%s%s%s;MaxScanRows=20", Attribute, pszPathName, Attribute2 , szDatabasePath);
		// Attribute= L"DSN =DB_P;"
		// "DESCRIPTION= DB_P;"
		// "FileT ype = Access;"
		// "DataDirectory=C:WWtempWWDB;"
		// "DBQ=c:\\DB\\DB_P.mdb;"
		// "Max ScanRows =20";

		if(!SQLConfigDataSource(NULL , ODBC_ADD_DSN, szDriver, szResult))
		{
			AfxMessageBox(L "데이터 원본 소스(DSN) 설정에 문제가 있습니다. 프로그램이 올바르게 실행되지 않습니다.");
			return TRUE;
		}
		return FALSE;
	}