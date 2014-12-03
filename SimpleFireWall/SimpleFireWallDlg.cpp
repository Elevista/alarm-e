
// SimpleFireWallDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SimpleFireWall.h"
#include "SimpleFireWallDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
	

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimpleFireWallDlg 대화 상자



CSimpleFireWallDlg::CSimpleFireWallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleFireWallDlg::IDD, pParent)
	//, m_siteEdit(_T(""))
	//, m_detailEdit(_T(""))
	, m_siteEdit(_T(""))
	, m_detailEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleFireWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BLOCKLIST, m_blockListBox);
	DDX_Control(pDX, IDC_BLOCKLIST, m_blockListBox);
	DDX_Text(pDX, IDC_EDIT_SITE, m_siteEdit);
	DDX_Text(pDX, IDC_EDIT_DETAIL, m_detailEdit);
}

BEGIN_MESSAGE_MAP(CSimpleFireWallDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_ADD, &CSimpleFireWallDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CSimpleFireWallDlg::OnBnClickedBtnDel)
END_MESSAGE_MAP()


// CSimpleFireWallDlg 메시지 처리기

//BOOL CSimpleFireWallDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
//
//	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
//	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
//	ASSERT(IDM_ABOUTBOX < 0xF000);
//
//	CMenu* pSysMenu = GetSystemMenu(FALSE);
//	if (pSysMenu != NULL)
//	{
//		BOOL bNameValid;
//		CString strAboutMenu;
//		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
//		ASSERT(bNameValid);
//		if (!strAboutMenu.IsEmpty())
//		{
//			pSysMenu->AppendMenu(MF_SEPARATOR);
//			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
//		}
//	}
//
//	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
//	//  프레임워크가 이 작업을 자동으로 수행합니다.
//	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
//	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
//
//	// TODO: 여기에 추가 초기화 작업을 추가합니다.
//
//	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
//}

void CSimpleFireWallDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSimpleFireWallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSimpleFireWallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CSimpleFireWallDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//로그인 유무 확인 Reg - start

	DWORD dwType = REG_SZ;
	DWORD dwSize = 16;
	HKEY hKey;
	TCHAR szBuffer[16] = { '\0', };
	bool auth = false;
	//LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Alarm-e\\Alarm-e v1.0\\authority"), 0, KEY_READ, &hKey);
	m_forwardIp = "127.0.0.1";
	GetWindowsDirectory(windir,MAX_PATH);
	m_hostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts"),windir);
	m_fakeHostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts.temp"),windir);/*
	if (ERROR_SUCCESS == lResult)
	{
		RegQueryValueEx(hKey, _T("power"), NULL, &dwType, (LPBYTE)szBuffer, &dwSize);
		RegCloseKey(hKey);
		auth = szBuffer[0];
	}*/




	HANDLE hMapFile;
	//메모리 매핑 생성 이름은 Alarme_authority
	hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_authority"));
	//권한을 저장할 메모리맵의 포인터를 받아옴
	bool* authority=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&auth,authority,sizeof(bool));//권한을 읽어옴.
	UnmapViewOfFile(authority);//파일 해제


	//로그인 유무 확인 Reg - end

	if (auth){
		
	}
	else{
		AfxMessageBox(_T("권한이 부족 합니다."));
		return -1;
	}

	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}



//void CSimpleFireWallDlg::PreInitDialog()
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	AfxMessageBox(_T("권한이 부족 합니다."));
//
//
//	CDialogEx::PreInitDialog();
//}


BOOL CSimpleFireWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	//m_blockListBox.AddString(_T("ttttt"));
	
