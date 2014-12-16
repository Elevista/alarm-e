
// SimpleFireWallDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSimpleFireWallDlg 대화 상자
class CSimpleFireWallDlg : public CDialogEx
{
// 생성입니다.
public:
	CSimpleFireWallDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SIMPLEFIREWALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
//	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	

	virtual BOOL OnInitDialog();
	CListCtrl m_blockListBox;
	afx_msg void OnBnClickedBtnAdd();
	
	CString m_siteEdit;
	CString m_detailEdit;
	CString m_forwardIp;
	CString m_hostsPath;
	CString m_fakeHostsPath;
	void siteAdd();
	afx_msg void OnBnClickedBtnDel();
	TCHAR windir[MAX_PATH];

	CBitmapButton m_btnAdd;
	CBitmapButton m_btnDelete;
	CBitmapButton m_btnX;
	afx_msg void OnBnClickedBtnX();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
