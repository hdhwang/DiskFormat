
// DiskFormatDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDiskFormatDlg 대화 상자
class CDiskFormatDlg : public CDialogEx
{
// 생성입니다.
public:
	CDiskFormatDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DISKFORMAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
