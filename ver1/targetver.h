#pragma once
//다음 매크로는 필요한 최소 플랫폼을 정의합니다. 필요한 최소 플랫폼은
//응용 프로그램을 실행하는 데 필요한 기능이 포함된 가장 빠른 버전의 Windows, Internet Explorer
//등입니다. 이 매크로는 지정된 버전 이상의 플랫폼 버전에서 사용 가능한 모든 기능을 활성화해야 작동합니다.


#ifndef WINVER
#define WINVER 0x0600
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0700
#endif
