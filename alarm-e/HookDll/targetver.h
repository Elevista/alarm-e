#pragma once

// SDKDDKVer.h를 포함하면 최고 수준의 가용성을 가진 Windows 플랫폼이 정의됩니다.

// 이전 Windows 플랫폼에 대해 응용 프로그램을 빌드하려는 경우에는 SDKDDKVer.h를 포함하기 전에
// WinSDKVer.h를 포함하고 _WIN32_WINNT 매크로를 지원하려는 플랫폼으로 설정하십시오.

//#include <SDKDDKVer.h>
#ifndef WINVER  // 필요한 최소 플랫폼 VISTA 
#define WINVER 0x0600
#endif 

#ifndef _WIN32_WINNT // 필요한 최소 플랫폼 VISTA 
#define _WIN32_WINNT 0x0600
#endif 


#ifndef _WIN32_WINDOWS  // 필요한 최소 플랫폼 Win98
#define _WIN32_WINDOWS 0x0410
#endif 


#ifndef _WIN32_IE // 필요한 최소 IE 7.0 
#define _WIN32_IE 0x0700 
#endif 
