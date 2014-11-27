#pragma once

class JKRegistry
{
public:
	JKRegistry();
	JKRegistry(HKEY nKEY);
	JKRegistry(HKEY nKEY,const WCHAR * szPath);
	JKRegistry(HKEY nKEY,const WCHAR * szPath,const WCHAR * szName);	
	~JKRegistry();

	//������Ʈ���� ���ڿ� ����
	BOOL SetString (HKEY nKEY,const WCHAR * szPath,const WCHAR * szName, const WCHAR * szValue);
	BOOL SetString (const WCHAR * szPath, const WCHAR * szName, const WCHAR * szValue);
	BOOL SetString (const WCHAR * szValue);
	//������Ʈ���� ���� ����
	BOOL SetInteger(HKEY HKey, const WCHAR * szPath, const WCHAR * szName, const DWORD dwValue);
	BOOL SetInteger(const WCHAR * szName, const DWORD dwValue);
	BOOL SetInteger(const DWORD dwValue);
	//������Ʈ���� ���ڿ� �б�
	BOOL GetString(HKEY HKey, const WCHAR * szPath, const WCHAR * szName, const WCHAR * szValue);
	BOOL GetString(const WCHAR * szName, const WCHAR * szValue);
	BOOL GetString(const WCHAR * szValue);
	//������Ʈ���� ���� �ϱ�
	DWORD GetInteger(HKEY HKEY, const WCHAR * szPath, const WCHAR * szName);
	DWORD GetInteger(const WCHAR * szPath, const WCHAR * szName);
	DWORD GetInteger(const WCHAR * szName);
	DWORD GetInteger();
	// Root Ű ���� �Ǵ� ����
	void SetHKey (HKEY nKey);
	// Path ���� �Ǵ� ����
	void SetPath (const WCHAR * szPath);
	// ������ ���� �Ǵ� ����
	void SetName (const WCHAR * szName);
	// Path ����
	BOOL DeletePath(HKEY HKey, const WCHAR * szPath);
	BOOL DeletePath(const WCHAR * szPath);
	BOOL DeletePath();
	//���� ����
	BOOL DeleteName (HKEY HKey, const WCHAR * szPath, const WCHAR * szName);
	BOOL DeleteName (const WCHAR * szPath, const WCHAR * szName);
	BOOL DeleteName (const WCHAR * szName);
	BOOL DeleteName ();

protected:
	HKEY m_hkey;
	WCHAR m_szPath[100];
	WCHAR m_szName[100];
};