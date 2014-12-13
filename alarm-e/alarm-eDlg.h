
// alarm-eDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "WordFilterDlg.h"
#include "ScreenshotDlg.h"

// CalarmeDlg ��ȭ ����
class CalarmeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CalarmeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void SetTray(void);
	afx_msg LRESULT TrayMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Login(void);
	void Logout(void);
	void ShowDlg(void);
	void ColseDlg(void);
	afx_msg void OnBnClickedClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	CBitmapButton m_btnX;
	afx_msg void OnBnClickedWordFilter();
	void SwitchChildDlg(int num);
	CWordFilterDlg wordFilterDlg;
	afx_msg void OnBnClickedSiteBlock();
	CScreenshotDlg screenshotDlg;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedScreenShot();
	CBitmapButton m_btnScreenShot;
	CBitmapButton m_btnSiteBlock;
	CBitmapButton m_btnWordFilter;
};
