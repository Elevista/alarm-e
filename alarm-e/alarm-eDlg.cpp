
// alarm-eDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "alarm-e.h"
#include "alarm-eDlg.h"
#include "afxdialogex.h"
#include "ScreenShot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_TRAY_MSG WM_USER+1

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
}

BEGIN_MESSAGE_MAP(CalarmeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CalarmeDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_TRAY_MSG,TrayMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CalarmeDlg �޽��� ó����

BOOL CalarmeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	if(lParam == WM_LBUTTONDBLCLK)
		ShowWindow(SW_SHOW);
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
