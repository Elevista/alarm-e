#pragma once
#include "fullscreendlg.h"
#include "dbconsumer.h"


// CScreenshotDlg 대화 상자입니다.

class CScreenshotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenshotDlg)

public:
	CScreenshotDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScreenshotDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SCREEN_SHOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
