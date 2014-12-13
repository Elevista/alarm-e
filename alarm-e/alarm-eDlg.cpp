
// alarm-eDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "alarm-e.h"
#include "alarm-eDlg.h"
#include "afxdialogex.h"
#include "ScreenShot.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_TRAY_MSG WM_USER+1
#define WM_DLGSHOW WM_USER+2
#define WM_LOGIN WM_USER+3
#define WM_LOGOUT WM_USER+4
#define WM_CLOSEDLG WM_USER+5
#define WORD_FILTER 1
#define SCREEN_SHOT 2
#define SITE_BLOCK 3

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CalarmeDlg ��ȭ ����




CalarmeDlg::CalarmeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CalarmeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CalarmeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOSE, m_btnX);
	DDX_Control(pDX, IDC_CLOSE, m_btnX);
	DDX_Control(pDX, IDC_SCREEN_SHOT, m_btnScreenShot);
	DDX_Control(pDX, IDC_SITE_BLOCK, m_btnSiteBlock);
	DDX_Control(pDX, IDC_WORD_FILTER, m_btnWordFilter);
}

BEGIN_MESSAGE_MAP(CalarmeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CalarmeDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_TRAY_MSG,TrayMsg)
	ON_COMMAND(WM_LOGIN,Login)
	ON_COMMAND(WM_LOGOUT,Logout)
	ON_COMMAND(WM_DLGSHOW,ShowDlg)
	ON_COMMAND(WM_CLOSE,ColseDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CLOSE, &CalarmeDlg::OnBnClickedClose)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_WORD_FILTER, &CalarmeDlg::OnBnClickedWordFilter)
	ON_BN_CLICKED(IDC_SITE_BLOCK, &CalarmeDlg::OnBnClickedSiteBlock)
	ON_BN_CLICKED(IDC_SCREEN_SHOT, &CalarmeDlg::OnBnClickedScreenShot)
END_MESSAGE_MAP()


// CalarmeDlg �޽��� ó����

BOOL CalarmeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//�׽�Ʈ��
	//::SetAuthority(true);

	//�ڽ� ���̾�α� ��ġ ũ�� �ϰ� �����κ�
	int childX,childY,childW,childH;
	childX=30;	//x��ǥ
	childY=100;	//y��ǥ
	childW=630;	//����
	childH=400;	//����
	//�ڽ� ���̾�α� �߰��κ�. ǥ�ô� SwitchChildDlg�Լ���
	wordFilterDlg.Create(CWordFilterDlg::IDD,this);
	wordFilterDlg.MoveWindow(childX,childY,childW,childH);
	screenshotDlg.Create(CScreenshotDlg::IDD,this);
	screenshotDlg.MoveWindow(childX,childY,childW,childH);

	//��ư �̹��� ����κ�
	m_btnX.LoadBitmaps(IDB_X_BTN,IDB_X_CLICK,IDB_X_BTN,IDB_X_BTN);
	m_btnX.SizeToContent();
	m_btnScreenShot.LoadBitmaps(IDB_SCREEN_SHOT_ON);
	m_btnScreenShot.SizeToContent();
	m_btnWordFilter.LoadBitmaps(IDB_WORD_FILTER_ON);
	m_btnWordFilter.SizeToContent();
	m_btnSiteBlock.LoadBitmaps(IDB_SITE_BLOCK_ON);
	m_btnSiteBlock.SizeToContent();


	SetBackgroundImage(IDB_BG,BACKGR_TOPLEFT);
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		/*
		2014.11.30 
		Ole ��Ʈ�� ������ ����.		
		*/
	AfxEnableControlContainer(); 
	if(!AfxOleInit()) return false;
	
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	ShowWindow(SW_SHOW);
	PostMessage (WM_SHOWWINDOW,FALSE, SW_OTHERUNZOOM);
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTray();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CalarmeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if(nID==SC_MINIMIZE||nID==SC_CLOSE)	//â�ݱ⳪ �ּ�ȭ Ŭ���� �����
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CalarmeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CalarmeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CalarmeDlg::OnBnClickedButton1()
{
	AfxMessageBox(ScreenShot::capture());
	ScreenShot::getlastimgfile();
}


void CalarmeDlg::SetTray()
{
	 NOTIFYICONDATA  nid;
	 nid.cbSize = sizeof(nid);
	 nid.hWnd = m_hWnd; // ���� ������ �ڵ�
	 nid.uID = IDR_MAINFRAME;  // ������ ���ҽ� ID
	 nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // �÷��� ����
	 nid.uCallbackMessage = WM_TRAY_MSG; // �ݹ�޽��� ����
	 nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // ������ �ε�
	 lstrcpy(nid.szTip, _T("alarm-e �۵���")); 
	 Shell_NotifyIcon(NIM_ADD, &nid);
	 SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
}


