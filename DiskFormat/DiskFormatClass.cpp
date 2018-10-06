#include "StdAfx.h"
#include "afxdialogex.h"
#include "DiskFormatClass.h"
#include "FMIFS.H"
#include <iostream>

using namespace std;


DiskFormatClass::DiskFormatClass(){
}
 DiskFormatClass::~DiskFormatClass(){
}

 BOOLEAN __stdcall FormatExCallback(CALLBACKCOMMAND Command, DWORD Modifier, PVOID Argument){
	 PDWORD percent;
	 PTEXTOUTPUT output;
	 PBOOLEAN status;
	 static BOOLEAN createStructures = FALSE;

	 switch(Command){
	 case PROGRESS:
		 percent = (PDWORD)Argument;
		 break;

	 case OUTPUT:
		 output = (PTEXTOUTPUT)Argument;
		 break;

	 case DONE:
		 status = (PBOOLEAN)Argument;
		 if(*status ==TRUE){

		 }
		 else
			break;
	 }
	 return TRUE;
 }

//�ý��ۿ� �����ϴ� �ϵ�,�̵��ĵ�ũ ����̺� �о���� �Լ�
 CString DiskFormatClass::drive_list(int i){
	 
	 return _T("");
 }

 //���� �ý��� ���� �Լ�
 CString DiskFormatClass:: filesystem_list(int num){
	 switch(num){
	 case 0 :
		 return _T("FAT");
	 
	 case 1 :
		 return _T("FAT32");

	 case 2 :
		 return _T("NTFS");

	 default: 
		 return _T("");
	 }

	 return _T("");
 }

 //�Ҵ� ���� ũ�� ���� �Լ�
 CString DiskFormatClass:: bau_size_list(int num){
	 switch(num){
	 case 0 :
		 return _T("�⺻ �Ҵ� ũ��");

	 case 1 :
		 return _T("4096����Ʈ");

	 case 2 :
		 return _T("8192����Ʈ");

	 case 3 :
		 return _T("16KB");

	 case 4 :
		 return _T("32KB");

	 case 5 :
		 return _T("64KB");

	 default: 
		 return _T("");
	 }

	 return _T("");
 }

 int DiskFormatClass::ret_bau_size(CString val){
	 if(val==_T("�⺻ �Ҵ� ũ��")){
		return 4096;
	 }

	 else if(val==_T("4096����Ʈ")){
		return 4096;
	 }

	 else if(val==_T("8192����Ʈ")){
		return 8192;
	 }

	 else if(val==_T("16KB")){
		return 16384;
	 }

	 else if(val==_T("32KB")){
		 return 32768;
	 }

	 return 4096;
 }



 BOOL DiskFormatClass::Start_format(CString drive, CString filesystem,
	 int real_bau_size, CString volume_lable, bool quick_format){
		WCHAR WCdrive[8];
		memset(WCdrive,0,sizeof(WCdrive));
		WCHAR WCfilesystem[128];
		memset(WCfilesystem,0,sizeof(WCfilesystem));
		WCHAR WCvolume_lable[128];
		memset(WCvolume_lable,0,sizeof(WCvolume_lable));
		wcscpy_s(WCdrive, drive.GetBuffer(0));
		wcscpy_s(WCfilesystem, filesystem.GetBuffer(0));
		wcscpy_s(WCvolume_lable, volume_lable.GetBuffer(0));
		


		DWORD driveType;
		DWORD media;
		driveType = GetDriveTypeW(WCdrive);
		
		if(driveType != DRIVE_FIXED){
			media = FMIFS_FLOPPY;
		}
		
		if(driveType == DRIVE_FIXED){
			media = FMIFS_HARDDISK;
		}

		if(driveType == DRIVE_REMOVABLE){
			media = FMIFS_REMOVABLE;
		}

		PFORMATEX FormatEx;
		HMODULE hModule;
		hModule = LoadLibrary(_T("fmifs.dll"));
		if (hModule == NULL)
			return FALSE;

		if (!(FormatEx = (PFORMATEX) GetProcAddress (GetModuleHandle (_T("fmifs.dll")), "FormatEx")))
		{
			FreeLibrary (hModule);
			return FALSE;
		}

		FormatEx (WCdrive, media, WCfilesystem, WCvolume_lable, quick_format, real_bau_size, FormatExCallback);
 }