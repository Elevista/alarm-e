������Ʈ�� ���� ����
CalarmeApp theApp�� ����ִ� �޼ҵ���
SetRegistryKey(_T("Alarm-e"));	//HKEY_CURRENT_USER\Software �����Ʒ� �����̸� ����

free( ( void* )m_pszProfileName );
m_pszProfileName = _tcsdup(_T("Alarm-e v1.0")) ; //HKEY_CURRENT_USER\Software\Alarm-e �����Ʒ� �����̸� ����


������Ʈ�� ����
WriteProfile~�Լ��� ����ϴµ� ù���ڴ� Alarm-e v1.0�������� ������ �����ڴ� ���� �����ڴ� ��.


������Ʈ�� �б�
GetProfileStringW(_T("registrant"),_T("ID"),_T("��Ͼ���"));
ù���ڴ� Alarm-e v1.0���� ���� ������. �����ڴ� ����, �����ڴ� ���н� ���ϰ�.
������ �� ����




DB�� ���̵� admin ��ȣ�� 123456

/*	��� ���¹�
CDatabase DB;
DB.OpenEx(_T("DBQ=alarm-e.mdb;DefaultDir=.;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=alarm-e.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;PWD=123456;UserCommitSync=Yes;"));
*/

/*	������ resultset ��¹�
CRecordset rs(&DB);
CString Query;
Query.Format(_T("Select * From wordFilter"));

CDBVariant var;
rs.Open(CRecordset::dynaset,Query);

rs.GetFieldValue(_T("word"),var);
CString msg=*var.m_pstring;
*/

/*	���� �����¹�
DB.ExecuteSQL(_T("Insert Into wordFilter (word) Values ('�����߰�')"));
*/