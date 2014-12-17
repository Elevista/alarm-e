//레지스트리를 관리하는 메소드들을 모아놓은 파일입니다.

#include "StdAfx.h"
#include "RegManager.h"


CRegManager::CRegManager(void)
{
}


CRegManager::~CRegManager(void)
{
}


void CRegManager::SetID(CString id)	//레지에 아이디 저장
{
	AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ID"),id);
}


CString CRegManager::GetID(void)	//레지에서 아이디 불러옴
{
	return AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ID"),_T("등록없음"));
}


bool CRegManager::GetScreenShotVal(void)	//자동스크린샷이 활성화인지 아닌지 얻어옴
{
	CString value=AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("false"));
	if(value.Compare(_T("true"))==0){
		return true;
	}else{
		return false;
	}
}


void CRegManager::SetScreenShotVal(bool value)	//자동 스크린샷 활성비활성 레지 작성
{
	if(value){
		AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("true"));
	}else{
		AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("false"));
	}
}


int CRegManager::GetScreenShotFreq(void)	//자동스샷 주기 초 읽어옴
{
	return _ttoi(AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ScreenShotTime"),_T("30")));
}


void CRegManager::SetScreenShotFreq(int second)	//자동스샷 주기 초 셋팅
{
	CString val;
	val.Format("%d",second);
	AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotTime"),val);
}
