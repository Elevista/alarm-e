// ScreenshotDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "ScreenshotDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CScreenshotDlg, CDialogEx)
	ON_STN_CLICKED(IDC_PC_SS_PREVIEW, &CScreenshotDlg::OnStnClickedPcSsPreview)
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CScreenshotDlg::OnStnClickedPcSsPreview()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
