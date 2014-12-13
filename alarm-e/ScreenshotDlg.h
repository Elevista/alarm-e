#pragma once


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
};
