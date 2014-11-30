#pragma once

// SDKDDKVer.h�� �����ϸ� �ְ� ������ ���뼺�� ���� Windows �÷����� ���ǵ˴ϴ�.

// ���� Windows �÷����� ���� ���� ���α׷��� �����Ϸ��� ��쿡�� SDKDDKVer.h�� �����ϱ� ����
// WinSDKVer.h�� �����ϰ� _WIN32_WINNT ��ũ�θ� �����Ϸ��� �÷������� �����Ͻʽÿ�.

//#include <SDKDDKVer.h>
#ifndef WINVER  // �ʿ��� �ּ� �÷��� VISTA 
#define WINVER 0x0600
#endif 

#ifndef _WIN32_WINNT // �ʿ��� �ּ� �÷��� VISTA 
#define _WIN32_WINNT 0x0600
#endif 


#ifndef _WIN32_WINDOWS  // �ʿ��� �ּ� �÷��� Win98
#define _WIN32_WINDOWS 0x0410
#endif 


#ifndef _WIN32_IE // �ʿ��� �ּ� IE 7.0 
#define _WIN32_IE 0x0700 
#endif 
