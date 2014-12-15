// WordFilterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"
#include "DBconsumer.h"
#include <vector>

// CWordFilterDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWordFilterDlg, CDialogEx)

	CWordFilterDlg::CWordFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWordFilterDlg::IDD, pParent)
	, index(-1)
{
	SetBackgroundColor(RGB(255,255,255));
	m_strWord = _T("");
}

CWordFilterDlg::~CWordFilterDlg()
{
}

void CWordFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERT_WORD, m_btnInsert);
	DDX_Control(pDX, IDC_DELETE_WORD, m_btnDelete);
	DDX_Control(pDX, IDC_LIST_WORD, m_listWord);
	DDX_Text(pDX, IDC_EDIT1, m_strWord);
	DDV_MaxChars(pDX, m_strWord, 20);
}


BEGIN_MESSAGE_MAP(CWordFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_INSERT_WORD, &CWordFilterDlg::OnBnClickedInsertWord)
	ON_BN_CLICKED(IDC_DELETE_WORD, &CWordFilterDlg::OnBnClickedDeleteWord)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WORD, &CWordFilterDlg::OnLvnItemchangedListWord)
END_MESSAGE_MAP()


// CWordFilterDlg 메시지 처리기입니다.


void CWordFilterDlg::OnBnClickedInsertWord()
{
	UpdateData(true);
	if(m_strWord.IsEmpty())return;
	
	for(unsigned i=0;i<m_vecWords.size();i++){
		if(strcmp(m_strWord,m_vecWords[i])==0){	//(CString)wordDB.m_word가 해당 단어 값
			AfxMessageBox("이미 있습니다.");
			return;
		}
	}
	wordDB.AddNew();
	wordDB.m_word=m_strWord;
	wordDB.Update();
	Refresh();
}


void CWordFilterDlg::OnBnClickedDeleteWord()
{
	if(index==-1) return;
	if(wordDB.IsEOF())return;
	wordDB.MoveFirst();
	wordDB.Move(index);
	if(!wordDB.IsEOF()&&!wordDB.IsBOF()){
		wordDB.Delete();
		Refresh();
	}
}





void CWordFilterDlg::Refresh(void)
{
	if(wordDB.IsOpen()){wordDB.Close();wordDB.Open();}
	else{wordDB.Open();}
	index=-1;
	m_listWord.DeleteAllItems();	//리스트 갱신위해 다 지우기
	m_vecWords.clear();	//백터 갱신위해 다 지우기
	CString word;

	//!!!
	if(wordDB.IsEOF())return; //비어있으면 아무것도 안함
	wordDB.MoveLast();	//마지막부터
	
	while(!wordDB.IsBOF()){	//첫 결과까지
		word.Format(_T("%s"),(CString)wordDB.m_word);	//(CString)wordDB.m_word가 해당 단어 값
		m_vecWords.push_back((CString)wordDB.m_word);	//벡터에 추가
		m_listWord.InsertItem(0,word);	//리스트에 추가
		wordDB.MovePrev();	//결과 하나 전으로 이동
	}
}


BOOL CWordFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listWord.InsertColumn(0, _T("단어"), LVCFMT_LEFT, 250, -1);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	m_btnInsert.LoadBitmaps(IDB_INSERT);
	m_btnInsert.SizeToContent();
	Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CWordFilterDlg::OnLvnItemchangedListWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	index=pNMLV->iItem;	//현재 선택 아이템의 인덱스를 저장
	*pResult = 0;
}
UINT CWordFilterDlg::MyThreadFunc(LPVOID pThreadParam)
{
	// 넘어 온 파라미터가 void 형 포인터 이므로 THREADPARAM 형 포인터로 반드시 캐스팅해야 한다.
	THREADPARAM *pParam = (THREADPARAM *)pThreadParam;
	CWordFilterDlg *pMydlg = (CWordFilterDlg *) pParam->pWnd; // 이것 또한 캐스팅 해야 한다.
	BOOL *pDo = pParam->pDo; // 이것은 같은 타입이므로 캐스팅 필요 없다.
	// 변수에 필요한 포인터를 모두 담았으니 동적 생성된 pParam을 동적으로(?) 삭제해야 메모리 누수가 없다.
	delete pParam;

	// *pDo가 TRUE일 동안 쓰레드가 작업을 한다.
	while ( *pDo ) 
	{
		pMydlg->MyWorkFunc(); // 원하는 작업을 한다.
		// 기타 원하는 작업을 이곳에 넣으면 된다.
		Sleep(1000); //1초 마다
	}
	return 0; // 반드시 리턴을 해야 한다. 0으로 리턴 하는 것은 일종의 약속이다.
}
void CWordFilterDlg::MyWorkFunc()
{
	CString temp =  GetTypedWord();
	for(unsigned i=0;i<m_vecWords.size();i++){
		if(temp.Find(m_vecWords[i])>=0){	//(CString)wordDB.m_word가 해당 단어 값
			::ClearTypedWord();
			AfxMessageBox(m_vecWords[i] + "는(은) 비속어 입니다.\n 사용을 자제해 주세요\n", MB_OK | MB_SYSTEMMODAL);
		}
	}
}
void CWordFilterDlg::StartThread()
{
	// 쓰레드함수의 파라미터로 쓸 구조체를 동적으로 생성한다.
	THREADPARAM *pThreadParam = new THREADPARAM;
	pThreadParam->pWnd = this; // 여기서 this는 CMydlg 객체를 의미한다.
	pThreadParam->pDo = &m_bDo; // 플래그 포인터를 담는다.
	// AfxBeginThread 함수로 쓰레드가 생성되어 실행된다.
	m_pThread = AfxBeginThread(MyThreadFunc, pThreadParam);
}

 void CWordFilterDlg::StopThread()
{
	m_bDo = FALSE; // 쓰레드 정지 시키기 위해 FALSE를 입력한다.
	// 정지용 플래그 값을 입력했으니 아래 함수로 쓰레드가 끝날 때까지 기다려 준다.
	Sleep(1500);
	if ( ::WaitForSingleObject(m_pThread->m_hThread, INFINITE )) // INFINITE는 무한정 기다려 준다는 의미다.
	{
		// 쓰레드가 끝나면 이 속으로 들어온다.
		m_pThread = NULL; // 죽은 쓰레드니 비우자.
		// 쓰레드 끝나고 할 것들을 여기에 넣으면 된다.

	}
}



 BOOL CWordFilterDlg::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	 //키눌린 메시지가 들어올때 esc이거나 return  값이면
	//걍 리턴 시켜준다.
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_ESCAPE:
			case VK_CANCEL:
			return TRUE;
			case VK_RETURN:{OnBnClickedInsertWord();return TRUE;}
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
