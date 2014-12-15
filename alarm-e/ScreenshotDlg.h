#pragma once
#include "fullscreendlg.h"
#include "dbconsumer.h"


// CScreenshotDlg ��ȭ �����Դϴ�.

class CScreenshotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenshotDlg)

public:
	CScreenshotDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScreenshotDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SCREEN_SHOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_editSsFrequency;
	CSpinButtonCtrl m_spinSsFrequency;
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedPcSsPreview();
	CBitmapButton m_btnApply;
	CBitmapButton m_btnZoom;
	CBitmapButton m_btnDelete;
	CButton m_chkScreenShot;
	afx_msg void OnBnClickedApply();
	CListCtrl m_listScreenShot;
	void Refresh(void);
	afx_msg void OnLvnItemchangedListScreenshot(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_pcPreview;
	afx_msg void OnBnClickedZoom();
	CFullScreenDlg zoomDlg;
	int index;
	afx_msg void OnBnClickedDelete();
	CcaptureImageDB imgDB;
	afx_msg void OnBnClickedWebLink();
	CBitmapButton m_btnWebLink;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
