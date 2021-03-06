#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"winmm.lib")

#include "stdafx.h"
#include "Alarm-e.h"
#include "Alarm_UIPopup.h"

extern "C" void Hook() ;
extern "C" void Delete_UnHook();

IMPLEMENT_DYNAMIC(CAlarm_UIPopup, CDialog)

	CAlarm_UIPopup::CAlarm_UIPopup(CWnd* pParent /*=NULL*/)
	:CDialog(CAlarm_UIPopup::IDD, pParent)
{
	m_nCount = 0;
	m_nX = 0;
	m_nY = 0;
}

CAlarm_UIPopup::~CAlarm_UIPopup()
{
}
void CAlarm_UIPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlarm_UIPopup, CDialog)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CAlarm_UIPopup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ModityStyleEx(NULL , WS_EX_TOOLWINDOW) ;

	SkinLoad();
	SetTimer(1, 500, NULL) ;
	int nWidth = 503;
	int nHeight = 176;
	if(m_nX != 0 && m_nY != 0)
	{
		MoveWindow(m_nX, m_nY , nWidth, nHeight, TRUE);
		return TRUE;
	}

	int nX = GetScreenWidth();
	int nY = GetScreenHeight();
	//////////////////////////////////////
	MoveWindow(nX - nWidth - 50, nY - nHeight - 50,nWidth, nHeight, TRUE);

	BringWindowToTop();

	return TRUE; // return TRUE unless you set the focus to a control
}
void CAlarm_UIPopup::SkinLoad()
{
	//m_bmpDigUp.LoadBitmap( IDB_MAIN);
	//m_bmpDigDn.LoadBitmap( IDB_MAIN_OV);
	//m_bmpDigFs.LoadBitmap( IDB_MA IN_CL);
	//BITMAP bmp;
	//m_bmpDigUp.GetBitmap( &bmp);

	//SetWindowPos( NULL , 0, 0, bmp.bmWidth, bmp .bmHeight, SWP_NOZORDER );
	BitmapRgn(IDB_BITMAP_POPUP_MASK, RGB( 255,255,255) ) ;
	// CenterWindow();
}

BOOL CAlarm_UIPopup::BitmapRgn(UINT resource, COLORREF TansColor)
{
	HBITMAP m_hBack;
	HINSTANCE hlnstance = AfxGetInstanceHandle();
	m_hBack = (HBITMAP)LoadBitmap(hlnstance, MAKEINTRESOURCE(resource));
	::SetWindowRgn(m_hWnd, BitmapToRegion( m_hBack, TansColor, TansColor ) ,TRUE);

	return TRUE;
}

