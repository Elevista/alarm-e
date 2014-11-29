#include "stdafx.h"
#include "DBconsumer.h"

// CcaptureImageDB �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 28�� �ݿ���, ���� 9:44
IMPLEMENT_DYNAMIC(CcaptureImageDB, CRecordset)

CcaptureImageDB::CcaptureImageDB(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_datetime;
	m_image;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Date(pFX, _T("[datetime]"), m_datetime);
	RFX_LongBinary(pFX, _T("[image]"), m_image);

}
/////////////////////////////////////////////////////////////////////////////
// CcaptureImageDB ����

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


// CManager �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 27�� �����, ���� 1:49
IMPLEMENT_DYNAMIC(CManager, CRecordset)

CManager::CManager(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = L"";
	m_PW = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PW]"), m_PW);

}
/////////////////////////////////////////////////////////////////////////////
// CManager ����

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


// CwordFilter �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 27�� �����, ���� 2:02
IMPLEMENT_DYNAMIC(CwordFilter, CRecordset)

CwordFilter::CwordFilter(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_word = L"";
	m_nFields = 1;
	m_nDefaultType = dynaset;
}
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Text(pFX, _T("[word]"), m_word);

}
/////////////////////////////////////////////////////////////////////////////
// CwordFilter ����

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


