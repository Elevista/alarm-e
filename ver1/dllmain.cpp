#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <string.h>

#include <atlstr.h>
using namespace std;

#define WM_BANWORD (WM_USER + 5)
#define UM_CLOSEANIDLF (WM_USER + 2)
#define keySIZE 15

FILE *fp = NULL;

HINSTANCE hInst = NULL;
HWND g_Wnd = NULL;

HHOOK g_keyhook = NULL;
HHOOK g_mousehook = NULL;
HHOOK g_althook = NULL;
HHOOK g_delhook = NULL;

TCHAR g_keyStr[keySIZE+3];
int g_packData[keySIZE+3];
int g_idx, g_packidx, g_delLen;
vector <CString> g_vecStr;

TCHAR moum[15] ={_T("YUIOPHJKLBNM")};

extern "C" __declspec(dllexport) void UnHook();
extern "C" __declspec(dllexport) void Hook();
extern "C" __declspec(dllexport) bool isHook();
extern "C" __declspec(dllexport) bool isArtHook();

extern "C" __declspec(dllexport) void sendDB(vector<CString> dbData);
extern "C" __declspec(dllexport) void keyStrInit();
extern "C" __declspec(dllexport) void Delete_UnHook();
extern "C" __declspec(dllexport) void keyStrInit();

extern "C" __declspec(dllexport) bool isDelHook();

BOOL checkKeyword(TCHAR* matStr);
void deleteKey();
void inputKey(TCHAR key);

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GetAltMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
void GetDB();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	hInst = (HINSTANCE)hModule;
	return TRUE;
}
//bool g_blsLoadDB = FALSE;

