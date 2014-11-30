#pragma once
// 저장할 데이터 구조의 기본 단위 

#include <time.h>
//#define MAX_PATH 987654321
class SStrt
{
public:
	TCHAR m_Name[MAX_PATH];
	TCHAR m_URL[MAX_PATH];
	CTime m_StartTime;
	CTime m_EndTime;
	HWND m_hwnd;
	BOOL IsCheck;
};