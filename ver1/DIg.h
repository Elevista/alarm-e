// alarm-EDIg.h : ��� ����


#pragma once

#include "resource.h"
#include "afxwin.h"

// CalaarmeDIg ��ȭ ����
class CalarmeDIg : public CDialog
{
	// �����Դϴ�.
public:
	CalarmeDIg(CWnd* pParent = NULL); // ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARAME_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	HICON m_hlcon;

	//������ �޽��� �� �Լ�
virtual BOOL OnInitDialog();
afx_msg void OnSysCommand(UINT nID, LPARAM IParam);
afx_msg void OnPaint();
afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
};
