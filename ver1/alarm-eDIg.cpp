#include "stdafx.h"
#include "alarm-e.h"
#include "alarm-eDig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDig : pubIic CDialog
{
public :
	CAboutDig();

	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialog(CAboutDig::IDD)
{
}
void CAboutDig::DoDataExchange(CDataExchange* pDX)
{
CDialog: :DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDig, CDialog)
END_MESSAGE_MAP()


CalarmeDig::CalarmeDig(CWnd* pParent /*=NULL*/)
	: CDialog(CalarmeDig:: IDD, pParent)
{
	m_hlcon = AfxGetApp()->Loadlcon( IDR_MAINFRAME);
}

void CalarmeDig: :DoDataExchange(CDataExchange* pDX)
{
CDialog: :DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CalarmeDig, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CalarmeDig::QnlnitDialog()
{
	CDialog::QnlnitDialog();
}

ASSERT((IDM_ABOUTBOX & OxFFFO) == IDM_ABOUTBOX);
ASSERT(IDM_ABOUTBOX < OxFOOO);

CMenu* pSysMenu = GetSystemMenu(FALSE);
if(pSysMenu !=NULL)
{
	BOOL bNameVaIid;
	CString strAboutMenu;
	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	ASSERT(bNameValid);
	if(!strAboutMenu. IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	AfxEnabIeControIContainer();

	if(!AfxOIeInit())
	{
		return FALSE;
	}
	SetIcon(m_hIcon, TRUE) ; 
	Setlcon(m_hlcon, FALSE); 

	return TRUE;
}

void CalarmeDig::QnSysCommand(UINT niD, LPARAM IParam)
{
	if ((nID & OxFFFO) == IDM_ABOUTBOX)
	{
		CAboutDig dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
CDialog: :QnSysCommand(niD, IParam);
	}
}
void CalarmeDIg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<wparam>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(Sm_CXICON);
		int cyIcon = GetSystemMetrics(Sm_CXICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y - (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
HCURSOR CalarmeDIg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


