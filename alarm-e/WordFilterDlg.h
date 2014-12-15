#pragma once
#include "dbconsumer.h"


// CWordFilterDlg ��ȭ �����Դϴ�.
typedef struct tagThreadParam
{
	CWnd *pWnd; // CMydlg �����͸� ���� ����
	BOOL *pDo; // CMydlg�� ������ ������ �÷��׸� ���� ������ ����
	// �� �ۿ� �ʿ��� ���� �� ����ü�� �����ϸ� �ȴ�.
} THREADPARAM;
class CWordFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWordFilterDlg)

public:
	CWordFilterDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWordFilterDlg();
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WORD_FILTER };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDo; // ������ ������ �÷���
	CWinThread *m_pThread; // ������ ������
	static UINT MyThreadFunc(LPVOID pThreadParam); // ������ �Լ� : �����Լ��� �� ���� ������, Ŭ���� �� �Լ��� �� ���� static�� �ٿ��� �Ѵ�. ������ �Լ��� �ݵ�� �� ���·� ������ �Ѵ�. ����̴�. 
	void StartThread(); // �����带 ���� ��ų ����� ���� �Լ�
 	void StopThread(); // �����带 ���� ��ų ����� ���� �Լ�
 	void MyWorkFunc(); // ������ �Լ� ������ ������ �Լ�

	afx_msg void OnBnClickedInsertWord();
	afx_msg void OnBnClickedDeleteWord();
	afx_msg void OnBnClickedWordApply();
	void Refresh(void);
	CwordFilter wordDB;
	int index;
	CBitmapButton m_btnApply;
	CBitmapButton m_btnInsert;
	CBitmapButton m_btnDelete;
	CListCtrl m_listWord;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListWord(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strWord;


	vector<CString> m_vecWords;
};
