#include "stdafx.h"
#include "Alarm-e.h"
#include "Alarm_UIChild.h"
#include "Alarm_UILogin.h"
#include "JKRegistry.h"
#include <mmsystem.h>

IMPLEMENT_DYNAMIC(CAlarm_UIChild, CDialog)
	CAlarm_UIChild::CAlarm_UIChild(CWnd* pParent /*=NULL*/)
	:CDialog(CAlarm_UIChild::IDD, pParent)
{
	m_nMode = O;
	m_blsEditModeEdu =FALSE;
	m_nChild5MsgMode = WILLSEND ;

	m_nDeletelndex2 = O;
	m_nDeletelndex5 = O;

	m_lsUpdateModeEdu =FALSE;
	m_popUPDig = NULL ;
}

CAlarm_UIChild::~CAlarm_UIChild()
{
}
void CAlarm_UIChild::DoDataExchange(CDataExchange* pOX)
{
	CDialog::DoDataExchange(pDX);
}

//EDUURL MODE START
DDX_Control(pDX, IDC_EDIT37, m_editEduTiTie) ;
DDX_Control(pDX, IDC_EDIT38, m_editEduURL) ;
DDX_Control(pDX, IDC_COMB01, m_comboEduTimeHour1) ;
DDX_Control(pDX, IDC_COMB04, m_comboEduTimeMinute1);
DDX_Control(pDX, IDC_CHECK1, m_chMon);
DDX_Control(pDX, IDC_CHECK2, m_chTUE);
DDX_Control(pDX, IDC_CHECK3, m_chWED);
DDX_Control(pDX, IDC_CHECK4, m_chTHU) ;
DDX_Control(pDX, IDC_CHECK5, m_chFRI);
DDX_Control(pDX, IDC_CHECK6, m_chSAT) ;
DDX_Control(pDX, IDC_CHECK7, m_chSUN);
//EDUURL MODE END

DDX_Control(pDX, IDC_EDIT44, m_editMSGMEssage) ;
DDX_Control(pDX, IDC_COMB07, m_comboMSGTimeHour);
DDX_Control(pDX, IDC_COMB08, m_comboMSGTimeMinute);
DDX_Control(pDX, IDC_CHECK8, m_chReSend);
DDX_Control(pDX, IDC_EDIT50, m_editMSG);
}
BEGIN_MESSAGE_MAP(CAiarm_UIChi ld, CDialog)
	ON_WM_DESTROY()
	//////////////////////
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BITMAP_CHILD2, &CAiarm_UIChild: :QnBnCIickedBtnEduURL)
	ON_BN_CLICKED(IDC_BITMAP_CHILD5, &CAiarm_UIChild: :QnBnCIickedBtnMessage)

	ON_BN_CLICKED(IDC_BITMAP_CHILD2_CANCEL, &CAiarm_UIChild::QnBnCIickedBtnC2Cancel)
	ON_BN_CLICKED(IDC_BITMAP_CHILD2_REPAIR, &CAiarm_UIChild::QnBnCIickedBtnC2Repair)
	ON_BN_CLICKED(IDC_BITMAP_CHILD2_SAVE, &CAiarm_UIChild::QnBnCIickedBtnC2Save)
	ON_BN_CLICKED(IDC_BITMAP_CHILD5_SAVE, &CAiarm_UIChild ::QnBnCIickedBtnC5Save)

	ON_BN_CLICKED(IDC_BITMAP_CHILD5_WILLSEND,&CAiarm_UIChild::QnBnCIickedBtnC5WiIlSend)
	ON_BN_CLICKED(IDC_BITMAP_CHILD5_SENDED,&CAiarm_UIChild::QnBnCIickedBtnC5Sended)
	ON_BN_CLICKED(IDC_BITMAP_CHILD5_RECIEVE,&CAiarm_UIChild::QnBnCIickedBtnC5Recieve)
	ON_BN_CLICKED(IDC_BITMAP_CHILD5_DELETE,&CAiarm_UIChild::QnBnCIickedBtnC5Delete)

	ON_MESSAGE(WM_BANWORD, &CAiarm_UIChi ld: :QnBanWord)
	ON_MESSAGE(UM_TRAYICON, &CAiarm_UIChi ld: :QnTraylcon)

	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL3, &CAiarm_UIChild::QnNMDblclkL stEdu)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL4, &CAiarm_UIChild::QnNMDblclkL stWillSend)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL5, &CAiarm_UIChild::QnNMDblclkL stSended)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL6, &CAiarm_UIChild::QnNMDblclkL stRecieve)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL4, &CAiarm_UIChild::QnNMKiIlfocuslistEdu)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL4, &CAiarm_UIChild::QnNMKilIfocuslistWillSend)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL5, &CAiarm_UIChild::QnNMKilIfocuslistSended)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL6, &CAiarm_UIChild::QnNMKilIfocuslistRecieve)

	ON_WM_TIMER()

	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

BOOL CAiarm_UIChild::QnlnitDialog()
{
	CDialog::OnlnitDialog();

	MoveDigCenter(m_hWnd, 646, 630); //640, 600

	SetlmageButtonMode();
	SetComboBoxContents();

	SetlistCtrlEDU();
	SetPositionEDU();
	SetChecklabelEDU();

	SetlistCtrlMessage();
	SetPositionMessage();
	SetChecklabelMessage();

	SetModeVisible(FALSE, CHILD_MESSAGE);

	SelectDBFromEcampusURL();
	SelectDBFromMSGToParent();
	theApp.LoadBanWordDB();
	theApp.LoadBanURLDB();

	theApp.LoadEcampuslist();

	m_editMSG.EnableWindow(FALSE);
	return TRUE;

	/////////////////////////
}
void CAiarm_UIChild::QnPaint()
{
	CPaintDC dc(this); // device context for paint ing
	OnDraw(dc.m_hDC);
}


