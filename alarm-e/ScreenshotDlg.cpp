// ScreenshotDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "ScreenshotDlg.h"
#include "afxdialogex.h"
#include "RegManager.h"
#include "ScreenShot.h"

// CScreenshotDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScreenshotDlg, CDialogEx)

CScreenshotDlg::CScreenshotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenshotDlg::IDD, pParent)
{
	SetBackgroundColor(RGB(255,255,255));
	m_editSsFrequency = _T("");
}

CScreenshotDlg::~CScreenshotDlg()
{
}

void CScreenshotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SS_FREQUENCY, m_editSsFrequency);
	DDX_Control(pDX, IDC_SPIN_SS_FREQUENCY, m_spinSsFrequency);
	DDX_Control(pDX, IDC_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_ZOOM, m_btnZoom);
	DDX_Control(pDX, IDC_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_CHK_SCREENSHOT, m_chkScreenShot);
}


BEGIN_MESSAGE_MAP(CScreenshotDlg, CDialogEx)
	ON_STN_CLICKED(IDC_PC_SS_PREVIEW, &CScreenshotDlg::OnStnClickedPcSsPreview)
	ON_BN_CLICKED(IDC_APPLY, &CScreenshotDlg::OnBnClickedApply)
END_MESSAGE_MAP()


// CScreenshotDlg 메시지 처리기입니다.


BOOL CScreenshotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_spinSsFrequency.SetRange(30,1000);
	m_btnApply.LoadBitmaps(IDB_APPLY);
	m_btnApply.SizeToContent();
	m_btnZoom.LoadBitmaps(IDB_ZOOM);
	m_btnZoom.SizeToContent();
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	m_chkScreenShot.SetCheck(CRegManager::GetScreenShotVal());
	CString val;
	val.Format(_T("%d"),CRegManager::GetScreenShotFreq());
	m_editSsFrequency=val;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScreenshotDlg::OnStnClickedPcSsPreview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CScreenshotDlg::OnBnClickedApply()
{
	UpdateData(true);
	CRegManager::SetScreenShotVal(m_chkScreenShot.GetCheck());
	CRegManager::SetScreenShotFreq(_ttoi(m_editSsFrequency));
	ScreenShot::start();
	AfxMessageBox(_T("적용 되었습니다."));
	Sleep(1500);	//쓰레드 종료 검출 텀
}
