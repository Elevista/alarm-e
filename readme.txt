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
