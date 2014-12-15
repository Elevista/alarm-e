// WordFilterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "alarm-e.h"
#include "WordFilterDlg.h"
#include "afxdialogex.h"
#include "DBconsumer.h"
#include <vector>

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


// CWordFilterDlg �޽��� ó�����Դϴ�.


void CWordFilterDlg::OnBnClickedInsertWord()
{
	UpdateData(true);
	if(m_strWord.IsEmpty())return;
	
	for(unsigned i=0;i<m_vecWords.size();i++){
		if(strcmp(m_strWord,m_vecWords[i])==0){	//(CString)wordDB.m_word�� �ش� �ܾ� ��
			AfxMessageBox("�̹� �ֽ��ϴ�.");
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
	m_listWord.DeleteAllItems();	//����Ʈ �������� �� �����
	m_vecWords.clear();	//���� �������� �� �����
	CString word;

	//!!!
	if(wordDB.IsEOF())return; //��������� �ƹ��͵� ����
	wordDB.MoveLast();	//����������
	
	while(!wordDB.IsBOF()){	//ù �������
		word.Format(_T("%s"),(CString)wordDB.m_word);	//(CString)wordDB.m_word�� �ش� �ܾ� ��
		m_vecWords.push_back((CString)wordDB.m_word);	//���Ϳ� �߰�
		m_listWord.InsertItem(0,word);	//����Ʈ�� �߰�
		wordDB.MovePrev();	//��� �ϳ� ������ �̵�
	}
}


BOOL CWordFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listWord.InsertColumn(0, _T("�ܾ�"), LVCFMT_LEFT, 250, -1);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	m_btnInsert.LoadBitmaps(IDB_INSERT);
	m_btnInsert.SizeToContent();
	Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CWordFilterDlg::OnLvnItemchangedListWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	index=pNMLV->iItem;	//���� ���� �������� �ε����� ����
	*pResult = 0;
}
UINT CWordFilterDlg::MyThreadFunc(LPVOID pThreadParam)
{
	// �Ѿ� �� �Ķ���Ͱ� void �� ������ �̹Ƿ� THREADPARAM �� �����ͷ� �ݵ�� ĳ�����ؾ� �Ѵ�.
	THREADPARAM *pParam = (THREADPARAM *)pThreadParam;
	CWordFilterDlg *pMydlg = (CWordFilterDlg *) pParam->pWnd; // �̰� ���� ĳ���� �ؾ� �Ѵ�.
	BOOL *pDo = pParam->pDo; // �̰��� ���� Ÿ���̹Ƿ� ĳ���� �ʿ� ����.
	// ������ �ʿ��� �����͸� ��� ������� ���� ������ pParam�� ��������(?) �����ؾ� �޸� ������ ����.
	delete pParam;

	// *pDo�� TRUE�� ���� �����尡 �۾��� �Ѵ�.
	while ( *pDo ) 
	{
		pMydlg->MyWorkFunc(); // ���ϴ� �۾��� �Ѵ�.
		// ��Ÿ ���ϴ� �۾��� �̰��� ������ �ȴ�.
		Sleep(1000); //1�� ����
	}
	return 0; // �ݵ�� ������ �ؾ� �Ѵ�. 0���� ���� �ϴ� ���� ������ ����̴�.
}
void CWordFilterDlg::MyWorkFunc()
{
	CString temp =  GetTypedWord();
	for(unsigned i=0;i<m_vecWords.size();i++){
		if(temp.Find(m_vecWords[i])>=0){	//(CString)wordDB.m_word�� �ش� �ܾ� ��
			::ClearTypedWord();
			AfxMessageBox(m_vecWords[i] + "��(��) ��Ӿ� �Դϴ�.\n ����� ������ �ּ���\n", MB_OK | MB_SYSTEMMODAL);
		}
	}
}
void CWordFilterDlg::StartThread()
{
	// �������Լ��� �Ķ���ͷ� �� ����ü�� �������� �����Ѵ�.
	THREADPARAM *pThreadParam = new THREADPARAM;
	pThreadParam->pWnd = this; // ���⼭ this�� CMydlg ��ü�� �ǹ��Ѵ�.
	pThreadParam->pDo = &m_bDo; // �÷��� �����͸� ��´�.
	// AfxBeginThread �Լ��� �����尡 �����Ǿ� ����ȴ�.
	m_pThread = AfxBeginThread(MyThreadFunc, pThreadParam);
}

 void CWordFilterDlg::StopThread()
{
	m_bDo = FALSE; // ������ ���� ��Ű�� ���� FALSE�� �Է��Ѵ�.
	// ������ �÷��� ���� �Է������� �Ʒ� �Լ��� �����尡 ���� ������ ��ٷ� �ش�.
	Sleep(1500);
	if ( ::WaitForSingleObject(m_pThread->m_hThread, INFINITE )) // INFINITE�� ������ ��ٷ� �شٴ� �ǹ̴�.
	{
		// �����尡 ������ �� ������ ���´�.
		m_pThread = NULL; // ���� ������� �����.
		// ������ ������ �� �͵��� ���⿡ ������ �ȴ�.

	}
}



 BOOL CWordFilterDlg::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	 //Ű���� �޽����� ���ö� esc�̰ų� return  ���̸�
	//�� ���� �����ش�.
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
	if(pMsg->message == WM_SYSKEYDOWN)	//�˶߿��ڻ�
	{
		if(pMsg->wParam == VK_F4)
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
 }
