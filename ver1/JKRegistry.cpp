#include "stdatx.h"
#include "JKRegistry.h"

JKRegistry::JKRegistry()
{
	m_hKey = HKEY_CURRENT_USER;
	wcscpy(m_szPath,TEXT("ControlPanel"));
	wcscpy(m_szName, L"Default");
}

JKRegistry::JKRegistry(HKEY nKey)
{
	m_hKey = nKey;
}

JKRegistry::JKRegistry(HKEY nKey,const WCHAR * szPath)
{
	m_hKey = nKey;
	wcscpy(m_szPath ,szPath);
}
JKRegistry::JKRegistry(HKEY nKey,const WCHAR * szPath,const WCHAR * szName)
{
	m_hKey = nKey;
	wcscpy(m_szPath,szPath);
	wcscpy(m_szName, szName);
}

JKRegistry::~JKRegistry()
{

}

BOOL JKRegistry::SetString(HKEY HKey,const WCHAR * szPath,const WCHAR * szName, const WCHAR *
	szValue)
{
	m_hKey = HKey;
	wcscpy(m_szPath,szPath);
	wcscpy(m_szName ,szName);

	HKEY hKey;

	DWORD dwDisposition = O;

	RegCreateKeyEx(m_hKey, szPath , 0, NULL, 0, 0, NULL, &hKey, &dwDisposition);

	if(!hKey) 
	{
		RegOpenKeyEx(m_hKey, szPath, 0, KEY_ALL_ACCESS, &hKey);
	}
	if(! hKey)
	{
		RegCioseKey(hKey) ;
		return FALSE;
	}
}
DWORD dwRes = RegSetValueEx (hKey,szName,O,REG_SZ, (PBYTE)szValue,(lstrlen(szValue)+1)*sizeof(WCHAR));

RegCloseKey(hKey);