void CAlarm_UIChild::QnDraw(HDC hDC)
{
	RECT winRect;
	GetCIientRect(&winRect) ;
	HDC MemDC = ::CreateCompatibleDC(hDC);
	HBITMAP MyBMP = CreateCompatibleBitmap(hDC, winRect.right, winRect . bottom);
	HBITMAP OldBMP = (HBITMAP)SelectObject(MemDC, MyBMP);

	DrawBackgroundlmage(MemDC);

	BitBit(hDC, 0, 0, winRect.right, winRect.bottom, MemDC, 0, 0, SRCCOPY);
	DeleteObject(OidBMP);
	DeleteObject(MyBMP);
	DeleteDC(MemDC) ;
}
BOOL CAlarm_UIChild::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:

		switch(pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;

		case VK_ESCAPE :
			return TRUE;
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CAlarm_UIChild::DrawBackgroundlmage(HDC hDC)
{
	HBITMAP hBitmap;
	switch(m_nMode)
	{
	case CHILD_EDUURL:
		hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CHILD2));
		break;


	case CHILD_MESSAGE:
		hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_CHILD5));
		break;
	}
	DrawlmageBitBit(hDC,hBitmap,O,O);


	void CAlarm_UIChild::SetComboBoxContents()
	{
		CString szHour = L"" ;
		CString szMinute = L"";

		for(int i=0; i<24; i++)
		{
			if(i<10) szHour.Format(L "O%d", i);
			else szHour.Format(L "%d", i);

			m_comboEduTimeHour1.AddString(szHour);
			m_comboMSGTimeHour.AddString(szHour);
		}

		for (int i=0; i<60; i++)
		{
			if(i<10) szMinute.Format(L "O%d", i) ;
			else szMinute.Format(L"%d", i);

			m_comboEduTimeMinute1.AddString(szMinute);
			m_comboMSGTimeMinute.AddString(szMinute);
		}
		CString szlnit = L"";
		m_comboEduTimeHour1.SetCurSel(O);
		m_comboMSGTimeHour.SetCurSel(O);
		m_comboEduTimeMinute1.SetCurSel(O);
		m_comboMSGTimeMinute.SetCurSel(O);
	}


	void CAlarm_UIChild::SetlmageButtonMode()
	{

		m_ibtnEduURL =new CBitmapButton();
		m_ibtnEduURL->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW; CRect(10, 10, 116,64), this, 
			IDC_BITMAP_CHILD2);
		m_ibtnEduURL->LoadBitmaps( IDB_BITMAP_CMENU2A, IDB_BITMAP_CMENU2B, IDB_BITMAP_CMENU2C, 
			IDB_BITMAP_CMENU1A);

		m_ibtnMessage =new CBitmapButton();
		m_ibtnMessage->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(136,10,116,64), this, 
			IDC_BITMAP_CHILD5);
		m_ibtnMessage->LoadB itmaps( IDB_BITMAP_CMENU5A, IDB_BITMAP_CMENU5B, IDB_BITMAP_CMENU5C, 
			IDB_BITMAP_CMENU1A);


		m_ibtn2_save =new CBitmapButton();
		m_ibtn2_save->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526,306,116,64), this,
			IDC_BITMAP_CHILD2_SAVE);

		m_ibtn2_save->LoadBitmaps(IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE2, IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE1);

		m_ibtn2_cancel = new CBitmapButton();
		m_ibtn2_cancei->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(426,306,116,64), this, 
			IDC_BITMAP_CHILD2_CANCEL);
		m_ibtn2_cancei->LoadBitmaps( IDB_BITMAP_CANCEL1, IDB_BITMAP_CANCEL2, IDB_BITMAP_CANCEL1, 
			IDB_BITMAP_CANCEL1);

		m_ibtn2_repair = new CBitmapButton();
		m_ibtn2_repair->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(526,306,116,64), this, 
			IDC_BITMAP_CHILD2_REPAIR) ;
		m_ibtn2_repair->LoadBitmaps( IDB_BITMAP_REPAIR1, IDB_BITMAP_REPAIR2, IDB_BITMAP_REPAIR1 , 
			IDB_BITMAP_REPAIR1);

		m_ibtn2_delete = new CBitmapButton();
		m_ibtn2_delete->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(326,306,116,64), this, 
			IDC_BITMAP_CHILD2_DELETE);
		m_ ibtn2_delete->LoadBitmaps( IDB_BITMAP_DELETE1 , IDB_BITMAP_DELETE2, IDB_BITMAP_DELETE1, 
			IDB_BITMAP_DELETE2) ;


		m_ibtn5_save = new CBitmapButton();
		m_ibtn5_save->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526 ,266,116,64), this , 
			IDC_BITMAP_CHILD5_SAVE);
		m_ibtn5_save->LoadBitmaps( IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE2 , IDB_BITMAP_SAVE1, IDB_BITMAP_SAVE1)

			m_ibtn5_delete = new CBitmapButton();
		m_ ibtn5_delete->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(526,560,116,64), this , 
			IDC_BITMAP_CHILD5_DELETE) ;
		m_ibtn5_delete->LoadBitmaps( IDB_BITMAP_DELETE1, IDB_BITMAP_DELETE2 , IDB_BITMAP_DELETE1, 
			IDB_BITMAP_DELETE2) ;

		m_ibtn5_willSend = new CBitmapButton();
		m_ibtn5_willSend ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(38 , 317,95 ,50), this ,
			IDC_BITMAP_CHILD5_WILLSEND);
		m_ibtn5_willSend ->LoadBitmaps( IDB_BITMAP_WILLSENDA_, IDB_BITMAP_WILLSENDB_, 
			IDB_BITMAP_WILLSENDB_ , IDB_BITMAP_WILLSENDB_) ;

		m_ibtn5_sended = new CBitmapButton() ;
		m_ibtn5_sended ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(132,317 , 95 , 50), this 
			, IDC_BITMAP_CHILD5_SENDED) ;
		m_ibtn5_sended ->LoadBitmaps( IDB_BITMAP_SENDEDA_, IDB_BITMAP_SENDEDB_, IDB_BITMAP_SENDEDB_ , 
			IDB_BITMAP_SENDEDB_);

		m_ibtn5_recieved = new CBitmapButton() ;
		m_ibtn5_recieved ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(226 ,317 , 95 ,50) , this
			, IDC_BITMAP_CHILD5_RECIEVE) ;
		m_ibtn5_recieved ->LoadBitmaps( IDB_BITMAP_RECEIVEA_ , 	IDB_BITMAP_RECEIVEB_ , IDB_BITMAP_RECEIVEB_,
			IDB_BITMAP_RECEIVEB_) ;

		m_ibtnEduURL	->SizeToContent();
		m_ibtnMessage	->SizeToContent();

		m_ibtn2_save	->SizeToContent();
		m_ibtn2_cancel	->SizeToContent();
		m_ibtn2_repair	->SizeToContent();
		m_ibtn2_delete	->SizeToContent();

		m_ibtn5_save		->SizeToContent();
		m_ibtn5_delete		->SizeToContent();
		m_ibtn5_willSend	->SizeToContent();
		m_ibtn5_sended		->SizeToContent();
		m_ibtn5_recieved	->SizeToContent();

	}

	void CAlarm_UIChild::QnBnCIickedBtnEduURL()
	{
		if(m_nMode != CHILD_EDUURL)
		{
			SetModeVisible(FALSE);
			m_nMode = CHILD_EDUURL;
			SetModeVisible(TRUE);
			m_ibtn2_delete->ShowWindow(SW_HIDE);
			lnitEduComponent();
			lnval idate(FALSE);
		}
	}
	void CAlarm_UIChild::QnBnCIickedBtnMessage()
	{
		if(m_nMode != CHILD_MESSAGE)
		{
			SetModeVisible(FALSE);
			m_nMode = CHILD_MESSAGE;
			m_ibtn5_delete->EnableWindow(FALSE);
			SetModeVisible(TRUE);
			SetMSGBtnVisible();
			lnval idate(FALSE);
		}
	}
	void CAlarm_UIChild::SetModeVisible(BOOL bVisible)
	{
		SetModeVisible(bVisible, O);
	}

	void CAlarm_UIChild::SetModeVisible(BOOL bVisible, int nMode)
	{
		int nCmdShow = O;
		if(bVisible ==TRUE) nCmdShow = SW_SHOW;
		else nCmdShow = SW_HIDE;

		if(nMode == 0) nMode = m_nMode;

		switch (nMode)
		{

		case CHILD_EDUURL:
			m_editEduTiTie			.ShowWindow(nCmdShow);
			m_editEduURL			.ShowWindow(nCmdShow);
			m_comboEduTimeHour1		.ShowWindow(nCmdShow);
			m_comboEduTimeMinute1	.ShowWindow(nCmdShow);

			m_chMon		.ShowWindow(nCmdShow);
			m_chTUE		.ShowWindow(nCmdShow);
			m_chWED		.ShowWindow(nCmdShow);
			m_chTHU		.ShowWindow(nCmdShow);
			m_chFRI		.ShowWindow(nCmdShow);


			m_chSAT			.ShowWindow(nCmdShow);
			m_chSUN			.ShowWindow(nCmdShow);

			m_listCtrIEdu		->ShowWindow(nCmdShow);
			m_ibtn2_save		->ShowWindow(nCmdShow);
			m_ibtn2_cancel		->ShowWindow(nCmdShow);
			m_ibtn2_repair		->ShowWindow(nCmdShow) ;
			m_ibtn2_delete		->ShowWindow(nCmdShow) ;
			break;


		case CHILD_MESSAGE:
			m_editMSGMEssage		.ShowWindow(nCmdShow) ;
			m_comboMSGTimeHour	.ShowWindow(nCmdShow) ;
			m_comboMSGTimeMinute.ShowWindow(nCmdShow) ;
			m_chReSend			.ShowWindow(nCmdShow) ;


			m_istCtriMSGWillSend
				m_istCtriMSGReceive	->ShowW ndow(nCmdShow);
			m_istCtriMSGSended		->ShowW ndow(nCmdShow);
			m_btn5_save			->ShowW ndow(nCmdShow);
			m_btn5_delete			->ShowW ndow(nCmdShow);
			m_btn5_willSend		->ShowW ndow(nCmdShow);
			m_btn5_sended			->ShowW ndow(nCmdShow);
			m_btn5_recieved		->ShowW ndow(nCmdShow);

			m_editMSG				.ShowW ndow(nCmdShow);
			break;
		}
	}


	void CAiarm_UIChi ld : :SetlistCtriEDU()
	{
		m_listCtriEdu = new CListCtrl() ;
		m_l istCtriEdu->Create(WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT ,
			CRect(0,0,1 ,1),
			this ,
			IDC_LISTCTRL3);

		m_l istCtriEdu->SetExtendedStyle(m_l istCtriEdu->GetExtendedStyle() LVS_EX_GRIDLINES) ;

		m_l istCtriEdu->SetExtendedStyle(m_l istCtriEdu->GetExtendedStyle() LVS_EX_FULLROWSELECT);

		m_l istCtrIEdu->lnsertColumn(O ,L"번호", 0, 50 , -1);
		m_l istCtrIEdu->lnsertColumn(1, L"강의제목", 0, 110, -1);
		m_l istCtrIEdu->lnsertColumn(2, L"인터넷주소" 0, 200 ; -1);
		m_l istCtrIEdu->lnsertColumn(3, L"수강요일", 0, 100, -1);
		m_l istCtrIEdu->lnsertColumn(4, L"알람시간", 0, 100, -1);

	}
	void CAlarm_UIChild::SetPositionEDU()
	{
		// 276 241 214 25
		m_editEduT iTie			.MoveWindow(38, 115, 564, 32, TRUE);
		m_editEduURL			.MoveWindow(38, 178, 564, 32, TRUE);
		m_comboEduTimeHour1		.MoveWindow(38 , 241, 97, 25, TRUE);
		m_comboEduTimeMinute1   .MoveWindow(155, 241, 97, 25, TRUE) ;

		m_chMon					.MoveWindow(50, 280, 13, 13, TRUE) ;
		m_chTUE					.MoveWindow(128, 280, 13, 13, TRUE);
		m_chWED					.MoveWindow(211, 280, 13, 13, TRUE);
		m_chTHU					.MoveWindow(288, 280, 13, 13, TRUE);
		m_chFRI					.MoveWindow(369, 280, 13, 13, TRUE);


		m_chSAT		.MoveWindow(450, 280, 13, 13, TRUE);
		m_chSUN		.MoveWindow(530, 280, 13, 13, TRUE);

		m_listCtrIEdu		->MoveWindow(38, 357, 564, 233, TRUE);
	}
	void CAlarm_UIChild::SetChecklabeiEDU()
	{
		m_chMon.SetWindowText(L"");
		m_chTUE.SetWindowText(L"");
		m_chWED.SetWindowText(L"");
		m_chTHU.SetWindowText(L"");
		m_chFRI.SetWindowText(L"");
		m_chSAT.SetWindowText(L"");
		m_chSUN.SetWindowText(L"");
	}

	void CAlarm_UIChild::QnNMDblclklistEdu(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
		CPoint point(pia->ptAction);
		UINT uFlags;
		int iSelect = m_listCtriEdu->HitTest(point, &uFlags);

		CString szTitle = L"";
		CString szURL = L"";
		CString szDays = L"";
		CString szAiarmTime = L"";

		if(iSeIect ! = -1)
		{
			szTitle = m_l istCtriEdu->GetltemText(iSelect, 1);
			szURL = m_l istCtriEdu->GetltemText(iSelect, 2);
			szDays = m_l istCtriEdu->GetltemText(iSelect, 3);
			szAiarmTime = m_l istCtriEdu->GetltemText(iSelect, 4);

			int nlengthDays = szDays.Getlength();

			m_nDeletelndex2 = iSelect;

			m_chMon.SetCheck(O);
			m_chTUE.SetCheck(O);
			m_chWED.SetCheck(O);
			m_chTHU.SetCheck(O);
			m_chFRI.SetCheck(O);
			m_chSAT.SetCheck(O);
			m_chSUN.SetCheck(O);
			for(int i = O; i < nlengthDays; i++)
			{
				if(i%2==0)
				{
					if(szDays.Mid(i,1) == L"월")		m_chMon.SetCheck(1);
					else if(szDays.Mid(i,1) == L" 화")  m_chTUE.SetCheck(1);
					else if(szDays.Mid(1) == L"수" )	m_chWED.SetCheck(1);
					else if(szDays.Mid(1) == L"목")		m_chTHU.SetCheck(1);
					else if(szDays.Mid(1) == L"금")		m_chFRI.SetCheck(1);
					else if(szDays.Mid(1) == L"토")		m_chSAT.SetCheck(1);
					else if(szDays.Mid(1) == L"일")		m_chSUN.SetCheck(1);
				}

			}

			CString szHour = szAlarmTime.Mid(0,2);
			CString szMinute = szAlarmTime.Mid(3,2);


			m_editEduTiTie.SetWindowText(szTitle);
			m_editEduURL.SetWindowText(szURL);
			m_comboEduTimeHour1.SeteurSel(_ttoi(szHour));
			m_comboEduTimeMinute1 .SeteurSel(_ttoi(szMinute));

			m_szEduTitle = szTitle;
			m_szEduURL = szURL;
			m_nEduTimeHour = _ttoi(szHour);
			m_nEduTimeMinute = _ttoi(szMinute);
			m_ibtn2_delete->EnableWindow(SW_HIDE);

			m_blsEditModeEdu =FALSE;
			Sete2BtnVisible();
		}

		*pResuIt = 0;

	}

	void eAlarm_Ulchild::OnNMDblclklistWillSend(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMAeTIVATE pia = (LPNMITEMAeTIVATE)pNMHDR;
		CPoint point(pia->ptAction);
		UINT uFlags;
		int iSelect = m_listetriMSGWillSend->HitTest(point, &uFlags);

		CString szMSG = L"";
		if(iSeIect ! = -1)
		{
			szMSG= m_listetriMSGWillSend->GetltemText(iSelect, 1);

			m_editMSG.SetWindowText(szMSG);

			m_szWilISendMSG = szMSG;

			m_szDe I eteMSG = m_listeCtrIMSGWiIISend->Get I temText(iSeIect, 1);
			m_szDeleteTime = m_listeCtrIMSGWiIISend->GetltemText(iSelect, 2);
			m_szDeleteSavedTime = m_listeCtrIMSGWiIISend->GetltemText(iSelect, 3);
			m_nDeletelndex5 = iSelect;
			m_ibtn5_delete->EnableWindow(TRUE);
		}
		else
		{
			m_ibtn5_delete->EnableWindow(FALSE);
		}
		*pResuIt = O;
	}

	void eAlarm_UlChild::QnNMDblclklistSended(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMAeTIVATE pia = (LPNMITEMAeTIVATE)pNMHDR;
		ePoint point(pia->ptAction);
		UINT uFlags;
		int iSelect = m_listetriMSGSended->HitTest(point, &uFlags);
		eString szMSG = L"";
		if(iSeIect ! = -1)
		{
			szMSG = m_listetriMSGSended->GetltemText(iSelect, 1);
			m_editMSG.SetWindowText(szMSG);

			m_szSendedMSG = szMSG;

			m_szDeleteMSG = m_listCtriMSGSended->GetltemText(iSelect, 1);
			m_szDeleteTime = m_listCtriMSGSended->GetltemText(iSelect, 2);
			m_szDeleteSavedTime = m_listCtriMSGSended->GetltemText(iSelect, 3);
			m_nDeletelndex5 = iSelect;
			m_ibtn5_delete->EnableWindow(TRUE);
		}
		else
		{
			m_ibtn5_delete->EnableWindow(FALSE);
		}
		*pResuIt = 0;
	}
	void CAlarm_UIChild::QnNMDblclklistRecieve(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE}pNMHDR;
		CPoint point(pia->ptAction);
		UINT uFlags;
		int iSelect = m_listCtriMSGReceive->HitTest(point, &uFlags} ;
		CString szMSG = L"";
		if(iSeIect != -1)
		{
			szMSG = m_listCtriMSGReceive->GetltemText(iSelect, 1);

			m_editMSG.SetWindowText(szMSG);

			m_szReciveMSG = szMSG;

			m_szDeleteMSG = m_listCtriMSGReceive->GetltemText( iSelect, 1);
			m_szDeleteTime = m_listCtriMSGReceive->GetltemText( iSelect, 2) ;
			m_szDeleteSavedTime = m_listCtriMSGReceive->GetltemText( iSelect, 3);
			m_nDeletelndex5 = iSelect ;
			m_ibtn5_delete->EnableWindow(TRUE);
		}
		else{
			m_ibtn5_delete->EnableWindow(FALSE);
		}
		*pResult = O;
}

