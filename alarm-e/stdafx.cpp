
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// alarm-e.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

HANDLE hMapFile3;

CString GetTypeWord(){
	if(hMapFile3==NULL){
		//���������� �޸� ���� ���� �̸��� Alarme_authority
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_TypedWord"));
	}
	/*
	CString* typedWord=(CString*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&Authority,auth,sizeof(bool));	//�޸𸮿� ���о����
	return Authority;*/
	return "";
}