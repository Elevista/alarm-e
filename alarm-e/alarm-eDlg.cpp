
// alarm-eDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CalarmeDlg 대화 상자




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


// CalarmeDlg 메시지 처리기

BOOL CalarmeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//테스트용
	//::SetAuthority(true);

	//자식 다이얼로그 위치 크기 일괄 지정부분
	int childX,childY,childW,childH;
	childX=30;	//x좌표
	childY=100;	//y좌표
	childW=630;	//넓이
	childH=400;	//높이
	//자식 다이얼로그 추가부분. 표시는 SwitchChildDlg함수로
	wordFilterDlg.Create(CWordFilterDlg::IDD,this);
	wordFilterDlg.MoveWindow(childX,childY,childW,childH);
	screenshotDlg.Create(CScreenshotDlg::IDD,this);
	screenshotDlg.MoveWindow(childX,childY,childW,childH);

	//버튼 이미지 적용부분
	m_btnX.LoadBitmaps(IDB_X_BTN,IDB_X_CLICK,IDB_X_BTN,IDB_X_BTN);
	m_btnX.SizeToContent();
	m_btnScreenShot.LoadBitmaps(IDB_SCREEN_SHOT_ON);
	m_btnScreenShot.SizeToContent();
	m_btnWordFilter.LoadBitmaps(IDB_WORD_FILTER_ON);
	m_btnWordFilter.SizeToContent();
	m_btnSiteBlock.LoadBitmaps(IDB_SITE_BLOCK_ON);
	m_btnSiteBlock.SizeToContent();


	SetBackgroundImage(IDB_BG,BACKGR_TOPLEFT);
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
		Ole 컨트롤 지원을 위해.		
		*/
	AfxEnableControlContainer(); 
	if(!AfxOleInit()) return false;
	
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	ShowWindow(SW_SHOW);
	PostMessage (WM_SHOWWINDOW,FALSE, SW_OTHERUNZOOM);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTray();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CalarmeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if(nID==SC_MINIMIZE||nID==SC_CLOSE)	//창닫기나 최소화 클릭시 숨기기
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CalarmeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	 nid.hWnd = m_hWnd; // 메인 윈도우 핸들
	 nid.uID = IDR_MAINFRAME;  // 아이콘 리소스 ID
	 nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // 플래그 설정
	 nid.uCallbackMessage = WM_TRAY_MSG; // 콜백메시지 설정
	 nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // 아이콘 로드
	 lstrcpy(nid.szTip, _T("alarm-e 작동중")); 
	 Shell_NotifyIcon(NIM_ADD, &nid);
	 SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
}


LRESULT CalarmeDlg::TrayMsg(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd=GetSafeHwnd();
	POINT pos;
	GetCursorPos(&pos);
	if(lParam==WM_LBUTTONDBLCLK){	//로그인된 상태에서 더블클릭시 창띄움
		if(::GetAuthority())ShowWindow(SW_SHOW);
	}
	else if(lParam==WM_RBUTTONUP){
		HMENU hMenu = CreatePopupMenu();
		if(::GetAuthority()){//로그인 된 상태면
			AppendMenu(hMenu, MF_STRING, WM_DLGSHOW, _T("설정"));
			AppendMenu(hMenu, MF_STRING, WM_LOGOUT, _T("관리자 로그아웃"));
			AppendMenu(hMenu, MF_STRING, WM_CLOSE, _T("프로그램 종료"));
		}
		else
			AppendMenu(hMenu, MF_STRING, WM_LOGIN, _T("관리자 로그인"));
		
		SetForegroundWindow();	//생성된 팝업메뉴 밖을 클릭할 때 팝업 닫기
		TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,pos.x, pos.y, 0, hWnd, NULL);
	}
	return 0;
}


void CalarmeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; // 메인 윈도우 핸들
	nid.uID = IDR_MAINFRAME;

	// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
	Shell_NotifyIcon(NIM_DELETE, &nid);
	CloseHandle(hMapFile);
}



BOOL CalarmeDlg::PreTranslateMessage(MSG* pMsg)
{
	//키눌린 메시지가 들어올때 esc이거나 return  값이면
	//걍 리턴 시켜준다.
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
	if(pMsg->message == WM_SYSKEYDOWN)	//알뜨에쁘뽀
    {
        if(pMsg->wParam == VK_F4)
            return TRUE;
    }
   return CDialogEx::PreTranslateMessage(pMsg);
}


void CalarmeDlg::Login(void)
{
	CLoginDlg dlg;	//로그인 다이얼로그 생성
	dlg.DoModal();	//로그인 창에서 로그인 성공하면
	if(GetAuthority())ShowWindow(SW_SHOW);//메인화면 보이기
}


void CalarmeDlg::Logout(void)
{
	ShowWindow(SW_HIDE);
	::SetAuthority(false);
	AfxMessageBox(_T("로그아웃 되었습니다"));
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int height=30;//타이틀바 두께
	int width=641;//창닫기 버튼을 제외한 타이틀바 넓이
	if(point.x<=width&&point.y<=height)
		SendMessage( WM_NCLBUTTONDOWN, HTCAPTION, 0 );	//타이틀바 클릭한걸로 속임

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CalarmeDlg::OnBnClickedWordFilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SwitchChildDlg(WORD_FILTER);
}


void CalarmeDlg::SwitchChildDlg(int num)
{
	//모든 자식 다이얼로그를 숨긴후에
	wordFilterDlg.ShowWindow(SW_HIDE);
	screenshotDlg.ShowWindow(SW_HIDE);
	
	m_btnScreenShot.LoadBitmaps(IDB_SCREEN_SHOT_OFF);
	m_btnWordFilter.LoadBitmaps(IDB_WORD_FILTER_OFF);
	m_btnSiteBlock.LoadBitmaps(IDB_SITE_BLOCK_OFF);
	m_btnScreenShot.SetFocus();
	m_btnWordFilter.SetFocus();
	m_btnSiteBlock.SetFocus();
	
	

	//선택한 다이얼로그만 표시.
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