void CAlarm_UIChild::SetPositionMessage()
{
	m_editMSGMEssage		.MoveWindow(44, 121, 552 , 124, TRUE);
	m_comboMSGTimeHour		.MoveWindow(38 , 282, 97, 25, TRUE) ;
	m_comboMSGTimeMinute	.MoveWindow(155, 282, 97 , 25 , TRUE);
	m_chReSend				.MoveWindow(279, 288 , 13, 13, TRUE);

	//m_ l ist Ct r iMSGSend	->MoveW indow(44, 340 , 370 , 243 , TRUE);
	//m_ l ist Ct r iMSGReceive ->MoveWi ndow(436 , 340, 160, 243, TRUE );
	m_listCtriMSGSended	->MoveWindow(44, 354, 370 , 231, TRUE);
	m_listCtr IMSGWiIISend ->MoveWindow(44, 354, 370, 231 , TRUE);

	m_l istCtriMSGReceive ->MoveWindow(44, 354, 370, 231, TRUE);
	m_editMSG .MoveWindow(436, 354, 160, 179, TRUE);
	//->MoveWindow(436, 354, 160, 231 , TRUE);
}

void CAlarm_UIChild::SetChecklabeiMessage()
{
	//m_chReSend.SetWindowText(L "못 받았을 경우 재전송합니다.");
	m_chReSend.SetWindowText(L"");
}


void CAlarm_UIChild::SetlistCtriMessage()
{
	m_listCtriMSGWillSend= new CListCtrl();
	m_listCtriMSGWillSend->Create(WS_CHILD I WS_VISIBLE I WS_BORDER I LVS_REPORT,
		CRee t ( 0, 0, 1 , 1) ,
		this,
		IDC_LISTCTRL4);

	m_l istCtriMSGWillSend->SetExtendedStyle(m_l istCtriMSGWi I ISend->GetExtendedStyle()
		LVS_EX_GRIDLINES);

	m_l istCtriMSGWillSend->SetExtendedStyle(m_l istCtriMSGWi I ISend->GetExtendedStyle()
		LVS_EX_FULLROWSELECT);

	m_listCtr IMSGWillSend->lnsertColumn(O, L"번호", 0, 50, -1);
	m_listCtr IMSGWillSend->lnsertColumn(1, L"메세지", 0, 200, -1);
	m_listCtr IMSGWillSend->lnsertColumn(2, L"전송할 시간", 0, 120 , -1);
	m_listCtr IMSGWillSend->lnsertColumn(3, L"저장시간" , 0, 100, -1);

	m_listCtriMSGSended =new CListCtrl();
	m_listCtriMSGSended->Create(WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT,
		CRect(0,0,1 ,1),
		this,
		IDC_LISTCTRL5);

	m_listCtriMSGSended->SetExtendedStyle(m_l istCtriMSGSended->GetExtendedStyle() | LVS_EX_GRIDLINES);

	m_listCtriMSGSended->SetExtendedStyle(m_l istCtriMSGSended->GetExtendedStyle() |
		LVS_EX_FULLROWSELECT);

	m_listCtr IMSGSended->lnsertColumn(O, L"번호", 0, 50, -1);
	m_listCtr IMSGSended->lnsertColumn(1, L"메세지", 0, 200, -1);
	m_listCtr IMSGSended->lnsertColumn(2, L"전송할 시간", 0, 120 , -1);
	m_listCtr IMSGSended->lnsertColumn(3, L"저장시간" , 0, 100, -1);


	m_listCtriMSGReceive = new CListCtrl();
	m_listCtriMSGReceive->Create(WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT,
		CRect(0,0,1,1),
		this,
		IDC_LISTCTRL6);

	m_listCtriMSGReceive->SetExtendedStyle(m_listCtriMSGReceive->GetExtendedStyle()
		LVS_EX_GRIDLINES);
	m_listCtriMSGReceive->SetExtendedStyle(m_listCtriMSGReceive->GetExtendedStyle()
		LVS_EX_FULLROWSELECT);


	m_listCtr IMSGReceive->lnsertColumn(O, L"번호", 0, 50, -1);
	m_listCtr IMSGReceive->lnsertColumn(1, L"메세지", 0, 200, -1);
	m_listCtr IMSGReceive->lnsertColumn(2, L"전송할 시간", 0, 120 , -1);
	m_listCtr IMSGReceive->lnsertColumn(3, L"저장시간" , 0, 100, -1);

	void CAlarm_UIChild::QnDestroy()
	{
		CD ialog: :QnDestroy();


		if(m_ibtnEduURL){
			m_ibtnEduURL->DestroyWindow();
			delete m_ibtnEduURL;
		}


		if(m_ibtnMessage){
			m_ibtnMessage->DestroyWindow();
			delete m_ibtnMessage;
		}

		if(m_listCtrIEdu){
			m_listCtrlEdu->DestroyWindow();
			delete m_listCtriEdu;
		}

		if(m_listCtrIMSGSended){
			m_listCtriMSGSended->DestroyWindow();
			delete m_listCtriMSGSended;
		}

		if(m_listCtriMSGReceive){
		}
		m_listCtriMSGReceive->DestroyWindow();
		delete m_listCtriMSGReceive;
	}

	if(m_listCtrIMSGWiIISend){
		m_listCtriMSGWiIISend->DestroyWindow();
		delete m_listCtriMSGWiIISend;
	}

	if(m_ibtn2_save){
		m_ibtn2_save->DestroyWindow() ;
		delete m_ibtn2_save;
	}
	if(m_ibtn2_cancel){
		m_ibtn2_cancei->DestroyWindow();
		delete m_ibtn2_cancel;
	}
	if(m_ ibtn2_repair){
		m_ibtn2_repair->DestroyWindow();
		delete m_ibtn2_repair;
	}
	if(m_ibtn2_delete){
		m_ibtn2_delete->DestroyWindow();
		delete m_ibtn2_delete;
	}

	if(m_ibtn5_save){
		m_ibtn5_save->DestroyWindow();
		delete m_ibtn5_save;
	}

	if(m_ibtn5_delete){
		m_ibtn5_deIete->DestroyWindow();
		delete m_ibtn5_delete;
	}

	if(m_ibtn5_willSend){
		m_ibtn5_willSend->DestroyWindow();
		delete m_ibtn5_willSend;
	}

	if(m_ibtn5_sended){
		m_ibtn5_sended->DestroyWindow() ;
		delete m_ibtn5_sended;
	}

	if(m_ibtn5_recieved){
		m_ibtn5_recieved->DestroyWindow();
		delete m_ibtn5_recieved;
	}

	if(m_popUPDIg ! = NULL)
	{
		m_popUPDig->DestroyWindow();
		delete m_popUPDig;
		m_popUPDig = NULL;
	}
	OnTraylconDelete();
}

