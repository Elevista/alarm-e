#pragma once
#include <time.h>

class SStrt
{
public:
	TCHAR m_Name[MAX_PATH];
	TCHAR m_URL[MAX_PATH]
	CTime m_StarTime;
	CTime m_EndTIme;
	HWND m_hwnd;
	BOOL IsCheck;
};