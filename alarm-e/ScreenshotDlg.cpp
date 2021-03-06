// ScreenshotDlg.cpp : 구현 파일입니다.
// 스크린샷 다이얼로그

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

// CScreenshotDlg 대화 상자입니다.
	
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
	DDX_Control(pDX, IDC_WEB_LINK, m_btnWebLink);
}


BEGIN_MESSAGE_MAP(CScreenshotDlg, CDialogEx)
	ON_STN_CLICKED(IDC_PC_SS_PREVIEW, &CScreenshotDlg::OnStnClickedPcSsPreview)
	ON_BN_CLICKED(IDC_APPLY, &CScreenshotDlg::OnBnClickedApply)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SCREENSHOT, &CScreenshotDlg::OnLvnItemchangedListScreenshot)
	ON_BN_CLICKED(IDC_ZOOM, &CScreenshotDlg::OnBnClickedZoom)
	ON_BN_CLICKED(IDC_DELETE, &CScreenshotDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_WEB_LINK, &CScreenshotDlg::OnBnClickedWebLink)
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
	m_btnWebLink.LoadBitmaps(IDB_WEB_LINK);
	m_btnWebLink.SizeToContent();
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	m_chkScreenShot.SetCheck(CRegManager::GetScreenShotVal());
	CString val;
	val.Format(_T("%d"),CRegManager::GetScreenShotFreq());
	m_editSsFrequency=val;
	UpdateData(false);
	m_listScreenShot.InsertColumn(0, _T("시간"), LVCFMT_LEFT, 250, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScreenshotDlg::OnStnClickedPcSsPreview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CScreenshotDlg::OnBnClickedApply()	//적용 버튼 클릭시
{
	UpdateData(true);
	CRegManager::SetScreenShotVal(m_chkScreenShot.GetCheck());	//레지에 설정값 저장
	CRegManager::SetScreenShotFreq(_ttoi(m_editSsFrequency));	//레지에 설정값 저장
	ScreenShot::start();	//쓰레드 생성
	AfxMessageBox(_T("적용 되었습니다."));
	Sleep(1500);	//기존 돌던 쓰레드 종료 검출 텀
}


void CScreenshotDlg::Refresh(void)	//리스트 갱신
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
		strTime.Format(_T("%d년 %d월 %d일, %d시 %d분 %d초"),time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		m_listScreenShot.InsertItem(0,strTime);
		imgDB.MoveNext();
	}
}


void CScreenshotDlg::OnLvnItemchangedListScreenshot(NMHDR *pNMHDR, LRESULT *pResult)
{	//리스트 아이템 선택시
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	index=pNMLV->iItem;	//현재 선택 아이템의 인덱스를 저장
	imgDB.MoveLast();
	imgDB.Move(-index); //해당 인덱스에 해당하는 레코드로
	if(!imgDB.IsEOF()&&!imgDB.IsBOF()){
		IStream* pStream = NULL;
		CreateStreamOnHGlobal(imgDB.m_image.m_hData,FALSE,&pStream);//DB의 데이터를 메모리로 로드 하기 위한 스트림 생성
		CImage image;
		image.Load(pStream);	//이미지를 불러와서
		Bitmap bitmap(image.Detach(),NULL);	//Bitmap을 생성
		
		int nWidth=340;	//가로는 고정 크기
		int nHeight=(int)(bitmap.GetHeight()*nWidth/bitmap.GetWidth()); //높이는 비율맞춰서
		
		
		//새로운 비트맵을 생성하고
		Gdiplus::Bitmap* newBitmap = new Gdiplus::Bitmap(nWidth, nHeight, bitmap.GetPixelFormat());
		Gdiplus::Graphics graphics(newBitmap);	//거기에 그래픽을 만들고
		graphics.DrawImage(&bitmap, 0, 0, nWidth, nHeight);	//그래픽에 원래 그림을 새로운 크기로 그림.

		
		HBITMAP hBitmap;
		newBitmap->GetHBITMAP(Color(0,0,0),&hBitmap);	//새로 만들어 그린 비트맵에서 HBITMAP얻음
		bitmap.GetHBITMAP(Color(0,0,0),&zoomDlg.hBitmap);	//풀스크린에는 그냥 원래 비트맵 전달
		m_pcPreview.SetBitmap(hBitmap);	//섬네일에는 새로만든 비트맵 그림.
	}
	*pResult = 0;
}



void CScreenshotDlg::OnBnClickedZoom()
{
	if(index!=-1)	//선택한 요소가 있으면
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



void CScreenshotDlg::OnBnClickedWebLink()	//버튼 클릭시 웹페이지 열기
{
	ShellExecute(NULL, "open", "http://alarme-sunnyholic.rhcloud.com", NULL, NULL, SW_SHOW); 
}


BOOL CScreenshotDlg::PreTranslateMessage(MSG* pMsg)	//종료 막기 위한 부분
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
