
// alarm-e.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "DBconsumer.h"

// CalarmeApp:
// �� Ŭ������ ������ ���ؼ��� alarm-e.cpp�� �����Ͻʽÿ�.
//

class CalarmeApp : public CWinApp
{
public:
	CalarmeApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	DECLARE_MESSAGE_MAP()
};

extern CalarmeApp theApp;
//���������� �߰�
extern CString ID;
extern CwordFilter filterDB;
extern CManager loginDB;
