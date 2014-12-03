#pragma once

class CAlarm_UIPopup : public CDialog
{
	DECLARE_DYNAMIC(CAlarm_UIPopup)
public:
	CAlarm_UIPopup(CWnd* pParent = NULL);
	virtual ~CAlarm_UIPopup();

	enum { IDD = IDD_ALARAME_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	void SkinLoad();
	BOOL BitmapRgn(UINT resource, COLORREF TansColor);
	HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, COLORREF cTolerance);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetMessage(CString szMSG);
	void SetPosition(int nX, int nY);
	CString m_szOutputMSG;
	int m_nX;
	int m_nY;
	int m_nCount;
};