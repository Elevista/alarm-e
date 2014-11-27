#include "stdafx.h "
#include "Alarm-e.h "
#include "Alarm_UIParent.h"
#include "Jpeg.h"
#include "Full.h"
#include <GdiPlus.h>
#include "Alarm_UICapture.h"
#include "JKRegistry.h "
#include "Alarm_UILogin.h "
#include <Imm.h>

#define TIMER_P4 2
#define TIMER_P5 1

IMPLEMENT_DYNAMIC(CAlarm_UIParent , CDialog)

	CAlarm_UIParent::CAlarm_UIParent(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarm_UIParent::IDD,pParent)
	, shownMonth(O)
	, shownYear(O)
{
	m_nParent6MsgMode = WILLSEND;
	m_nMode = O;
	m_blsUseTimeEditMode =FALSE;
}

CAlarm_UIParent::~CAlarm_UIParent()
{
}

void CAlarm_UIParent::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB08, m_editTimeUseHour);
	DDX_Control(pDX, IDC_COMB09, m_editTimeUseMinute);
	DDX_Control(pDX, IDC_COMB010, m_editTimeBanHour1);
	DDX_Control(pDX, IDC_COMB011, m_editTimeBanHour2);
	DDX_Control(pDX, IDC_COMB012, m_editTimeBanMinute1);
	DDX_Control(pDX, IDC_COMB013, m_editTimeBanMinute2);
	DDX_Control(pOX, IDC_CHECK1, m_chMon);
	DDX_Control(pDX, IDC_CHECK2, m_chTUE);
	DDX_Control(pDX, IDC_CHECK3, m_chWED);
	DDX_Control(pDX, IDC_CHECK4, m_chTHU);
	DDX_Control(pDX, IDC_CHECK5, m_chFRI);
	DDX_Control(pDX, IDC_CHECK6, m_chSAT);
	DDX_Control(pDX, IDC_CHECK7, m_chSUN);
	DDX_Control(pDX, IDC_EDIT7, m_eiditBanURL);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calenderCapture);
	DDX_Control(pDX, IDC_LIST1, m_listCapture);
	DDX_Control(pDX, IDC_COMB01, m_comboUser);
	DDX_Control(pDX, IDC_COMB02, m_comboYear);
	DDX_Control(pDX, IDC_COMB03, m_comboMonth);
	DDX_Control(pDX, IDC_EDIT8, m_editBanWord);
	DDX_Control(pDX, IDC_EDIT9, m_editMessage);
	DDX_Control(pDX, IDC_COMB04, m_comboMSGTimeHour);
	DDX_Control(pDX, IDC_COMB05, m_comboMSGTimeMinute);

	/////////////////////
	DDX_Control{pDX, IDC_CHECK8, m_chReSend);
	DDX_Control(pDX, IDC_EDIT12, m_editMSG);

	DDX_Control{pDX, IDC_EDIT1, m_editBanWordEng);
	}

	BEGIN_MESSAGE_MAP(CAiarm_UIParent, CDialog)
		ON_WM_PAINT() 
		ON_WM_DESTROY() 
		ON_BN_CLICKED(IDC_BITMAP_PARENT1, &CAiarm_UIParent::QnBnCI ckedBtnTimeSet)
		ON_BN_CLICKED(IDC_BITMAP_PARENT2, &CAiarm_UIParent::QnBnCI ckedBtnBanURLSet)
		ON_BN_CLICKED(IDC_BITMAP_PARENT3, &CAiarm_UIParent::QnBnCI ckedBtnCAPTURE)
		ON_BN_CLICKED(IDC_BITMAP_PARENT4, &CAiarm_UIParent::QnBnCI ckedBtnUserlnfo)
		ON_BN_CLICKED(IDC_BITMAP_PARENT5, &CAiarm_UIParent::QnBnCI ckedBtnBanWordSet)
		ON_BN_CLICKED(IDC_BITMAP_PARENT6, &CAiarm_UIParent::QnBnCI ckedBtnMessage)

		ON_BN_CLICKED(IDC_BITMAP_PARENT1_SAVE, &CAlarm_UIParent::QnBnCIickedBtnP1Save)
		ON_BN_CLICKED(IDC_BITMAP_PARENT1_CANCEL, &CAlarm_UIParent::QnBnCIickedBtnP1Cancel)
		ON_BN_CLICKED(IDC_BITMAP_PARENT1_REPAIR, &CAlarm_UIParent::QnBnCIickedBtnP1Repair)
		ON_BN_CLICKED(IDC_BITMAP_PARENT2_SAVE, &CAlarm_UIParent::QnBnCIickedBtnP2Save)
		ON_BN_CLICKED(IDC_BITMAP_PARENT2_DELETE, &CAlarm_UIParent::QnBnCIickedBtnP2Delete)
		ON_BN_CLICKED(IDC_BITMAP_PARENT3_CAPTURESETTING, &CAiarm_UIParent::
		OnBnCI ickedBtnP3CaptureSetting)
		ON_BN_CLICKED( IDC_BITMAP_PARENT3_DELETE, &CAiarm_UIParent::QnBnCIickedBtnP3Delete)
		ON_BN_CLICKED( IDC_BITMAP_PARENT5_SAVE, &CAiarm_UIParent::QnBnCIickedBtnP5Save)
		ON_BN_CLICKED( IDC_BITMAP_PARENT5_DELETE, &CAiarm_UIParent::QnBnCIickedBtnP5Delete)
		ON_BN_CLICKED( IDC_BITMAP_PARENT6_SAVE, &CAiarm_UIParent::QnBnCIickedBtnP6Save)
		ON_BN_CLICKED( IDC_BITMAP_PARENT6_WILLSEND, &CAiarm_UIParent::QnBnCIickedBtnP6WillSend)
		ON_BN_CLICKED( IDC_BITMAP_PARENT6_SENDED, &CAiarm_UIParent::QnBnCIickedBtnP6Sended)
		ON_BN_CLICKED( IDC_BITMAP_PARENT6_RECIEVE, &CAiarm_UIParent::QnBnCIickedBtnP6Recieve)
		ON_MESSAGE(UM_TRAYICON, &CAiarm_UIParent: :OnTraylcon)

		ON_NOTIFY(NM_CLICK, IDC_LISTCTRL7, &CAiarm_UIParent::QnNMDblclklistWillSend)
		ON_NOTIFY(NM_CLICK, IDC_LISTCTRL8, &CAiarm_UIParent::QnNMDblclklistSended)
		ON_NOTIFY(NM_CLICK, IDC_LISTCTRL9, &CAiarm_UIParent::QnNMDblclklistRecieve)

		ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL7, &CAlarm_UIParent::QnNMKillfocuslistWillSend)
		ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL8, &CAlarm_UIParent::QnNMKillfocuslistSended)
		ON_NOTIFY(NM_KILLFOCUS, IDC_LISTCTRL9, &CAlarm_UIParent::QnNMKillfocuslistRecieve)

		ON_WM_LBUTTONDOWN()
		//ON_CBN_CLOSEUP(IDC_COMB03, &CAlarm_UI Parent::QnCbnCioseupCombo3)
		ON_NOTIFY(MCN_SELECT,IDC_MONTHCALENDAR1, &CAlarm_UIParent::QnMcnSelectMonthcalendar1)
		ON_LBN_SELCHANGE(IDC_LIST1, &CAlarm_UIParent::QnlbnSelchangeList1)
		ON_CBN_SELCHANGE(IDC_COMB03, &CAlarm_UIParent::QnCbnSelchangeCombo3)
		ON_CBN_SELCHANGE(IDC_COMB02, &CAlarm_UIParent::QnCbnSelchangeCombo2)

		ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL1, &CAlarm_UIParent::QnNMOnNMDblclklistOne)
		ON_WM_TIMER()
		ON_WM_CLOSE()
		ON_WM_ACTIVATE()
	END_MESSAGE_MAP()


	//CAlarm_UIParent 메시지 처리기입니다.
	BOOL CAlarm_UIParent::QnlnitDialog{)
	{
		CDlalog::QnlnitDialog();

		MoveDIgCenter(m_hWnd, 646, 630); //640 , 600

		//ModitySty leEx(NULL , WS_EX_TOOLWINDOW) ;

		SetlmageButtonMode();

		SetPositionTimeSet();
		SetComboBoxData();
		SetChecklabeiTimeSet();
		GetTimeSetData();
		SetP1BtnVisible();

		SetlistCtrlBanURL();
		SetPositionBanURL();

		SetPositionCapture();

		SetlistCtrlUserlnfo();
		SetPositionUserlnfo();

		SetlistCtriBanWord();
		SetPositionBanWord();

		SetlistCtrlMessage();
		SetPositionMessage();
		SetChecklabelMessage();

		//SetModeVisible(FALSE, PARENT_TIMESET); //TEST 후 삭제
		SetModeVisble(FALSE, PARENT_BANURLSET);
		SetModeVisble(FALSE, PARENT_CAPTURE);
		SetModeVisble(FALSE, PARENT_USEINFO);
		SetModeVisble(FALSE, PARENT_BANWORDSET);
		SetModeVisble(FALSE, PARENT_MESSAGE);

		theApp.LoadUsingURLDB();
		theApp.LoadGameDB();
		theApp.LoadVideoDB();
		theApp.LoadlmageDB();
		theApp.LoadEduURLDB();


		for(int i=O; i<31; i++)
		{
			isDataDays[i] = false;
		}

		UpdateBanWordData();
		SelectDBFromMSGToParent();

		m_editMSG.EnableWindow(FALSE);
		m_editBanWordEng.ShowWindow(SW_HIDE);
		m_szEngBanWord = L"";

		m_comboUser.ShowWindow(SW_HIDE);
		return TRUE; // return TRUE unless you set the focus to a control
	}

	void CAlarm_UIParent::SelectDBFromMSGToParent()
	{
		CDatabase db;

		CString szSelect L"Select alarmTime, contents , savedDate, !sCheck from MSGToChild";

		///////////////////////////////////////
		CStr ng szQurry = L"";
		CStr ng szAiarmTime = L"";
		CStr ng szContents = L"";
		CStr ng szSavedDate = L"";
		CStr ng szNumber = L"";
		CStr ng szlsCheck = L"";


		szQurry = szSelect;
		if(g_szUserName != "") szQurry .Format(L"%s where savedUseriD = '%s'" , szSelect, g_szUserName);
		CRecordset rs(&db);
		if(ldb.OpenEx(L "DSN=AiarmEducation ", 0)) OutputDebugString(L "Failed- ODBC Open\n");
		if (!rs.Open( CRecordset::dynaset, szSeIect)) Outpu tDebugSt ring( L "FaiIed - ODBC Qurry\n");
		if(!rs.lsBOF())rs.MoveFirst() ; // 처음부터 읽기
		while(!rs.IsEOF())
		{
			rs.GetFieldValue(short(O), szAlarmTime);
			rs.GetFieldValue(short(1), szContents);
			rs.GetFieldValue(short(2), szSavedDate);
			rs .GetFieldValue(short(3), szlsCheck);
			rs.MoveNext();

			if(szIsCheck == "0")
			{
				int nRow = m_listCtriMSGWillISend->GetltemCount();
				szNumber.Format(L"%d", nRow) ;
				m_listCtriMSGWillSend->lnsertltem(nRow,szNumber, O);
				m_listCtriMSGWillSend->SetltemText(nRow,1, szContents);

				m_listCtriMSGWillSend->SetltemText(nRow, 2, szSavedDate);
			}
			else
			{

				int nRow = m_l istCtriMSGSended->GetltemCount();
				szNumber .Format(L"%d", nRow);
				m_listCtriMSGSended->lnsertltem(nRow, szNumber, O);
				m_listCtriMSGSended->SetltemText(nRow, 1, szContents);

				m_listCtriMSGSended->SetltemText(nRow, 2, szSavedDate);
			}

		}
		rs.Close();
		db.CIose();

		CDatabase db2;
		szSelect = L"Select alarmTime, contents, savedDate , IsCheck from MSGToParent";
		szQurry = szSelect;
		if(g_szUserName != "") szQurry.Format(L"%S where savedUseriD = '%s', IsCheck= false", szSelect,
			g_szUserName) ;
		CRecordset rs2(&db2);
		if(!db2.0penEx(L "DSN=AiarmEducat ion", 0)) OutputDebugString(L "Failed- ODBC Open\n");
		if(!rs2.Open( CRecordset::dynaset, szSeIect)) OutputDebugString( L"FaiIed - ODBC Qurry\n");
		if(!rs2.IsBOF())rs2.MoveFirst();
		while (!rs2. lsEOF())
		{
			rs2.GetFieldValue(short(O), szAlarmTime);
			rs2.GetFieldValue(short(1), szContents);
			rs2.GetFieldValue(short(2), szSavedDate);
			rs2.GetFieldValue(short(3), szlsCheck);
			rs2.MoveNext();

			if(szlsCheck == "1")
			{
				int nRow = m_listCtriMSGReceive->GetltemCount();
				szNumber.Format(L" %d ", nRow);
				m_listCtriMSGReceive->lnsertltem(nRow, szNumber , O);
				m_listCtriMSGReceive - >SetltemText(nRow, 1, szSavedDate) ;
				m_listCtriMSGReceive->SetltemText(nRow , 2, szContents);
				m_listCtriMSGReceive->SetltemText(nRow , 3, szSavedDate) ;
			}
		}
		rs2.Close() ;
		db2.Close();
		void CAlarm_UIParent::OnPaint()
		{
			CPaintDC dc(this);//device context for painting
			//m_ nMode


			DrawBackgroundlmage(dc.m_hDC);
			switch (m_nMode)
			{
			case PARENT_CAPTURE:


				UpdateData(TRUE) ;
				if(m_strImgName ! = L"")
				{
					CalarmeDIg CAPTURE;
					CString str ;

					str.Format(L"%s%s", theApp.m_captureDirectory, m_strlmgName) ;
					BSTR strBstr = str .AIlocSysString() ;
					Image img(strBstr) ;
					Graphics g(dc.m_hDC);
					g.Drawlmage(&img , 235, 100 , 340, 430);
					SysFreeString(strBstr) ;
				}
				break;
			}
		}


		void CAlarm_UIParent::DrawBackgroundlmage(HDC hDC)
		{
			HBITMAP hBitmap;

			switch(m_nMode)
			{
			case PARENT_TIMESET:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_PARENT1_)) ;
				break;
				cas e PARENT_BANURLSET:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_PARENT2)) ;
				break;
			case PARENT_CAPTURE:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_PARENT34)) ;
				break;
			case PARENT_USEINFO:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_PARENT4));
				break;

			case PARENT_BANWORDSET:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_PARENT5)) ;
				break;
			case PARENT_MESSAGE:
				hBitmap = LoadBitmap(AfxGetlnstanceHandle() , MAKEINTRESOURCE( IDB_BITMAP_PARENT6));
				break;
			}
			DrawlmageBitBit(hDC ,hBitmap , O, O) :
		}

		void CAlarm_UIParent::SetlmageButtonMode()
		{
			m_ibtnTimeSet = new CBitmapButton() ;
			m_ibtnTimeSet ->Create(NULL, WS_CHILDIWS _VISIBLEIBS_OWNERDRAW , CRect(10 ,10 ,95,50), this, 
				IDC_BITMAP_PARENT1) ;
			m_ ibtnTimeSet ->LoadBitmaps( IDB_BITMAP _PMENU1A, IDB_BITMAP_PMENU1B , IDB_BITMAP_PMENU1C , 
				IDB_BITMAP_PMENU1A);


			m_ibtnBanURLSet =new CBitmapButton() ;
			m_ibtnBanURLSet ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect ( 115 , 10 , 95 ,50) , this, 
				IDC_BITMAP_PARENT2) ;
			m_i btnBanURLSet ->LoadBitmaps( IDB_BITMAP_PMENU2A, IDB_BITMAP_PMENU2B , IDB_BITMAP_PMENU2C , 
				IDB_BITMAP_PMENU2A) ;

			m_ibtnCapture =new CBitmapButton() :
			m_ibtnCapture ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(220,10 ,95,50), this,
				IDC_BITMAP_PARENT3) ;
			m_ibtnCapture ->LoadBitmaps( IDB_BITMAP_PMENU3A , IDB_BITMAP_PMENU3B , IDB_BITMAP_PMENU 3C, 
				IDB_BITMAP_PMENU3A) ;

			m_ ibtnUselnfo =new CBitmapButton() ;
			m_ ibtnUselnfo ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(325 ,10 ,95 ,50) , this,
				IDC _BITMAP_PARENT4);
			m_ibtnUselnfo ->LoadBitmaps{ IDB_BITMAP_PMENU4A, IDB_BITMAP_PMENU4B , IDB_B ITMAP_PMENU4C , 
				IDB_BITMAP_PMENU4A) ;

			m_ibtnBanWordSet =new CBitmapButton() ;
			m_ibtnBanWordSet ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(430 , 10,95 , 50) , this
				IDC_BITMAP_PARENT5) ;
			m_ ibtnBanWordSet ->LoadBitmaps( IDB_BITMAP_PMENU5A , IDB_BITMAP_PMENU5B , IDB _BITMAP_PMENU5C , 
				IDB_BITMAP_PMENU5A) ;

			m_ibtnMessage =new CBitmapButton():
			m_i btnMessage - >Create(NULL, WS_CHILDIWS_VISIBLE I BS~ OWNERDRAW , CRect(535 , 10 , 95,50) , this ,
				IDC_BITMAP_PARENT6) ;
			m_ibtnMessage ->LoadBitmaps( IDB_BITMAP_PMENU6A , IDB_BITMAP_PMENU6B , IDB_BITMAP_PMENU6C , 
				IDB_BITMAP_PMENU6A);

			m_ibtn1_save =new CBitmapButton() :
			m_ibtn1_save ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(525 , 249 , 95 ,50), this,
				, IDC _BITMAP_PARENT1_SAVE) ;
			m_ ibtn1 _save ->LoadBitmaps( IDB_BITMAP_SAVE1 , IDB_BITMAP_SAVE2, IDB_BITMAP_SAVE1 ,
				I DB_BITMAP~SAVE1) ;

			m_ibtn1_cancel =new CBitmapButton();
			m_ibtn1_cancel ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(425,249,95,50) , this 
				, IDC_BITMAP_PARENT1_CANCEL);
			m_ibtn1_cancel ->LoadBitmaps( IDB_BITMAP_CANCEL1 , IDB_BITMAP_CANCEL2 , IDB _BITMAP_CANCEL1 , 
				IDB_BITMAP_SAVE1);


			m_ ibtn1_repair =new CBitmapButton() ;
			m_ibtn1_repair ->Create(NULL , WS_CHILDIWS_V ISIBLE I BS_OWNERDRAW, CRect(525,249,95,50) , this 
				, IDC_BITMAP_PARENT1_REPAIR);
			m_ibtn1_repair ->LoadBitmaps( IDB_BITMAP_REPAIR1, IDB_BITMAP_REPAIR2, IDB_BITMAP_REPAIR1 , 
				IDB_BITMAP_REPAIR1) ;

			m_ibtn2_save =new CBitmapButton();
			m_ibtn2_save ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526 , 102,95,50) , this 
				, IDC_BITMAP_PARENT2_SAVE) ;
			m_ibtn2_save ->LoadBitmaps( IDB_BITMAP_SAVE1 , IDB_BITMAP_SAVE2 , IDB_BITMAP_SAVE1, 
				IDB_BITMAP_SAVE1) ;

			m_ibtn2_delete =new CBitmapButton();
			m_ibtn2_delete - >Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526 ,560,95,50), this 
				, IDC_BITMAP_PARENT2_DELETE) ;
			m_ibtn2_delete ->LoadBitmaps( IDB_BITMAP_DELETE1, IDB_BITMAP_DELETE2, IDB_BITMAP_DELETE1 , 
				IDB_BITMAP_DELETE1);

			m_ibtn3_captureSett ing =new CBitmapButton() ;
			m_ibtn3_captureSetting - >Create(NULL , WS_CHILD IWS_VISIBLE I BS_OWNERDRAW , CRect(119,560 , 95,
				50) , this, IDC_BITMAP_PARENT3_CAPTURESETTING) ;
			m_ ibtn3_captureSetting ->LoadBitmaps( IDB_BITMAP_CAPTURE1, IDB_BITMAP_CAPTURE2 ,
				IDB_BITMAP_CAPTURE1, IDB_B ITMAP_CAPTURE1);

			m_ibtn3_delete =new CBitmapButton();
			m_ibtn3_delete ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(38,560 ,95,50), this 
				IDB_BITMAP_DELETE1);

			m_ibtn5_save = new CBitmapButton() ;
			m_i btn5_save ->Create(NULL , WS_CHILDIWS_V ISIBLE I BS_OWNERDRAW , CRect(526,102,95 ,50), this 
				, IDC_BITMAP_PARENT5_SAVE) ;
			m_ibtn5_save ->LoadBitmaps( IDB_BITMAP_SAVE1 , IDB_BITMAP_SAVE2, IDB_BITMAP_SAVE1 , 
				IDB_BITMAP_SAVE1);

			m_ibtn5_delete =new CBitmapButton() ;
			m_ ibtn5_delete ->Create(NULL , WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526,560 , 95 , 50) , this 
				, IDC_BITMAP_PARENT5_DELETE);
			m_ibtn5_delete ->LoadBitmaps( IDB_BITMAP_DELETE1 , IDB_BITMAP_DELETE2 , IDB_BITMAP_DELETE1, 
				IDB_BITMAP_DELETE1) ;

			m_ibtn6_save =new CBitmapButton() ;
			m_ ibtn6_save ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW , CRect(526,263,95,50), this 
				, IDC_BITMAP_PARENT6_SAVE);
			m_ibtn6_save ->LoadBitmaps( IDB_BITMAP_SAVE1 , IDB_BITMAP_SAVE2, IDB_BITMAP_SAVE1, 
				IDB_BITMAP_SAVE1);

			m_ibtn6_wi iSend =new CBitmapButton() ;
			m_ibtn6_wi iSend ->Create(NULL, WS_CHILDIWS_V ISIBLE BS_OWNERDRAW, CRect(38,303 ,95 ,50) , this
				IDC_BITMAP_PARENT6~WILLSEND) ;
			m_ibtn6_wi iSend ->LoadBitmaps( IDB_BITMAP_WILLSENDA_, IDB_BITMAP_WILLSENDB_,
				IDB_BITMAP_WILLSENDB_ , IDB_BITMAP_WILLSENDB_) ;
			m_ibtn6 _sended =new CBitmapButton();

			m_ibtn6_sended ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(132,303,95,50) , this 
				, IDC_BITMAP_PARENT6_SENDED);
			m_ib t n6_sended ->LoadBitmaps( IDB_BITMAP_SENDEDA_, IDB_BITMAP_SENDEDB_ , IDB_BITMAP_SENDEDB_ , 
				IDB_BITMAP_SENDEDB_);

			///////////////////////////////////////////////////////////////////////

			m_ibtn6_recieved =new CBitmapButton();
			m_ibtn6_recieved ->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(226,303,95,50), 
				this , IDC_BITMAP_PARENT6_RECIEVE);
			m_ibtn6_recieved ->LoadBitmaps( IDB_BITMAP_RECEIVEA_, IDB_BITMAP_RECEIVEB_,
				IDB_BITMAP_RECEIVEB_, IDB_BITMAP_RECEIVEB_);

			m_ibtn6_delete =new CBitmapButton() ;
			m_ibtn6_delete->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(526,560,116,64), this, 
				IDC_BITMAP_PARENT6_DELETE);
			m_ibtn6_delete->LoadBitmaps( IDB_BITMAP_DELETE1, IDB_BITMAP_DELETE2, IDB_BITMAP_DELETE1, ~
				IDB_BITMAP_DELETE2);

			m_ibtnTimeSet		->SizeToContent();
			m_ibtnBanURLSet		->SizeToContent();
			m_ibtnCapture		->SizeToContent();
			m_ibtnUselnto		->SizeToContent();
			m_ibtnBanWordSet	->SizeToContent();
			m_ibtnMessage		->SizeToContent();

			m_ibtn1_save		->SizeToContent();
			m_ibtn1_cancel		->SizeToContent();
			m_ibtn1_repair		->SizeToContent();

			m_ibtn2_save		->SizeToContent();
			m_ibtn2_delete		->SizeToContent();
			m_ibtn3_captureSetting	->SizeToContent();
			m_ibtn3_delete		->SizeToContent();
			m_ibtn5_save		->SizeToContent();
			m_ibtn5_delete		->SizeToContent();
			m_ibtn6_save		->SizeToContent();
			m_ibtn6_wIISend		->SizeToContent();
			m_ibtn6_sended		->SizeToContent();
			m_ibtn6_recieved	->SizeToContent();
			m_ibtn6_delete		->SizeToContent();	

			}

			void CAlarm_UIParent::SetModeVisible(BOOL bVisible)
			{
				SetModeVisible(bVisible, O);
			}

			void CAlarm_UIParent::SetModeVisible(BOOL bVisible, int nMode)
			{
				int nCmdShow = O;
				it(bVisible ==TRUE) nCmdShow = SW_SHOW;
		else nCmdShow = SW_HIDE;

		if(nMode == 0) nMode = m_nMode;

		switch ( nMode)
		{
		case PARENT_TIMESET:
			m_editTimeUseHour		.ShowWindow(nCmdShow);
			m_editTimeUseMinute		.ShowWindow(nCmdShow);
			m_editTimeBanHour1		.ShowWindow(nCmdShow);
			m_editTimeBanHour2		.ShowWindow(nCmdShow);
			m_editTimeBanMinute1	.ShowWindow(nCmdShow);
			m_editTimeBanMinute2	.ShowWindow(nCmdShow);
			m_chMon					.ShowW ndow(nCmdShow);

			//////////////////////

			m_chTUE		.ShowWindow(nCmdShow);
			m_chWED		.ShowWindow(nCmdShow);
			m_chTHU		.ShowWindow(nCmdShow);
			m_chFRI		.ShowWindow(nCmdShow);
			m_chSAT		.ShowWindow(nCmdShow);
			m_chSUN		.ShowWindow(nCmdShow);

			m_ibtn1_save		->ShowWindow(nCmdShow);
			m_ibtn1_cancel		->ShowWindow(nCmdShow);
			m_ibtn1_repair		->ShowWindow(nCmdShow);



			break;
		case PARENT_BANURLSET:
			m_eidtBanURL		.ShowWindow(nCmdShow);
			m_listCtriBanURL	->ShowWindow(nCmdShow);

			m_ibtn2_save		->ShowWindow(nCmdShow);
			m_ibtn2_delete		->ShowWindow(nCmdShow);



			break;
		case PARENT_CAPTURE:
			m_calenderCapture	.ShowWindow(nCmdShow);
			m_listCapture		.ShowWindow(nCmdShow);


			m_ibtn3_captureSetting	->ShowWindow(nCmdShow);
			m_ibtn3_delete		->ShowWindow(nCmdShow);
			break;

		case PARENT_USEINFO:
			//m_co mboUser		.ShowWindow(nCmdShow);
			m_comboYear			.ShowWindow(nCmdShow);
			m_comboMonth		.ShowWindow(nCmdShow);

			m_listCtriUserlnfo		->ShowWindow(nCmdShow);
			m_listCtriUserlnfolnternet	->ShowWindow(nCmdShow);
			m_listCtriUserlnfoGame	->ShowWindow(nCmdShow);
			m_listCtriUserlnfoVideo	->ShowWindow(nCmdShow);

			break;
		case PARENT_BANWORDSET:
			m_editBanWord		.ShowWindow(nCmdShow);
			m_listCtriBanWord	->ShowWindow(nCmdShow);


			m_ibtn5_save	->ShowWindow(nCmdShow);
			m_ibtn5_delete	->ShowWindow(nCmdShow);
			break;
		case PARENT_MESSAGE :
			m_editMessage		.ShowWindow(nCmdShow);
			m_comboMSGTimeHour		.ShowWindow(nCmdShow);
			m_comboMSGTimeMinute	.ShowWindow(nCmdShow);
			m_chReSend				.ShowWindow(nCmdShow);

			m_listCtrIMSGWiIISend		->ShowWindow(nCmdShow);
			m_listCtriMSGReceive		->ShowWindow(nCmdShow);
			m_listCtriMSGSended			->ShowWindow(nCmdShow);
			.ShowWindow(nCmdShow);	->ShowWindow(nCmdShow);

			m_ibtn6_save		->ShowWindow(nCmdShow);
			m_ibtn6_wiiSend		->ShowWindow(nCmdShow);
			m_ibtn6_sended		->ShowWindow(nCmdShow);
			m_ibtn6_recieved	->ShowWindow(nCmdShow);
			m_editMSG			.ShowWindow(nCmdShow);
			m_ibtn6_delete		->ShowWindow(nCmdShow);
			break;
		}
			}


			void CAlarm_UIParent::QnBnCIickedBtnTimeSet()
			{
				if(m_nMode != PARENT_TIMESET)
				{
					SetModeVisible(FALSE);
					m_nMode = PARENT_TIMESET;
					SetModeVisible(TRUE);
					GetTimeSetData();
					m_blsUseTimeEditMode =FALSE;
					SetP1BtnVisible();


					lnvalidate(FALSE);
				}
			}

			void CAlarm_UIParent::GetTimeSetData()
			{
				JKRegistry reg;
				reg .SetHKey(HKEY_LOCAL_MACHINE);
				reg.SetPath(TEXT("SoftwareWWAiarmEWWParent1"));

				//CString szUseHour, szUseMinute, szBanHour1 , szBanMinute1, szBanHour2, szBanMinute2;
				WCHAR szUseHou r [ 16] = L"";
				WCHAR szUseMinute[16] = L"";
				WCHAR szBanHour1[16] = L"";
				WCHAR szBanMinute1[16] = L"";
				WCHAR szBanHou r 2 [ 16] = L"";
				WCHAR szBanMinute2[16] = L"";


				reg.SetName(TEXT("UseHour"));
				reg.GetString(szUseHour);

				reg.SetName(TEXT("UseMinute"));
				reg.GetString(szUseMinute);

				reg.SetName(TEXT("BanHour1"));
				reg.GetString(szBanHour1);

				reg.SetName(TEXT("BanMinute1"));
				reg.GetString(szBanMinute1);

				reg.SetName(TEXT("BanHour2"));
				reg.GetString(szBanHour2);

				reg.SetName(TEXT("BanMinute2")) ;
				reg.GetString(szBanMinute2);

				reg.SetName(TEXT("IsMon"));
				int nMonCheck = reg.Getlnteger();

				reg.SetName(TEXT("IsTUE"));
				int nTUECheck = reg.Getlnteger();

				reg .SetName(TEXT("lsWED"));
				int nWEDCheck = reg.Getlnteger() ;

				reg.SetName(TEXT("IsTHU"));
				int nTHUCheck = reg.Getlnteger() ;

				reg.SetName(TEXT("IsFRI"));
				int nFRICheck = reg.Getlnteger();

				reg.Set Name (TEXT("IsSAT"));
				int nSATCheck = reg.Getlnteger();

				reg.SetName(TEXT("IsSUN"));
				int nSUNCheck = reg.Getlnteger();

				m_editTimeUseHour .SetCurSel(_ttoi(szUseHour));
				m_editTimeUseMinute.SetCurSel(_ttoi(szUseMinute));
				m_editTimeBanHour1 .SetCurSel(_ttoi(szBanHour1));
				m_editTimeBanMinute1.SetCurSel(_ttoi(szBanMinute1));
				m_ed itTimeBanHour2.SetCurSel(_ttoi(szBanHour2));
				m_editTimeBanMinute2.SetCurSel(_ttoi(szBanMinute2));

				m_chMon.SetCheck(nMonCheck);
				m_chTUE.SetCheck(nTUECheck);
				m_chWED.SetCheck(nWEDCheck);
				m_chTHU.SetCheck(nTHUCheck);
				m_chFRI.SetCheck(nFRICheck);
				m_chSAT.SetCheck(nSATCheck);
				m_chSUN.SetCheck(nSUNCheck);
			}

			void CAlarm_UIParent::OnBnCI ickedBtnBanURLSet()
			{
				if(m_nMode != PARENT_BANURLSET)
				{
					//theApp.LoadBanURLDB();
					SetModeVisible(FALSE);
					m_nMode = PARENT_BANURLSET;

					CString szNumber;
					m_listCtriBanURL->DeleteAIIItems() ;


					int nltems = theApp.BlockingURLinfo .GetCount();
					POSITION pos = theApp.BlockingURLinfo.GetHeadPosition();
					for (int i =0; i<nItems; i++)
					{
						CDBDataForm temp = theApp.BiockingURLinfo.GetNext(pos);

						int nRow = m_listCtrIBanURL ->GetItemCount() ;
						szNumber .Format(L"%d", nRow);
						m_listCtriBanURL->Insertltem(nRow, szNumber , 0);
						m_listCtriBanURL->SetltemText(nRow, 1, temp.m_Url);
						m_listCtriBanURL->SetltemText(nRow, 2, temp.m_Date) ;
					}
					SetModeVisible(TRUE);
					lnval idate(FALSE);
				}
				//////////////////
			}
			void CAlarm_UIParent::OnBnCIickedBtnCAPTURE()
			{
				if(m_nMode != PARENT_CAPTURE)
				{
					// theApp.LoadlmageDB();

					CString strMsg;
					SYSTEMTIME sysTime;
					m_calenderCapture.GetCurSel(&sysTime);
					sysTime.wHour = sysTime.wMinute = sysTime.wSecond = sysTime.wMiIIiseconds = O;
					CTime l_time(sysTime);
					strMsg.Format(L "%d-%02d-%02d" , l_time.GetYear(), l_time.GetMonth() , l_time.GetDay());


					SetModeVisible(FALSE);
					m_nMode = PARENT_CAPTURE;

					int nltems = theApp .capturelnfo .GetCount();

					m_listCapture.ResetContent();

					CString yearMonth;

					POSITION pos = theApp.capturelnfo.GetHeadPosition();

					for(int i=0; i<nItems; i++)
					{
						CDBDataForm temp= theApp.capturelnfo.GetNext(pos);

						if(StrCmpW(temp.m_Date,strMsg) == 0)
						{
							m_listCapture.AddString(temp.m_Url);
						}
					}

					SetModeVisible(TRUE);
					lnvalidate(FALSE);
				}
			}


			void CAlarm_UIParent::OnBnCI ickedBtnUserlnfo()
			{
				SetTimer(TIMER_P4, 50, NULL);


				if(m_nMode != PARENT_USEINFO)
				{
					SetModeVisible(FALSE);
					m_nMode = PARENT_USEINFO;
					SetModeVisible(TRUE);
					lnvalidate(FALSE);
				}
			}

			void CAlarm_UIParent::OnBnCIickedBtnBanWordSet()
			{
				if(m_nMode != PARENT_BANWORDSET)


				{
					SetTimer(TIMER_P5, 50, NULL);
					SetModeVisible(FALSE);
					m_nMode = PARENT_BANWORDSET;
					SetModeVisible(TRUE);
					lnval idate(FALSE);

				}
			}
			void CAlarm_UIParent::QnBnCIickedBtnMessage()
			{
				if(m_nMode != PARENT_MESSAGE)
				{
					SetModeVisible(FALSE);
					m_nMode = PARENT_MESSAGE;
					SetModeVisible(TRUE) ;
					m_ibtn6_delete->EnableWindow(FALSE);
					SetMSGBtnVisible();
					lnvalidate(FALSE);
				}
			}

			void CAlarm_UIParent::SetPositionTimeSet()
			{
				m_editT meUseHour		.MoveW ndow( 38,101, 77, 25, TRUE);
				m_editT meUseMinute		.MoveW ndow(165 ,101, 77, 25, TRUE);
				m_editT meBanHour1		.MoveW ndow( 38,214, 97, 25, TRUE);
				m_editT meBanHour2		.MoveW ndow(315,214, 97, 25, TRUE);
				m_editT meBanMinute1	 .MoveW ndow(155,214, 97, 25, TRUE);
				m_editT meBanMinute2	 .MoveW ndow(432,214, 97, 25, TRUE);


				m_chMon			.MoveWindow( 49,167, 13, 13, TRUE);
				m_chTUE			.MoveWindow(129,167, 13, 13, TRUE);
				m_chWED			.MoveWindow(210,167, 13, 13, TRUE);
				m_chTHU			.MoveWindow(287,167, 13, 13, TRUE);
				m_chFRI			.MoveWindow(368,167, 13, 13, TRUE);
				m_chSAT			.MoveWindow(449,167, 13, 13, TRUE);
				m_chSUN			.MoveWindow(530,167, 13, 13, TRUE);
			}

			void CAlarm_UIParent::SetComboBoxData()
			{
				CString szHour = L"" ;
				CString szMinute = L"" ;
				for(int i=O; i<24; i++)
				{
					if(i< 10) szHour .Format(L"O%d ", i);
					else szHour.Format(L"%d", i);
					m_editTimeUseHour .AddString(szHour);
					m_editTimeBanHour1 .AddString(szHour);
					m_editTimeBanHour2.AddString(szHour);
					m_comboMSGTimeHour .AddString(szHour);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////
				for (int i=0; i<60; i++)
				{
					if(i<10) szMinute.Format(L "0%d", i);
					else szMinute.Format(L "0%d", i);

					m_editTimeUseMinute .AddString(szMinute);
					m_editTimeBanMinute1 .AddString(szMinute);
					m_editTimeBanMinute2 .AddString(szMinute);

					m_comboMSGTimeMinute .AddString(szMinute) ;
				}

				m_editT meUseHour.SetCurSei(O);
				m_editT meBanHour1.SetCurSei(O);
				m_editT meBanHour2.SetCurSei(O);
				m_editT meUseMinute.SetCurSei(O);
				m_editT meBanMinute1.SetCurSei(O);
				m_editT meBanMinute2.SetCurSei(O);

			}

			void CAlarm_UIParent::setChecklabeiTimeSet()
			{
				m_chMon		.SetWindowText(L "" );
				m_chTUE		.SetWindowText(L "" );
				m_chWED		.SetWindowText(L "" );
				m_chTHU		.SetWindowText(L "" );
				m_chFRI		.SetWindowText(L "" );
				m_chSAT		.SetWindowText(L "" );
				m_chSUN		.SetWindowText(L "" );
			}

			void CAlarm_UIParent::SetlistCtriBanURL()
			{
			}
			m_listCtriBanURL =new ClistCtrl();
			m_listCtriBanURL->Create(WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT,
				CRect(0,0,1,1),
				this,
				IDC_LISTCTRL1) ;

			m_listCtriBanURL->SetExtendedStyle(m_l istCtriBanURL->GetExtendedStyle() LVS_EX_GRIDLINES) ;

			m_listCtriBanURL->SetExtendedStyle(m_l istCtriBanURL->GetExtendedStyle() LVS_EX_FULLROWSELECT) ;

			m_listCtr IBanURL->InsertColumn(O, L"번호", 0, 50, -1);
			m_listCtr IBanURL->InsertColumn(1, L"인터넷 주소", 0, 400, -1);
			m_listCtr IBanURL->InsertColumn(2, L"날짜", 0, 100, -1);

		}

		void Cliarm_UIParent::SetPositionBanURL()
		{	
			m_eidtBanURL		.MoveWindow (41, 104, 451, 26, TRUE) ;
			m_listCtrI BanURL	->MoveWindow(44, 169, 552, 375 , TRUE);
		}


		void CAlarm_UIParent::SetPositionCapture()
		{
			m_listCapture.MoveWindow(44, 230, 150, 312);
			m_calenderCapture.MoveWindow(44, 86, 150, 140);
			//216 86 380 457
		}
		/////////////////////////
		void eAlarm_UIParent::SetlistetriUserlnfo()
		{
			m_ listetriUserlnfo =new eListetrl() ;
			m_ listetriUserlnfo->ereate(WS_CHILD I WS_VISIBLE I WS_BORDER I LVS_REPORT,
				eRect(0,0,1,1),
				this,
				IDe_LISTeTRL1);

			m_ listetrlUserlnfo->SetExtendedStyle(m_l istetriUserlnfo- >GetExtendedStyle() LVS_EX_GRIDLINES);
			m_ listetrIUser I nfo->SetExtendedStyle(m_listetrIUserInfo->GetExtendedStyle() 
				LVS_EX_FULLROWSELEeT);
			m_listetrIUserInfo->lnsertColumn(O, L "날짜" , 0 , 40 , -1) ;
			m_listetrIUserInfo->lnsertColumn(1, L "인터넷" , 0 , 60 , -1) ;
			m_listetrIUserInfo->lnsertColumn(2, L "게임" , 0 , 60, -1) ;
			m_listetrIUserInfo->lnsertColumn(3, L "동영상", 0, 60 , -1) ;
			m_listetrIUserInfo->lnsertColumn(4, L "" , 0, 02, -1) ;
			m_listetrIUserInfo->lnsertColumn(5, L "00~07" , 0 , 50 , -1) ;
			m_listetrIUserInfo->lnsertColumn(6, L "08" , 0, 30, -1) ;
			m_listetrIUserInfo->lnsertColumn(7, L "09" , 0, 30, -1) ;
			m_listetrIUserInfo->lnsertColumn(8, L "10" , 0, 30, -1) ;
			m_listetrIUserInfo->lnsertColumn(9, L "11" , 0, 30, -1) ;
			m_listetrIUserInfo->lnsertColumn(10,L "12" , 0, 30 , -1) ;
			m_listetrIUserInfo->lnsertColumn(11,L "13", 0, 30 , -1);
			m_listCtrIUserlnfo->lnsertColumn(12,L "14", 0, 30 , - 1) ;
			m_listCtrIUserlnfo->lnsertColumn(13,L"15" , 0, 30, - 1);
			m_listCtrIUserlnfo->lnsertColumn(14,L"16 ", 0, 30 , -1) ;
			m_listCtrIUserlnfo->lnsertColumn(15 L"17 ", 0, 30, -1) ;
			m_listCtrIUserlnfo->lnsertColumn(16 L"18", 0 , 30, -1) ;
			m_listCtrIUserlnfo->lnsertColumn(17 L"19 " , 0, 30, -1) ;
			m_listetrIUserlnfo->lnsertColumn(18,L "20 ", 0, 30, - 1) ;
			m_listetrIUserlnfo->lnserteolumn(19,L "21" , 0 , 30, -1);
			m_listCtrIUserlnfo->lnsertColumn(20,L "22 ", 0 , 30, -1);
			m_listCtrIUserlnfo->lnsertColumn(21,L "23" , 0 , 30 , -1);


			m_listetriUserlnfolnternet =new eListetrl();
			m_listetriUserlnfolnternet->Create( WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT ,
				CRee t ( 0 , 0 , 1 , 1) ,
				this,
				IDe_LISTeTRL1);

			m_listetriUserlnfolnternet->SetExtendedStyle(m_l istetriUserlnfolnternet->GetExtendedStyle()
				LVS_EX_GRIDLINES) ;
			m_listetriUserlnfolnternet->SetExtendedStyle(m_l i stetriUserlnfolnternet->GetExtendedStyle()
				LVS_EX_FULLROWSELEeT) ;
			m_listetrIUser lnfolnternet - >lnserteolumn(O , L " " , 0 , 0 , -1) ;
			m_listetrIUser lnfolnternet->lnserteolumn(1 , L "강의목록" , 0, 100 , -1);
			m_listetrIUser lnfolnternet - >lnserteolumn(2 , L "시간" , 0, 100, -1);

			m_listetriUserlnfoGame =new CListCtrl();
			m_listetriUserlnfoGame->ereate(WS_eHILD I WS_VISIBLE WS_BORDER LVS_REPORT ,
				eRect(0 , 0 , 1 , 1) ,
				this,
				IDe_LISTeTRL1) ;

			m_listetr I User lnfoGame->SetExtendedStyle(m_listetrIUser lnfoGame - >GetExtendedStyle()
				LVS_EX_GRIDLINES) ;
			m_listCtr I User lnfoGame->SetExtendedStyle(m_listetrIUser lnfoGame->GetExtendedStyle()

				.//////////////////void CAiarm_UIParent: :SetPositionUserlnfo()
				LVS_EX_FULLROWSELECT);
			m_listCtrlUser lnfoGame->lnsertColumn(O, L"" , 0, 0, -1);
			m_listCtrlUser lnfoGame->lnsertColumn(1, L"게임 제목", 0, 100, -1);
			m_listCtrlUser lnfoGame->lnsertColumn(2, L"시간", 0, 100, -1);
		}

		m_listCtriUserlnfoVideo =new CListCtrl();
		m_listCtriUserlnfoVideo->Create(WS_CHILD I WS_VISIBLE WS_BORDER I LVS_REPORT,
			CRee t ( 0, 0 , 1 , 1) ,
			this,
			IDC_LISTCTRL1);
		m_listCtriUserlnfoVideo->SetExtendedStyle(m_listCtriUserlnfoVideo->GetExtendedStyle()
			LVS_EX_GRIDLINES);
		m_listCtriUserlnfoVideo->SetExtendedStyle(m_listCtriUserlnfoVideo->GetExtendedStyle()
			LVS_EX_FULLROWSELECT);
		m_listCtrIUserlnfoVideo->lnsertColumn(O, L"" , 0, 0, -1);
		m_listCtrlUserlnfoVideo->lnsertColumn(1, L "동영상 제목& ", 0, 100, -1);
		m_listCtrlUserlnfoVideo->lnsertColumn(2, L"시간", 0, 100, -1) ;
		void CAiarm_UIParent: :SetPositionUserlnfo()
		{
			/*m_comboUser		. MoveW indow( 88 , 82 , 97, 25, TRUE) ;
			m_comboYear			MoveWindow(205, 82, 97, 25, TRUE);
			m_comboMonth		MoveWindow(322 , 82, 97 , 25 , TRUE);*/
			m_comboYear			MoveWindow(88- 50, 83, 85, 25, TRUE);
			m_comboMonth		MoveWindow(193- 50, 83, 95, 25, TRUE);
			m_listCtriUserlnfo	->MoveWindow(41, 155, 558, 254, TRUE);
			m_listCtr I User lnfolnternet	->MoveWindow(41, 425, 172, 162, TRUE);
			m_listCtriUserlnfoGame		->MoveWindow(234, 425, 172, 162, TRUE);
			m_listCtriUserlnfoVideo		->MoveWindow(427, 425, 172, 162, TRUE);
		}

		void CAlarm_UIParent::SetPositionMessage()
		{
			m_edit Message		.MoveWindow(44, 107, 552, 124, TRUE);
			m_comboMSGTimeHour	.MoveWindow(38, 268, 95, 32, TRUE);
			m_comboMSGTimeMinute	.MoveWindow(155, 268, 95, 32, TRUE) ;
			//155 268 16 16
			m_chReSend			.MoveWindow(279, 274, 12, 12, TRUE);

			m_listCtriMSGSended		->MoveWindow(44, 354, 370, 231, TRUE);
			m_listCtr IMSGWiIISend	->MoveWindow(44, 354, 370, 231, TRUE);
			m_listCtriMSGReceive	->MoveWindow(44, 354, 370, 231, TRUE);
			m_ed i tMSG				.MoveWindow(436, 354, 160, 179, TRUE);


			void CAlarm_UIParent::SetChecklabeiMessage()
			{
				m_chReSend .SetWindowTextW(L"" );
			}
			void CAlarm_UIParent: :SetlistCtriBanWord()
			{
				m_llistCtrlBanWord =  new CListCtrl();

				//////////////
				m_listCtriBanWord->Create(WS_CHILD WS_VISIBLE I WS_BORDER I LVS_REPORT,
					CRee t ( 0 , 0, 1 , 1) ,
					this,
					IDC_LISTCTRL1);

				m_listCtrlBanWord->SetExtendedStyle(m_listCtriBanWord->GetExtendedStyle() LVS_EX_GRIDLINES);
				m_listCtrlBanWord->SetExtendedStyle(m_listCtriBanWord->GetExtendedStyle() LVS_EX_FULLROWSELECT);
				m_listCtrlBanWord->lnsertColumn(O, L"번호", 0, 50, -1);
				m_listCtrlBanWord->lnsertColumn(1 , L"금지어", 0, 350, -1);
				m_listCtrlBanWord->lnsertColumn(2, L"저장 날짜" , 0, 130, -1);
			}
			void CAlarm_UIParent::SetPositionBanWord()
			{
				m_editBanWord		. MoveWindow(41 , 104, 451, 26, TRUE);
				m_listCtriBanWord	->MoveWindow(44, 169, 552, 375, TRUE);
			}


			void CAlarm_UIParent::SetlistCtriMessage()
			{
				m_listCtrlMSGWillSend =new CListCtrl() ;
				m_listCtrlMSGWi I ISend->Create(WS_CHILD I WS_VISIBLE I WS_BORDER I LVS_REPORT,
					CRect ( 0, 0 , 1 , 1) ,
					this,
					IDC_LISTCTRL7);
				m_listCtriMSGWi I ISend->SetExtendedStyle(m_listCtriMSGWiIISend->GetExtendedStyle()
					LVS_EX_GRIDLINES);

				m_listCtriMSGWi I ISend->SetExtendedStyle(m_listCtriMSGWiIISend->GetExtendedStyle()
					LVS_EX_FULLROWSELECT);

				m_listCtrIMSGWiIISend->lnsertColumn(O, L"", 0, 30, -1);
				m_listCtrIMSGWiIISend->InsertCoIumn(1, L"메세지", 0, 150 , -1);
				m_listCtrIMSGWIlISend->InsertCoIumn(2, L"날짜", 0, 100, -1);


				m_listCtriMSGSended =new CListCtrl();
				m_listCtriMSGSended->Create(WS_CHILD I WS_VISIBLE I WS_BORDER I LVS_REPORT,
					CReet(0,0,1 ,1),
					this,
					IDC_LISTCTRLB);

				m_listCtriMSGSended->SetExtendedStyle(m_listCtriMSGSended->GetExtendedStyle() LVS_EX_GRIDLINES);
				m_listCtriMSGSended->SetExtendedStyle(m_listCtriMSGSended->GetExtendedStyle()
					LVS_EX_FULLROWSELECT);

				m_listCtrIMSGSended->lnsertColumn(O, L"", 0, 30, -1);
				m_listCtrIMSGSended->InsertColumn(1, L"메세지", 0, 150, -1);
				m_listCtrIMSGSended->lnsertColumn(2, L"날짜", 0, 100, -1);
				m_listCtrlMSGReeeive =new CListCtrl();
				m_listCtrlMSGReeeive->Create(WS_CHILD I WS_VISIBLE I WS_BORDER I LVS_REPORT,
					CRect (0, 0, 1, 1) ,
					this,
					////////////////////
					IDC_LISTCTRL9);

				m_listCtrlMSGReceive->SetExtendedStyle(m_listCtriMSGReceive->GetExtendedStyle()
					LVS_EX_GRIDLINES);

				m_listCtrIMSGReceive->SetExtendedStyle(m_listCtriMSGReceive->GetExtendedStyle()
					LVS_EX_FULLROWSELECT);

				m_listCtrlMSGReceive->lnsertColumn(O, L"", 0, 30, -1);
				m_listCtrlMSGReceive->lnsertColumn(1, L"메세지", 0, 150, -1);
				m_listCtrIMSGReceive->lnsertColumn(1, L"날짜" , 0, 100, -1);

			}


			void CAlarm_UIParent::OnBnCIickedBtnP1Save()
			{
				CString usingHour, usingMinute, banHour1, banHour2, banMinute1, banMinute2;

				m_editT meUseHour.GetWindowTextW(usingHour);
				m_editT meUseMinute.GetWindowTextW(usingMinute);
				m_editT meBanHour1.GetWindowTextW(banHour1);
				m_editT meBanHour2.GetWindowTextW(banHour2);
				m_editT meBanMinute1.GetWindowTextW(banMinute1);
				m_editT meBanMinute2.GetWindowTextW(banMinute2);

				int nMonCheck = O;
				int nTUECheck = O;
				int nWEDCheck = O;
				int nTHUCheck = O;
				int nFRICheck = O;
				int nSATCheck = O;
				int nSUNCheck = O;

				if(m_chMon.GetCheck() == 1) nMonCheck = 1;
				if(m_chTUE.GetCheck() == 1) nTUECheck = 1;
				if(m_chWED.GetCheck() == 1) nWEDCheck = 1;
				if(m_chTHU.GetCheck() == 1) nTHUCheck = 1;
				if(m_chFRI.GetCheck() == 1) nFRICheck = 1;
				if(m_chSAT.GetCheck() == 1) nSATCheck = 1;
				if(m_chSUN.GetCheck() == 1) nSUNCheck = 1;

				JKRegistry reg;
				reg.SetHKey(HKEY_LOCAL_MACHINE);
				reg.SetPath(TEXT("Software\\AlarmE\\Parent1"));

				reg.SetName(TEXT("UseHour"));
				reg.SetString(usingHour .GetBuffer(O));

				reg.SetName(TEXT("UseMinute"));
				reg.SetStr ing(usingMinute.GetBuffer(O));

				reg.SetName(TEXT("BanHour1"));
				reg.SetString(banHour1 .GetBuffer(O));

				reg.SetName(TEXT("BanMinute1"));
				reg.SetString(banMinute1.GetBuffer(O));

				reg.SetName(TEXT("BanHour2"));
				reg.SetString(banHour2.GetBuffer(O));

				reg.SetName(TEXT("BanMinute2"));
				reg.SetString(banMinute2.GetBuffer(O));

				reg.SetName(TEXT("IsMon"));

				////////////////
				reg.Setlnteger(nMonCheck) ;

				reg.SetName(TEXT("lsTUE")) ;
				reg.Setlnteger(nTUECheck);

				reg.SetName(TEXT("IsWED"));
				reg.Setlnteger(nWEDCheck);

				reg.SetName(TEXT("IsTHU"));
				reg.Setlnteger(nTHUCheck);

				reg.SetName(TEXT("lsFRI")) ;
				reg.Setlnteger(nFRICheck);

				reg.SetName(TEXT("IsSAT")) ;
				reg.Setlnteger(nSATCheck) ;

				reg.SetName(TEXT("lsSUN")) ;
				reg.Setlnteger(nSUNCheck) ;

				m_blsUseTimeEditMode =FALSE;
				SetP1BtnVisible();
			}

			void CAlarm_UIParent::QnBnCIickedBtnP1Cancel()
			{
				m_blsUseTimeEditMode =FALSE ;
				GetTimeSetData();
				SetP1BtnVisible() ;
			}

			void CAlarm_UIParent::QnBnCIickedBtnP1Repair()
			{
				m_blsUseTimeEditMode =TRUE ;
				SetP1BtnVisible();
			}

			void CAlarm_UIParent::SetP1BtnVisible()
			{
				m_blsUseTimeEditMode ==TRUE? m_ibtn1_cancei->ShowWindow(SW_SHOW) : m_ibtn1_cancei->ShowWindow 
					(SW_HIDE);
				m_blsUseTimeEditMode ==TRUE? m_ibtn1_save ->ShowWindow(SW_SHOW): m_ibtn1_save ->ShowW indow 
					(SW_HIDE);
				m_blsUseTimeEditMode ==TRUE? m_ibtn1_repair->ShowWindow(SW_HIDE): m_ibtn1_repair->ShowWindow 
					(SW_SHOW);
				m_blsUseTimeEditMode ==TRUE? m_editTimeUseHour .EnableWindow(TRUE):	m_editTimeUseMinute
					EnableWindow(FALSE);
				m_blsUseTimeEditMode ==TRUE? m_editTimeUseMinute .EnableWindow(TRUE):m_editTimeBanHour1
					EnableWindow(FALSE);
				m_blsUseTimeEd itMode ==TRUE? m_editTimeBanHour1.EnableW indow(TRUE):m_editTimeBanHour2
					EnableWindow(FALSE);
				m_blsUseTimeEditMode ==TRUE? m_editTimeBanHour2 .EnableWindow(TRUE):m_editTimeBanHour2
					EnableWindow(FALSE);
				m_blsUseTimeEditMode ==TRUE? m_editTimeBanMinute1 .EnableWindow(TRUE):m_editTimeBanMinute1 
					EnableWindow(FALSE) ;
				m_blsUseTimeEditMode ==TRUE? m_editTimeBanMinute2.EnableWindow(TRUE):m_editTimeBanMinute2
					EnableWindow(FALSE);


				m_blsUseTimeEditMode ==TRUE? m_chMon.EnableWindow(TRUE) : m_chMon.EnableWindow(FALSE) ;
				m_blsUseTimeEditMode ==TRUE? m_chTUE.EnableWindow(TRUE) : m_chTUE.EnableWindow(FALSE) ;
				m_blsUseTimeEditMode ==TRUE? m_chWED.EnableWindow(TRUE) : m_chWED.EnableWindow(FALSE) ;

				////////////////////
				m_blsUseTimeEditMode ==TRUE?: m_chTHU.EnableWindow(TRUE)
					m_blsUseTimeEditMode ==TRUE?: m_chFRI.EnableWindow(TRUE)
					m_blsUseTimeEditMode ==TRUE?:: m_chSAT.EnableWindow(TRUE)
					m_blsUseT imeEd itMode ==TRUE? m_chSUN.EnableWindow(TRUE)
			}
			void eAlarm_UIParent::QnBnelickedBtnP2Save()
			{
				Cstring urI,date ;
				m_eidtBanURL.GetWindowTextW(url) ;
				date.Format(L"%d-%02d-%02d", CTime::GetCurrentTime() .GetYear() ,
					CTime::GeteurrentTime() .GetMonth(), CTime ::GetCurrentTime() .GetDay());

				if(!url.lsEmpty())
				{
					eDBDataForm temp;
					temp.m_Date = date;
					temp.m_Url =url;
					if( !theApp. islnthe3List(temp,&theApp.BiockingURLinfo))
					{
						theApp. Insert3PrmTabIe(theApp. e_URL, urI);
						//theApp.Block ingURL info .AddHead(temp);
						theApp.BiockingURLinfo .AddTai !(temp);
						int nRow = m_listetriBanURL->Getltemeount();
						eString szlisteolumn1 = L"" ;
						szlisteolumn1.Format(L "%d", nRow) ;
						m_listCtrlBanURL ->Insert I tern( nRow , szl i steo I umn1, 0) ;
						m_listCtrlBanURL ->Set I temText ( nRow , 1 , temp. m_Ur I);
						m_listCtrlBanURL ->SetltemText(nRow , 2, temp.m_Date);
						m_eidtBanURL.SetSei(0,-1);
						m_eidtBanURL.elear();
						void eAiarm_UIParent: :OnBnel ickedBtnP2Delete()
						{
							if(IDNO == MessageBox(L"정말 이ㅣ 금지된 사이트를 삭제하시겠습니까?" , L"금지된 사이트 삭제",
								MB_YESNO))
							{
								return;
							}
							int m_nDeletelndex = m_l istetriBanURL->GetNextltem(-1,LVNI_SELEeTED);
							estring m_szBanURL, m_szDate;
							if(m_nDeletelndex < 0)
								return ;

							CDatabase db;
							//////////////
							CString szQurryTemp = L"" ;
							CString szQurryString = L"";

							m_szBanURL = m_l istCtriBanURL->GetltemText(m_nDeletelndex ,1);
							m_szDate = m_l istCtriBanURL->GetltemText(m_nDeletelndex,2);

							if(!db .OpenEx(L"DSN=AiarmEducat ion ", 0))			OutputDebugString(L"Failed - ODBC Open\n ");

							CString szDelete = L"Delete from banURL where banURLPath = ";
							szQurryString.Format(L "%s '%s ' and savedDate = '%s' ", szDelete, m_szBanURL, m_szDate);

							db.ExecuteSQL(szQurryString);
							db.Close();

							m_listCtrlBanURL->Deleteltem(m_nDeletelndex) ;

							POSITION pos = theApp.BlockingWordlnfo.GetHeadPosition() ;
							for(int i = 0; i<theApp.BIockingURLInfo.GetCount() ; i ++)
							{
								if(theApp.BlockingURLinfo.GetAt(pos).m_Date == m_szDate && theApp.BlockingURLlnfo.GetAt(pos).m_Url == m_szBanURL)
								{
									theApp.BlockingURLinfo.RemoveAt(pos);
									break;
								}

								theApp.BiockingURLinfo.GetNext(pos);
							}
						}
					}
					void CAlarm_UIParent::OnBnCIickedBtnP3CaptureSetting()
					{
						Alarm_UICapture dig;
						dIg.DoModal() ;
					}

					voidCAlarm_UIParent::onBnCIickedBtnP3Delete()
					{
						if(IDNO == MessageBox(L"정말 이 파일을 삭제하시겠습니까?,L"선택된 파일 삭제", MB_YESNO))
						{
							return ;
						}

						int nTotal = m_listCapture .GetCount();
						int nSel = m_istCapture.GetCurSel();
						CString sCurrentltem;
						CString szSaveDate;
						CDatabase db;
						CString szQurryTemp = L"";
						CString szQurryString = L"";


						if (nSeI < 0)
							return;
						m_listCapture. GetText(nSeI,sCurrentItem) ;
						m_listCapture. DeIeteString(nSeI);

						POSITION pos = theApp.capturelnfo.GetHeadPosition();
						for(int i=O ; i<theApp.capturelnfo.GetCount(); i++)
						{
							////////////////

							POSITION tempPos = pos;
							CDBDataForm temp= theApp .capturelnfo.GetNext(pos);
							if(StrCmpW(temp.m_UrI,sCurrentItern) == 0)
							{
								szSaveDate = temp.m_Date;
								theApp.capturelnfo.RemoveAt(tempPos);
								break;
							}
						}


						if(!db.OpenEx(L"DSN=AlarmEducation ", 0))		OutputDebugString(L"Failed - ODBC Open\n");

						CString szDelete;
						szDelete.Format(L"Delete from capturelmg where lmgPath = '%s' and savedDate = '%s'",
							szDelete, sCurrentItem, szSaveDate);

						db.ExecuteSQL(szDelete);
						db.CIose();


						CFiIedeIetingFiIe;
						CString pathDir;
						pathDir. Format(L"%s%s",theApp.m_szCaptureDirectory,sCurrentItem);
						deIetingFiIe.SetFiIePath(pathDir);
						deIetingFiIe.Remove(pathDir);

						RedrawWindow();
					}

					{void CAlarm_UIParent::OnBnCIickedBtnP5Save() 
					{
						CString url,date;
						m_editBanWord.GetWindowTextW(url);
						date.Format(L"%d-%02d-%02d",CTime::GetCurrentTime().GetYear(),
							CTime::GetCurrentTime(). GetMonth() , CTime::GetCurrentTime(). GetDay());

						if(!uri.lsEmpty())
						{
							CDBDataForm temp;
							temp.m_Date = date;
							temp.m_Url =uri;

							if(!theApp.isInthe3List(temp,&theApp.BIockingWordInfo))
							{
								CString szlnsert;
								szInsert.Format(L"INSERT INTO banWord (word, keys, savedDa te) VALUES ('%s', '%s', '%s')",
									url, m_szEngBanWord, date);
								theApp.DBinputForm(szlnsert);

								theApp.BlockingWordlnfo.AddTail(temp);

								int nRow = m_listCtriBanWord->GetltemCount();
								CString szlistColumn1 = L"";
								szlistColumn1.Format(L "%d", nRow);

								/* HIMC hlrnc = lmmGetContext((HWND)m_editBanWordEng);
								lmmSetConversionStatus( hlmc, 0, 0 ) ;
								lmmReleaseContext((HWND)m_editBanWordEng, hlmc);
								CString temp2;
								m_editBanWordEng .GetWindowText(temp2) ;*/
								//m_szEngBanWord


								m_listCtrIBanWord->lnsertItem(nRow, szlistColumn1, 0);
								m_listCtrlBanWord->SetltemText(nRow, 1, temp.m_Url);
								m_listCtrlBanWord->SetltemText(nRow, 2, temp .m_Date);
							}

							m_szEngBanWord = L"";
							m_editBanWord.SetSei(0,-1);
							m_editBanWord.Ciear();
						}
					}

					void CAlarm_UIParent::OnBnCIickedBtnP5Delete()
					{
						int m_nDeletelndex = m_listCtriBanWord->GetNextltem(-1 ,LVNI_SELECTED);
						CString m_szBanWord, m_szDate;

						if(m_nDeletelndex < 0)
							return;

						if(IDNO == MessageBox("정말 이 금지어를 삭제하시겠습니까?", L"금지어 삭제", MB_YESNO))
						{
							return;
						}

						CDatabase db;
						CString szQurryTemp = L"";
						CString szQurryString = L"";

						CDBDataForm temp;

						temp.m_Url = m_szBanWord = m_listCtriBanWord->GetltemText(m_nDeletelndex,1);
						temp.m_Date = m_szDate = m_listCtriBanWord->GetltemText(m_nDeletelndex,2);

						if(!db.OpenEx(L"DSN=AlarmEducation ", 0))		 OutputDebugString(L "Failed- ODBC Open\n");

						CString szDelete = L"Delete from banWord where word= ";
						szQurryString.Format(L"%s '%s' and savedDate = '%s'", szDelete, m_szBanWord, m_szDate);

						db.ExecuteSQL(szQurryString);
						db.Close();

						m_listCtriBanWord->Deleteltem(m_nDeletelndex);

						POSITION pos = theApp.BlockingWordlnfo.GetHeadPosition();
						whiIe(1)
						{
							if(theApp.BlockingWordlnfo.GetAt(pos).m_Date == m_szDate && theApp.BlockingWordlnfo.GetAt 
								(pos).m_Url == m_szBanWord)
							{
								theApp.BlockingWordlnfo.RemoveAt(pos);
								break;
							}
							theApp.BlockingWordlnfo.GetNext(pos);
						}
						////////////////////////
					}
					void CAlarm_UIParent::QnBnCIickedBtnP6Save()
					{
						CString szContents = L"";
						CString szlsResendMode = L"false ";
						m_tToday = CTime::GetCurrentTime();
						CString szDate;
						szDate.Format ( L "%d-%02d-%02d n, m_tToday. Get Year() , m_tToday. Get Month() , m_ tToday. Get Day());
							CString szAiarmTime = L"";
						CString szTimeHour = L"";
						CString szTimeMinute = L"";


						m_editMessage.GetWindowText(szContents);
						m_comboMSGTimeHour .GetWindowText(szTimeHour);
						m_comboMSGTimeMinute.GetWindowText(szTimeMinute) ;

						szAlarmTime.Format(L "%s:%s ", szTimeHour, szTimeMinute);

						int nCheck = m_chReSend.GetCheck();
						if(nCheck) szlsResendMode = L"true ";

						CDatabase db;
						CString szQurryString = L"" ;
						i f (!db.OpenEx( L"DSN=AIarmEducation", 0)) OutputDebugString(L "Failed- ODBC Open\n");

						CStr ing szlnsert = L"INSERT INTO MSGToChild (alarmTime, isCheck, isResendMode, contents, savedUserID, savedDate) VALUES(";
						szQurryStr ing.Format(L"%s '%s', false, %s , '%s' , '%s', '%s')",
							szlnsert, szAlarmTime, szlsResendMode, szContents, g_szUserName, szDate);

						db.ExecuteSQL(szQurryString);
						db.Close();

						int nRow = m_listCtriMSGWiIISend->GetltemCount();
						CString szlistColumn1 = L"";
						CString szlistColumn2Temp = L"";
						CString szlistColumn2 = L"";
						int nlength = szContents.Getlength();
						szlistColumn2 = szlistColumn2Temp = szContents.Mid(O, 10);
						if(nlength > 10) szlistColumn2.Format(L"%s .... ", szlistColumn2Temp);
						szlistColumn1.Format(L"%d ", nRow);
						m_listCtriMSGWiIISend->lnsertltem(nRow, szlistColumn1, O);
						m_listCtriMSGWiIISend->SetltemText(nRow, 1, szlistColumn2);
						m_listCtriMSGWiIISend->SetltemText(nRow, 2, szDate);
					}
					void CAlarm_UIParent::QnBnCIickedBtnP6WiIISend()
					{
						m_nParent6MsgMode = WILLSEND;
						SetMSGBtnVisible();
					}

					void CAlarm_UIParent::QnBnCIickedBtnP6Sended()
					{
						m_nParent6MsgMode = SENDED;
						SetMSGBtnVisible();

						//////////////
					}

					void CAlarm_UIParent::QnBnCIickedBtnP6Recieve()
					{
						m_nParent6MsgMode = RECIEVE;
						SetMSGBtnVisible();
					}


					BOOL CAlarm_UIParent::PreTranslateMessage(MSG* pMsg)
					{
						switch(pMsg->message)
						{
						case WM_KEYDOWN:
							switch(pMsg->wParam)
							{
							case VK_RETURN:
								return TRUE;

							case VK_ESCAPE:
								return TRUE;
							default:
								if(IDC_EDIT8 == GetFocus()->GetDigCtrl ID())
								{
									switch (pMsg->IParam)
									{
									case 1966081: m_szEngBanWord += L"A"; break;
									case 3145729: m_szEngBanWord += L"B"; break;
									case 3014657: m_szEngBanWord += L"C"; break;
									case 2097153: m_szEngBanWord += L"D"; break;
									case 1179649: m_szEngBanWord += L"E"; break;
									case 2162689: m_szEngBanWord += L"F"; break;
									case 2228225: m_szEngBanWord += L"G"; break;
									case 2293761: m_szEngBanWord += L"H"; break;
									case 1507329: m_szEngBanWord += L"l"; break;
									case 2359297: m_szEngBanWord += L"J"; break;
									case 2424833: m_szEngBanWord += L"K"; break;
									case 2490369: m_szEngBanWord += L"L"; break;
									case 3276801: m_szEngBanWord += L"M"; break;
									case 3211265: m_szEngBanWord += L"N"; break;
									case 1572865: m_szEngBanWord += L"O"; break;
									case 1638401: m_szEngBanWord += L"P"; break;
									case 1048577: m_szEngBanWord += L"Q"; break;
									case 1245185: m_szEngBanWord += L"R"; break;
									case 2031617: m_szEngBanWord += L"S"; break;
									case 1310721: m_szEngBanWord += L"T"; break;
									case 1441793: m_szEngBanWord += L"U"; break;
									case 3080193: m_szEngBanWord += L"V"; break;
									case 1114113: m_szEngBanWord += L"W"; break;
									case 2949121: m_szEngBanWord += L"X"; break;
									case 1376257: m_szEngBanWord += L"Y"; break;
									case 2883585: m_szEngBanWord += L"Z"; break;
									case 917505 :
										if(m_szEngBanWord.Getlength() > 0)
											m_szEngBanWord = m_szEngBanWord.Mid(O, m_szEngBanWord.Getlength() - 1);
										break;
									}

									WCHAR szTemp[16] = L"" ;
									wsprintf(szTemp, L"%dWn" , pMsg->IParam);
									OutputDebugString(szTemp);
								}
								break;

								//////////////////////
							}
							break;
						}
						return CDialog::PreTranslateMessage(pMsg) ;
					}
					void CAlarm_UIParent::UpdateBanWordData()
					{
						CDatabase db;

						CString szSelect = L"Select word , savedDate from banWord";
						CString szWord = L"" ;
						CString szSavedDate = L"";
						CString szNumber = L"";

						CRecordset rs(&db);
						if(!db.OpenEx(L"DSN=AIarmEducation", 0)) OutputDebugSt ring(L "FaiIed - ODBC Open\n);
							if(!rs.Open(CRecordset::dynaset , szSelect)) OutputDebugString(L "Failed - ODBC Qurry\n");
						if(!rs.IsBOF())rs.MoveFirst();
						whiIe(!rs.IsEOF())
						{
							rs.GetFieldValue(short(O), szWord);
							rs.GetFieldValue(short(1), szSavedDate);
							rs.MoveNext();

							int nRow =m_listCtrIBanWord->GetItemCount ();
							szNumber.Format(L"%d",nRow);
							m_listCtriBanWord->lnsertltem(nRow, szNumber, O);
							m_listCtriBanWord->SetltemText(nRow, 1, szWord);
							m_listCtriBanWord->SetltemText(nRow, 2, szSavedDate);

						}
						rs.Close() ;
						db.Close() ;
					}

					void CAlarm_UIParent::SetMSGBtnVisible()
					{
						m_nParent6MsgMode == WILLSEND? m_listCtriMSGWiIISend->ShowWindow(SW_SHOW) 
							m_listCtriMSGWiIISend->ShowWindow(SW_HIDE);
						m_nParent6MsgMode == SENDED? m_listCtriMSGSended ->ShowWindow(SW_SHOW) m_listCtr iMSGSended 
							->ShowWindow(SW_H IDE);
						m_nParent6MsgMode == RECIEVE? m_listCtriMSGReceive ->ShowWindow(SW_SHOW) m_listCtriMSGReceive
							->ShowWindow(SW_H IDE);
					}

					void CAlarm_UIParent::OnDestroy()
					{
CDialog :OnDestroy();


						if(m_ibtnTimeSet){
							m_ibtnTimeSet->DestroyWindow();
							delete m_ibtnTimeSet;
						}

						if(m_ibtnBanURLSet){
							m_ibtnBanURLSet->DestroyWindow();
							delete m_ibtnBanURLSet;
						}

						if(m_ibtnCapture){							
							m_ibtnCapture->DestroyWindow();
							delete m_ibtnCapture;
						}

						if(m_ibtnUselnfo){
							m_ibtnUselnfo->DestroyWindow();
							delete m_ibtnUselnfo;
						}

						if(m_ibtnBanWordSet){
							m_ibtnBanWordSet->DestroyWindow();
							delete m_ibtnBanWordSet;
						}

						if(m_ibtnMessage){
							m_ibtnMessage->DestroyWindow();
							delete m_ibtnMessage;
						}

						if(m_listCtriBanURL){
							m_listCtriBanURL->DestroyWindow();
							delete m_listCtriBanURL;
						}

						if(m_listCtrIUserInfo){
							m_listCtrlUserlnfo->DestroyWindow();
							delete m_listCtrlUserlnfo;
						}

						if(m_listCtrIUserlnfolnternet){
							m_listCtrlUserlnfolnternet->DestroyWindow();
							delete m_listCtriUserlnfolnternet;
						}

						if(m_listCtrIUserInfoGame){
							m_listCtrlUserlnfoGame->DestroyWindow();
							delete m_listCtrIUserInfoGame;
						}

						if(m_listCtrlUserlnfoVideo){
							m_listCtriUserlnfoVideo->DestroyWindow();
							delete m_listCtriUserlnfoVideo;
						}

						if(m_listCtrIBanWord){
							m_listCtriBanWord->DestroyWindow();
							delete m_listCtriBanWord;
						}

						if(m_listCtrIMSGWiIISend){
							m_listCtriMSGWiIISend->DestroyWindow();
							delete m_listCtriMSGWiIlSend;
						}

						if(m_listCtrIMSGSended){
							m_listCtriMSGSended->DestroyWindow();
							delete m_listCtriMSGSended;
						}

						if(m_listCtrIMSGReceive){
							m_listCtriMSGReceive->DestroyWindow();
							delete m_listCtriMSGReceive;

							///////////
						}
						if(m_ibtn1_save){
							m_ibtn1_save->DestroyWindow();
							delete m_ibtn1_save;
						}

						if(m_ibtn1_cancel){
							m_ibtn1_cancei->DestroyWindow();
							delete m_ibtn1_cancel;
						}

						if(m_ibtn1_repair){
							m_ibtn1_repair->DestroyWindow();
							delete m_ibtn1_repair;
						}

						if(m_ibtn2_save){
							m_ibtn2_save->DestroyWindow();
							delete m_ibtn2_save;
						}

						if(m_ibtn2_delete){
							m_ibtn2_delete->DestroyWindow();
							delete m_ibtn2_delete;
						}

						if(m_ibtn3_captureSetting){
							m_ibtn3_captureSetting->DestroyWindow();
							delete m_ibtn3_captureSetting;
						}

						if(m_ibtn3_delete){
							m_ibtn3_delete->DestroyWindow();
							delete m_ibtn3_delete;
						}

						if(m_ibtn5_save){
							m_ibtn5_save->DestroyWindow();
							delete m_ibtn5_save;
						}

						if(m_ibtn5_delete){
							m_ibtn5_delete->DestroyWindow();
							delete m_ibtn5_delete;
						}

						if(m_ibtn6_save){
							m_ibtn6_save->DestroyWindow();
							delete m_ibtn6_save;
						}

						if(m_ibtn6_wiiSend){
							m_ibtn6_wiiSend->DestroyWindow();
							delete m_ibtn6_wiiSend;
						}

						if(m_ibtn6_sended){
							m_ibtn6_sended->DestroyWindow();
							delete m_ibtn6_sended;
						}
						///////////////
						if(m_ibtn6_recieved){
							m_ibtn6_recieved->Dest royWindow();
							delete m_ibtn6_recieved ;
						}

						OnTraylconDelete();
					}

					void CAlarm_UIParent::onLButtonDown(UINT nFiags, CPoint point)
					{
						CString imgPath;
						imgPath.Format(L "%s%s" , theApp.m_captureDirectory ,m_strlmgName);

						CFileFind finder;
						BOOL bWorking =finder.FindFile(imgPath);

						if(m_nMode == PARENT_CAPTURE && m_strlmgName != L"" && bWorking)
						{
							if(point.x >= 235 && point.x <= 575
								&& point.y >= 100 && point .y <= 530)
							{
								//MessageBox( L"ASd f");
								CFulI dlg(m_strlmgName);
								dIg.DoModaI();
							}
						}
						CDialog::OnLButtonDown(nliags, point);
					}


					UINT CAlarm_UIParent::CalcUsedTime(CList<CDBDataForm,CDBDataForm&> Iist)
					{
						int nIterns = Iist.GetCount();
						UINT second= O;
						UINT minute= O;
						UINT hour = O;

						POSITION pos = I ist.GetHeadPosition();
						for(int i=0; i<nItems; i++)
						{
							CDBDataForm temp;
							CString timeForm ;
							timeForm = temp.m_UsedTime;

							UINT num = _ttoi(timeForm);

							second += num%100;
							num = num/100;
							minute += num %100;
							hour += num/100;
						}
						minute += second/60;
						second = second%60;
						hour += minute/60;
						minute= minute%60;

						UINT total =second+ 100*minute + 10000 *hour;

						//////////////////////////
						return total;
					}
					CString CAlarm_UIParent::CalcUsedTimestr(CList<CDBDataForm,CDBDataForm&>* Iist)
					{
						int nltems = list->GetCount();
						UINT second = o;
						UINT minute = O;
						UINT hour = O;

						POSITION pos = Iist->GetHeadPosition();

						for (int i=0; i<nItems; i++)
						{
							CDBDataForm temp = Iist->GetNext(pos);
							CString timeForm;
							timeForm = temp .m_UsedTime;
							timeForm.Remove(':');

							UINT num = _ttoi(timeForm);

							second += num%100;
							num = num/100;
							minute+= num %100;
							hour += num/100;
						}
						minute += second/60;
						second = second%60;
						hour += minute/60;
						minute = minute%60;

						CString totaI;
						total.Format(L "%d:%02d:%02d", hour, minute, second);

						return total;
					}

					void CAlarm_UIParent::set_listCtriUserlnfo(int shownYear, int shownMonth)
					{
						int nltems = theApp. internetMonthlnfo .GetCount();


						int nRow =O;
						CString onlyDate,minusStr;
						minusStr .Format(L"%d-%02d-" ,shownYear ,shownMonth);
						m_listCtrIUserInfo->DeIeteAIIItems() ;

						for(int i=0; i<31; i++)
						{
							POSITION posi = theApp.internetMonthlnfo.GetHeadPosition();
							POSITION posg = theApp.gameMonthlnfo.GetHeadPosition();
							POSITION posv = theApp.videoMonthlnfo.GetHeadPosition();
							if(isDataDays[i])
							{
								CString tempDate;
								tempDate.Format(L"%d-%02d-%02d" ,shownYear ,shownMonth, i);

								CList<CDBDataForm,CDBDataForm&> aDaylnternet,aDayGame,aDayMovie;
								////////////////////////////////
								int nltems = theApp. internetMonthlnfo.GetCount();
								for(int i=0; i<nItems; i++)
								{
									CDBDataForm templ = theApp.internetMonthlnfo.GetNext(posi);
									if(StrCmpW(templ.m_Date, tempDate) ==0)
									{
										aDaylnternet.AddHead(templl);
									}
								}

								nltems = theApp .gameMonthlnfo.GetCount();
								for(int i=0; i<nItems; i++)
								{
									CDBDataForm tempG = theApp.gameMon1hlnfo.GetNext(posg);
									if(StrCmpW(tempG .m_Date, tempDate) ==0)
									{
										aDayGame .AddHead(tempG);
									}
								}
								nltems = theApp.videoMonthlnfo .GetCount();
								for(int i=0; i<nItems; i++)
								{
									CDBDataForm tempV = theApp.videoMonthlnfo.GetNext(posv);
									if(StrCmpW(tempV.m_Date,tempDate) ==0)
									{
										aDayMovie .AddHead(tempV);
									}
								}

								CString szNumber;
								CString internetTime = CalcUsedTimestr(&aDaylnternet);
								CString gameTime = CalcUsedTimestr(&aDayGame);
								CString movieTime = CalcUsedTimestr(&aDayMovie);

								onlyDate.Format(L "%d ", i) ;

								int nRow = m_listCtriUserlnfo->GetltemCount();
								szNumber.Format(L "%d ", nRow);
								if(StrCmpW( internetTime,L "0:00:00") == 0 && StrCmpW(gameTime,L "0:00:00") == 0 &&
									StrCmpW(movieTime,L "O:00:00") == 0)
									return;

								m_listCtrlUserlnfo->lnsertltem(nRow, onlyDate, O);
								m_listCtrIUser lnfo->SetItemText(nRow, 1, internetTime);
								m_listCtriUserlnfo->SetltemText(nRow, 2, gameTime);
								m_listCtriUserlnfo->SetltemText(nRow, 3, movieTime);
							}
						}
					}
					void CAlarm_UIParent::set_listCtriUserlnfoGame()
					{
						int nltems = theApp.gameMonthlnfo.GetCount();

						CString onlyDate,minusStr;
						minusStr.Format(L "%d-%02d-%02d " ,shownYear ,shownMonth,shownDay);

						m_listCtriUserlnfoGame->DeleteAIIItems();
						POSITION pos = theApp.gameMonthlnfo.GetHeadPosition();
						////////////////////////////////////////////////////////////////////////////////////
						int nltems = theApp. internetMonthlnfo.GetCount();
						for(int i=0; i<nItems; i++)
						{
							CDBDataForm tempi = theApp.internetMonthlnfo.GetNext(posi);
							if(StrCmpW(templ.m_Date, tempDate) ==0)
							{
								aDaylnternet.AddHead(templ1;
							}
						}

						nltems = theApp .gameMonthlnfo.GetCount();
						for(int i=0; i<nItems; i++)
						{
							CDBDataForm tempG = theApp.gameMon1hlnfo.GetNext(posg);
							if(StrCmpW(tempG .m_Date, tempDate) ==0)
							{
								aDayGame .AddHead(tempG);
							}
						}
						nltems = theApp.videoMonthlnfo .GetCount();
						for(int i=0; i<nItems; i++)
						{
							CDBDataForm tempV = theApp .videoMonthlnfo.GetNext(posv);
							if(StrCmpW(tempV.m_Date, tempDate) ==0)
							{
								aDayMovie.AddHead(tempV);
							}
						}

						CString szNumber;
						CString internetTime = CalcUsedTimestr(&aDaylnternet);
						CString gameTime = CalcUsedTimestr(&aDayGame);
						CString movieTime = CalcUsedTimestr(&aDayMovie);

						onlyDate.Format(L "%d ", i) ;


						int nRow = m_listCtriUserlnfo->GetltemCount();
						szNumber.Format(L "%d ", nRow);
						if(StrCmpW(internetTime,L "0:00:00") == 0 && StrCmpW(gameTime,L "0:00:00") == o &&
							StrCmpW(movieTime,L "0:00:00") == 0)
							return;
						m_listCtrlUserlnfo->lnsertltem(nRow, onlyDate, O);
						m_listCtrIUser lnfo->SetItemText(nRow, 1, internetTime);
						m_listCtrlUserlnfo->SetltemText(nRow, 2, gameTime);
						m_listCtrlUserlnfo->SetltemText(nRow, 3, movieTime);
					}
					}
				}
				void CAlarm_UIParent::set_listCtriUserlnfoGame()
				{
					int nltems = theApp.gameMonthlnfo.GetCount();

					CString onlyDate,minusStr;
					minusStr.Format(L "%d-%02d-%02d ",shownYear,shownMonth,shownDay);

					m_listCtriUserlnfoGame->DeleteAI I Items();
					POSITION pos = theApp.gameMonthlnfo.GetHeadPosition();

					//////////////////////////////
					for(int i=0; i<nItems; i++)
					{
						CDBDataForm temp= theApp.gameMonthlnfo.GetNext(pos);
						CString szNumber;
						CString onlyDate = temp.m_Date;
						if(StrCmpW(temp.m_Date,minusStr) != 0)
							continue;
						onlyDate.Replace(minusStr ,L"");
						int nRow = m_listCtriUserlnfoGame->GetltemCount();
						szNumber.Format(L "%d;;, nRow);
							m_listCtrIUser lnfoGame->lnsertItem(nRow, onlyDate, 0);
						m_listCtrlUserlnfoGame->SetltemText(nRow, 1, temp.m_Url);
						m_listCtrlUserlnfoGame->SetltemText(nRow, 2, temp.m_UsedTime);
					}
				}

				void CAlarm_UIParent::set_listCtriUserlnfolnternet()
				{
					int nltems = theApp.internetMonthlnfo.GetCount();

					CString onlyDate,minusStr;
					minusStr.Format(L "%d-%02d-%02d " ,shownYear ,shownMonth, shownDay);

					m_listCtrIUserlnfolnternet->DeleteAIII terns();
					POSITION pos = theApp . internetMonthlnfo .GetHeadPosition();
					for(int i=O; i<nl terns; i++)
					{
						CDBDataForm temp= theApp. internetMonthlnfo .GetNext(pos);
						CString szNumber;

						CString onlyDate = temp.m_Date;
						if(StrCmpW(temp.m_Date,minusStr) != 0)
							continue;
						onIyDate.RepIace(minusStr, L "");

						int nRow = m_listCtriUserlnfolnternet->GetltemCount();
						szNumber.Format(L"%d", nRow);
						m_listCtrlUserlnfolnternet->lnsertltem(nRow, onlyDate, O);
						m_listCtrIUserInfoInternet->SetItemText( nRow, 1, temp. m_Ur I);
						m_listCtrIUserlnfolnternet->SetItemText(nRow, 2, temp.m_UsedTime);
					}
				}

				void CAlarm_UIParent::set_listCtrIUserlnfoVideo()
				{
					int nltems = theApp.videoMonthlnfo.GetCount();

					CString onlyDate,minusStr;
					minusStr.Format ( L "%d-%02d-%02d"; , shown Year, shownMonth, shownDay) ;

					m_listCtriUserlnfoVideo->DeleteAI I Items();
					POSITION pos = theApp.videoMonthlnfo.GetHeadPosition();
					for(int i=0; i<nItems; i++)
					{
						CDBDataForm temp= theApp.videoMonthln.fo.GetNext(pos);
						CString szNumber;

						CString onlyDate = temp.m_Date;
						if(StrCmpW(temp.m_Date,minusStr) !=0)
							continue;
						onlyDate.Replace(minusStr,L"");
						//////////////////////////
						int nRow = m_listCtriUserlnfoVideo->GetltemCount();
						szNumber.Format(L "%d", nRow);
						m_listCtrlUserlnfoVideo->lnsertltem(nRow , onlyDate, 0);
						m_listCtrIUserlnfoVideo->SetItemText(nRow, 1, temp .m_Ur I);
						m_listCtrlUserlnfoVideo->SetltemText(nRow, 2, temp .m_UsedTime);
					}
				}

				void CAlarm_UIParent::OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
				{

					LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
					CString strMsg;
					SYSTEMTIME sysTime;
					m_calenderCapture.GetCurSel(&sysTime);
					sysTime.wHour = sysTime.wMinute = sysTime.wSecond = sysTime.wMilliseconds = O;
					CTime l_time(sysTime);
					strMsg.Format(L"%d-%02d-%02d ",l_time.Get Year() ,l_time.GetMonth(),l_time.GetDay());

					int nltems = theApp .capturelnfo.GetCount();

					m_listCapture.ResetContent();

					CString yearMonth;

					POSITION pos = theApp.capturelnfo.GetHeadPosition();

					for(int i=0; i<nItems; i++)
					{
						CDBDataForm temp= theApp.capturelnfo.GetNext(pos);

						if(StrCmpW(temp.m_Date,strMsg) == 0)
						{
							m_listCapture.AddString(temp.m_Url);
						}
					}
					*pResuIt = 0;
				}

				void CAlarm_UIParent::OnlbnSelchangelist1()
				{

					int nTotal = m_listCapture.GetCount();
					int nSeI = m_listCapture.GetCurSeI();
					CString sCurrentltem;

					if(nSeI < 0)
						return;

					CString str2;
					str2.Format(L "%d" , nTotaI);
					m_listCapture.GetText(nSel,sCurrentltem);
					m_strlmgName = sCurrentltem;
					//////////////////////////////
					RedrawWindow() ;
				}
				void CAlarm_UIParent::QnCbnSelchangeCombo3()
				{
					for(int i=O; i<31; i++)
					{
						isDataDays[i] = false ;
					}

					CString year, month;
					int nlndex = m_comboYear.GetCurSel() ;
					if(nlndex < 0)
						return;
					m_comboYear.GetLBText(nlndex,year);

					nlndex = m_comboMonth .GetCurSel() ;
					if(nlndex < 0)
						return;

					m_comboMonth.GetLBText(nlndex,month);

					shownYear = _ttoi(year);
					shownMonth = _ttoi(month);

					theApp.LoadUsingURLDB(shownYear ,shownMonth);
					theApp.LoadGameDB(shownYear ,shownMonth);
					theApp.LoadVideoDB(shownYear ,shownMonth);

					LoadlnDataDate();

					m_listCtrlUserlnfoGame->DeleteAIIItems();
					m_listCtrlUserlnfoVideo->DeleteAIIItems();
					m_listCtrIUserInfolnternet->DeleteAIIIterns();
					set_listCtriUserlnfo(shownYear,shownMonth);
					void CAlarm_UIParent::QnCbnSelchangeCombo2()
					{
						for(int i=O; i<31; i++)
						{
							isDataDays[i] = false;
						}

						CString year, month;
						int nlndex = m_comboYear .GetCurSel();
						if(nlndex < 0)
							return;
						m_comboYear.GetLBText(nlndex,year);

						nlndex = m_comboMonth.GetCurSel();
						if(nlndex < 0)
							return;

						m_comboMonth.GetLBText(nlndex ,month);

						shownYear = _ttoi(year);
						shownMonth = _ttoi(month);
						///////////////////////
						theApp.LoadUsingURLDB(shownYear ,shownMonth);
						theApp.LoadGameDB(shownYear ,shownMonth);
						theApp.LoadVideoDB(shownYear ,shownMonth);

						LoadlnDataDate();

						m_listCtrlUserlnfoGame->DeleteAIIItems();
						m_listCtrlUserlnfoVideo->DeleteAIIItems();
						m_listCtrIUser lnfolnternet->DeleteAIIIterns();

						set_listCtrlUserlnfo(shownYear,shownMonth);
					}

					void CAlarm_UIParent::OnNMKiIlfocuslistWiIISend(NMHDR *pNMHDR, LRESULT *pResult)
					{
						m_ibtn6_delete->EnableWindow(FALSE) ;
						*pResuIt = 0;
					}

					void CAlarm_UIParent::OnNMKiIlfocuslistSended(NMHDR *pNMHDR , LRESULT *pResult)
					{
						m_ibtn6_delete->EnableWindow(FALSE) ;
						*pResult = O;
					}

					void CAlarm_UIParent::OnNMKiIlfocuslistRecieve(NMHDR *pNMHDR, LRESULT *pResult)
					{
						m_ibtn6_delete->EnableWindow(FALSE) ;
						*pResuIt = 0;
					}

					void CAlarm_UIParent::OnNMOnNMDblclklistOne(NMHDR *pNMHDR , LRESULT *pResult)
					{
						if(pNMHDR->hwndFrom == m_listCtriUserlnfo->m_hWnd) 
						{
							LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR ;
							CPoint point(pia->ptAct ion);
							UINT uFlags;
							int iSelect = m_listCtriUserlnfo->HitTest(point, &uFiags);
							CString m_nUserlnfoSeleted;

							if(iSelect != -1)
							{
								m_nUserlnfoSeleted = m_listCtriUserlnfo->GetltemText(iSelect, 0);
								shownDay = _ttoi(m_nUserlnfoSeleted);
								set_listCtrlUserlnfoGame();
								set_IistCtrIUserInfoInternet ();
								set_listCtrlUserlnfoVideo();
							}
						}
					}
					void CAlarm_UIParent::LoadlnDataDate()
					{

						int nltemsl = theApp . internetMonth lnfo .GetCount();
						int nltemsG = theApp.gameMonthlnfo .GetCount();
						int nltemsV = theApp.videoMonthlnfo.GetCount();

						CString yearMonth;
						////////////////////////////////////////////////
						for( int nDate =O;nDate<31 ;nDate++)
						{
							yearMonth.Format(L "%d-%02d-%02d " ,shownYear ,shownMonth,nDate);
							POSITION posl = theApp. internetMonthlnfo.GetHeadPosition();
							POSITION posV = theApp.videoMonthlnfo.GetHeadPosition();
							POSITION posG = theApp.gameMonthlnfo.GetHeadPosition();
							for (int i=0; i<nItemsI; i++)
							{
								CDBDataForm temp= theApp.internetMonthlnfo.GetNext(posl);
								if(StrStrW(temp.m_Date,yearMonth))
								{
									isDataDays[nDate] = true;
								}
							}
							for(int i=O; i<nltemsV; i++)
							{
								CDBDataForm temp= theApp.videoMonthlnfo.GetNext(posG);
								if(StrStrW(temp.m_Date,yearMonth))
								{
									isDataDays[nDate] = true;
								}
							}
							for (int i=0; i<nItemsG; i++)
							{
								CDBDataForm temp = theApp.gameMonthlnfo .GetNext(posG);
								if(StrStrW(temp.m_Date,yearMonth))
								{
									isDataDays[nDate] = true;
								}
							}
						}
					}


					void CAlarm_UIParent::OnNMDblclklistWiIISend(NMHDR *pNMHDR, LRESULT *pResult)
					{
						LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR ;
						CPoint point(pia->ptAction) ;
						UINT uFlags;
						int iSelect = m_listCtriMSGWiIISend->HitTest(point, &uFlags);

						CString szMSG = L"";
						if(iSeIect ! = -1)
						{
							szMSG = m_listCtrIMSGWiIISend->GetItemText(iSeIect , 1);

							m_editMSG.SetWindowText(szMSG);

							m_szWiIISendMSG = szMSG;

							m_szDeleteMSG = m_listCtriMSGWiIISend->GetltemText(iSelect, 1);
							m_szDeleteTime = m_listCtriMSGWiIISend->GetltemText(iSelect, 2);
							m_szDeleteSavedTime = m_listCtriMSGWiIISend->GetltemText(iSelect, 3);
							m_nDeletelndex6 = iSelect;
							m_ibtn6_delete->EnableWindow(TRUE);
							////////////////////////////////////////
						}
						else
						{
							m_ibtn6_delete->EnableWindow(FALSE);
						}
						*pResuIt = 0;
					}
					void CAlarm_UIParent::OnNMDblclklistSended(NMHDR *pNMHDR, LRESULT *pResult)
					{
						LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
						CPoint point(pia->ptAction);
						UINT uFlags;
						int iSelect = m_listCtriMSGSended->HitTest(point, &uFlags);

						CString szMSG = L"";
						if(iSeIect ! = -1)
						{
							szMSG = m_listCtriMSGSended->GetltemText(iSelect, 1);

							m_editMSG.SetWindowText(szMSG);

							m_szSendedMSG = szMSG;

							m_szDeleteMSG = m_listCtriMSGSended->GetltemText(iSelect, 1);
							m_szDeleteTime = m_listCtriMSGSended->GetltemText(iSelect, 2);
							m_szDeleteSavedTime = m_listCtriMSGSended->GetltemText(iSelect, 3);
							m_nDeletelndex6 = iSelect;
							m_ibtn6_delete->EnableWindow(TRUE);

						}
						else
						{
							m_ibtn6_delete->EnableWindow(FALSE);
						}
						*pResuIt = O;

						void CAlarm_UIParent::QnNMDblclklistRecieve(NMHDR *pNMHDR, LRESULT *pResult)
						{
							LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
							CPoint point(pia->ptAction);
							UINT uFlags;
							int iSelect = m_listCtriMSGReceive->HitTest(point, &uFlags);

							CString szMSG = L"";
							if(iSelect != -1)
							{
								szMSG = m_listCtriMSGReceive->GetltemText(iSelect, 2);

								m_editMSG.SetWindowText(szMSG);

								m_szReciveMSG = szMSG;

								m_szDeleteMSG = m_listCtriMSGReceive->GetltemText( iSelect, 1);
								m_szDeleteTime = m_listCtriMSGReceive->GetltemText( iSelect, 2);
								m_szDeleteSavedTime = m_listCtriMSGReceive->GetltemText( iSelect, 3);
								m_nDeletelndex6 = iSelect;
								m_ibtn6_delete->EnableWindow(TRUE);
								///////////////////////
							}
							else
							{
								m_ibtn6_delete->EnableWindow(FALSE);
							}

							*pResult = O;
						}

						void CAlarm_UIParent::QnTimer(UINT_PTR nIDEvent)
						{
							switch (niDEvent)
							{
							case 1 :
								KiIITimer(1) ;
								theApp.LoadBanWordDB();
								break;
							case 2:
								if(m_comboYear .GetCount() == 0)
								{
									int nCnt;
									nCnt = CTime::GetCurrentTime().GetYear() - 2010;
									for(int i=0; i<=nCnt; i++)
									{
										CString year;
										year.Format(L"%04d" ,2010 + i);

										m_comboYear.AddString(year);
									}
								}

								if(m_comboMonth.GetCount() == 0)
								{
									for(int i=1; i<=12; i++)
									{
										CString month;
										month.Format(L "%02d ", i);

										m_comboMonth .AddString(month);
									}
								}
								break;
							}
							CDialog::QnTimer(niDEvent);
						}

						void CAlarm_UIParent: :OnClose()
						{
							ShowWindow(SW_HIDE);
							NOTIFYICONDATA nid;
							nid.cbSize = sizeof(nid);
							nid .hWnd = m_hWnd; 
							nid.uID = O;
							nid .uFlags = NIF_MESSAGEINIF_ICONINIF_TIP;
							nid.uCallbackMessage = UM_TRAYICON;
							nid.hlcon = AfxGetApp()->Loadlcon( IDR_MAINFRAME);
							_tcscpy(nid.szTip, _T( "Alarm-e")); 
							She! I_Notifylcon(NIM_ADD ,&nid);
							//CDialog::OnClose();
						}
						/////////////////////////////
						LRESULT CAiarm_UIParent::OnTraylcon(WPARAM wParam, LPARAM IParam){
							UINT uID = (UINT)wParam;
							UINT uMouseMsg = (UINT) IParam;
							POINT MousePos;

							switch(uMouseMsg){
							case WM_LBUTTONDOWN:
							case WM_LBUTTONDBLCLK:
								OnTraylconDelete();
								OnOK();
								CAlarm_UILogin dig;
								dlg.DoModal();
								break;
							}
							return 1;
						}

						void CAlarm_UIParent::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
						{

							CDialog::OnActivate(nState, pWndOther, bMinimized);
						}

						void CAlarm_UIParent: :OnTraylconDelete()
						{
							ShowWindow(SW_HIDE);
							NOTIFYICONDATA nid;
							nid.cbSize = sizeof(nid);
							nid.hWnd = m_hWnd; 
							nid.uiD = O; 
							nid.uCaIIbackMessage = UM_TRAYICON; 
							nid.uFlags = O;
							ShelI_Notifylcon(NIM_DELETE,&nid);
						}
