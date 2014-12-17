
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// alarm-e.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


//~~~~~~~~~전역 함수~~~~~~~~
CString GetTypedWord(){	//메모리맵에서 후킹한 문자열 목록을 얻어오는 부분
	if(hMapFile3==NULL){
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char)*40,_T("Alarme_TypedWord"));
	}
	char* mapFile=(char*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(char)*40);
	char typedWord[40];
	memcpy(typedWord,mapFile,sizeof(char)*40);	//메모리에 값읽어오기

	CString str;
	str.Format(_T("%s"),typedWord);
	UnmapViewOfFile(mapFile);
	return str;
}

void ClearTypedWord(CString word){	//해당 문자열을 후킹한 문자열에서 제거해주는 부분
	if (hMapFile3 == NULL){
		hMapFile3 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(char)* 40, _T("Alarme_TypedWord"));
	}
	char* mapFile = (char*)MapViewOfFile(hMapFile3, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char)* 40);
	char typedWord[40];
	memcpy(typedWord,mapFile,sizeof(char)*40);	//메모리에 값읽어오기
	CString str;
	str.Format(_T("%s"),typedWord);
	str.Replace(word,"");
	memcpy(mapFile, str, sizeof(char)* 40);	//메모리에 값쓰기
	UnmapViewOfFile(mapFile);
	return;
}