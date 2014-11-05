#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "TSTimeStruct.h"
#include "Alarm_UIPopup.h"
#include <vector>
using namespace std;

#include "afxtempl.h"
// CAlarm_UIChild 대화 상자입니다.

class CAlarm_UIChild : public CDialog
{
	DECLARE_DYNAMIC(CAlarm_UIChild)

#define CALENDAR_PREV	   -1
#define CALENDAR_CURRENT	0
#define CALENDAR_NEXT		1

	typedef enum {CHILD_EDUURL =0, CHILD_MESSAGE} DIgMode;
	typedef enum {WILLSEND =0, SENDED, RECIEVE} MESSAGEMODE;
public:
	CAlarm_UIChild(CWnd* pParent = NULL); // 표준 생성자입니다.
	virtual ~CAlarm_UIChild();

	//대화 상자 데이터입니다.
	enum { IDD = IDD_ALARAME_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CList<TSTimeArr, TSTimeArr&> m_listTime;
	//vextor<vextor> m_arrPlan;

	CBitmapButton* m_ibtnEduURL;
	CBitmapButton* m_ibtnMessage;

	CBitmapButton* m_ibtn2_save;
	CBitmapButton* m_ibtn2_cancel;
	CBitmapButton* m_ibtn2_repair;
	CBitmapButton* m_ibtn2_delete;

	CBitmapButton* m_ibtn5_save;
	CBitmapButton* m_ibtn5_delete;

	int m_nMode;

	bool m_bIsEditModeEdu;
	bool m_IsUpdateModeEdu;

	CEdit m_editEduTiTle;
	CEdit m_editEduURL;
	CComboBox m_comboEduTimeHour1;
	CComboBox m_comboEduTimeMinute1;
	CListCtrl* m_liostCtrlEdu;
	CListCtrl* m_liostCtrlMSGWillSend;
	CListCtrl* m_liostCtrlMSGSended;
	CListCtrl* m_liostCtrlMSGReceive;

	CButton m_cMon;
	CButton m_chTUE;
	CButton m_chWED;
	CButton m_chTHU;
	CButton m_chFRI;
	CButton m_chSAT;
	CButton m_chSUN;
	CEdit m_editMSGMEssage;
	CComboBox m_comboMSGTimeHour;
	CComboBox m_comboMSGTimeMinute;
	CButton m_chReSend;

	CBitmapButton* m_ibtn5_willSend;
	CBitmapButton* m_ibtn5_sended;
	CBitmapButton* m_ibtn5_recieved;

	COleDateTime m_tToday;
	int m_nChild5MsgMode;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();

	afx_msg void OnBnClickedBtnEduURL();
	afx_msg void OnBnClickedBtnMessage();

	afx_msg void OnBnClickedBtnC2Save();
	afx_msg void OnBnClickedBtnC2Cancel();
	afx_msg void OnBnClickedBtnC2Repair();
	afx_msg void OnBnClickedBtnC2Delete();

	afx_msg void OnBnClickedBtnC5Save();
	afx_msg void OnBnClickedBtnC5Sended();
	afx_msg void OnBnClickedBtnC5WillSend();
	afx_msg void OnBnClickedBtnC5Recieve();
	afx_msg void OnBnClickedBtnC5Delete();
	afx_msg LRESULT OnBanWord(WPARAM wParam, LPARAM IParam);
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM IParam);

	void SetImageButtonMode();
	void SetModeVisible(BOOL bVisible);
	void SetModeVisible(BOOL bVisible, int nMode);
	void DrawBackgroundImage(HDC hDC);
	void OnDraw(HDC hDC);
	BOOL CheckSave();
	void SetMSGBtnVisible();
	void SetComboBoxContents();
	void InitEduComponent();
	void SelectDBFromEcampusURL();
	void SelectDBFromMSGToParent();
	void SetC2BtnVisible();
	void SetC5BtnVisible();
	void OnTrayIconDelete();

	//EDU MODE
	void SetPositionEDU();
	void SetCheckLabelEDU();
	void SetListCtrlEDU();


	//MESSAGE MODE
	void SetListCtrlMessage();
	void SetPositionMessage();
	void SetCheckLabelMessage();

	afx_msg void OnNMDblclkListEdu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListWillSend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSended(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListRecieve(NMHDR *pNMHDR, LRESULT *pResult);

	CEdit m_editMSG;

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString m_szEduTitle;
	CString m_szEduURL;

	CString m_szWillSendMSG;
	CString m_szSendedMSG;
	CString m_szReciveMSG;

	CString m_szDeleteMSG;
	CString m_szDeleteTime;
	CString m_szDeleteSavedTime;

	int m_nDeleteIndex2;
	int m_nDeleteIndex5;

	int m_nEduTimeHour;
	int m_nEduTimeMinute;
	CAlarm_IUPopup *m_popUPDIg;

	afx_msg void OnNMKillfocusListWillSend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListSended(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListRecieve(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusListEdu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};

