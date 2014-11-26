// Manager.h : CManager Ŭ������ �����Դϴ�.



// CManager �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 27�� �����, ���� 1:49

#include "stdafx.h"
#include "Manager.h"
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


