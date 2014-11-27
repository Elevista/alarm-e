#pragma once

class JKRegistry
{
public:
	JKRegistry();
	JKRegistry(HKEY nKEY);
	JKRegistry(HKEY nKEY,const WCHAR * szPath);
	JKRegistry(HKEY nKEY,const WCHAR * szPath,const WCHAR * szName);	
	~JKRegistry();

	//레지스트리에 문자열 저장
	BOOL SetString (HKEY nKEY,const WCHAR * szPath,const WCHAR * szName, const WCHAR * szValue);
	BOOL SetString (const WCHAR * szPath, const WCHAR * szName, const WCHAR * szValue);
	BOOL SetString (const WCHAR * szValue);
	//레지스트리에 숫자 저장
	BOOL SetInteger(HKEY HKey, const WCHAR * szPath, const WCHAR * szName, const DWORD dwValue);
	BOOL SetInteger(const WCHAR * szName, const DWORD dwValue);
	BOOL SetInteger(const DWORD dwValue);
	//레지스트리에 문자열 읽기
	BOOL GetString(HKEY HKey, const WCHAR * szPath, const WCHAR * szName, const WCHAR * szValue);
	BOOL GetString(const WCHAR * szName, const WCHAR * szValue);
	BOOL GetString(const WCHAR * szValue);
	//레지스트리에 숫자 일기
	DWORD GetInteger(HKEY HKEY, const WCHAR * szPath, const WCHAR * szName);
	DWORD GetInteger(const WCHAR * szPath, const WCHAR * szName);
	DWORD GetInteger(const WCHAR * szName);
	DWORD GetInteger();
	// Root 키 설정 또는 변경
	void SetHKey (HKEY nKey);
	// Path 설정 또는 변경
	void SetPath (const WCHAR * szPath);
	// 벨류명 설정 또는 변경
	void SetName (const WCHAR * szName);
	// Path 삭제
	BOOL DeletePath(HKEY HKey, const WCHAR * szPath);
	BOOL DeletePath(const WCHAR * szPath);
	BOOL DeletePath();
	//벨류 삭제
	BOOL DeleteName (HKEY HKey, const WCHAR * szPath, const WCHAR * szName);
	BOOL DeleteName (const WCHAR * szPath, const WCHAR * szName);
	BOOL DeleteName (const WCHAR * szName);
	BOOL DeleteName ();

protected:
	HKEY m_hkey;
	WCHAR m_szPath[100];
	WCHAR m_szName[100];
};