void CAlarm_UIChild::SetC2BtnVisible()
{
	m_blsEditModeEdu ==TRUE? m_ibtn2_cancei->ShowWindow(SW_SHOW) :m_ibtn2_cancei->ShowWindow
		( SW_HIDE) ;
	m_blsEditModeEdu ==TRUE? m_ibtn2_save ->ShowWindow(SW_SHOW): m_ibtn2_save ->ShowWindow
		( SW_HIDE);
	m_blsEditModeEdu ==TRUE? m_ibtn2_repair->ShowWindow(SW_HIDE): m_ibtn2_repair->ShowWindow
		(SW_SHOW);
	m_blsEditModeEdu ==TRUE? m_editEduTiTie.EnableWindow(TRUE): m_editEduTiTie .EnableWindow
		(FALSE);
	m_blsEditModeEdu ==TRUE? m_editEduURL.EnableWindow(TRUE): m_editEduURL.EnableWindow
		(FALSE);
	m_blsEditModeEdu ==TRUE? m_comboEduTimeHour1 .EnableWindow(TRUE): m_comboEduTimeHour1.
		EnableWindow(FALSE);
	m_blsEditModeEdu ==TRUE? m_comboEduTimeMinute1.EnableWindow(TRUE) : m_comboEduTimeMinute1 .
		EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chMon.EnableWindow(TRUE) :	m_chMon.EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chTUE.EnableWindow(TRUE) : m_chTUE.EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chWED.EnableWindow(TRUE) : m_chWED.EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chTHU.EnableWindow(TRUE) : m_chTHU.EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chFRI.EnableWindow(TRUE) : m_chFRI.EnableWindow(FALSE);
	m_blsEd tModeEdu == TRUE ? m_chSAT.EnableWindow(TRUE) : m_chSAT.EnableWindow(FALSE);
	m_blsEditModeEdu == TRUE ? m_chSUN.EnableWindow(TRUE) : m_chSUN.EnableWindow(FALSE);

}
void CAiarm_UIChild::OnBnCIickedBtnC2Save()
{
	int nlsMon = m_chMon.GetCheck();
	int nlsTue = m_chTUE.GetCheck();
	int nlsWed = m_chWED.GetCheck();
	int nlsThu = m_chTHU.GetCheck() ;
	int nlsFri = m_chFRI.GetCheck();
	int nlsSat = m_chSAT.GetCheck();
	int nlsSun = m_chSUN.GetCheck();


	CString szTitle = L"";
	CString szURL = L"";
	CString szHour1 = L"";

	CString szMinute1 = L"";

	CString szTime = L"";

	if(nlsMon ==1) szTime += L"월";
	if(nlsTue ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",화";} else {szTime += L "화";}}
	if(nlsWed ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",수";} else {szTime += L "수";}}
	if(nlsThu ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",목";} else {szTime += L "목";}}
	if(nlsFri ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",금";} else {szTime += L "금";}}
	if(nlsSat ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",토";} else {szTime += L "토";}}
	if(nlsSun ==1) {if(szTime.GetLength() % 2 == 1) {szTime += L ",일";} else {szTime += L "일";}}

	m_editEduTiTie			 .GetWindowText(szTitle);
	m_editEduURL			 .GetWindowText(szURL);
	m_comboEduTimeHour1		 .GetWindowText(szHour1);
	m_comboEduTimeMinute1	 .GetWindowText(szMinute1);

	CString szTime1;
	szTime1.Format(L"%s:%s", szHour1, szMinute1);

	CString szQurryString = L"";
	// CString szDate = m_tToday.Format(_T("%Y-%m-%d "));
	bool blsExist =FALSE;
	CDatabase db;

	if(m_lsUpdateModeEdu)
	{
		if(!db .OpenEx(L""DSN=AiarmEducat ion", 0)) OutputDebugString(L""Failed - ODBC Open\n");

		CString szUpdate = L"UPDATE ecampusURL set uri = ";
		szQurryString.Format(L"%s '%s', Title= '%s', Time1 = '%s' where day_= '%s' and userID = '%s'",
			szUpdate,
			szURL, szTitle, szTime1, szTime,
			g_szUserName);
		db.ExecuteSQL(szQurryString);
		db.CIose();

		m_lsUpdateModeEdu = FALSE;

		m_listCtriEdu->SetltemText(m_nDeletelndex2, 1, szTitle);
		m_listCtr1Edu->SetltemText(m_nDeletelndex2, 2, szURL);
		m_listCtriEdu->SetltemText(m_nDeletelndex2, 3, szTime);
		m_listCtriEdu->SetltemText(m_nDeletelndex2, 4, szTime1);
		eIse 
		{
			if(!db.OpenEx(L"DSN=AiarmEducation", 0)) OutputDebugString(L"Failed - ODBC Open\n");

			CString szlnsert = L"INSERT INTO ecampusURL (useriD, uri, title, day_, Time1) VALUES(";
			szQurryString.Format(L"%s '%s', '%s', '%s', '%s', '%s')",
				szlnsert, g_szUserName, szURL,
				szTitle, szTime, szTime1);

			db.ExecuteSQL(szQurryString);
			db.Ciose();

			int nRow = m_listCtriEdu->GetltemCount();
			CString szListColumn1 = L"";


			szListColumn1 .Format(L"%d", nRow);
			m_liistCtriEdu->lnsertltem(nRow, szListColumn1, 0);
			m_listCtriEdu->SetltemText(nRow, 1, szTitle);
			m_listCtriEdu->SetltemText(nRow, 2, szURL);
			m_listCtriEdu->SetltemText(nRow, 3, szTime);
			m_listCtriEdu->SetltemText(nRow, 4, szTime1);

			m_blsEditModeEdu = FALSE;
			SetC2BtnVisible();
		}

		lnitEduComponent();
	}
	void CAlarm_UIChild::lnitEduComponent()
	{
		m_editEduTiTie		.SetWindowText(L"");
		m_ed i tEduURL		.SetWindowText(L"");

		m_comboEduTimeHour1 .SetCurSei(O);
		m_comboEduTimeMinute1 .SetCurSei(O);

		m_comboEduTimeMinute1 .SetWindowText(L"OO");
		m_chMon.SetCheck(O);
		m_chTUE.SetCheck(O);
		m_chWED.SetCheck(O);
		m_chTHU.SetCheck(O);
		m_chFRI.SetCheck(O);
		m_chSAT.SetCheck(O);
		m_chSUN.SetCheck(O);


		m_blsEditModeEdu =TRUE;
		SetC2BtnVisible();

		this->SetFocus();
	}

	void CAlarm_UIChild::QnBnCIickedBtnC5Save()
	{
		CString szContents = L"";
		CString szlsResendMode = L"false";
		CString szDate = m_tToday.Format(_T("%Y-%m-%d"));
		CString szAiarmTime = L"";
		CString szTimeHour = L"";
		CString szTimeMinute = L"";


		m_editMSGMEssage.GetWindowText(szContents);
		m_comboMSGTimeHour .GetWindowText(szTimeHour);
		m_comboMSGTimeMinute.GetWindowText(szTimeMinute);

		szAlarmTime.Format(L"%s:%s", szTimeHour, szTimeMinute);

		int nCheck = m_chReSend.GetCheck();
		if(nCheck) szlsResendMode = L"true";


		CDatabase db;
		CString szQurryString = L"";
		if(!db.OpenEx(L"DSN=AiarmEducation", 0)) OutputDebugStr ing(L:"Failed - ODBC Open\n");

		CString szlnsert = L"INSERT INTO MSGToparent (alarmTime, isCheck, isResendMode, contents,
			savedUseriD, savedDate) VALUES (";
			szQurryString.Format(L"%s '%s', false, %s, '%s', '%s', '%s')",
			szlnsert, szAiarmTime, szlsResendMode, szContents, g_szUserName, szDate);


		db.ExecuteSQL(szQurryString);
		db.Close();


		int nRow = m_listCtrIMSGWiIISend->GetItemCount();
		CString szlistColumn1 = L"";
		CString szlistColumn2Temp = L"";
		CString szlistColumn2 = L"";
		int nlength = szContents.Getlength();
		szlistColumn2 = szlistColumn2Temp = szContents.Mid(O, 10);
		if(nLength > 10) szlistColumn2.Format(L"%s .... ", szlistColumn2Temp);
		szlistColumn1.Format(L"%d", nRow);
		m_listCtriMSGWiIISend->lnsertltem(nRow, szlistColumn1, 0);
		m_listCtriMSGWiIISend->SetltemText(nRow, 1, szlistColumn2);
		m_listCtriMSGWilISend->SetltemText(nRow, 2, szAiarmTime);

		m_editMSGMEssage.SetWindowText(L"");
		m_comboMSGTimeHour.SetCurSei(O);
		m_comboMSGTimeMinute.SetCurSei(O);
	}

	void CAiarm_UIChi ld: :QnBnCI ickedBtnC5Wi I !Send()
	{
		m_nChi ld5MsgMode = WILLSEND;
		SetMSGBtnVisible();
	}
	void CAiarm_UIChi ld: :QnBnCI ickedBtnC5Sended()
	{
		m_nChi ld5MsgMode = SENDED;
		SetMSGBtnVisible();
	}
	void CAlarm_UIChild::QnBnCIickedBtnC5Recieve()
	{
		m_nChild5MsgMode = RECIEVE;
		SetMSGBtnVisible();
	}

	void CAlarm_UIChild::SetMSGBtnVisible()
	{
		m_nChild5MsgMode == WILLSEND? m_listCtriMSGWillSend->ShowWindow(SW_SHOW) m_listCtriMSGWillSend
			->ShowWindow(SW_HIDE);
		m_nChild5MsgMode == SENDED? m_listCtriMSGSended ->ShowWindow(SW_SHOW) m_listCtriMSGSended 
			->ShowWindow(SW_HIDE);
		m_nChild5MsgMode == RECIEVE? m_listCtriMSGReceive ->ShowWindow(SW_SHOW) m_listCtriMSGReceive 
			->ShowWindow(SW_HIDE);
	}

	void CAlarm_UIChild::SelectDBFromEcampusURL()
	{
		CDatabase db;

		CString szSelect = L" Select uri, Title, day_, Time1 from ecampusURL"; 
		CString szQurry = L"";
		CString szURL = L"";
		CString szTitIe = L"";
		CString szDay = L"";
		CString szTime1 = L"";
		CString szNumber = L"";
		szQurry = szSelect;
		if(g_szUserName != "") szQurry.Format(L"%s where useriD = '%s'", szSelect, g_szUserName);
		CRecordset rs(&db);
		if(!db.OpenEx(L"DSN=AiarmEducation", 0)) OutputDebugString(L"Failed - ODBC Open\n");
		if(!rs.Open(CRecordset: :dynaset, szQurry)) OutputDebugStr ing(L"Failed - ODBC Qurry\n");
		if (!rs.IsBOF())rs.MoveFirst(); 
		while (!rs.lsEOF())
		{
			rs.GetFieldValue(short(O), szURL);
			rs.GetFieldValue(short(1), szTitle);
			rs.GetFieldValue(short(2), szDay);
			rs.GetFieldValue(short(3), szTime1);
			rs.MoveNext();

			int nRow = m_listCtriEdu->GetltemCount();
			szNumber.Format(L"%d", nRow);
			m_listCtr IEdu->lnsertItem(nRow, szNumber, 0);
			m_listCtriEdu->SetltemText(nRow, 1, szTitle);
			m_listCtriEdu->SetltemText(nRow, 2, szURL);
			m_listCtriEdu->SetltemText(nRow, 3, szDay);
			m_listCtriEdu->SetltemText(nRow, 4, szTime1);
		}
		rs.Close();
		db.CIose();
	}

	void CAiarm_UIChild::SelectDBFromMSGToParent()
	{
		CDatabase db;

		CString szSelect = L"Select alarmTime, contents, savedDate, !sCheck from MSGToParent";
		CString szQurry = L"";
		CString szAiarmTime = L"";
		CString szContents = L"";
		CString szSavedDate = L"";

		CString szNumber = L"";
		CString szlsCheck = L"";

		szQurry = szSelect;
		if(g_szUserName != "") szQurry.Format(L"%s where savedUseriD = '%s"', szSelect, g_szUserName);
			CRecordset rs(&db);
		if(db.OpenEx(L"DSN=AIarmEducation", 0)) OutputDebugString L"FaiIed - ODBC Open\n") ;
		if(!rs.Open(CRecordset::dynaset, szQurry)) OutputDebugString(L"Failed- ODBC Qurry\n");
		if(!rs.lsBOF())rs.MoveFirst(); 
		while(!rs.lsEOF())
		{
			rs.GetFieldValue(short(O), szAiarmTime);
			rs.GetFieldValue(short(1), szContents);
			rs.GetFieldValue(short(2), szSavedDate);
			rs.GetFieldValue(short(3), szlsCheck);
			rs.MoveNext();

			if(szIsCheck == "0" )
			{
				int nRow = m_listCtriMSGWillSend->GetltemCount();
				szNumber .Format(L"%d", nRow);
				m_listCtriMSGWillSend->lnsertltem(nRow, szNumber, O);
				m_listCtriMSGWillSend->SetltemText(nRow, 1, szContents);
				m_listCtriMSGWillSend->SetltemText(nRow, 2, szAiarmTime);
				m_listCtriMSGWillSend->SetltemText(nRow, 3, szSavedDate);
			}
			else
			{
				int nRow = m_l istCtriMSGSended->GetltemCount();
				szNumber .Format(L"%d", nRow);
				m_listCtriMSGSended->lnsertltem(nRow, szNumber, O);
				m_listCtriMSGSended->SetltemText(nRow, 1, szContents);
				m_listCtriMSGSended->SetltemText(nRow, 2, szAiarmTime);
				m_listCtriMSGSended->SetltemText(nRow, 3, szSavedDate);
			}
		}
		rs.Close();
		db.CIose();


		CDatabase db2;
		szSelect = L"Select alarmTime, contents, savedDate, !sCheck from MSGToChild";
		szQurry = szSelect;
		if(g_szUserName != "") szQurry.Format(L"%s where savedUseriD = '%s' and IsCheck = 0", szSelect,
			g_szUserName);
		CRecordset rs2(&db2);
		if(!db2.0penEx(L"DSN=AiarmEducat ion", 0))	OutputDebugString(L"Failed - ODBC Open\n");
		if(!rs2.0pen(CRecordset: :dynaset, szQurry))OutputDebugString(L"FaiIed - ODBC Qurry\n");
		if(!rs2.IsBOF())rs2.MoveFirst();
		whiIe(!rs2.IsEO())
		{
			rs2.GetFieldValue(short(O), szAiarmTime);
			rs2.GetFieldValue(short(1), szContents);
			rs2.GetFieldValue(short(2), szSavedDate);
			rs2.GetFieldValue(short(3), szlsCheck);
			rs2.MoveNext();

			if(szlsCheck == "1")
			{
				int nRow = m_listCtriMSGReceive->GetltemCount();
				szNumber.Format(L"%d", nRow);
				m_listCtriMSGReceive->lnsertltem(nRow, szNumber, 0);
				m_listCtriMSGReceive->SetltemText(nRow, 1, szContents);

				m_listCtriMSGReceive->SetltemText(nRow, 2, szAiarmTime);
				m_listCtriMSGReceive->SetltemText(nRow, 3, szSavedDate);
			}
		}
		rs2.Ciose();
		db2.Ciose();
	}


	void CAlarm_UIChild::QnBnCIickedBtnC2Cancel()
	{
		m_editEduTiTie.SetWindowText(m_szEduTitle);
		m_editEduURL.SetWindowText(m_szEduURL);
		m_comboEduTimeHour1.SetCurSel(m_nEduTimeHour);
		m_comboEduTimeMinute1.SetCurSel(m_nEduTimeMinute);
	}

	if(m_szEduTitIe !=L"" || m_szEduURL ! = L "")
	{
		m_blsEditModeEdu =FALSE;
		m_lsUpdateModeEdu = FALSE;
		SetC2BtnVisible();
	}
}
void CAiarm_UIChi ld: :QnBnCI ickedBtnC2Repair()
{
	m_blsEditModeEdu =TRUE;
	m_lsUpdateModeEdu =TRUE;
	SetC2BtnVisible();
}

