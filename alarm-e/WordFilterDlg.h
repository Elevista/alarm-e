#pragma once
#include "dbconsumer.h"


// CWordFilterDlg 대화 상자입니다.
typedef struct tagThreadParam
{
	CWnd *pWnd; // CMydlg 포인터를 담을 변수
	BOOL *pDo; // CMydlg의 쓰레드 정지용 플래그를 담을 포인터 변수
	// 그 밖에 필요한 것을 이 구조체에 선언하면 된다.
} THREADPARAM;
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
	BOOL m_bDo; // 쓰레드 정지용 플래그
	CWinThread *m_pThread; // 쓰레드 포인터
	static UINT MyThreadFunc(LPVOID pThreadParam); // 쓰레드 함수 : 전역함수로 할 수도 있지만, 클래스 내 함수로 할 경우는 static을 붙여야 한다. 쓰레드 함수는 반드시 이 형태로 만들어야 한다. 약속이다. 
	void StartThread(); // 쓰레드를 시작 시킬 사용자 정의 함수
 	void StopThread(); // 쓰레드를 정지 시킬 사용자 정의 함수
 	void MyWorkFunc(); // 쓰레드 함수 내에서 실행할 함수

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
