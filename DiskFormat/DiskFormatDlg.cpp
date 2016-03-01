
// DiskFormatDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "DiskFormat.h"
#include "DiskFormatDlg.h"
#include "afxdialogex.h"
#include "DiskFormatClass.h"

DiskFormatClass class1;
CString seldrive=_T("empty");
CString filesystem=_T("");
CString bau_size=_T("");
static bool program_first = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiskFormatDlg 대화 상자


CDiskFormatDlg::CDiskFormatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiskFormatDlg::IDD, pParent)
	, volume_lable(_T(""))
	, quick_format_check(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiskFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	m_Progress.SetPos(0);
	DDX_Control(pDX, IDC_COMBO1, c_SelectDrive);
	DDX_Control(pDX, IDC_COMBO2, c_FileSystem);
	DDX_Control(pDX, IDC_COMBO3, C_BAU_size);
	DDX_Text(pDX, IDC_EDIT1, volume_lable);
	DDX_Check(pDX, IDC_CHECK1, quick_format_check);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);

}

BEGIN_MESSAGE_MAP(CDiskFormatDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDiskFormatDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDiskFormatDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDiskFormatDlg::OnCbnSelchangeCombo3)
	ON_EN_CHANGE(IDC_EDIT1, &CDiskFormatDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiskFormatDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDiskFormatDlg 메시지 처리기

BOOL CDiskFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
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
	if(program_first == false){
		//시스템에 존재하는 하드,이동식디스크 드라이브 읽어오기
		CString strDrive;    // 논리적 드라이브명 임시 저장
		TCHAR pTmp[64];
		memset(pTmp, '\0', 64);
		GetLogicalDriveStrings(64, pTmp);

		for(int i=0 ; i<64 ; i++) {
			if(pTmp[i] == '\0' && pTmp[i+1] == '\0')
				break;
			strDrive.Empty();

			while(pTmp[i] != '\0')
				strDrive += pTmp[i++];

			if (GetDriveType(strDrive) == DRIVE_REMOVABLE || GetDriveType(strDrive) == DRIVE_FIXED) {
				c_SelectDrive.AddString(strDrive);
				if(strcmp((LPSTR)(LPCTSTR)seldrive,"empty")==0){
					seldrive = strDrive;
				}
			}
		}
		c_SelectDrive.SetCurSel(0);

		//////////////////////파일 시스템/////////////////////////
		for(int i = 0; i < 3 ; i++ ){
			c_FileSystem.InsertString(i, class1.filesystem_list(i));
		}
		c_FileSystem.SetCurSel(2);

		////////////////////할당 단위 크기////////////////////////
		for(int i = 0; i < 6 ; i++ ){
			C_BAU_size.InsertString(i, class1.bau_size_list(i));
		}
		C_BAU_size.SetCurSel(0);
	}
	
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDiskFormatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDiskFormatDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiskFormatDlg::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//콤보 박스의 해당 인덱스 위치의 항목 값을 얻어온다.
}

void CDiskFormatDlg::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDiskFormatDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDiskFormatDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	
	c_SelectDrive.GetLBText(c_SelectDrive.GetCurSel(), seldrive);
	c_FileSystem.GetLBText(c_FileSystem.GetCurSel(), filesystem);
	C_BAU_size.GetLBText(C_BAU_size.GetCurSel(), bau_size);

	class1.drive = seldrive;
	class1.filesystem = filesystem;
	class1.bau_size = bau_size;
	class1.volume_lable=volume_lable;
	class1.quick_format=quick_format_check;
	int real_bausize = class1.ret_bau_size(bau_size);

	class1.Start_format(class1.drive, class1.filesystem, real_bausize,
						class1.volume_lable, class1.quick_format);
	program_first = true;
	m_Progress.SetPos(100);
	UpdateData(FALSE);
	AfxMessageBox(_T("포맷을 완료하였습니다."),MB_ICONINFORMATION|MB_OK);
}