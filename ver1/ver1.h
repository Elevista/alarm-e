
// ver1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cver1App:
// �� Ŭ������ ������ ���ؼ��� ver1.cpp�� �����Ͻʽÿ�.
//

class Cver1App : public CWinApp
{
public:
	Cver1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cver1App theApp;