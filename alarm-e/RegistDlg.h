#pragma once


// CRegistDlg ��ȭ �����Դϴ�.

class CRegistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegistDlg)

public:
	CRegistDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegistDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_ID;
	CString m_PW;
	CString m_PWconfirm;
};
