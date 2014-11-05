#pragma once
#include "afxwin.h"

// Alarm_IUCapture 대화 상자입니다.

class Alarm_IUCapture : public CDialog
{
	DECLARE_DYNAMIC(Alarm_UICapture)

	typedef enum {LOW = 0, MIDDLE, HIGH} CaptureLevel;

public:
	Alarm_UICapture(CWnd* pParent = NULL); // 표준 생성자입니다.
	virtual ~Alarm_UICapture();

	//대화 상자 데이터입니다.
	enum { IDD = IDD_ALARAME_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 지원입니다.

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


