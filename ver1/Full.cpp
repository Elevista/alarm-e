
#include "stdafx.h"
#include "FulI.h"
#include "Alarm_UIParent.h"
#include "Alarm-e.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __ FILE __ ;
#endif

CFulI::CFulI(CWnd* pParent /*=NULL*/)
	:CDialog(CFulI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFuII)
	//NOTE:the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFulI::CFulI(CString imgPath,CWnd* pParent /*=NULL*/)
	: CDialog(CFulI::IDD, pParent)
{
	this->imgPath = imgPath;
	//{{AFX_DATA_INIT(CFulI)
	// NOTE:the ClassWizard wiII add member initialization here
	//}}AFX_DATA_INIT
}

void CFulI::DoDataExchange(CDataExchange* pOX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFuII)
	//NOTE:the ClassWizard wiII add DDX and DDV calIs here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFulI, CDialog}
//{{AFX_MSG_MAP(CFul I)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//CFulI message handlers
void CFull::OnPaint()
{
	if(IsIconic())
	{
		/////////////////////////////////
		CPaintDC dc(this);// device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), O);

		// Center icon in cIientrec tangIe
		int cxlcon = GetSystemMetrics(SM_CXICON);
		int cylcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetCI ientRect(&rect);
		int x = (rect.Width() - cxlcon + 1) I 2;
		int y = (rect.Height() - cylcon + 1) I 2;

		// Draw the icon
		dc.Drawlcon(x, y, m_hlcon);
	}
	else
}
CPaintDC dc(this);
OnDraw(&dc);
CDialog::OnPaint();
}
}
void CFulI::QnDraw(CDC *pDC)
{
	UpdateData(TRUE);
	CAlarm_UIParent CAPTURE;
	CString str2;
	str2.Format(L"%s%s", theApp.m_captureDi rectory, imgPath);
	IIstr2 =((CCaptureDIg*)AfxGetMainWnd()) ->m_strjuso;
	CString str(str2);
	BSTR strBstr = str .AI locSysString();
	Image img(strBstr);
	Graphics g(pDC->m_hDC);
	g.Drawlmage(&img, 11, 15, 1245, 850);
	SysFreeString(strBstr);
}

void CFulI::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDiaIog::OnOK();
	CDialog::QnLButtonDown(nFiags, point);
}

BOOL CFulI::QnlnitDialog()
{
	CDialog::QnlnitDialog();


	int nWidth = GetScreenWidth();
	int nHeight = GetScreenHeight();

	MoveDigCenter(this->m_hWnd, nWidth - 100, nHeight - 100);

	return TRUE; // return TRUE unless you set the focus to a control
}