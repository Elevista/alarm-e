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
