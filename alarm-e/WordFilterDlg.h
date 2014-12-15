#pragma once
#include "dbconsumer.h"


// CWordFilterDlg 대화 상자입니다.

class CWordFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWordFilterDlg)

public:
	CWordFilterDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWordFilterDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORD_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
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
};
