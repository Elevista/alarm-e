#pragma once
#include "afxwin.h"

// Alarm_IUCapture ��ȭ �����Դϴ�.

class Alarm_IUCapture : public CDialog
{
	DECLARE_DYNAMIC(Alarm_UICapture)

	typedef enum {LOW = 0, MIDDLE, HIGH} CaptureLevel;

public:
	Alarm_UICapture(CWnd* pParent = NULL); // ǥ�� �������Դϴ�.
	virtual ~Alarm_UICapture();

	//��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARAME_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	CBitmapButton* m_ibtnCancel;
	CBitmapButton* m_ibtnOK;
	int m_nCaptureLevel;

	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	void SetBitmapButton();
	void SetControlPosition();
	void SetComponentData();
	void SetCaptureLevel();
	void SetImgBtnFocus();
	void SetCheckMode();


	void OnBnClickedBtnHigh();
	void OnBnClickedBtnMiddle();
	void OnBnClickedBtnLow();
	afx_msg void OnBnClickedBtnOK();
	afx_msg void OnBnClickedBtnCancel();

	CComboBox m_comboMinute;
	CButton m_chHigh;
	CButton m_chMiddle;
	CButton m_chLow;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
};


