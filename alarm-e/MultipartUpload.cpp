#include "stdafx.h"
#include "MultipartUpload.h"
#include "alarm-e.h"
CString sPrefix;
static DWORD length;
static LPVOID lpData;

void MultipartUpload::Upload(BYTE* pImgData,DWORD len){
	length=len;
	AfxBeginThread(UploadThread,pImgData);
}


CString MultipartUpload::join(CString id,CString pw){

	CInternetSession internetSession;
	CHttpConnection * httpConnection = internetSession.GetHttpConnection(_T("alarme-sunnyholic.rhcloud.com"), (INTERNET_PORT)80,NULL ,NULL);
	CHttpFile * httpFile = httpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, _T("/join"));

	
	//�����. ��Ƽ��Ʈ������Ÿ. ���� �ٿ����~ UA�� �����
	httpFile->AddRequestHeaders(_T("Accept: */*\r\nContent-Type: multipart/form-data; boundary=---------------------------7d13a23b368\r\nUser-Agent: alarm-e\r\n"));

		
	//���� ����.
	sPrefix = _T("-----------------------------7d13a23b368");
	CString sSuffix = _T("-----------------------------7d13a23b368--");
	CString sContent;
	sContent.Format(_T("\r\n%s\r\n Content-Disposition: form-data; name=\"id\"\r\n\r\n%s\r\n%s\r\nContent-Disposition: form-data; name=\"pw\"\r\n\r\n%s\r\n%s\r\n"),sPrefix,id,sPrefix,pw,sSuffix);
	
	
	//�ݴ� ����
	DWORD dwPostDataLen = sContent.GetLength();	//�� ���� post�� ũ��

	
	
	/* ���� post���� ����Ʈ �ڵ�� �Ű� ���� �κ� */
	BYTE * szPostData, * pCurrentByte;
	szPostData = pCurrentByte = new BYTE[dwPostDataLen];	//���� ������
	
	
	char *pTemp;	//2����Ʈ �����ڵ忡�� 1����Ʈ ���ڷ� ��ȯ��

	pTemp = new char[dwPostDataLen];
	strcpy(pTemp, CT2A(sContent));
	memcpy((void *)szPostData, pTemp, dwPostDataLen);

	CString sResponse = _T("");
	TCHAR buf[1024];
	try {
		//������!
		httpFile->SendRequest(NULL, 0, (LPVOID)szPostData, dwPostDataLen);
		//ȸ�� �о��.
		DWORD dwRet;
		httpFile->QueryInfoStatusCode(dwRet);
		
		TCHAR* strRet =httpFile->ReadString(buf, 1024);
		sResponse.Format(_T("%s"),strRet);
		//sResponse = ConvertUTF8toUnicode((char*)strRet);
		delete (LPVOID)szPostData;
	}catch (CInternetException& exc){
		TRACE("Caught Exception (%d)\n", exc.m_dwError);
	}

	httpFile->Close();
	delete httpFile;
	delete httpConnection;

	return sResponse;
}


CString MultipartUpload::ConvertUTF8toUnicode(char* ansiStr)
{
	int nSize = MultiByteToWideChar(CP_UTF8, 0, ansiStr ,  -1 , 0 , 0);

	TCHAR* uniStr = new TCHAR[nSize+1];
	MultiByteToWideChar(CP_UTF8, 0, ansiStr ,  -1 , (LPWSTR)uniStr, nSize);
	uniStr[nSize] = '\0';

	CString str(uniStr);
	delete uniStr;
	return str;
} 

