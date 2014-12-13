#include "StdAfx.h"
#include "RegManager.h"


CRegManager::CRegManager(void)
{
}


CRegManager::~CRegManager(void)
{
}


void CRegManager::SetID(CString id)
{
	AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ID"),id);
}


CString CRegManager::GetID(void)
{
	return AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ID"),_T("등록없음"));
}


bool CRegManager::GetScreenShotVal(void)
{
	CString value=AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("false"));
	if(value.Compare(_T("true"))==0){
		return true;
	}else{
		return false;
	}
}


void CRegManager::SetScreenShotVal(bool value)
{
	if(value){
		AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("true"));
	}else{
		AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotValue"),_T("false"));
	}
}


int CRegManager::GetScreenShotFreq(void)
{
	return _ttoi(AfxGetApp()->GetProfileStringA(_T("Setting"),_T("ScreenShotTime"),_T("30")));
}


void CRegManager::SetScreenShotFreq(int second)
{
	CString val;
	val.Format("%d",second);
	AfxGetApp()->WriteProfileStringA(_T("Setting"),_T("ScreenShotTime"),val);
}
