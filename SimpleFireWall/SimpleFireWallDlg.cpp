
// SimpleFireWallDlg.cpp : ���� ����
// ����Ʈ ���� ���̾�α�. ���� ������ �ٸ��� ������ ���� ������Ʈ ����
// ȣ��Ʈ ���� �������� ����.

#include "stdafx.h"
#include "SimpleFireWall.h"
#include "SimpleFireWallDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
	

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSimpleFireWallDlg ��ȭ ����



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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSimpleFireWallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSimpleFireWallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CSimpleFireWallDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//�α��� ���� Ȯ�� Reg - start

	DWORD dwType = REG_SZ;
	DWORD dwSize = 16;
	HKEY hKey;
	TCHAR szBuffer[16] = { '\0', };
	bool auth = false;
	m_forwardIp = "121.189.57.82";
	GetWindowsDirectory(windir,MAX_PATH);	//�������� ��ġ ���丮 ��������
	m_hostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts"),windir);	//ȣ��Ʈ ���� ��ġ
	m_fakeHostsPath.Format(_T("%s\\System32\\drivers\\etc\\hosts.temp"),windir);



	HANDLE hMapFile;
	//�޸� ���� ���� �̸��� Alarme_authority
	hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(bool),_T("Alarme_authority"));
	//������ ������ �޸𸮸��� �����͸� �޾ƿ�
	bool* authority=(bool*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(bool));
	memcpy(&auth,authority,sizeof(bool));//������ �о��.
	UnmapViewOfFile(authority);//���� ����


	//�α��� ���� Ȯ�� Reg - end

	if (auth){	//���� Ȯ��. �� alarm-e ���� ���̾�αװ� ������ ���� �α��� �Ǿ� �־�߸� ���� ����
		
	}
	else{
		AfxMessageBox(_T("������ ���� �մϴ�."));
		return -1;
	}

	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}



BOOL CSimpleFireWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText("����Ʈ ����");
	
	// ����Ʈ �ʱ�ȭ 
	m_btnX.LoadBitmaps(IDB_X_BTN,IDB_X_CLICK,IDB_X_BTN,IDB_X_BTN);
	m_btnX.SizeToContent();
	m_btnAdd.LoadBitmaps(IDB_INSERT);
	m_btnAdd.SizeToContent();
	m_btnDelete.LoadBitmaps(IDB_DELETE);
	m_btnDelete.SizeToContent();
	SetBackgroundImage(IDB_BG,BACKGR_TOPLEFT);

	m_blockListBox.DeleteAllItems();

	// ����Ʈ ��Ÿ�� ����
	m_blockListBox.SetExtendedStyle(LVS_EX_GRIDLINES);

	// Ÿ��Ʋ ����
	m_blockListBox.InsertColumn(0, _T("���� ����Ʈ"), LVCFMT_LEFT, 310, -1);
	m_blockListBox.InsertColumn(1, _T("����"), LVCFMT_CENTER, 109, -1);
	//hosts file init setting start
	CStdioFile     sFile;

	BOOL    bRet = FALSE;
	BOOL    bInit = FALSE;
	

	TCHAR	tszFilePath[MAX_PATH] = { 0 };
	TCHAR	tszWrite[MAX_PATH] = { 0 };
	_tsetlocale(LC_ALL, _T("Kor"));
	CString line;

	CString comb = _T("# SimpleFireWall�� ���� �����͵� �Դϴ�. ���� �ÿ� ������ ���� �� �ֽ��ϴ�.");
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
	
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSimpleFireWallDlg::OnBnClickedBtnAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	
	UpdateData(TRUE);

	if (m_siteEdit.IsEmpty()){
		AfxMessageBox(_T("���� �� ����Ʈ�� ����ֽ��ϴ�."));
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	POSITION pos = m_blockListBox.GetFirstSelectedItemPosition();
	
	
		
	if (pos == NULL)
		AfxMessageBox(_T("���� �� ������ �����ϴ�."));
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CSimpleFireWallDlg::OnOK();
}


void CSimpleFireWallDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int height=40;//Ÿ��Ʋ�� �β�
	int width=590;//â�ݱ� ��ư�� ������ Ÿ��Ʋ�� ����
	if(point.x<=width&&point.y<=height)
		SendMessage( WM_NCLBUTTONDOWN, HTCAPTION, 0 );	//Ÿ��Ʋ�� Ŭ���Ѱɷ� ����

	CDialogEx::OnLButtonDown(nFlags, point);
}