////////////////////
if(dwRes == ERROR_SUCCESS) return TRUE;
return FALSE;
}
BOOL JKRegistry::GetString(HKEY HKey,const WCHAR * szPath,const WCHAR * szName, WCHAR * szValue)
{
	m_hKey = HKey;
	wcscpy(m_szPath,szPath);
	wcscpy (m_szName, szName);

	HKEY hKey;

	RegOpenKeyEx (m_hKey, szPath, 0, KEY_ALL_ACCESS, &hKey);

	//RegCr eateKeyEx(m_hKey, szPath, 0, NULL, 0, 0, NULL, &hKey, &dwDispos iti on);

	if(!hKey)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	DWORD dwSize = 1024;
	DWORD dwType = REG_SZ;
	DWORD dwRes = RegQueryValueEx(hKey, szName, 0, &dwType , (PBYTE)szValue,&dwSize);

	RegCloseKey(hKey) ;

	if(dwRes == ERROR_SUCCESS) return TRUE;
	return FALSE;

}
BOOL JKRegistry::Setlnteger(HKEY HKey,const WCHAR * szPath,const WCHAR * szName , const DWORD dwValue)
{
	m_hKey = HKey;
	wcscpy(m_szPath,szPath);
	wcscpy(m_szName ,szName);

	HKEY hKey;

	DWORD dwDisposition = O;

	RegCreateKeyEx(m_hKey, szPath, 0, NULL, 0, 0, NULL, &hKey, &dwDisposition);

	if(!hKey)
	{
		RegOpenKeyEx(m_hKey, szPath, 0, KEY_ALL_ACCESS, &hKey);
		if( ! hKey)
		{
			RegCloseKey(hKey);
			return FALSE;
		}
	}
	DWORD dwRes = RegSetValueEx (hKey ,szName, O,REG_DWORD,(LPBYTE)&dwValue,sizeof(DWORD));
	RegCioseKey(hKey) ;
	if(dwRes == ERROR_SUCCESS) return TRUE ;
	return FALSE;
	)
		DWORD JKRegistry : :Getlnteger(HKEY HKey,const WCHAR * szPath ,const WCHAR * szName)
	{

		/////////////////////////////////////////////////
		m_hKey = HKey;
		wcscpy(m_szPath ,szPath);
		wcscpy(m_szName, szName);

		HKEY hKey;

		DWORD dwDisposition = O;

		RegOpenKeyEx (m_hKey, szPath, 0, KEY_ALL_ACCESS, &hKey);
		//RegCreateKeyEx(m_hKey, szPath , 0, NULL , 0, 0, NULL , &hKey, &dwDi sposition):

		if(!hKey)
		{
			RegCloseKey(hKey);
			return FALSE;
		}

		DWORD dwValue = O;
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof(DWORD);

		DWORD dwRes = RegQueryValueEx( hKey, szName, 0, &dwType , (LPBYTE)&dwValue, &dwSize);

		RegCioseKey(hKey);

		return dwValue;
	}
	BOOL JKRegistry::SetString (const WCHAR * szPath, const WCHAR * szName, const WCHAR * szValue)
	{ return SetString (m_hKey,szPath,szName,szValue);};
	BOOL JKRegistry::Setlnteger(const WCHAR * szPath, const WCHAR * szName , const DWORD dwValue)
	{ return Setlnteger(m_hKey,szPath,szName,dwValue);};
	BOOL JKRegistry::GetString (const WCHAR * szPath, const WCHAR * szName, WCHAR * szValue)
	{ return GetString (m_hKey,szPath,szName,szValue);};
	DWORD JKRegistry::Getlnteger(const WCHAR * szPath, const WCHAR * szName)
	{ return Getlnteger (m_hKey,szPath,szName) ; };
	BOOL JKRegistry::SetString (const WCHAR * szName, const WCHAR * szValue)
	{ return SetString (m_hKey,m_szPath,szName,szValue); };
	BOOL JKRegistry::GetString (const WCHAR * szName, WCHAR * szValue)
	{ return GetString (m_hKey,m_szPath,szName,szValue); };
	BOOL JKRegistry::Setlnteger(const WCHAR * szName, const DWORD dwValue)
	{ return Setlnteger(m_hKey,m_szPath,szName,dwValue); };
	DWORD JKRegistry::Getlnteger(const WCHAR * szName)
	{ return Getlnteger(m_hKey,m_szPath,szName);	};
	BOOL JKRegistry::SetString (const WCHAR * szValue)
	{ return SetString (m_hKey,m_szPath,m_szName,szValue);	};
	BOOL JKRegist ry::GetString (WCHAR * szValue)
	{ return GetString (m_hKey,m_szPath,m_szName,szValue);	};
	BOOL JKRegistry::Setlnteger(const DWORD dwValue)
	{ return Setlnteger(m_hKey,m_szPath,m_szName,dwValue);	};
	DWORD JKRegistry::Get Integer()
	{ return Getlnteger(m_hKey,m_szPath ,m_szName);
	VOID JKRegistry: :SetHKey(HKEY HKey) {m_hKey = HKey; };
	VOID JKRegistry: :SetPath(const WCHAR * szPath) {wcscpy(m_szPath,szPath); };
	VOID JKRegistry : :SetName (const WCHAR * szName) {wcscpy(m_szName,szName);};


	BOOL JKRegistry::DeletePath(HKEY HKey , const WCHAR * szPath)
	{
		m_hKey = HKey;
		wcscpy(m_szPath,szPath) ;

		DWORD dwRes = RegDeleteKey(m_hKey,m_szPath);

		if(dwRes == ERROR_SUCCESS) return TRUE;
		return FALSE ;
		///////////////////////////////////
	}
	BOOL JKRegistry::DeleteName(HKEY HKey, const WCHAR * szPath, const WCHAR * szName)
	{
		m_hKey = HKey;
		wcscpy(m_szPath,szPath);
		wcscpy(m_szName, szName ) ;

		HKEY hKey;

		RegOpenKeyEx (m_hKey, m_szPath, 0, KEY_ALL_ACCESS, &hKey);
		if(!hKey)
		{
			RegCloseKey(hKey);
			return FALSE;
		}

		DWORD dwRes = RegDeleteValue( hKey, m_szName);

		RegCloseKey(hKey);

		if(dwRes == ERROR_SUCCESS) return TRUE;
		return FALSE;
		BOOL JKRegistry::DeletePath()
		{ return DeletePath(m_hKey, m_szPath); };
		BOOL JKRegistry::DeletePath(const WCHAR * szPath)
		{ return DeletePath(m_hKey, szPath); };
		BOOL JKRegistry::DeleteName()
		{ return DeleteName(m_hKey, m_szPath,m_szName); };
		BOOL JKRegistry::DeleteName(const WCHAR * szName)
		{ return DeleteName(m_hKey, m_szPath,szName); };
		BOOL JKRegistry::DeleteName(const WCHAR * szPath, const WCHAR * szName)
		{ return DeleteName(m_hKey, szPath,szName); };