LRESULT CalarmeDlg::TrayMsg(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd=GetSafeHwnd();
	POINT pos;
	GetCursorPos(&pos);
	if(lParam==WM_LBUTTONDBLCLK){	//�α��ε� ���¿��� ����Ŭ���� â���
		if(::GetAuthority())ShowWindow(SW_SHOW);
	}
	else if(lParam==WM_RBUTTONUP){
		HMENU hMenu = CreatePopupMenu();
		if(::GetAuthority()){//�α��� �� ���¸�
			AppendMenu(hMenu, MF_STRING, WM_DLGSHOW, _T("����"));
			AppendMenu(hMenu, MF_STRING, WM_LOGOUT, _T("������ �α׾ƿ�"));
			AppendMenu(hMenu, MF_STRING, WM_CLOSE, _T("���α׷� ����"));
		}
		else
			AppendMenu(hMenu, MF_STRING, WM_LOGIN, _T("������ �α���"));
		
		SetForegroundWindow();	//������ �˾��޴� ���� Ŭ���� �� �˾� �ݱ�
		TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,pos.x, pos.y, 0, hWnd, NULL);
	}
	return 0;
}


void CalarmeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; // ���� ������ �ڵ�
	nid.uID = IDR_MAINFRAME;

	// �۾� ǥ����(TaskBar)�� ���� ������ �������� �����Ѵ�.
	Shell_NotifyIcon(NIM_DELETE, &nid);
	CloseHandle(hMapFile);
}



BOOL CalarmeDlg::PreTranslateMessage(MSG* pMsg)
{
	//Ű���� �޽����� ���ö� esc�̰ų� return  ���̸�
	//�� ���� �����ش�.
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_ESCAPE:
			case VK_RETURN:
			case VK_CANCEL:
			return TRUE;
			default:
			break;
		}
	}
	if(pMsg->message == WM_SYSKEYDOWN)	//�˶߿��ڻ�
    {
        if(pMsg->wParam == VK_F4)
            return TRUE;
    }
   return CDialogEx::PreTranslateMessage(pMsg);
}


void CalarmeDlg::Login(void)
{
	CLoginDlg dlg;	//�α��� ���̾�α� ����
	dlg.DoModal();	//�α��� â���� �α��� �����ϸ�
	if(GetAuthority())ShowWindow(SW_SHOW);//����ȭ�� ���̱�
}


void CalarmeDlg::Logout(void)
{
	ShowWindow(SW_HIDE);
	::SetAuthority(false);
	AfxMessageBox(_T("�α׾ƿ� �Ǿ����ϴ�"));
}


void CalarmeDlg::ShowDlg(void)
{
	ShowWindow(SW_SHOW);
}


void CalarmeDlg::ColseDlg(void)
{
	CDialogEx::OnCancel();
}


void CalarmeDlg::OnBnClickedClose()
{
	ShowWindow(SW_HIDE);
}


void CalarmeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int height=30;//Ÿ��Ʋ�� �β�
	int width=641;//â�ݱ� ��ư�� ������ Ÿ��Ʋ�� ����
	if(point.x<=width&&point.y<=height)
		SendMessage( WM_NCLBUTTONDOWN, HTCAPTION, 0 );	//Ÿ��Ʋ�� Ŭ���Ѱɷ� ����

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CalarmeDlg::OnBnClickedWordFilter()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SwitchChildDlg(WORD_FILTER);
}


void CalarmeDlg::SwitchChildDlg(int num)
{
	//��� �ڽ� ���̾�α׸� �����Ŀ�
	wordFilterDlg.ShowWindow(SW_HIDE);
	screenshotDlg.ShowWindow(SW_HIDE);
	
	m_btnScreenShot.LoadBitmaps(IDB_SCREEN_SHOT_OFF);
	m_btnWordFilter.LoadBitmaps(IDB_WORD_FILTER_OFF);
	m_btnSiteBlock.LoadBitmaps(IDB_SITE_BLOCK_OFF);
	m_btnScreenShot.SetFocus();
	m_btnWordFilter.SetFocus();
	m_btnSiteBlock.SetFocus();
	
	

	//������ ���̾�α׸� ǥ��.
	switch(num){
		case WORD_FILTER:{
			wordFilterDlg.ShowWindow(SW_SHOW);
			m_btnWordFilter.LoadBitmaps(IDB_WORD_FILTER_ON);
			m_btnWordFilter.SetFocus();
			break;}
		case SCREEN_SHOT:{
			screenshotDlg.ShowWindow(SW_SHOW);
			m_btnScreenShot.LoadBitmaps(IDB_SCREEN_SHOT_ON);
			m_btnScreenShot.SetFocus();
			break;}
		case SITE_BLOCK:{
			m_btnSiteBlock.LoadBitmaps(IDB_SITE_BLOCK_ON);
			m_btnSiteBlock.SetFocus();
			break;}
	}
}


void CalarmeDlg::OnBnClickedSiteBlock()
{
	SwitchChildDlg(SITE_BLOCK);
	ShellExecute(NULL, "open", "SimpleFireWall.exe", NULL, NULL, SW_SHOW); 
}


void CalarmeDlg::OnBnClickedScreenShot()
{
	SwitchChildDlg(SCREEN_SHOT);
}
