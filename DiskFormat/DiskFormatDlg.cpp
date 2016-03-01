
// DiskFormatDlg.cpp : ���� ����
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


// CDiskFormatDlg ��ȭ ����


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


// CDiskFormatDlg �޽��� ó����

BOOL CDiskFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDiskFormatDlg::OnPaint()
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
	if(program_first == false){
		//�ý��ۿ� �����ϴ� �ϵ�,�̵��ĵ�ũ ����̺� �о����
		CString strDrive;    // ���� ����̺�� �ӽ� ����
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

		//////////////////////���� �ý���/////////////////////////
		for(int i = 0; i < 3 ; i++ ){
			c_FileSystem.InsertString(i, class1.filesystem_list(i));
		}
		c_FileSystem.SetCurSel(2);

		////////////////////�Ҵ� ���� ũ��////////////////////////
		for(int i = 0; i < 6 ; i++ ){
			C_BAU_size.InsertString(i, class1.bau_size_list(i));
		}
		C_BAU_size.SetCurSel(0);
	}
	
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDiskFormatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDiskFormatDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CDiskFormatDlg::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//�޺� �ڽ��� �ش� �ε��� ��ġ�� �׸� ���� ���´�.
}

void CDiskFormatDlg::OnCbnSelchangeCombo3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDiskFormatDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDiskFormatDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	AfxMessageBox(_T("������ �Ϸ��Ͽ����ϴ�."),MB_ICONINFORMATION|MB_OK);
}