// ScreenshotDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "ScreenshotDlg.h"
#include "afxdialogex.h"
#include "RegManager.h"
#include "ScreenShot.h"
#include "DBconsumer.h"
#include "FullScreenDlg.h"
#include <Gdiplus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;

// CScreenshotDlg ��ȭ �����Դϴ�.
	
IMPLEMENT_DYNAMIC(CScreenshotDlg, CDialogEx)

CScreenshotDlg::CScreenshotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenshotDlg::IDD, pParent)
	, index(-1)
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
	DDX_Control(pDX, IDC_LIST_SCREENSHOT, m_listScreenShot);
	DDX_Control(pDX, IDC_PC_SS_PREVIEW, m_pcPreview);
}


BEGIN_MESSAGE_MAP(CScreenshotDlg, CDialogEx)
	ON_STN_CLICKED(IDC_PC_SS_PREVIEW, &CScreenshotDlg::OnStnClickedPcSsPreview)
	ON_BN_CLICKED(IDC_APPLY, &CScreenshotDlg::OnBnClickedApply)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SCREENSHOT, &CScreenshotDlg::OnLvnItemchangedListScreenshot)
	ON_BN_CLICKED(IDC_ZOOM, &CScreenshotDlg::OnBnClickedZoom)
	ON_BN_CLICKED(IDC_DELETE, &CScreenshotDlg::OnBnClickedDelete)
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
	m_listScreenShot.InsertColumn(0, _T("�ð�"), LVCFMT_LEFT, 250, -1);

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


void CScreenshotDlg::Refresh(void)
{
	if(imgDB.IsOpen()){imgDB.Close();imgDB.Open();}
	else{imgDB.Open();}
	index=-1;
	m_listScreenShot.DeleteAllItems();
	CString strTime;
	CTime time;
	if(imgDB.IsEOF())return;
	imgDB.MoveFirst();
	while(!imgDB.IsEOF()){
		time=imgDB.m_datetime;
		strTime.Format(_T("%d�� %d�� %d��, %d�� %d�� %d��"),time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		m_listScreenShot.InsertItem(0,strTime);
		imgDB.MoveNext();
	}
}


void CScreenshotDlg::OnLvnItemchangedListScreenshot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	index=pNMLV->iItem;	//���� ���� �������� �ε����� ����
	imgDB.MoveLast();
	imgDB.Move(-index); //�ش� �ε����� �ش��ϴ� ���ڵ��
	if(!imgDB.IsEOF()&&!imgDB.IsBOF()){
		IStream* pStream = NULL;
		CreateStreamOnHGlobal(imgDB.m_image.m_hData,FALSE,&pStream);
		CImage image;
		image.Load(pStream);	//�̹����� �ҷ��ͼ�
		Bitmap bitmap(image.Detach(),NULL);	//Bitmap�� ����
		
		int nWidth=340;	//���� ����
		int nHeight=(int)(bitmap.GetHeight()*nWidth/bitmap.GetWidth()); //���̴� �������缭
		
		
		//���ο� ��Ʈ���� �����ϰ�
		Gdiplus::Bitmap* newBitmap = new Gdiplus::Bitmap(nWidth, nHeight, bitmap.GetPixelFormat());
		Gdiplus::Graphics graphics(newBitmap);	//�ű⿡ �׷����� �����
		graphics.DrawImage(&bitmap, 0, 0, nWidth, nHeight);	//�׷��ȿ� ���� �׸��� �׸�.

		
		HBITMAP hBitmap;
		newBitmap->GetHBITMAP(Color(0,0,0),&hBitmap);	//���� ����� �׸� ��Ʈ�ʿ��� HBITMAP����
		bitmap.GetHBITMAP(Color(0,0,0),&zoomDlg.hBitmap);	//Ǯ��ũ������ �׳� ���� ��Ʈ�� ����
		m_pcPreview.SetBitmap(hBitmap);	//�����Ͽ��� ���θ��� ��Ʈ�� �׸�.
	}
	*pResult = 0;
}



void CScreenshotDlg::OnBnClickedZoom()
{
	if(index!=-1)	//������ ��Ұ� ������
		zoomDlg.DoModal();
}


void CScreenshotDlg::OnBnClickedDelete()
{
	if(index==-1) return;
	if(imgDB.IsEOF())return;
	imgDB.MoveLast();
	imgDB.Move(-index);
	if(!imgDB.IsEOF()){
		imgDB.Delete();
		Refresh();
	}
}

