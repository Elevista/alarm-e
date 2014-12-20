
// SimpleFireWallDlg.cpp : 구현 파일
// 사이트 차단 다이얼로그. 실행 권한이 다르기 때문에 따로 프로젝트 생성
// 호스트 파일 변경으로 차단.

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
	, m_siteEdit(_T(""))
	, m_detailEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleFireWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BLOCKLIST, m_blockListBox);
	DDX_Text(pDX, IDC_EDIT_SITE, m_siteEdit);
	DDX_Text(pDX, IDC_EDIT_DETAIL, m_detailEdit);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_X, m_btnX);
}

BEGIN_MESSAGE_MAP(CSimpleFireWallDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_ADD, &CSimpleFireWallDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CSimpleFireWallDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_X, &CSimpleFireWallDlg::OnBnClickedBtnX)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()




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
	m_forwardIp = "121.189.57.82";
	GetWindowsDirectory(windir,MAX_PATH);	//윈도우즈 설치 디렉토리 가져오기
	m_hostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts"),windir);	//호스트 파일 위치
	m_fakeHostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts.temp"),windir);



	HANDLE hMapFile;
	//메모리 매핑 생성 이름은 Alarme_authority
	hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_authority"));
	//권한을 저장할 메모리맵의 포인터를 받아옴
	bool* authority=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&auth,authority,sizeof(bool));//권한을 읽어옴.
	UnmapViewOfFile(authority);//파일 해제


	//로그인 유무 확인 Reg - end

	if (auth){	//권한 확인. 즉 alarm-e 메인 다이얼로그가 관리자 모드로 로그인 되어 있어야만 실행 가능
		
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



BOOL CSimpleFireWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText("사이트 차단");
	
	// 리스트 초기화 
	m_btnX.LoadBitmaps(IDB_X_BTN,IDB_X_CLICK,IDB_X_BTN,IDB_X_BTN);
	m_btnX.SizeToContent();
	m_btnAdd.LoadBitmaps(IDB_INSERT);
	m_btnAdd.SizeToContent();
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	SetBackgroundImage(IDB_BG,BACKGR_TOPLEFT);

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
		sFile.WriteString((CString)comb+"\n");
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
	sFile.WriteString((CString)dataTemp+"\n");
	sFile.Close();

	//to do
}


void CSimpleFireWallDlg::OnBnClickedBtnDel()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_blockListBox.GetFirstSelectedItemPosition();
	
	
		
	if (pos == NULL)
		AfxMessageBox(_T("선택 한 내용이 없습니다."));
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

		file.Replace(dataTemp+"\n", "");
		file.Replace(dataTemp, "");

		
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


void CSimpleFireWallDlg::OnBnClickedBtnX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CSimpleFireWallDlg::OnOK();
}


void CSimpleFireWallDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int height=40;//타이틀바 두께
	int width=590;//창닫기 버튼을 제외한 타이틀바 넓이
	if(point.x<=width&&point.y<=height)
		SendMessage( WM_NCLBUTTONDOWN, HTCAPTION, 0 );	//타이틀바 클릭한걸로 속임

	CDialogEx::OnLButtonDown(nFlags, point);
}