BOOL checkKeyword(TCHAR* matStr){
	int i, j, k, m, key_len, cnt, moumLen;
	TCHAR targetStr[50], keyStr[50];
	cnt = (int)g_vecStr.size();
	for(i=0; i<cnt; ++i)
	{
		_tcscpy(keyStr,g_vecStr[i]);
		key_len =_tcslen(keyStr);
		for(j=0; j<keySIZE; ++j)
		{
			for(k=0; k<key_len; ++k)
			{
				targetStr[k] = matStr[(j+k)%keySIZE];
			}
			targetStr[key_len]='\0';
			if(_tcscmp(keyStr, targetStr) == 0)
			{
				g_delLen=0,moumLen=_tcslen(moum);
				for(k=0; k<key_len; ++k)
				{
					for(m=0; m<moumLen; ++m)
					{
						if(moum[m] == keyStr[k])
						{
							++g_delLen;
						}
					}
				}
				memset(g_keyStr,0,sizeof(g_keyStr));
				return TRUE;
			}
		}
	}
	return FALSE;
}
LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam){
	if (nCode<0)
		return CallNextHookEx(g_keyhook, nCode, wParam, lParam);

	KBDLLHOOKSTRUCT *pkey=(KBDLLHOOKSTRUCT *)lParam;

	if(wParam==WM_KEYDOWN){
		if(pkey->vkCode == VK_BACK) deleteKey();
		else inputKey((TCHAR)pkey->vkCode);

		WCHAR szTemp[32] = L"";
		wsprintf(szTemp,L"-----------%s\n", g_keyStr);
		OutputDebugString(szTemp);
		if(checkKeyword(g_keyStr)){
			Sleep(500);
			g_Wnd = NULL;
			g_Wnd = FindWindow(_T("CAlarm_UIChild"), NULL);
			if(g_Wnd != NULL)		SendMessage(g_Wnd, WM_BANWORD, 0, 0);
			else					MessageBox(NULL, _T("핸들실패했따!"), _T(""), MB_OK);

			g_packidx = (g_packidx+1)%keySIZE;
			OutputDebugString(g_keyStr);

			RECT rc;
			HWND explorerhWnd=::FindWindow(_T("IEFrame"), NULL);
			::GetWindowRect(explorerhWnd, &rc);

			SetCursorPos((int)(rc.left + rc.right)*0.5, (int)(rc.top + rc.bottom)*0.5);
		}
	}
	return CallNextHookEx(g_keyhook, nCode, wParam, lParam);
}
LRESULT CALLBACK GeetAltMsgProc(int nCode, WPARAM wParam, LPARAM lParam){
	BOOL fEatKeystorke = FALSE;

	if(nCode == HC_ACTION){
		switch (wParam){
		case WM_KEYDOWN: 
		case WM_SYSKEYDOWN:
		case WM_KEYUP:   
		case WM_SYSKEYUP:
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
			fEatKeystorke =
				((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
				((p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN) !=0)) ||
				((p->vkCode == VK_ESCAPE) && (( GetKeyState(VK_CONTROL) & 0x8000) !=0));
			break;
		}
	}
	return (fEatKeystorke ? 1 : CallNextHookEx(g_althook, nCode, wParam, lParam);
}
void inputKey(TCHAR key) {
	int i,moumLen;
	bool flag;

	if( (key>='A' && key<='Z')) 
	{
		flag = false;
		moumLen=(int)_tcslen(moum);
		for(i=0;i<moumLen&&!flag; ++i)
		{
			if(key ==moum[i])flag = true;
		}
		if(flag) {
			if(g_packData[g_packidx] == 0)
			{
				++g_packData[g_packidx];
				g_packidx = (g_packidx+1)%keySIZE;
			}
			else if(g_packData[g_packidx] == 1)
			{				
				++g_packData[g_packidx];
			}
			else
			{
				g_packidx=(g_packidx+1)%keySIZE;
				g_packData[g_packidx]=0;
				--g_packData[g_packidx-1];
				g_packData[g_packidx]+=2;
			}
		}
		else
		{
			if(g_packData[g_packidx]>=3) ++g_packidx;
			++g_packData[g_packidx];
		}
		g_keyStr[g_idx] = key;
		g_idx = (g_idx+1)%keySIZE;
	}
	else if((key>='0' && key<='9')|| (key=='.' ||key==','||key=='/'||key==' '))
	{
		g_packidx = (g_packidx+1)%keySIZE;
		g_packData[g_packidx]=1;
		g_packidx = (g_packidx+1)%keySIZE;
		g_packData[g_packidx]=0;
	
		g_keyStr[g_idx] = key;
		g_idx = (g_idx+1)%keySIZE;
	}
}
void deleteKey() {
	if(g_packData[g_packidx] ==0 )
	{
		g_packidx = (g_packidx + keySIZE-1) % keySIZE;
		while(g_packData[g_packidx]--)
		{
			g_idx = (g_idx+keySIZE-1) %keySIZE;
			g_keyStr[g_idx] = '\0';
		}
		g_packData[g_packidx]=0;
	}
	else
	{
		g_idx = (g_idx +keySIZE-1)%keySIZE;
		g_keyStr[g_idx]='\0';
		--g_packData[g_packidx];
	}
}
extern "C" __declspec(dllexport) void keyStrInit() {
	g_idx =0;
	memset(g_keyStr, 0,sizeof(g_keyStr));
}
extern "C" __declspec(dllexport) void Hook() {
	if(g_keyhook == NULL) {
		g_keyhook = SetWindowsHookEx(WH_KEYBOARD_LL, GetMsgProc, hInst, NULL);
			if(g_keyhook == NULL) MessageBox(NULL, _T("keyboard hooking error"),_T("KeyHook"),MB_OK);
	}
	OutputDebugString(L"Hook Function\n");
}
extern "C" __declspec(dllexport) void UnHook() {
	if(g_keyhook != NULL) {
		UnhookWindowsHookEx(g_keyhook);
		g_keyhook = NULL;
	}
}
extern "C" __declspec(dllexport) bool isHook() {
	if(g_keyhook == NULL) return false;
	else return true;
}
extern "C" __declspec(dllexport) bool isArtHook() {
	if(g_althook == NULL) return false;
	else return true;
}
extern "C" __declspec(dllexport) void Delete_UnHook() {
	if(g_delhook != NULL) {
		UnhookWindowsHookEx(g_delhook);
		g_delhook = NULL;
	}
}
extern "C" __declspec(dllexport) void sendDB( vector<CString> dbData) 
{
	g_vecStr = dbData;
}
extern "C" __declspec(dllexport) bool isDelHook()
{
	if(g_delhook == NULL) return false;
	else return true;
}
