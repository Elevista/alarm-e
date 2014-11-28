#include "StdAfx.h"
#include "ScreenShot.h"

CString ScreenShot::capture(){

	CImage capImage;
	HDC windowDC = ::GetWindowDC(NULL); //현재 윈도우의 DC를 가져옴

	CRect rect;
	::GetWindowRect(GetDesktopWindow(), &rect); //데스크탑 윈도의 크기를 rect에 저장

	capImage.Create(rect.Width(), rect.Height(), 32);	//윈도 화면 크기로 CImage생성.

	HDC capimgDC = capImage.GetDC();	//캡쳐 이미지의 DC

	//캡쳐 이미지 DC에 화면 해상도 크기로 현재 윈도우DC를 복사.
	BitBlt(capimgDC, 0, 0, rect.Width(), rect.Height(), windowDC, 0, 0, SRCCOPY);

	CcaptureImageDB imgDB;
	imgDB.Open();	//디비를 열고
	imgDB.AddNew();	//새 레코드 생성
	imgDB.m_datetime=CTime::GetCurrentTime();	//현재 시간 넣고

	
	IStream* pStream = NULL;	//스트림 생성
	CreateStreamOnHGlobal(0, TRUE,   &pStream);	//스트림 초기화
	capImage.Save(pStream, Gdiplus::ImageFormatJPEG);	//스트림에 이미지 지정
	
	
	STATSTG streamStats;	//스트림에 관한 정보
	pStream->Stat(&streamStats, 0);	//스트림에 관한 정보 저장
	
	imgDB.m_image.m_dwDataLength=streamStats.cbSize.QuadPart;	//이미지 크기에 스트림 사이즈 넣음
	GetHGlobalFromStream(pStream,&imgDB.m_image.m_hData);	//스트림으로부터 데이터 저장
	
	imgDB.SetFieldDirty(&imgDB.m_image);	//?필수
	imgDB.SetFieldNull(&imgDB.m_image,FALSE);	//?필수

	imgDB.Update();	//디비에 반영
	
	capImage.ReleaseDC();

	
	return _T("fine");
}

CImage ScreenShot::getlastimg(){
	CcaptureImageDB imgDB;
	imgDB.Open();	//디비를 열고
	imgDB.MoveLast();	//마지막 레코드로 이동
	
	IStream* pStream = NULL;
	//마지막 레코드의 바이너리 데이터 스트림 지정
	CreateStreamOnHGlobal(imgDB.m_image.m_hData,FALSE,&pStream);
	CImage img;	//이미지 객체 생성
	img.Load(pStream);	//이미지 객체에 스트림 읽어옴
	

	return img;
}

void ScreenShot::getlastimgfile(){
	CcaptureImageDB imgDB;
	imgDB.Open();	//디비를 열고
	imgDB.MoveLast();	//마지막 레코드로 이동
	
	CString sFileName;	//파일명은 시간으로
	sFileName.Format(_T("%d-%d-%d %d시%d분%d초"),
		imgDB.m_datetime.GetYear(),
		imgDB.m_datetime.GetMonth(),
		imgDB.m_datetime.GetDay(),
		imgDB.m_datetime.GetHour(),
		imgDB.m_datetime.GetMinute(),
		imgDB.m_datetime.GetSecond());

	int length=imgDB.m_image.m_dwDataLength;	//파일 크기
	//파일 생성
	CFile file(sFileName+_T(".jpg"), CFile::modeCreate| CFile::modeReadWrite);

	//GlobalLock은 HGOLBAL의 버퍼를 준다.
	LPCVOID lpBuffer=GlobalLock(imgDB.m_image.m_hData);
	file.Write(lpBuffer,length);	//버퍼 쓰기
	file.Close();
	GlobalUnlock(imgDB.m_image.m_hData);
	return;
}


/* Cimage를 CBitmap 만드는법
	CImage image;
	image.Load(_T("C:\\image.png")); // just change extension to load jpg
	CBitmap bitmap;
	bitmap.Attach(image.Detach());
*/