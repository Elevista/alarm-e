//Alarm_UIJoin.cpp

#include "stdafx.h"
#include "Alarm-e.h"
#include "Alarm_UIJoin.h"
#include "Alarm_UILogin.h"

IMPLEMENT_DYNAMIC(CAlarm_UIJoin, CDialog)

	CAlarm_UIJoin::CAlarm_UIJoin(CWnd* pParent /*=NULL*/)
	:CDialog(CAlarm_UIJoin::IDD, pParent)
{

}
CAlarm_UIJoin : :-CAiarm_UIJoin()
				{

				}

				void CAlarm_UIJoin::DoDataExchange(CDataExchange* pDX)
				{
					CDialog::DoDataExchange(pDX);
					DDX_Control(pDX, IDC_EDIT1, m_editName);
					DDX_Control(pDX, IDC_EDIT.2, m_editNumber1);
					DDX_Control(pDX, IDC_EDIT3, m_editNumber2);
					DDX_Control(pDX, IDC_EDIT4, m_editSchool);
					DDX_Control(pDX, IDC_EDIT5, m_editGrade);
					DDX_Control(pDX, IDC_COMB01, m_comboFamilyPosition);
				}

				BEGIN_MESSAGE_MAP(CAlarm_UIJoin, CDialog)
					ON_WM_PAINT()
					ON_WM_DESTROY()
					ON_BN_CLICKED( IDC_BTN_JOIN, &CAiarm_UIJoin: :OnBnCI ickedBtnJoin)
					ON_BN_CLICKED( IDC_BTN_CANCEL, &CAiarm_UIJoin: :OnBnCI ickedBtnCancel)
					ON_EN_UPDATE( IDC_EDIT2, &CAiarm_UIJoin: :OnEnUpdateEdit2)
					ON_EN_UPDATE( IDC_EDIT3, &CAiarm_UIJoin: :OnEnUpdateEdit3)
				END_MESSAGE_MAP()

				BOOL CAlarm_UIJoin::OnlnitDialog()
				{
					CDialog::QnlnitDialog();

					MoveDigCenter(m_hWnd, 486, 420);

					SetBitmapButton();

					SetControiPosition();
					SetComboData();

					return TRUE; // return TRUE unless you set the focus to a control
				}
				void CAlarm_UIJoin::SetBitmapButton()
				{
					m_ibtnJoin =new CBitmapButton();
					m_ibtnJoin->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(264,344,50,30 }, this, 
						IDC_BTN_JO IN) ;
					m_ibtnJoin->LoadBitmaps(IDB_BITMAP_JOINOK2, IDB_BITMAP_JOINOK1, IDB_BITMAP_JOINOK2, 
						IDB_BITMAP_JOINOK2);
					m_ibtnCancel =new CBitmapButton();
					m_ibtnCancei->Create(NULL, WS_CHILDIWS_VISIBLE I BS_OWNERDRAW, CRect(350,344, 50, 30) , th is, 
						IDC_BTN_CANCEL) ;
					m_ibtnCancei - >LoadBitmaps( IDB_BITMAP_JOINCANCEL2 , IDB_BITMAP_JOINCANCEL1, IDB_BITMAP_JOINCANCEL2,
						IDB_BITMAP_JOINCANCEL2) ;


					m_ibtnJoin->SizeToContent();
					m_ibtnCancei->SizeToContent();
}

void CAlarm_UIJoin::SetComboData()
{
	m_comboFamilyPosition.lnsertString(O, L "아버지");
	m_comboFamiIyPosition.Inser tString(1, L"어머니");
	m_comboFamilyPosition.lnsertString(2, L "아들");
	m_comboFamilyPosition.lnsertString(3, L"딸");

	m_comboFamilyPosition.SetCurSei(O);
}


void CAlarm_UIJoin::SetControiPosition()
{
	m_editName					.MoveWindow(111, 86, 85, 15) ;
	m_edit Number 1				.MoveWindow(163, 134, 85, 15);
	m_edit Number 2				.MoveWindow(261, 134, 85, 15);
	m_editSchool				.MoveWindow(111, 182, 85, 15);
	m_editGrade					.MoveWindow(111, 230 , 85, 15);
	m_comboFamilyPosition		.MoveWindow(137, 278 , 85, 15);
}

void CAlarm_UIJoin::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	HBITMAP hBitmap = LoadBitmap(AfxGetlnstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_JOIN));

	DrawlmageBitBit(dc.m_hDC,hBitmap,O,O) ;
}

void CAlarm_UIJoin::onDestroy()
{
	CDialog::OnDestroy();

	if(m_ibtnJoin){
		m_ibtnJoin->DestroyWindow();
		delete m_ibtnJoin ;
	}

	if(m_ibtnCancel){
		m_ibtnCancei->DestroyWindow();
		delete m_ibtnCancel;

	}

}

