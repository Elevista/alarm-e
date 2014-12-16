// RegistDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
#include "MultipartUpload.h"
#include "RegManager.h"

// CRegistDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegistDlg, CDialogEx)

CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegistDlg::IDD, pParent)
{
	m_ID = _T("");
	m_PW = _T("");
	m_PWconfirm = _T("");
}

CRegistDlg::~CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDV_MaxChars(pDX, m_ID, 20);
	DDX_Text(pDX, IDC_PW, m_PW);
	DDV_MaxChars(pDX, m_PW, 20);
	DDX_Text(pDX, IDC_PWconfirm, m_PWconfirm);
	DDV_MaxChars(pDX, m_PWconfirm, 20);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegistDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegistDlg 메시지 처리기입니다.


void CRegistDlg::OnBnClickedOk()
{
	UpdateData(TRUE); 
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//유효성 검사하는 부분.
	if(m_ID.IsEmpty()){
		AfxMessageBox(_T("아이디를 입력해 주세요"));
		return;
	}else if(m_PW.IsEmpty()){
		AfxMessageBox(_T("패스워드를 입력해 주세요"));
		return;
	}else if(!onlyASCIIcheck(m_ID)){
		AfxMessageBox(_T("아이디는 영어 숫자 기호만 써주세요"));
		return;
	}else if(!onlyASCIIcheck(m_PW)){
		AfxMessageBox(_T("패스워드는 영어 숫자 기호만 써주세요"));
		return;
	}else if(m_PWconfirm.IsEmpty()){
		AfxMessageBox(_T("패스워드 확인을 입력해 주세요"));
		return;
	}else if(m_PW.Compare(m_PWconfirm)){
		AfxMessageBox(_T("패스워드가 일치하지 않습니다."));
		return;
	}
	
	/*
		이부분에 서버로 보내는 내용 들어갈 예정.
	*/
	CString response;
	response.Format(_T("서버가 말하길: %s"),MultipartUpload::join(m_ID,m_PW));
	if(response.Compare(_T("서버가 말하길: ok"))==0){
		AfxMessageBox(_T("회원가입 성공"));
		//디비에 등록
		loginDB.Open();
		loginDB.AddNew();	//새 레코드 추가
		loginDB.m_ID=m_ID;	//아이디 넣고
		loginDB.m_PW=m_PW;	//패스워드 넣고
		loginDB.Update();	//커밋
		//레지스트리에 등록
		CRegManager::SetID(m_ID);
		ID=m_ID;	//전역변수에도 등록.
		::SetAuthority(true);//로그인 상태. 메모리맵 등록.
	}else{
		AfxMessageBox(response);
		if(loginDB.IsOpen())loginDB.Close();
		return;
	}
	if(loginDB.IsOpen())loginDB.Close();
	CDialogEx::OnOK();
}


bool CRegistDlg::onlyASCIIcheck(CString str)
{
	long nLen = str.GetLength();
 	for( long i=0 ; i < nLen ; ++i)
	{
	   BYTE tt = str.GetAt(i);

	   if( IsDBCSLeadByte(tt) )
	   {
		   return false;
	   }
	}
	return true;
}