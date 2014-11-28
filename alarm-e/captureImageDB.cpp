// captureImageDB.h : CcaptureImageDB Ŭ������ �����Դϴ�.



// CcaptureImageDB �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 28�� �ݿ���, ���� 9:44

#include "stdafx.h"
#include "captureImageDB.h"
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