void CAlarm_UIJoin::OnBnCI ickedBtnJoin()
{
	try
	{
		if(InsertJoinDB())
		{
			OnOK();
			//CAiarm_UILogin dig;
			//INT_PTR nResponse = dlg.DoModal();
			//if (nResponse == IDOK) {}//자녀모드
		}
	}
	catch (CException* e)
}
WCHAR szError[255] = L"";
e->GetErrorMessage(szError, sizeof(szError));
OutputDebugString(L"Insert Failed - Join\n");
OutputDebugString(szError);
OutputDebugString(L"\n");
BOOL CAlarm_UIJoin::lnsertJoinDB()
{
	CString szQurryString = L "";
	CString szUserID =L"";
	CString szFamiIyPosition = L"";
	CString szPassWord =L"";
	CString szYearTwo = L"";
	CString szEdit1 = L"";
	CString szDate = L"";
	CString szCurrentYear = L"";
	CString szCurrentYearTwo = L"";
	CString szNumber20ne = L"";

	int nAge = O;
	int nYearTwo = O;
	int nCurrentYear = O;
	int nCurrentYearTwo = O;

	m_editName.GetWindowText(szUserID);
	m_comboFamilyPosition.GetWindowText(szFamilyPosition);
	m_editNumber2.GetWindowText(szPassWord);
	m_editNumber1.GetWindowText(szEdit1);

	CString szJumin = L "";
	szJumin.Format(L "%s%s", szEdit1, szPassWord);
	if(szUserID != L"" && szEdit1 != L"" && szPassWord != L"")
	{
		//if(VenrifyJunimNumber(szJumin))
		{
			COleDateTime tToday = COleDateTime::GetCurrentTime();
			szDate= tToday.Format(L"%Y-%m-%d");
			szYearTwo = szEdit1.Mid(O, 2);
			szCurrentYear = szDate.Mid(O, 4);
			szCurrentYearTwo = szCurrentYear.Mid(2,4);
			szNumber20ne = szPassWord.Mid(0,1);


			////////////////////////////////////
			nYearTwo = _ttoi(szYearTwo);
			nCurrentYearTwo = _ttoi(szCurrentYearTwo);
			nCurrentYear = _ttoi(szCurrentYear);

			if(nCurrentYearTwo - nYearTwo >= 0 && (szNumber20ne == L"3" || szNumber20ne == L"4" )) 
			{
				nAge = nCurrentYearTwo - nYearTwo;
			}
			else
			{
				nAge = nCurrentYearTwo - nYearTwo + 100;
			}


			if(szFamilyPosition == L"어머니" II szFamilyPosition == "아버지" )
				szFamiIyPosition = L"true";
			else
				szFamiIyPosition = L"true";


			CDatabase db;
			if(!db.OpenEx(L"DSN=AlarmEducation", 0))
			{
				OutputDebugString(L"Failed- ODBC Open\n");
			}

			CString szlnsert = L"INSERT INTO userTable (userID, password, savedDate, age, lsChild) 
				VALUES (" ;
				szQurryString.Format(L"%s '%s ' , '%s ' , '%s ' , %d, %s)", szlnsert, szUseriD, szPassWord,
				szDate, nAge, szFamilyPosition);

			db.ExecuteSQL(szQurryString);
			db.Ciose();

			//((Aiarm_U ILogin*)this->GetParent())
			((CAlarm~UILogin*)this->GetParent())->UpdateDataFromJoin(szUserID, szPassWord );

			return TRUE ;
		}
		/*else
		{
		MessageBox( L"잘못된 주민등록번호 입니다. 다시 확인해주세요.");
		}*/
	}
	else
	{
		MessageBox(L"항목을 모두 기입해주세요.");
	}
	return FALSE;

}

BOOL CAlarm_UIJoin::VenrifyJunimNumber(CString szJuminNumber)
{
	const int tab[]= {2,3,4,5,6,7,8,9,2,3,4,5};

	int number[13];

	for( int i=O ; i<13; i++)
	{
		number[i] = _ttoi(szJuminNumber .Mid(i,1));
	}
	///////////////////////////
	int sum= O;
	int i = 0;
	for(i=O ; i<12 ; i++)
		sum+= number[i] * tab[i];

	return ((11-(sum%11))%10 == number[12])? TRUE:FALSE;
}

void CAlarm_UIJoin::QnBnCIickedBtnCancel()
{
	OnOK();
}
BOOL CAiarm_UIJoin: :PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message) 
	{
	case WM_KEYDOWN:

		if(IDC_EDIT2 == GetFocus()->GetDigCtrlID())
		{
			CString szText = L"";
			m_editNumber1.GetWindowText(szText);
			if(szText.Getlength() >= 6 && pMsg->IParam != 917505)
			{
				m_editNumber2.SetFocus();
				return TRUE;
			}
		}
		else if( IDC_EDIT3 == GetFocus()->GetDigCtrlID())
		{
			CString szText = L"";
			m_editNumber2.GetWindowText(szText);
			if(szText.Getlength() >= 7 && pMsg->IParam != 917505)
			{
				m_editSchool.SetFocus();
				return TRUE;
			}
		}

		switch(pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;

		case VK_ESCAPE:
			return TRUE;
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CAlarm_UIJoin::QnEnUpdateEdit2()
{
	CString szText = L"";
	m_editNumber1.GetWindowText(szText);
	if(szText.Getlength() >= 6)
	{
		m_editNumber2.SetFocus();
	}
}

void CAlarm_UIJoin::OnEnUpdateEdit3()
{
	CString szText = L "";
	m_editNumber2.GetWindowText(szText);
	if(szText.GetLength() >= 7)
	{
		m_editSchool.SetFocus();
	}
}