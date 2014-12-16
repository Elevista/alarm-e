
// SimpleFireWallDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSimpleFireWallDlg ��ȭ ����
class CSimpleFireWallDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSimpleFireWallDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SIMPLEFIREWALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
