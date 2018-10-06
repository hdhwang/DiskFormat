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

//시스템에 존재하는 하드,이동식디스크 드라이브 읽어오는 함수
 CString DiskFormatClass::drive_list(int i){
	 
	 return _T("");
 }

 //파일 시스템 지정 함수
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

 //할당 단위 크기 지정 함수
 CString DiskFormatClass:: bau_size_list(int num){
	 switch(num){
	 case 0 :
		 return _T("기본 할당 크기");

	 case 1 :
		 return _T("4096바이트");

	 case 2 :
		 return _T("8192바이트");

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
	 if(val==_T("기본 할당 크기")){
		return 4096;
	 }

	 else if(val==_T("4096바이트")){
		return 4096;
	 }

	 else if(val==_T("8192바이트")){
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