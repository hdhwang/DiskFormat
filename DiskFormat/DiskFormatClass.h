#include <afx.h>
#include <afxwin.h>

#ifndef DiskFormatClass_H
#define DiskFormatClass_H

class DiskFormatClass{
public:
	DiskFormatClass();
	virtual ~DiskFormatClass();

	CString drive_list(int i);
	CString filesystem_list(int num);//���� �ý��۸� ���� �Լ�
	CString bau_size_list(int num);//���� �ý��۸� ���� �Լ�
	int ret_bau_size(CString val);


	CString drive;
	CString filesystem;
	CString bau_size;
	CString volume_lable;//���� ���̺�� ���� ����
	bool quick_format;//���� ���� �ɼ� ����
	int real_bau_size;

	//����̺� ���� ���� �Լ�
	BOOL Start_format(CString drive, CString filesystem,
					int real_bau_size, CString volume_lable, bool quick_format);

};

#endif