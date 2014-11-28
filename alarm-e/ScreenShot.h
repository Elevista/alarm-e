#pragma once

#include "captureImageDB.h"

class ScreenShot
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	static CString capture();	//전체화면을 jpg로 캡쳐하여 DB에 저장
	static CImage getlastimg();	//디비에 저장된 마지막 이미지를 리턴
	static void getlastimgfile();	//디비에 저장된 마지막 이미지를 파일로 저장
private:
	
};

