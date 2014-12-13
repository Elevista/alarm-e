// ScreenshotDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "ScreenshotDlg.h"
#include "afxdialogex.h"
#include "RegManager.h"
#include "ScreenShot.h"

// CScreenshotDlg ��ȭ �����Դϴ�.

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


// CScreenshotDlg �޽��� ó�����Դϴ�.


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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CScreenshotDlg::OnStnClickedPcSsPreview()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CScreenshotDlg::OnBnClickedApply()
{
	UpdateData(true);
	CRegManager::SetScreenShotVal(m_chkScreenShot.GetCheck());
	CRegManager::SetScreenShotFreq(_ttoi(m_editSsFrequency));
	ScreenShot::start();
	AfxMessageBox(_T("���� �Ǿ����ϴ�."));
	Sleep(1500);	//������ ���� ���� ��
}