void CAlarm_UIChild::QnTimer(UINT_PTR niDEvent)
{
	switch (niDEvent)
	{
	case 1 :
		KiIITimer(1);
		break;
	case 2:
		WCHAR szName[MAX_PATH] = {0,};
		GetCIassName(this->m_hWnd, szName , sizeof(szName)) ;
		HWND g_Wnd = ::FindWindow(szName, NULL);
		::SendMessage(g_Wnd, WM_BANWORD, 0, O);
		break;
	}
	CDialog::QnTimer(nlDEvent);
}

void CAlarm_UIChild::QnBnCIickedBtnC2Delete()
{
	if (IDNO == MessageBox( L "정말 강의정보를 삭제하시겠습니까?", L"강의정보 삭제", MB_ YESNO))
	{
		return ;
	}
	CDatabase db;
	CSt ring szQur ryTemp = L "";

	CString szQurryString = L"";

	if(!db.OpenEx(L"DSN=AiarmEducat ion",0))    OutputDebugSt ring(L"FaiIed.- ODBC OpenWn");

	CString szDelete = L"Delete from ecampusURL where Title = ";
	szQurryTemp.Format(L"%s '%s' and urI = '%s' ", szDelete, m_szEduTitle, m_szEduURL);

	szQurryString = szQurryTemp;

	if(g_szUserName != L"") szQurryString.Format(L"%s and useriD = '%s'", szQurryTemp, g_szUserName);

	db.ExecuteSQL(szQurryString);
	db.CIose();

	m_listCtriEdu->Deleteltem(m_nDeletelndex2);
}

