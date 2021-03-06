
// alarm-e.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "DBconsumer.h"


bool SetRunning();	//중복실행 방지부분
void SetAuthority(bool Authority);	//권한 설정부분
bool GetAuthority(void);	//권한 불러오기

// CalarmeApp:
// 이 클래스의 구현에 대해서는 alarm-e.cpp을 참조하십시오.
//

class CalarmeApp : public CWinApp
{
public:
	CalarmeApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	DECLARE_MESSAGE_MAP()
	
};

extern CalarmeApp theApp;
//전역변수로 추가
extern CString ID;
extern HANDLE hMapFile;
extern HANDLE hMapFile2;
extern CwordFilter filterDB;
extern CManager loginDB;