HRGN CAlarm_UIPopup::BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, COLORREF cTolerance)
{
	HRGN hRgn = NULL;

	if ( hBmp)
	{
		// Create a memory DC inside which we wi I I scan the bitmap content
		HDC hMemDC = CreateCompatibleDC(NULL);
		if ( hMemDC)
		{
			//Get bitmap size
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);

			//Create a 32 bits depth bitmap and select it into the memory DC
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {
				sizeof(BITMAPINFOHEADER),// biSize
				bm.bmWidth, //biWidth;
				bm.bmHeight, // biHeight;
				1, //biPlanes;
				32, // biBitCount
				BI_RGB, //biCompression;
				0, // biSizelmage;
				0, // biXPelsPerMeter;
				0, //biYPelsPerMeter;
				0, //biCIrUsed;
				0  //biCirImportant;
			};
			VOID * pbits32 ;
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO,
				/////////////////////////////
				DIB_RGB_COLORS , &pbits32 , NULL, 0) ;
			if(hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC , hbm32) ;

				//Create a DC just to copy the bitmap into the memory DC
				HDC hDC = CreateCompatibleDC(hMemDC) ;
				if (hDC)
				{
					//Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits)
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32) ;
					while (bm32.bmWidthBytes% 4)
						bm32.bmWidthBytes++;

					// Copy the bitmap into the memory DC
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					BitBlt(hMemDC, 0, 0, bm . bmWidth , bm.bmHeight , hDC, 0 , 0, SRCCOPY);

					// For better performances , we wiII use the ExtCreateRegion() function to create the

					// region. This function take a RGNDATA str uctur e on entry . We wiII add rectangles by

					// amount of ALLOG_UNIT number in this structure.
#define ALLOC_UNIT 100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) *maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData) ;
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG , MAXLONG , 0, 0) ;

					// Keep on hand highest and lowest va lu es f or the "t ransparent " pixels
					BYTE lr = GetRValue(cTransparentColor) ;
					BYTE lg = GetGValue(cTransparentColor) ;
					BYTE lb = GetBValue(cTransparentColor) ;
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// Scan ea ch bitmap row from bottom to top (the bitmap is inverted vertically)
					BYTE *p32 =(BYTE *)bm32.bmBits + (bm32.bmHeight- 1) * bm32.bmWidthBytes ;
					for(int y=0; y<bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to right
						for ( int x= 0; x<bm.bmWidth; x++)
						{
							//Search for a continuous rang e of "non tran spare nt pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b=GetRValue(*p);
								if(b >= lr&& b <=hr)
								{
									b = GetGValue(*p);
									if (b >= lg&&b <= hg)
									{
										b = GetBValue(*p) ;
										if(b >= lb && b <= hb)
											//This pixe l is "transparent"
											break;
										/////////////////////////////////////										
									}
								}
								p++;
								x++;
							}

							if(x > x0)
							{
								// Add the pixel s (xO, y) to (x, y+1) as a new rectangle in the region
								if(pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof
										(RECT) * maxRects), GMEM_MOVEABLE) ;
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1) ;
								if(x0 < pData->rdh.rcBound. left)
									pData->rdh.rcBound. left= x0 ;
								if(y < pData->rdh.rcBound. top)
									pData->rdh.rcBound.top= y;
								if(x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1 ;
								pData->rdh.nCount++;
								// On Windows98, Ext Cr eat eRegio n() may fa i I if the number of rectangles is too

								//large (ie: > 4000 ) . The refore, we have to create the region by multiple steps.
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);

									if(hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR) ;
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// Go to next row (remember , the bitmap is inverted vertically)
						p32 -= bm32 .bmWidthBytes;
					}
					//Create or extend the region with the remaining rectangles
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if(hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						////////////////////////////////////

						hRgn = h;
					//Clean up
					GlobalFree(hData);
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}
				DeleteObject(SelectObject(hMemDC, holdBmp));
			}
			DeleteDC(hMemDC);
		}
	}
	return hRgn;
}
void CAlarm_UIPopup::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(1);
}
void CAlarm_UIPopup::OnPaint()
{
	CPaintDC dc(this); // device context for paint ing
	// dc.BitBIt(O, 0, 1000 , 1000, &MemDC, 0, 0, SRCCOPY);

	HBITMAP hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_POPUP));
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&hBitmap);
	
	DrawImageBitBlt(dc.m_hDC, hBitmap, 0, 0);
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_POPUP1));
	DrawImageBitBlt(dc.m_hDC, hBitmap, 0, 0);
}
HBRUSH CAlarm_UIPopup::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	CBrush brush;

	switch (nCtlColor)
	{
		//case CTLCOLOR_LISTBOX:
		//case CTLCOLOR_BTN :
		//case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_DLG:
		{
			//hbr = (HBRUSH)m_brushDIg;
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB( 0, 0, 0));
			break ;
		}
	default:
		break;
		//////////////////////////////////////
	}
	return hbr;
}
void CAlarm_UIPopup::OnMouseMove(UINT nFlags, CPoint point)
{
	if(nFlags == MK_LBUTTON)
	{
		::ReleaseCapture();
		::SendMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CAlarm_UIPopup::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
		if(m_nCount == INT_MAX)
		{
			m_nCount = 0;
		}
		CDC *pDC = GetDC();
		HBITMAP hBitmap;
		m_nCount%2 == 0 ? hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_POPUP1)) : hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_POPUP2));
		DrawImageBitBlt(pDC->m_hDC, hBitmap, 0, 0);
		RECT rc = {214, 80, 488 , 143};
		if(m_szOutputMSG.GetLength() <57)
		{
			RECT rc2 = {214, 50, 488, 143};
			RECT rc3 = {214, 110, 488, 143};

			CString szTemp =_T("");
			CString szTemp2 =_T("");
			CString szTemp3 =_T("");
			szTemp  = m_szOutputMSG.Mid(0, 19);
			szTemp2 = m_szOutputMSG.Mid(19, 19);
			szTemp3 = m_szOutputMSG.Mid(38, 19);

			DrawTextEx(pDC->m_hDC, szTemp.GetBuffer(0), &rc2, TRUE, 25, BLACKNESS, DT_VCENTER | DT_CENTER);

			DrawTextEx(pDC->m_hDC, szTemp2.GetBuffer(0), &rc, TRUE, 25, BLACKNESS, DT_VCENTER | DT_CENTER);

			DrawTextEx(pDC->m_hDC, szTemp3.GetBuffer(0), &rc3, TRUE, 25, BLACKNESS, DT_VCENTER | DT_CENTER);
		}
		else if(m_szOutputMSG.GetLength() < 38)
		{
			RECT rc2 = {214, 110, 488, 143};
			CString szTemp = _T("");
			CString szTemp2 = _T("");
			szTemp = m_szOutputMSG.Mid(0, 19);
			szTemp2 = m_szOutputMSG.Mid(19, 19);
			DrawTextEx(pDC->m_hDC, szTemp.GetBuffer(0), &rc, TRUE, 25, BLACKNESS,DT_VCENTER | DT_CENTER) ;
			DrawTextEx(pDC->m_hDC, szTemp2.GetBuffer(0), &rc2, TRUE, 25, BLACKNESS ,DT_VCENTER | DT_CENTER) ;
		}
		////////////////////////////////////////
		else if(m_szOutputMSG.GetLength() < 19)
		{
			DrawTextEx(pDC->m_hDC, m_szOutputMSG.GetBuffer(0), &rc, TRUE, 25, BLACKNESS,DT_VCENTER|DT_CENTER);
		}
		ReleaseDC(pDC);
		m_nCount++;
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
void CAlarm_UIPopup::OnLButtonDown(UINT nFlags, CPoint point)
{
	Hook();
	Delete_UnHook();
	OnOK();
	CDialog::OnLButtonDown(nFlags, point);
}
void CAlarm_UIPopup::SetMessage(CString szMSG)
{
	m_szOutputMSG = szMSG;
}
void CAlarm_UIPopup::SetPosition(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
}
