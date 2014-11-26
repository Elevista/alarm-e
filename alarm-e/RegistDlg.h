#pragma once


// CRegistDlg 대화 상자입니다.

class CRegistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegistDlg)

public:
	CRegistDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRegistDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_ID;
	CString m_PW;
	CString m_PWconfirm;
};
