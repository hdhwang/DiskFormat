
// DiskFormatDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDiskFormatDlg ��ȭ ����
class CDiskFormatDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDiskFormatDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DISKFORMAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox c_SelectDrive;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox c_FileSystem;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox C_BAU_size;
	afx_msg void OnEnChangeEdit1();
	CString volume_lable;
	afx_msg void OnBnClickedButton1();
	BOOL quick_format_check;
	CProgressCtrl m_Progress;
};
