#pragma once

#include <vector>
using namespace std;
// CAlarm_ULogin ��ȭ �����Դϴ�.

class CAlarm_UILogin : public CDialog
{
	DECLARE_DYNAMIC(CAlarm_UILogin)

public:
	CAlarm_UILogin(CWnd* pParent = NULL); //ǥ�� �������Դϴ�.
	virtual ~CAlarm_UILogin();

	//��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALARAME_LOGIN };
	typedef enum {NOTHING_USER = 0, CHILD_USER, PARENT_USER} UserMode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnNew();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM IParam);
	int SelectLoginDB();
	void SetBitmapButton();
	void SetControlPosition();
	void OnTrayIconDelete();
	void GetDB();
	BOOL cs_util_un_register_start_prog(WCHAR* sPath);
	BOOL cs_util_register_start_Prg (WCHAR* sValue, WCHAR* sPath);
	CBitmapButton* m_ibtnNew;
	CBitmapButton* m_ibtnLogin;
	vector <CString> m_vDB;

	CEdit m_editID;
	CEdit m_editPassword;
	void UpdateDataFromJoin(CString szName, CString szPass2);
	CString m_szName;
	CString m_szPass1;
	CString m_szPass2;

	void saveDBToTXT();

	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
};