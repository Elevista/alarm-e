
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// alarm-e.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


//~~~~~~~~~���� �Լ�~~~~~~~~
CString GetTypedWord(){	//�޸𸮸ʿ��� ��ŷ�� ���ڿ� ����� ������ �κ�
	if(hMapFile3==NULL){
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char)*40,_T("Alarme_TypedWord"));
	}
	char* mapFile=(char*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(char)*40);
	char typedWord[40];
	memcpy(typedWord,mapFile,sizeof(char)*40);	//�޸𸮿� ���о����

	CString str;
	str.Format(_T("%s"),typedWord);
	UnmapViewOfFile(mapFile);
	return str;
}

void ClearTypedWord(CString word){	//�ش� ���ڿ��� ��ŷ�� ���ڿ����� �������ִ� �κ�
	if (hMapFile3 == NULL){
		hMapFile3 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(char)* 40, _T("Alarme_TypedWord"));
	}
	char* mapFile = (char*)MapViewOfFile(hMapFile3, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char)* 40);
	char typedWord[40];
	memcpy(typedWord,mapFile,sizeof(char)*40);	//�޸𸮿� ���о����
	CString str;
	str.Format(_T("%s"),typedWord);
	str.Replace(word,"");
	memcpy(mapFile, str, sizeof(char)* 40);	//�޸𸮿� ������
	UnmapViewOfFile(mapFile);
	return;
}