레지스트리 폴더 지정
CalarmeApp theApp에 들어있는 메소드임
SetRegistryKey(_T("Alarm-e"));	//HKEY_CURRENT_USER\Software 폴더아래 폴더이름 지정

free( ( void* )m_pszProfileName );
m_pszProfileName = _tcsdup(_T("Alarm-e v1.0")) ; //HKEY_CURRENT_USER\Software\Alarm-e 폴더아래 폴더이름 지정


레지스트리 쓰기
WriteProfile~함수로 등록하는데 첫인자는 Alarm-e v1.0폴더안의 폴더명 둘인자는 값명 셋인자는 값.


레지스트리 읽기
GetProfileStringW(_T("registrant"),_T("ID"),_T("등록없음"));
첫인자는 Alarm-e v1.0폴더 안의 폴더명. 둘인자는 값명, 셋인자는 실패시 리턴값.
성공시 값 리턴




DB는 아이디 admin 암호는 123456

/*	디비 여는법
CDatabase DB;
DB.OpenEx(_T("DBQ=alarm-e.mdb;DefaultDir=.;Driver={Microsoft Access Driver (*.mdb)};DriverId=25;FIL=MS Access;FILEDSN=alarm-e.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;PWD=123456;UserCommitSync=Yes;"));
*/

/*	쿼리로 resultset 얻는법
CRecordset rs(&DB);
CString Query;
Query.Format(_T("Select * From wordFilter"));

CDBVariant var;
rs.Open(CRecordset::dynaset,Query);

rs.GetFieldValue(_T("word"),var);
CString msg=*var.m_pstring;
*/

/*	쿼리 때리는법
DB.ExecuteSQL(_T("Insert Into wordFilter (word) Values ('새로추가')"));
*/