#include "stdafx.h"
#include "DBconsumer.h"

// CcaptureImageDB 구현입니다.

// 코드 생성 위치 2014년 11월 28일 금요일, 오후 9:44
IMPLEMENT_DYNAMIC(CcaptureImageDB, CRecordset)

CcaptureImageDB::CcaptureImageDB(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_datetime;
	m_image;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CcaptureImageDB::GetDefaultConnect()
{
	return _T("DBQ=alarm-e.mdb;DefaultDir=.;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=alarm-e.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;PWD=123456;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString CcaptureImageDB::GetDefaultSQL()
{
	return _T("[captureImage]");
}

void CcaptureImageDB::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Date(pFX, _T("[datetime]"), m_datetime);
	RFX_LongBinary(pFX, _T("[image]"), m_image);

}
/////////////////////////////////////////////////////////////////////////////
// CcaptureImageDB 진단

#ifdef _DEBUG
void CcaptureImageDB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CcaptureImageDB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


// CManager 구현입니다.

// 코드 생성 위치 2014년 11월 27일 목요일, 오전 1:49
IMPLEMENT_DYNAMIC(CManager, CRecordset)

CManager::CManager(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = L"";
	m_PW = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CManager::GetDefaultConnect()
{
	return _T("DBQ=alarm-e.mdb;DefaultDir=.;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=alarm-e.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;PWD=123456;UserCommitSync=Yes;");
}

CString CManager::GetDefaultSQL()
{
	return _T("[Manager]");
}

void CManager::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PW]"), m_PW);

}
/////////////////////////////////////////////////////////////////////////////
// CManager 진단

#ifdef _DEBUG
void CManager::AssertValid() const
{
	CRecordset::AssertValid();
}

void CManager::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


// CwordFilter 구현입니다.

// 코드 생성 위치 2014년 11월 27일 목요일, 오전 2:02
IMPLEMENT_DYNAMIC(CwordFilter, CRecordset)

CwordFilter::CwordFilter(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_word = L"";
	m_nFields = 1;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CwordFilter::GetDefaultConnect()
{
	return _T("DBQ=alarm-e.mdb;DefaultDir=.;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=alarm-e.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;PWD=123456;UserCommitSync=Yes;");
}

CString CwordFilter::GetDefaultSQL()
{
	return _T("[wordFilter]");
}

void CwordFilter::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[word]"), m_word);

}
/////////////////////////////////////////////////////////////////////////////
// CwordFilter 진단

#ifdef _DEBUG
void CwordFilter::AssertValid() const
{
	CRecordset::AssertValid();
}

void CwordFilter::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


