#if !defined(AFX_FULL_H__88107A75_B709_445D_BD48_F3D7C0F07A76__INCLUDED_)
#define AFX_FULL_H__88107A75_B709_445D_BD48_F3D7C0F07A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endig // _MSC_VER > 1000
// Full.h : header file

#include "Alarm_UIParent.h"


// CFull dialog

class CFull : public CDialog
{
	//Construction
public:
	CFull(Cwnd* pParent = NULL); // standard constructor
	CFull(CString imgPath,CWnd* pParent = NULL);
	void	OnDraw(CDC *pDC);
	// Dialog Data
	// {{AFX_DATA(CFull)
	enum { IDD = IDD_ALARAME_FULL };
	CString imgPath;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	//Overrides
	//ClassWizard generated virtual function overrides
	//{{AFX_VURTUAL(CFull)
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

	//Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CFull)
	afx_msg void OnPaint();
	afx_msg void OnLButtionDown(UINT nFlags, CPoint point);
	//{{AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif