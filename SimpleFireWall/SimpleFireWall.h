
// SimpleFireWall.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSimpleFireWallApp:
// �� Ŭ������ ������ ���ؼ��� SimpleFireWall.cpp�� �����Ͻʽÿ�.
//

class CSimpleFireWallApp : public CWinApp
{
public:
	CSimpleFireWallApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSimpleFireWallApp theApp;