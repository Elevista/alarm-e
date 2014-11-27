#pragma once
#include "Resource.h"
#include "afxwin.h"

class CalarmeDlg : public CDialog {
public :
	CalarmeDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_ALARAME_LOGIN };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

};