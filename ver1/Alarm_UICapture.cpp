#include "stdafx.h"
#include "Alarm-e.h"
#include "Alarm_UICapture.h"
#include "JKRegistry.h"

// Alarm_UICapture 

IMPLEMENT_DYNAMIC(Alarm_UICapture, CDialog)

	Alarm_UICapture::Alarm_UICapture(CWnd* pParent /*=NULL*/)
	:CDialog(Alarm_UICapture::IDD, pParent)
{
	m_nCaptureLevel = O;
}

Alarm_UICapture::~Alarm_UICapture()
{
}
void Alarm_UICapture::DoDataExchange(CDataExchange* pDX)
{
	CDlalog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB01, m_comboMinute);
	DDX_Control(pDX, IDC_CHECK1, m_chHigh);
	DDX_Control(pDX, IDC_CHECK2, m_chMiddle);
	DDX_Control(pDX, IDC_CHECK3, m_chLow);
}

BEGIN_MESSAGE_MAP(Alarm_UICapture, CDialog)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED( IDC_BITMAP_PARENT3_CAPTURE_OK, &Aiarm_UICapture::QnBnCI ickedBtnOK)
	ON_BN_CLICKED( IDC_BITMAP_PARENT3_CAPTURE_CANCEL, &Aiarm_UICapture::OnBnCI ickedBtnCancel)
	ON_BN_CLICKED( IDC_CHECK1, &Alarm_UICapture::OnBnCIickedCheck1)
	ON_BN_CLICKED( IDC_CHECK2, &Alarm_UICapture::OnBnCIickedCheck2)
	ON_BN_CLICKED( IDC_CHECK3, &Alarm_UICapture::OnBnCIickedCheck3)
END_MESSAGE_MAP()


//Ala rm_UICapture 
BOOL Alarm_UICapture: :QnlnitDialog()
{

	CDialog::OnlnitDialog();
	MoveDIgCenter(this->m_hWnd , 306, 230);
	SetBitmapButton();
	SetControlPosition();
	SetComponentData();
	GetCaptureLevel();
	return TRUE; // return TRUE unless you set the focus to a control
}

void Alarm_UICapture::QnDestroy()

	//////////////////////////////
{
	CDialog::onDestroy();

	if(m_ibtnCancel){
		m_ibtnCancei->DestroyWindow();
		delete m_ibtnCancel;
	}

	if(m_ibtnOK){
		m_ibtnOK->DestroyWindow();
		delete m_ibtnOK ;
	}
}
void Alarm_UICapture::onPaint()
{
	CPaintDC dc(this); 
	HBITMAP hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_CAPTURE));
	DrawlmageBitBit(dc.m_hDC,hBitmap,O,O);
}

void Alarm_UICapture::SetBitmapButton()
{
	m_ibtnCancel = new CBitmapButton();
	m_ibtnCancei->Create(NULL, WS_CHILD|WS_VISIBLE | BS_OWNERDRAW, CRect(130,156,1 ,1), this,
		IDC_BITMAP_PARENT3_CAPTURE_OK);
	m_ibtnCancei->LoadBitmaps(IDB_BITMAP_CANCEL1, IDB_BITMAP_CANCEL2, IDB_BITMAP_CANCEL1,
		IDB_BITMAP_CANCEL1);


	m_ibtnOK =new CBitmapButton();
	m_ibtnOK->Create(NULL, WS_CHILD|WS_VISIBLE I BS_OWNERDRAW, CRect(210,156,1 ,1), this,
		IDC_BITMAP_PARENT3_CAPTURE_OK);
	m_ibtnOK->LoadBitmaps( IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE2, IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE1);

	m_ibtnCancei->SizeToContent();
	m_ibtnOK->SizeToContent();
}
void Alarm_UICapture::SetControiPosition()
{
	m_comboMinute	.MoveWindow(144, 72, 39, 15, TRUE);
	m_chHigh		.MoveWindow(86, 109, 13, 13, TRUE);
	m_chMiddle		.MoveWindow(125, 109, 13, 13, TRUE) ;
	m_chlow			.MoveWindow(165, 109, 13, 13, TRUE);
}

void Alarm_UICapture::SetComponentData()
{
	CString szMinute = L"";
	for(int i=5; i<= 60; i+= 5)
	{
		if(i == 5) szMinute.Format(L "0%d", i);
		/////////////////
		else szMinute.Format(L"%d", i);
		m_comboMinute . AddString(szMinute);
	}

	m_chHigh	.SetWindowText(L"");
	m_chMiddle	.SetWindowText(L"");
	m_chlow		.SetWindowText(L"");
}

void Alarm_UICapture::GetCapturelevel()
{
	JKRegistry reg;
	reg.SetHKey(HKEY_CURRENT_USER);
	reg.SetPath(TEXT("Software \\AlarmE\\Parent"));
	reg.SetName(TEXT("LevelSetting"));

	int m_nCaptureLevel = reg.Getlnteger();

	//SetlmgBtnFocus();
}

void Alarm_UICapture::SetlmgBtnFocus()
{

}
void Alarm_UICapture::OnBnCIickedBtnHigh()
{ 
	m_nCapturelevel = HIGH;
	SetCheckMode();
}

void Alarm_UICapture::OnBnCIickedBtnMiddle()
{
	m_nCaptureLevel = MIDDLE;
	SetCheckMode();
}

void Alarm_UICapture::OnBnCIickedBtnLow()
{
	m_nCaptureLevel = LOW;
	SetCheckMode();
}

void Alarm_UICapture::SetCheckMode()
{
	m_nCapturelevel == HIGH		? m_chHigh.SetCheck(1)	:m_chHigh.SetCheck(O);
	m_nCaptureLevel == MIDDLE	? m_chMiddle.SetCheck(1):m_chMiddle.SetCheck(O);
	m_nCapturelevel == LOW		? m_chLow.SetCheck(1)	:m_chLow.SetCheck(O);
}

void Alarm_UICapture::OnBnCIickedBtnOK()
{
	JKRegistry reg;
	reg.SetHKey(HKEY_CURRENT_USER) ;
	reg.SetPath(TEXT("Software\\AlarmE\\Parent\\Capture")) ;
	reg.SetName(TEXT("LevelSetting"));

	reg.Setlnteger((DWORD)m_nCaptureLevel);

	CString szMinute = L"";
	m_comboMinute.GetWindowText(szMinute);

	int nTime = 0;
	nTime = _ttoi(szMinute);

	reg.SetName(TEXT("CaptureText"));

	reg.SetInteger((DWORD)NTime);

	OnOK();
}

void Alarm_UICapture::OnBnClickedBtnCancel()
{
	OnOK();
}
void Alarm_UICapture::OnBnClickedCheck1()
{
	OnBnClickedBtnHigh();
}
void Alarm_UICapture::OnBnClickedCheck2()
{
	OnBnClickedBtnMiddle();
}
void Alarm_UICapture::OnBnClickedCheck3()
{
	OnBnClickedBtnLow();
}

