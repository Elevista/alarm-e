#pragma once
class CRegManager
{
public:
	CRegManager(void);
	~CRegManager(void);
	
	static void SetID(CString id);
	static CString GetID(void);
	static bool GetScreenShotVal(void);
	static void SetScreenShotVal(bool value);
	static int GetScreenShotFreq(void);
	static void SetScreenShotFreq(int second);
};

