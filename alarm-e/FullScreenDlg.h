#pragma once


// CFullScreenDlg ��ȭ �����Դϴ�.

class CFullScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFullScreenDlg)

public:
	CFullScreenDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFullScreenDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FULLSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_pcFullScreen;
	HBITMAP hBitmap;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
