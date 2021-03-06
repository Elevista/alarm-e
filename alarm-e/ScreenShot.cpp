#include "StdAfx.h"
#include "ScreenShot.h"
#include "MultipartUpload.h"
#include "RegManager.h"

static int freq;
static bool loop;
static bool running=false;
UINT ScreenShot::DoInBG(LPVOID pParam){	//스크린샷을 찍어 업로드 하는 쓰레드
	running=true;
	while(loop){
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

	
		LPVOID imageData=GlobalLock(imgDB.m_image.m_hData);
	
		imgDB.Update();	//디비에 반영

		//업로드 부분
		MultipartUpload::Upload((BYTE *)imageData,streamStats.cbSize.QuadPart);	//따로 쓰레드로 돌아감
	
		GlobalUnlock(imgDB.m_image.m_hData);
		capImage.ReleaseDC();
		for(int i=0;i<freq;i++){	//대기중 매초마다 쓰레드 종료할지 검사
			if(!loop) {running=false;return 4;}
			Sleep(1000);
		}
		
	}
	running=false;
	return 0;
}

void ScreenShot::start(){
	loop=CRegManager::GetScreenShotVal();	//레지에서 활성화 여부 가져옴
	freq=CRegManager::GetScreenShotFreq();	//레지에서 스샷 빈도 가져옴
	if(!running) AfxBeginThread(DoInBG,NULL);	//쓰레드 실행중이 아닐때만 새 쓰레드 생성
}

CImage ScreenShot::getlastimg(){	//확인차 넣은 메소드 구현에는 안쓰임
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

void ScreenShot::getlastimgfile(){	//확인차 넣은 메소드 구현에는 안쓰임. 마지막 이미지를 파일로 출력하는 기능
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


void ScreenShot::Stop(void)	//쓰레드 종료 메소드
{
	loop=false;
}
