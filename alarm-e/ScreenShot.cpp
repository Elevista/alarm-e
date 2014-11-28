#include "StdAfx.h"
#include "ScreenShot.h"

CString ScreenShot::capture(){

	CImage capImage;
	HDC windowDC = ::GetWindowDC(NULL); //���� �������� DC�� ������

	CRect rect;
	::GetWindowRect(GetDesktopWindow(), &rect); //����ũž ������ ũ�⸦ rect�� ����

	capImage.Create(rect.Width(), rect.Height(), 32);	//���� ȭ�� ũ��� CImage����.

	HDC capimgDC = capImage.GetDC();	//ĸ�� �̹����� DC

	//ĸ�� �̹��� DC�� ȭ�� �ػ� ũ��� ���� ������DC�� ����.
	BitBlt(capimgDC, 0, 0, rect.Width(), rect.Height(), windowDC, 0, 0, SRCCOPY);

	CcaptureImageDB imgDB;
	imgDB.Open();	//��� ����
	imgDB.AddNew();	//�� ���ڵ� ����
	imgDB.m_datetime=CTime::GetCurrentTime();	//���� �ð� �ְ�

	
	IStream* pStream = NULL;	//��Ʈ�� ����
	CreateStreamOnHGlobal(0, TRUE,   &pStream);	//��Ʈ�� �ʱ�ȭ
	capImage.Save(pStream, Gdiplus::ImageFormatJPEG);	//��Ʈ���� �̹��� ����
	
	
	STATSTG streamStats;	//��Ʈ���� ���� ����
	pStream->Stat(&streamStats, 0);	//��Ʈ���� ���� ���� ����
	
	imgDB.m_image.m_dwDataLength=streamStats.cbSize.QuadPart;	//�̹��� ũ�⿡ ��Ʈ�� ������ ����
	GetHGlobalFromStream(pStream,&imgDB.m_image.m_hData);	//��Ʈ�����κ��� ������ ����
	
	imgDB.SetFieldDirty(&imgDB.m_image);	//?�ʼ�
	imgDB.SetFieldNull(&imgDB.m_image,FALSE);	//?�ʼ�

	imgDB.Update();	//��� �ݿ�
	
	capImage.ReleaseDC();

	
	return _T("fine");
}

CImage ScreenShot::getlastimg(){
	CcaptureImageDB imgDB;
	imgDB.Open();	//��� ����
	imgDB.MoveLast();	//������ ���ڵ�� �̵�
	
	IStream* pStream = NULL;
	//������ ���ڵ��� ���̳ʸ� ������ ��Ʈ�� ����
	CreateStreamOnHGlobal(imgDB.m_image.m_hData,FALSE,&pStream);
	CImage img;	//�̹��� ��ü ����
	img.Load(pStream);	//�̹��� ��ü�� ��Ʈ�� �о��
	

	return img;
}

void ScreenShot::getlastimgfile(){
	CcaptureImageDB imgDB;
	imgDB.Open();	//��� ����
	imgDB.MoveLast();	//������ ���ڵ�� �̵�
	
	CString sFileName;	//���ϸ��� �ð�����
	sFileName.Format(_T("%d-%d-%d %d��%d��%d��"),
		imgDB.m_datetime.GetYear(),
		imgDB.m_datetime.GetMonth(),
		imgDB.m_datetime.GetDay(),
		imgDB.m_datetime.GetHour(),
		imgDB.m_datetime.GetMinute(),
		imgDB.m_datetime.GetSecond());

	int length=imgDB.m_image.m_dwDataLength;	//���� ũ��
	//���� ����
	CFile file(sFileName+_T(".jpg"), CFile::modeCreate| CFile::modeReadWrite);

	//GlobalLock�� HGOLBAL�� ���۸� �ش�.
	LPCVOID lpBuffer=GlobalLock(imgDB.m_image.m_hData);
	file.Write(lpBuffer,length);	//���� ����
	file.Close();
	GlobalUnlock(imgDB.m_image.m_hData);
	return;
}


/* Cimage�� CBitmap ����¹�
	CImage image;
	image.Load(_T("C:\\image.png")); // just change extension to load jpg
	CBitmap bitmap;
	bitmap.Attach(image.Detach());
*/