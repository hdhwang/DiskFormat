
// DiskFormat.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDiskFormatApp:
// �� Ŭ������ ������ ���ؼ��� DiskFormat.cpp�� �����Ͻʽÿ�.
//

class CDiskFormatApp : public CWinApp
{
public:
	CDiskFormatApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDiskFormatApp theApp;