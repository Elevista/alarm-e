#pragma once

#include "captureImageDB.h"

class ScreenShot
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	static CString capture();	//��üȭ���� jpg�� ĸ���Ͽ� DB�� ����
	static CImage getlastimg();	//��� ����� ������ �̹����� ����
	static void getlastimgfile();	//��� ����� ������ �̹����� ���Ϸ� ����
private:
	
};