//	m_detailEdit = "ttttt";
	
	// 리스트 초기화 
	m_blockListBox.DeleteAllItems();

	// 리스트 스타일 설정
	m_blockListBox.SetExtendedStyle(LVS_EX_GRIDLINES);

	// 타이틀 삽입
	m_blockListBox.InsertColumn(0, _T("차단 사이트"), LVCFMT_LEFT, 310, -1);
	m_blockListBox.InsertColumn(1, _T("설명"), LVCFMT_CENTER, 109, -1);
	//hosts file init setting start
	CStdioFile     sFile;

	BOOL    bRet = FALSE;
	BOOL    bInit = FALSE;
	

	TCHAR	tszFilePath[MAX_PATH] = { 0 };
	TCHAR	tszWrite[MAX_PATH] = { 0 };
	_tsetlocale(LC_ALL, _T("Kor"));
	CString line;

	CString comb = _T("# SimpleFireWall을 위한 데이터들 입니다. 수정 시에 문제가 있을 수 있습니다.");
	ULONGLONG fileOffset = 0;
	bRet = sFile.Open(m_hostsPath, CFile::modeReadWrite | CFile::typeText);

	if (bRet){
		while (sFile.ReadString(line))
		{
			
			
			line.Remove(_T('\r'));
			line.Remove(_T('\n'));
			if (comb.Compare(line) == 0){
				bInit = true;
				fileOffset = sFile.GetPosition();
			}

		}

		
	}
	if (!bInit){
		sFile.SeekToEnd();
		sFile.WriteString(_T("\r\n"));
		sFile.WriteString((CString)comb);
		fileOffset = sFile.SeekToEnd();
	}
	sFile.Seek(fileOffset, CFile::begin);
	while (sFile.ReadString(line))
	{
		CArray<CString, CString> v;
		CString field;
		int index = 0;
		int list4index = 0;
		while (AfxExtractSubString(field, line, index, _T('\t')))
		{
			field.Remove(_T('#'));
			v.Add(field);
			if (index == 1){
				m_blockListBox.InsertItem(list4index, v.GetAt(index));
			}
			if (index == 2){
				m_blockListBox.SetItem(list4index, 1, LVIF_TEXT, v.GetAt(index), 0, 0, 0, NULL);
			}
			index++;
		}
		list4index++;
	}
	sFile.Close();
	//hosts file init setting end
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSimpleFireWallDlg::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	
	UpdateData(TRUE);

	if (m_siteEdit.IsEmpty()){
		AfxMessageBox(_T("차단 할 사이트가 비어있습니다."));
		UpdateData(FALSE);
		return;
		
	}

	
	m_blockListBox.InsertItem(0, m_siteEdit);
	m_blockListBox.SetItem(0, 1, LVIF_TEXT,m_detailEdit, 0, 0, 0, NULL);
	
	siteAdd();
	m_detailEdit.Empty();
	m_siteEdit.Empty();
	UpdateData(FALSE);
	
	
	
	
	
	

}



void CSimpleFireWallDlg::siteAdd()
{
	CString dataTemp;
	dataTemp = m_forwardIp + "\t" + m_siteEdit + "\t#" + m_detailEdit;
	


	CStdioFile     sFile;
	dataTemp = dataTemp;
	sFile.Open(m_hostsPath, CFile::modeReadWrite | CFile::typeText);
	sFile.SeekToEnd();
	sFile.WriteString(_T("\r\n"));
	sFile.WriteString((CString)dataTemp);
	sFile.Close();

	//to do
}


void CSimpleFireWallDlg::OnBnClickedBtnDel()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_blockListBox.GetFirstSelectedItemPosition();
	
	
		
	if (pos == NULL)
		AfxMessageBox(_T("선택 한 내용이 없습니다.\n"));
	else
	{
		CString dataTemp = _T("tests");
		CString line , file;
		BOOL    bRet = FALSE;
		CStdioFile     sFile;
		ULONGLONG fileOffset;
		bRet = sFile.Open(m_hostsPath, CFile::modeReadWrite | CFile::typeText);

				
		int nItem = m_blockListBox.GetNextSelectedItem(pos);
			
		CString temp = m_blockListBox.GetItemText(nItem, 0);
		CString temp2 = m_blockListBox.GetItemText(nItem, 1);
		m_blockListBox.DeleteItem(nItem);
		dataTemp = m_forwardIp +"\t" + temp + "\t#" + temp2;

		
		if (bRet){
				
			while (sFile.ReadString(line)){

				file = file + line + "\n";

			}
				
		}
		sFile.Close();

		file.Replace(dataTemp , "");
		file.Replace("\r\n\r\n" , "\r\n");

		
		bRet = sFile.Open(m_fakeHostsPath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
		sFile.WriteString(file);
		sFile.Close();
		try{
			CFile::Remove(m_hostsPath);
			CFile::Rename(m_fakeHostsPath, m_hostsPath);
		}
		catch(CFileException* pEx )
		{
			TRACE(_T("File %20s not found, cause = %d\n"), m_fakeHostsPath, pEx->m_cause);
			pEx->Delete();
		}

		
		
		
	}
}
