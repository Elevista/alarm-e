// wordFilter.h : CwordFilter Ŭ������ �����Դϴ�.



// CwordFilter �����Դϴ�.

// �ڵ� ���� ��ġ 2014�� 11�� 27�� �����, ���� 2:02

#include "stdafx.h"
#include "wordFilter.h"
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