UINT MultipartUpload::UploadThread(LPVOID lpParam)
{
	CTime time=CTime::GetCurrentTime();
	LPVOID pImgData=lpParam;
	CInternetSession internetSession;
	CHttpConnection * httpConnection = internetSession.GetHttpConnection(_T("alarme-sunnyholic.rhcloud.com"), (INTERNET_PORT)80,NULL ,NULL);
	CHttpFile * httpFile = httpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, _T("/uploadServlet"));

	CString sFileName;	//���ϸ��� �ð�����
	sFileName.Format(_T("%d-%d-%d-%d-%d-%d"),
		time.GetYear(),
		time.GetMonth(),
		time.GetDay(),
		time.GetHour(),
		time.GetMinute(),
		time.GetSecond());


	//�����. ��Ƽ��Ʈ������Ÿ. ���� �ٿ����~ UA�� �����
	httpFile->AddRequestHeaders(_T("Accept: */*\r\nContent-Type: multipart/form-data; boundary=---------------------------7d13a23b368\r\nUser-Agent: alarm-e\r\n"));


	//���� ����
	sPrefix.Format(_T("\r\n-----------------------------7d13a23b368\r\nContent-Disposition: form-data; name=\"image\"; filename=\"%s\"\r\nContent-Type: image/jpeg\r\n\r\n"), sFileName);
	DWORD dwPrefix = sPrefix.GetLength();
	//�ݴ� ����
	CString sSuffix;
	sSuffix.Format(_T("\r\n-----------------------------7d13a23b368\r\nContent-Disposition: form-data; name=\"id\"\r\n\r\n%s\r\n-----------------------------7d13a23b368--\r\n-----------------------------7d13a23b368--\r\n"),ID);
	DWORD dwSuffix = sSuffix.GetLength();
		

	DWORD dwPostDataLen = dwPrefix + length + dwSuffix;	//�� ���� post�� ũ��

	
	
	
	
	/* ���� post���� ����Ʈ �ڵ�� �Ű� ���� �κ� */
	BYTE * szPostData, * pCurrentByte;
	szPostData = pCurrentByte = new BYTE[dwPostDataLen];	//���� ������
	
	
	char *pTemp;	//2����Ʈ �����ڵ忡�� 1����Ʈ ���ڷ� ��ȯ��

	//��� �κ�
	pTemp = new char[sPrefix.GetLength()];
	strcpy(pTemp, CT2A(sPrefix));
	memcpy((void *)szPostData, pTemp, dwPrefix);
	//memcpy((void *)szPostData, (const void *)(LPCTSTR)sPrefix, dwPrefix);
	pCurrentByte += dwPrefix;

	//���� �κ�
	memcpy((void *)pCurrentByte,pImgData, length);
	pCurrentByte+=length;

	//�ݴ� �κ�
	pTemp = new char[sSuffix.GetLength()] ;
	strcpy(pTemp, CT2A(sSuffix));
	memcpy((void *)pCurrentByte,pTemp, dwSuffix);
	//memcpy((void *)pCurrentByte,sSuffix, dwSuffix);


	CString sResponse = _T("");
	TCHAR buf[1024];
	try {
		//������!
		httpFile->SendRequest(NULL, 0, (LPVOID)szPostData, dwPostDataLen);
		//ȸ�� �о��.
		DWORD dwRet;
		httpFile->QueryInfoStatusCode(dwRet);
		TCHAR* strRet =httpFile->ReadString(buf, 1024);
		sResponse.Format(_T("%s"),strRet);
		//sResponse = ConvertUTF8toUnicode((char*)strRet);
		delete (LPVOID)szPostData;
	}catch (CInternetException& exc){
		TRACE("Caught Exception (%d)\n", exc.m_dwError);
	}

	httpFile->Close();
	delete httpFile;
	delete httpConnection;



	////������ ����
	//static TCHAR hdrs[] = _T("Content-Type: multipart/form-data; boundary=---------------------8cba7c0b4681f6e");
	//static char frmdata[] = "-----------------------8cba7c0b4681f6e\r\nContent-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\nContent-Type: application/octet-stream\r\n\r\nhello\r\n\r\n-----------------------8cba7c0b4681f6e--\r\n";
	//// for clarity, error-checking has been removed
	//HINTERNET hSession = InternetOpen(_T(""), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	//HINTERNET hConnect = InternetConnect(hSession, _T("web.sunnyholic.com"), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	//HINTERNET hRequest = HttpOpenRequest(hConnect, _T("POST"), _T("/uploadServlet"), NULL, NULL, NULL, 0, 1);
	//HttpSendRequest(hRequest, hdrs, wcslen(hdrs), frmdata, strlen(frmdata));

	return 1;
}
