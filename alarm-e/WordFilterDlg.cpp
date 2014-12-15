// WordFilterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"
#include "DBconsumer.h"


// CWordFilterDlg ��ȭ �����Դϴ�.

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


// CWordFilterDlg �޽��� ó�����Դϴ�.


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
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CWordFilterDlg::Refresh(void)
{
	if(wordDB.IsOpen()){wordDB.Close();wordDB.Open();}
	else{wordDB.Open();}
	index=-1;
	m_listWord.DeleteAllItems();
	CString word;

	//!!!
	if(wordDB.IsEOF())return; //��������� �ƹ��͵� ����
	wordDB.MoveLast();	//����������
	while(!wordDB.IsBOF()){	//ù �������
		word.Format(_T("%s"),(CString)wordDB.m_word);	//(CString)wordDB.m_word�� �ش� �ܾ� ��
		m_listWord.InsertItem(0,word);	
		wordDB.MovePrev();	//��� �ϳ� ������ �̵�
	}
}


BOOL CWordFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listWord.InsertColumn(0, _T("�ܾ�"), LVCFMT_LEFT, 250, -1);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CWordFilterDlg::OnLvnItemchangedListWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	index=pNMLV->iItem;	//���� ���� �������� �ε����� ����
	*pResult = 0;
}
