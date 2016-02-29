#include <afx.h>
#include <afxwin.h>

#ifndef DiskFormatClass_H
#define DiskFormatClass_H

class DiskFormatClass{
public:
	DiskFormatClass();
	virtual ~DiskFormatClass();

	CString drive_list(int i);
	CString filesystem_list(int num);//파일 시스템명 지정 함수
	CString bau_size_list(int num);//파일 시스템명 지정 함수
	int ret_bau_size(CString val);


	CString drive;
	CString filesystem;
	CString bau_size;
	CString volume_lable;//볼륨 레이블명 저장 변수
	bool quick_format;//빠른 포맷 옵션 변수
	int real_bau_size;

	//드라이브 포맷 수행 함수
	BOOL Start_format(CString drive, CString filesystem,
					int real_bau_size, CString volume_lable, bool quick_format);

};

#endif