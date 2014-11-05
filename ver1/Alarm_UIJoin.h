#pragma once
#include "afxwin.h"

// CAlarm_UIJoin ��ȭ �����Դϴ�.

class CAlarm_UIJoin : public CDialog
{
	DECLARE_DYNAMIC(CAlarm_UIJoin)

public:
	CAlarm_UIJoin(CWnd* pParent = NULL); //ǥ�� �������Դϴ�.
	virtual ~CAlarm_UIJoin();

	//��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARAME_JOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDx); // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void SetBitmapButton();
	void SetControlPosition();
	BOOL InsertJoinDB();
	void SetComboData();
	afx_msg void OnBnClickedBtnJoin();
	afx_msg void OnBnClickedBtnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL VenrifyJunimNumber(CString szJuminNumber);

	CEdit m_editName;
	CEdit m_editNumber1;
	CEdit m_editNumber2;
	CEdit m_editSchool;
	CEdit m_editSchool;
	CEdit m_editGrade;
	CComboBox m_comboFamilyPosition;

	CBitmapButton* m_ibtnJoin;
	CBitmapButton* m_ibtnCancel;
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();

	afx_msg void OnEnUpdateEdit2();
	afx_msg void OnEnUpdateEdit3();
};