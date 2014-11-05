#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "alarm-eDIg.h"
#include "DBDataForm.h"
#include "MessageForm.h"

// CAlram_UIParent 대화 상자입니다.

class CAlarm_UIParent : public Cdialog
{
	DECLARE_DYNAMIC(CAlaram_UIParent)
	typedef enum {WILLSEND = 0, SENDED, RECIEVE} MESSAGEMODE;

	typedef enum {PAPRENT_TIMESET= 0, PARENT_BANURLSET, PARENT_CAPTURE, PARENT_USEINFO, PARENT_BANWORDSET, PARENT_MESSAGE} DIgMode;
public:
	CAlarm_UIParent(CWnd* pParent = NULL); // 표준 생성자입니다.
	virtual ~CAlarm_UIParent();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALARAME_PARENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV지원입니다.
	int m_nMode;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetImageButtonMode();
	void SetModeVisible(BOOL bVisible);
	void SetModeVisible(BOOL bVisible, int nMode);
	void DrawBackgroundImage(HDC hDC);
	void UpdateBanWordData();

	//TIMESET MODE
	void SetPositionTimeSet();
	void SetCheckLabelTimeSet();
	void GetTimeSetData();
	void SetP1BtnVisible();

	//BANURL MODE
	void SetListCtrlBanURL();
	void SetPositionBanURL();

	//CALENDER MODE
	void SetPositionCapture();

	//USERINFO MODE
	void SetListCtrlUserInfo();
	void SetPositionUserInfo();

	//BANWORD MODE
	void SetListCtrlBanWord();
	void SetPositionBanWord();

	//MESSAGE MODE
	void SetListCtrlMessage();
	void SetPositionMessage();
	void SetCheckLabelMessage();

	CBitmapButton* m_ibtnTimeSet;
	CBitmapButton* m_ibtnBanURLSet;
	CBitmapButton* m_ibtnCapture;
	CBitmapButton* m_ibtnUseInfo;
	CBitmapButton* m_ibtnBanWordSet;
	CBitmapButton* m_ibtnMessage;

	/* 1 - save
	2 - save, delete 
	3 - delete, capture
	4 - x
	5 - save, delete
	6 - save*/
	bool m_bIsUseTimeEdit Mode;

	CBitmapButton* m_ibtn1_save;
	CBitmapButton* m_ibtn1_cancel;
	CBitmapButton* m_ibtn1_repair;

	CBitmapButton* m_ibtn2_save;
	CBitmapButton* m_ibtn2_delete;
	CBitmapButton* m_ibtn3_captureSetting;
	CBitmapButton* m_ibtn3_delete;
	CBitmapButton* m_ibtn5_save;
	CBitmapButton* m_ibtn5_delete;
	CBitmapButton* m_ibtn6_save;
	CBitmapButton* m_ibtn6_delete

		CBitmapButton* m_ibtn6_willSend;
	CBitmapButton* m_ibtn6_sended;
	CBitmapButton* m_ibtn6_recieved;

	CComboBox m_editTimeUseHour;
	CComboBox m_editTimeUseMinute;
	CComboBox m_editTimeUseBanHour1;
	CComboBox m_editTimeUseBanHour2;
	CComboBox m_editTimeUseBanMinute1;
	CComboBox m_editTimeUseBanMinute2;
	CButton m_chMon;
	CButton m_chTUE;
	CButton m_chWED;
	CButton m_chTHR;
	CButton m_chFRI;
	CButton m_chSAT;
	CButton m_chSUN;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestory();

	afx_msg void OnBnClickedBtnTimeSet();
	afx_msg void OnBnClickedBtnBanURLSet();
	afx_msg void OnBnClickedBtnCAPTURE();
	afx_msg void OnBnClickedBtnUser Info();
	afx_msg void OnBnClickedBtnBanWordset();
	afx_msg void OnBnClickedBtnMessage();

	afx_msg void OnBnClickedBtnP1Save();
	afx_msg void OnBnClickedBtnP1Cancel();
	afx_msg void OnBnClickedBtnP1Repair();
	void SetpP1BtnVisible();

	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM IParam);
	afx_msg void OnBnClickedBtnP2Save();
	afx_msg void OnBnClickedBtnP2Delete();
	afx_msg void OnBnClickedBtnP3CaptureSetting();
	afx_msg void OnBnClickedBtnP3Delete();
	afx_msg void OnBnClickedBtnP5Save();
	afx_msg void OnBnClickedBtnP5Delete();
	afx_msg void OnBnClickedBtnP6Save();
	void OnTrayIconDelete();

	afx_msg void OnNMKillfocusListRecieve(NMHDRR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListSended(NMHDRR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListWillSend(NMHDRR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtnP6WillSend();
	afx_msg void OnBnClickedBtnP6Sended();
	afx_msg void OnBnClickedBtnP6Recieve();

	afx_msg void OnNMDblclkListWillSend(NMHDRR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSended(NMHDRR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListRecieve(NMHDRR *pNMHDR, LRESULT *pResult);

	void SetMSGBtnVisible();
	void SetComboBoxData();

	int m_nParent6MsgMode;
	CEdit m_eidtBanURL;
	CListCtrl* m_listCtrlBanURL;
	CListCtrl* m_listCtrlUser Info;
	CListCtrl* m_listCtrlUser InfoInternet;
	CListCtrl* m_listCtrlUser InfoGame;
	CListCtrl* m_listCtrlUser InfoVideo;

	CMonthCalCtrl m_calenderCapture;
	CListBox m_listCapture;
	CComboBox m_comboUser;
	CComboBox m_comboYear;
	CComboBox m_comboMonth;

	CString m_szWillSendMSG;
	CString m_szSendedMSG;
	CString m_szReciveMSG;

	CString m_szDeleteMSG;
	CString m_szDeleteTime;
	CSting m_szDeleteSavedTime;
	INT m_nDeleteIndex6;

	CEdit		m_editBanword;
	CListCtrl*  m_listCtrlBanWord;
	CEdit		m_editMessage;
	CComboBox	m_comboMSGTimeHour;
	CComboBox	m_comboMSGTimeMinute;
	CButton		m_chReSend;
	CListCtrl* m_listCtrlMSGWillSend;
	CListCtrl* m_listCtrlMSGSended;
	CListCtrl* m_listCtrlMSGReceive;
	CEdit m_editMSG;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString m_strImgPath;
	CString m_strImgName;

	UINT CalcUsedTime(CList<CDBDataForm,CDBDataForm&> list);
	CString CalcUsedTimestr(CList<CDBDataForm, CDBDataForm&>* list);
	// afx_msg void OnCbnCloseupCombo3();
	int shownMonth;
	int shownYear;
	int shownDay;
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR *pNHDR, LRESULT *pResult);
	CTime m_t Today;
	CString m_szEngBanWord;

	void set_listCtrlUswerInfo(int shownYear,int shownMonth);
	void set_listCtrlUserInfoGame();
	void set_listCtrlUserInfoInternet();
	void set_listCtrlUserInfoVideo();

	void LoadingDataData();
	void SelectDBFromMSGToParent();

	bool isDataDays[31];
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo2();

	int m_nChild6MsgMode;
	//void SetMSGBtnVisible();
	afx_msg void OnNMOnNMDblclkListOne(NMHDR *pNMHDR, LRESULT *pResult);

	//CList<CMessageForm, CMessageForm&> m_RCVLIST,m_SENDEDLIST, m_WILLSENDLIST;
	afx_msg void OnTimer(UINT_PTR nlDEvent);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CEdit m_editBanWordEng;
	};
