
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// alarm-e.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

HANDLE hMapFile3;

CString GetTypeWord(){
	if(hMapFile3==NULL){
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char)*20,_T("Alarme_TypedWord"));
	}
	char* mapFile=(char*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(char)*40);
	char typedWord[20];
	memcpy(typedWord,mapFile,sizeof(char)*40);	//�޸𸮿� ���о����

	CString str;
	str.Format("%s",typedWord);
	UnmapViewOfFile(mapFile);
	return str;
}