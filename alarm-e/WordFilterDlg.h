#pragma once


// CWordFilterDlg ��ȭ �����Դϴ�.

class CWordFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWordFilterDlg)

public:
	CWordFilterDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWordFilterDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WORD_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
