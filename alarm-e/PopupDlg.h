#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "WordFilterDlg.h"
#include "ScreenshotDlg.h"

class CPopupDlg : public CDialog
{
public:
		CPopupDlg(CString msg);
		BOOL OnInitDialog();
};