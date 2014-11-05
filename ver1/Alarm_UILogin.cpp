#include "stdafx.h"
#include "Alarm-e.h"
#include "Alarm_UILogin.h"
#include "alarm-eDlg.h"
#include "alarm_Uljoin.h"
#include "JKRegistry.h"
#include "Alarm_UIChild.h"
#include "Alarm_UIParent.h"


extern CString g_szUserName;

#define WM_OBSENO (WM_USER + 3)

IMPLEMENT_DYNAMIC(CAlarm_UILogin, CDialog)
	CAlarm_UILogin::CAlarm_UILogin(CWnd* pParent /*=NULL*/ )
	:CDialog(CAlarm_UILogin::IDO, pParent)
{

}
CAlarm_UILogin::~CAlarm_UILogin()
{
}

void CAlarm_UILogin::DoDataExchange(CDataExchange* pDX)
{
CDialog: :OoOataExchange(pOX);
	DDX_Control(pDX, IDC_EOIT1, m_edit 1D);
	DDX_Control(pDX, IDC_EOIT2, m_editPassword);
}

BEGIN_MESSAGE_MAP(CAlarm_UILogin, CDialog)
	ON_BN_CLICKEO(IDC_BTN_LOGIN, &CAlarm_UILogin::OnBnCIickedBtnLogin)
	ON_BN_CLICKEO(IDC_BTN_NEW, &CAlarm_UILogin::OnBnCIickedBtnNew)
	ON_MESSAGE(UM_TRAYICON, &CAlarm_UILogin::OnTraylcon)
	ON_WM_PAINT()
	ON_WM_OESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CAlarm_UILogin::OnBnCIickedBtnLogin()
{
	int nUser = SelectLoginOB();
	JKRegistry reg;
	reg.SetHKey(HKEY_CURRENT_USER);
	reg.SetPath(TEXT("Software\\AlarmE\\Mode"));
	reg.Set Name(TEXT ("IsChild"));
	if(nUser == PARENT_USER)
	{
		reg.Setlnteger(O);
		theApp.lnitForReLoad();

		////////////////////
		OnOK();
		CAlarm_UIParent dig;
		dIg.DoModaI();
	else if(nUser == CHILD_USER)
	{
		reg.Setlnteger(1);
		theApp.InitForReload();
		OnOK();
		CAlarm_UIChild dig;
		dIg.DoModaI();
	}

	else if(nUser == NOTHING_USER)
	{
		CDC* pDC = GetDC();
		DrawTextEx(pDC->m_hDC, L "로그인 실패하였습니다.", 10, 140, FALSE, 10, RGB(O,O,O));
		ReleaseDC(pDC);
	}
	}
	void CAlarm_UILogin::GetDB()
	{
	}
	void CAlarm_UILogin::saveDBToTXT()
	{
		CDatabase db;

		CString szSelect = L"Select keys from banWord ";
		CString szKeys = L"";

		//char Temp[20]; ·
		CRecordset rs(&db);

		if(!db.OpenEx(L"DSN=AlarmEducation ", 0)) OutputDebugString(L "Failed- ODBC Open\n");
		if(!rs.Open(CRecordset::dynaset, szSelect)) OutputDebugString(L"Failed- ODBC Qurry\n");
		//fout.open("banWord");
		if(!rs.IsBOF())rs.MoveFirst(); 
		whiIe(!rs.IsEOF())
		{
			rs.GetFieldValue(short(O), szKeys);
			rs.MoveNext();

			//cstring ->char[]
			//memset(str,O,sizeof(char));
			//wcstombs(str, szKeys, szKeys .Getlength()+1);

			// fout <<str <<"\n";

			m_vDB.push_back(szKeys);
		}
		rs.CIose();
		db.Ciose();
		sendDB(rn_vDB);

		//ifstrearn fin; 
		//tin.open("banWord");
		//CString szTernp = L"";
		//
		//char buf[20];
		//while(fin.getline(buf, 20))
		//{
		//szTemp.Format( L"%s", but);
		//vecTemp.push_back(szTemp);
		//}
		//fin.cIose();
	}

	void CAlarm_UILogin::QnBnCIickedBtnNew()
	{
		CAlarm_UIJoin dIg;

		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK) //A:lL9.2.c:
		{
			//CAiarm_UIChi ld chi ldDig;
			//childDig.DoModal();
		}

		//OnCancel();
		//IDNO

		BOOL CAlarrn_UILogin::OnlnitDialog()
		{
			CDialog::OnlnitDialog();

			saveDBToTXT();

			JKRegistry reg;
			reg.SetHKey(HKEY_LOCAL_MACHINE);
			reg.SetPath(TEXT("Software\\AlarmE"));
			reg.SetNarne(TEXT("lsAutoStart"));

			int nAutoStart = O;
			nAutoStart = reg.Getlnteger();

			if(nAutoStart == 0) 
			{
				CString szEXE = L"";

				TCHAR pszPathNarne[_MAX_PATH] ;
				::GetModuleFileNarne(::AfxGetlnstanceHandle(), pszPathNarne, _MAX_PATH);
				PathRernoveFileSpec(pszPathNarne);
				szEXE.Forrnat(L"%sWWAiarrn-e.exe", pszPathNarne);

				cs_util_reg ster _start_Prog(L"AIarrn-e",szEXE.GetBuffer(0));

				reg.Setlnteger(1);
			}

			//ModifyStyleEx(NULL, WS_EX_TOOLWINDOW);

			MoveDIgCenter(m_hWnd, 306, 225);

			SetBitmapButton();

			SetControiPosition();

			return TRUE; // return TRUE unless you set the focus to a control

			BOOL CAiarm_UILogin::cs_util_register_start_Prog(WCHAR* sValue, WCHAR* sPath)
			{
				JKRegistry reg;
				reg.SetHKey(HKEY_LOCAL_MACHINE);
				reg.SetPath(TEXT( "Software\\Microsoft\\\indows\\CurrentVersion\\run"));
				reg.SetName(TEXT( "AlarmE ")) ;
				reg.SetString(sPath)

					return true;
			}
			/*------------------------------------------------------------------------*/
			BOOL CAlarm_UILogin::cs_util_un_register_start_Prog(WCHAR* sValue)
			{
				JKRegistry reg;
				reg.SetHKey(HKEY_LOCAL_MACHINE);
				reg.SetPath(TEXT( "Software\\Microsoft\\\indows\\CurrentVersion\\run"));
				reg.SetName(TEXT( "AlarmE "));
				reg.DeleteName();

				return true;
			}

			void CAlarm_UILogin::OnPaint()
			{
				CPaintDC dc(this);// device context for painting

				HBITMAP hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_LOGIN));

				DrawlmageBitBit(dc.m_hDC,hBitmap ,O,O);

			}
			void CAlarm_UILogin::SetBitmapButton()
			{
				m_ibtnNew =new CBitmapButton();
				m_ibtnNew->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(71 , 160, 50, 30), this, 
					IDC_BTN_NEW);
				m_ibtnNew->LoadBitmaps( IDB_BITMAP_JOIN2, IDB_BITMAP_JOIN1, IDB_BITMAP_JOIN2, IDB_BITMAP_JOIN2);
				m_ibtnlogin =new CBitmapButton();
				m_ibtnlogin->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(191, 160, 50, 30), this, 
					IDC_BTN_LOGIN);
				m_ibtnlogin->LoadBitmaps( IDB_BITMAP_LOGIN1, IDB_BITMAP_LOGIN2, IDB_BITMAP_LOGIN1, 
					IDB_BITMAP_LOGIN1);
				m_ibtnNew->SizeToContent();
				m_ibtnlogin->SizeToContent();
			}

			void CAlarm_UILogin::SetControiPosition()
			{
				m_editiD		.MoveWindow(114, 80, 144, 14, TRUE);
				m_editPassword	.MoveWindow(114, 104, 144, 14, TRUE);
			}

			void CAlarm_UILogin::UpdateDataFromJoin(CString szName, CString szPass2)
			{
				m_szName = szName;
				m_szPass2 = szPass2;
				m_editiD.SetWindowText(m_szName);
				m_editPassword.SetWindowText(szPass2);
			}


			int CAlarm_UILogin::SelectloginDB()
			{
				CString szQurryString = L"";
				CString szName = L"";
				CString szPassWord = L"";
				BOOL blslogin = false;

				m_editID.GetWindowText(szName);
				m_editPassword .GetWindowText(szPassWord);

				if(szName != L"" || szPassWord != L"" )
				{
					CDatabase db;
					if(!db.OpenEx(L"DSN=AlarmEducation", 0))
					{
						OutputDebugStr ing(L"Failed - ODBC Open\n");
					}

					CString szlnsert = L"Select lsChild , userID from userTable where userld = ",
						szQurryString.Format(L "%s '%s' and password= '%s'", szlnsert, szName, szPassWord);

					CRecordset rs(&db);
					if(!rs.Open(CRecordset::dynaset, szQurryString))
					{
						OutputDebugString(L"Failed - ODBC Qurry\n");
					}

					if(!rs.IsBOF())rs.MoveFirst();

					CString szResuIt = L"";
					CString szUserName = L"";
					//rs.GetFieIdVaIue(short(0), temp);
					whiIe(!rs.IsEOF())
					{
						blslogin = true;
						rs.GetFieldValue(short(O), szResult);
						rs.GetFieldValue(short(1), szUserName);
						rs.MoveNext();
					}
					rs.Close();
					db.Close();

					if(blslogin)
					{
						g_szUserName = szUserName;

						if(szResult == L"1")			return CHILD_USER;
						eIse if(szResuIt == L "0")		return PARENT_USER;
						)

							/*JKRegistry reg;
							reg.SetHKey(HKEY_CURRENT_USER);
							reg.SetPath(TEXT("Software\\AlarmE\\Mode"));
							reg.SetName(TEXT ("IsChiId"));

							if(szResult == L"1")
							{
							reg.Setlnteger(1);
							}
							else if(szResult == L"0")
							{
							reg.Setlnteger(O);
							}

							int nTemp = reg .Getlnteger();*/
					}
				}

				return NOTHING_USER;
				//return blslogin;
			}
			void CAlarm_UILogin::OnDestroy()
			{
				CDialog::OnDestroy();

				if(m_ibtnNew){
					m_ibtnNew->DestroyWindow();
					delete m_ibtnNew;
				}

				if(m_ibtnlogin){
					m_ibtnlogin->DestroyWindow() ;
					delete m_ibtnlogin;
				}
				OnTraylconDelete();
			}

			BOOL CAlarm_UILogin::PreTranslateMessage(MSG* pMsg)
			{
				switch(pMsg->message)
				{
				case WM_KEYDOWN:
				}
				switch(pMsg->wParam)
				{
				case VK_RETURN:
					return TRUE ;

				case VK_ESCAPE:
					return TRUE;

				}
				break;
			}
			return CDialog::PreTranslateMessage(pMsg);
		}
		void CAlarm_UILogin::OnClose()

			/////////////
		{
			ShowWindow(SW_HIDE);
			NOTIFYICONDATA nid;
			nid.cbSize = sizeof(nid);
			nid.hWnd = m_hWnd; 
			nid.uI D = 0;
			nid.uFiags = NIF_MESSAGEINIF_ICONINIF_TIP;
			nid.uCallbackMessage = UM_TRAYICON;
			nid.hlcon = AfxGetApp()->Loadlcon(IDR_MAINFRAME);
			_tcscpy(nid.szTip, _T("Alarm-e"));
			ShelI_Notifylcon(NIM_ADD,&nid);
		}


		LRESULT CAlarm_UILogin::QnTraylcon(WPARAM wParam, LPARAM IParam){
			UINT uiD = (UINT)wParam;
			UINT uMouseMsg = (UINT) IParam;
			POINT MousePos;


			switch(uMouseMsg){
			case WM_LBUTTONDOWN :
			case WM_LBUTTONDBLCLK:
				OnTraylconDelete();
				this->ShowWindow(SW_SHOW);
				break;
			}
			return 1;
		}


		void CAlarm_UILogin::QnTraylconDelete()
		{
			ShowWindow(SW_HIDE);
			NOTIFYICONDATA nid;
			nid.cbSize = sizeof(nid);
			nid.hWnd = m_hWnd; 
			nid.uID = O; 
			nid.uCallbackMessage = UM_TRAYICON;
			nid.uFiags = O;
			ShelI_Notifylcon(NIM_DELETE,&nid);
		}