void CAlarm_UIChild::QnBnCIickedBtnC5Delete()
{
	if (IDNO == MessageBox( L"정말 메세지를 삭제하시겠습니까?", L"메세지삭제", MB_ YESNO))
	{
		return;
	}
	CDatabase db;
	CString szQurryTemp = L "";
	CString szQurryString = L"";
	CString szDeleteTable = L"";

	switch(m_nChild5MsgMode)
	{
	case WILLSEND:
		szDeleteTable = L"MSGToParent";
		m_listCtriMSGWilISend->Deleteltem(m_nDeletelndex5);
		break:
	case SENDED:
		szDeleteTable = L"MSGToParent";
		m_listCtriMSGSended->Deleteltem(m_nDeletelndex5);
		break:
	case RECIEVE:
		szDeIeteTabIe=L"MSTToChiIdI"";
			m_listCtriMSGReceive->Deleteltem(m_nDeletelndex5);
		break:
	}
	if(!db.OpenEx( L "DSN=A I armEducat ion",0))   OutputDebugString(L"Failed - ODBC OpenWn");
	CString szDelete = L"update";
	szQurryTemp.Format(L"%s %s set IsCheck = true where contents = '%s' and alarmTime = '%s' and 
		savedDate = '%s'", szDelete, szDeleteTable, m_szDeleteMSG, m_szDeleteTime, m_szDeleteSavedTime);

		szQurryString = szQurryTemp;


	db.ExecuteSQL(szQurryString);
	db.CIose();
}


void CAlarm_UIChild::OnNMKiIlfocuslistEdu(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ibtn2_delete->ShowWindow(SW_SHOW):
*pResuIt = 0


}
void CAlarm_UIChild::QnNMKiIlfocusListWiIISend(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ibtn5_delete->EnableWindow(FALSE);
	*pResu I t = 0;
}

void CAiarm_UIChi ld: :QnNMKi I lfocusListSended(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ibtn5_delete->EnableWindow(FALSE);
	*pResu I t = 0;
}

void CAiarm_UIChi ld: :QnNMKi I lfocusListRecieve(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ibtn5_delete->EnableWindow(FALSE);
	*pResult = O;
}

LRESULT CAiarm_UIChi ld: :QnBanWord(WPARAM wParam, LPARAM IParam)
{
	if(m_popUPDig ==NULL)
	{
		m_popUPDig =new CAiarm_UIPopup(this);
		m_popUPDig->SetMessage(L "욕을 하면안되요. 바르고 고운말을 사용하세요");
		m_popUPDig->Create( IDD_ALARAME_POPUP, this);
	}
	sndPlaySound(L"dropdown.wav" ,SND_ASYNCISND_NODEFAULT);
	m_popUPDig->ShowWindow(SW_SHOW);
	m_popUPDig->BringWindowToTop();
	m_popUPDig->SetFocus();

	// dIg.DoModaI();
	//Sieep(5000);
	return 1;

	void CAlarm_UIChild::QnClose()
	{
	}
	ShowWindow(SW_HIDE);
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; 
	nid.uID = O;
	nid.uFlags = NIF_MESSAGE|NIF_|CON|NIF_TIP;
	nid.uCallbackMessage = UM_TRAYICQN; 
	nid.hlcon = AfxGetApp()->Loadlcon(IDR_MAINFRAME);
	_tcscpy(nid.szTip, _T("Alarm-e ")); 
	ShelI_Notifylcon(NIM_ADD,&nid);
	//CDialog::OnClose();
	LRESULT CAlarm_UIChild::QnTraylcon(WPARAM wParam, LPARAM IParam){
		UINT uID = (UINT)wParam;
		UINT uMouseMsg = (UINt) IParam;
		POINT MousePos;

		switch(uMouseMsg){
		case Wm_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			ONTrayIconDelete();
			OnOK();
			CAlarm_UILogin dIg;
			dIg.DoModal();
			break;
		}
		return 1;
	}

	void CAlarm_UIChild::OnTrayIconDelete()
	{
		ShowWindow(SW_HIDE);
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; 
		nid.uCallbackMessage = UM_TRAYICON;
		Shell_NotifyIcon(NIM_DELETE,&nid);
	}
}

