#pragma once


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
};
