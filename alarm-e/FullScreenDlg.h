#pragma once


// CFullScreenDlg 대화 상자입니다.

class CFullScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFullScreenDlg)

public:
	CFullScreenDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFullScreenDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FULLSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_pcFullScreen;
	HBITMAP hBitmap;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
