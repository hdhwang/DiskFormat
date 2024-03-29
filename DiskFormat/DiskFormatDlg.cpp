
// DiskFormatDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "DiskFormat.h"
#include "DiskFormatDlg.h"
#include "afxdialogex.h"
#include "DiskFormatClass.h"

DiskFormatClass diskFormatClass;
CString seldrive = _T("empty");
CString filesystem = _T("");
CString cluster_size = _T("");
static bool program_first = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiskFormatDlg 대화 상자



CDiskFormatDlg::CDiskFormatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DISKFORMAT_DIALOG, pParent)
	, c_editLabel(_T(""))
	, c_checkQuickFormat(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiskFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//m_Progress.SetPos(0);
	DDX_Control(pDX, comboDrive, c_comboDrive);
	DDX_Control(pDX, comboFileSystem, c_comboFileSystem);
	DDX_Control(pDX, comboClusterSize, c_comboClusterSize);
	DDX_Text(pDX, editLabel, c_editLabel);
	DDX_Check(pDX, checkBoxQuickFormat, c_checkQuickFormat);
	DDX_Control(pDX, progressFormat, m_Progress);
}

BEGIN_MESSAGE_MAP(CDiskFormatDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(buttonFormat, &CDiskFormatDlg::OnBnClickedbuttonformat)
END_MESSAGE_MAP()


// CDiskFormatDlg 메시지 처리기

BOOL CDiskFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDiskFormatDlg::OnPaint()
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
	if (program_first == false)
	{
		//시스템에 존재하는 하드,이동식디스크 드라이브 읽어오기
		CString strDrive;	// 논리적 드라이브명 임시 저장
		TCHAR pTmp[64];
		memset(pTmp, '\0', 64);
		GetLogicalDriveStrings(64, pTmp);

		for (int i = 0; i < 64; i++)
		{
			if (pTmp[i] == '\0' && pTmp[i + 1] == '\0')
			{
				break;
			}
			strDrive.Empty();

			while (pTmp[i] != '\0')
			{
				strDrive += pTmp[i++];
			}

			if (GetDriveType(strDrive) == DRIVE_REMOVABLE || GetDriveType(strDrive) == DRIVE_FIXED)
			{
				c_comboDrive.AddString(strDrive);
				if (strcmp((LPSTR)(LPCTSTR)seldrive, "empty") == 0)
				{
					seldrive = strDrive;
				}
			}
		}
		c_comboDrive.SetCurSel(0);

		//파일 시스템
		for (int i = 0; i < 4; i++)
		{
			c_comboFileSystem.InsertString(i, diskFormatClass.filesystem_list(i));
		}
		c_comboFileSystem.SetCurSel(2);

		//할당 단위 크기
		for (int i = 0; i < 6; i++)
		{
			c_comboClusterSize.InsertString(i, diskFormatClass.bau_size_list(i));
		}
		c_comboClusterSize.SetCurSel(0);

		program_first = true;
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDiskFormatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDiskFormatDlg::OnBnClickedbuttonformat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxGetApp()->m_pszAppName = _T("확인");

	if (AfxMessageBox(_T("경고: 포맷하면 디스크의 모든 데이터가 지워집니다.\n\n디스크를 포맷하려면 [확인]을 클릭하고, 취소하려면 [취소]를 클릭하십시오."), MB_YESNO) == IDYES)
	{
		UpdateData(TRUE);

		c_comboDrive.GetLBText(c_comboDrive.GetCurSel(), seldrive);
		c_comboFileSystem.GetLBText(c_comboFileSystem.GetCurSel(), filesystem);
		c_comboClusterSize.GetLBText(c_comboClusterSize.GetCurSel(), cluster_size);

		diskFormatClass.drive = seldrive;
		diskFormatClass.filesystem = filesystem;
		diskFormatClass.bau_size = cluster_size;
		diskFormatClass.volume_lable = c_editLabel;
		diskFormatClass.quick_format = c_checkQuickFormat;
		int real_bausize = diskFormatClass.ret_bau_size(cluster_size);

		diskFormatClass.Start_format(diskFormatClass.drive, diskFormatClass.filesystem, real_bausize,
			diskFormatClass.volume_lable, diskFormatClass.quick_format);

		m_Progress.SetPos(100);
		UpdateData(FALSE);

		AfxGetApp()->m_pszAppName = _T("알림");
		AfxMessageBox(_T("포맷을 완료하였습니다."), MB_ICONINFORMATION | MB_OK);

		//progress 상태 초기화
		UpdateData(TRUE);
		m_Progress.SetPos(0);
		UpdateData(FALSE);
	}
}
