#pragma once

#include "DBconsumer.h"

class ScreenShot
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	static void start();	//��üȭ���� jpg�� ĸ���Ͽ� DB�� ����
	static CImage getlastimg();	//��� ����� ������ �̹����� ����
	static void getlastimgfile();	//��� ����� ������ �̹����� ���Ϸ� ����
	static UINT DoInBG(LPVOID pParam);
public:
	static void Stop(void);
};

