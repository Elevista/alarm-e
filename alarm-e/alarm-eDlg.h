
// alarm-eDlg.h : ��� ����
//

#pragma once


// CalarmeDlg ��ȭ ����
class CalarmeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CalarmeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void SetTray(void);
	afx_msg LRESULT TrayMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
};
