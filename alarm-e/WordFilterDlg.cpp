// WordFilterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"
#include "DBconsumer.h"


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
	DDX_Control(pDX, IDC_WORD_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_INSERT_WORD, m_btnInsert);
	DDX_Control(pDX, IDC_DELETE_WORD, m_btnDelete);
	DDX_Control(pDX, IDC_LIST_WORD, m_listWord);
	DDX_Text(pDX, IDC_EDIT1, m_strWord);
	DDV_MaxChars(pDX, m_strWord, 20);
}


BEGIN_MESSAGE_MAP(CWordFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_INSERT_WORD, &CWordFilterDlg::OnBnClickedInsertWord)
	ON_BN_CLICKED(IDC_DELETE_WORD, &CWordFilterDlg::OnBnClickedDeleteWord)
	ON_BN_CLICKED(IDC_WORD_APPLY, &CWordFilterDlg::OnBnClickedWordApply)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WORD, &CWordFilterDlg::OnLvnItemchangedListWord)
END_MESSAGE_MAP()


// CWordFilterDlg 메시지 처리기입니다.


void CWordFilterDlg::OnBnClickedInsertWord()
{
	UpdateData(true);
	if(m_strWord.IsEmpty())return;
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


void CWordFilterDlg::OnBnClickedWordApply()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CWordFilterDlg::Refresh(void)
{
	if(wordDB.IsOpen()){wordDB.Close();wordDB.Open();}
	else{wordDB.Open();}
	index=-1;
	m_listWord.DeleteAllItems();
	CString word;

	//!!!
	if(wordDB.IsEOF())return; //비어있으면 아무것도 안함
	wordDB.MoveLast();	//마지막부터
	while(!wordDB.IsBOF()){	//첫 결과까지
		word.Format(_T("%s"),(CString)wordDB.m_word);	//(CString)wordDB.m_word가 해당 단어 값
		m_listWord.InsertItem(0,word);	
		wordDB.MovePrev();	//결과 하나 전으로 이동
	}
}


BOOL CWordFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listWord.InsertColumn(0, _T("단어"), LVCFMT_LEFT, 250, -1);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CWordFilterDlg::OnLvnItemchangedListWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	index=pNMLV->iItem;	//현재 선택 아이템의 인덱스를 저장
	*pResult = 0;
}
