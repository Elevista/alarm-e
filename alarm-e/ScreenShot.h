#pragma once

#include "DBconsumer.h"

class ScreenShot
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	static CString capture();	//��üȭ���� jpg�� ĸ���Ͽ� DB�� ����
	static CImage getlastimg();	//��� ����� ������ �̹����� ����
	static void getlastimgfile();	//��� ����� ������ �̹����� ���Ϸ� ����
	static UINT DoInBG(LPVOID pParam);
private:
	
};

