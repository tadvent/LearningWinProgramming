// Lesson18.cpp : CLesson18App �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "Lesson18.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CLesson18App theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x1CC68C59, 0x1060, 0x4B00, { 0x82, 0xCC, 0xB4, 0xC8, 0x7E, 0x7, 0xAE, 0x9B } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CLesson18App::InitInstance - DLL ��ʼ��

BOOL CLesson18App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CLesson18App::ExitInstance - DLL ��ֹ

int CLesson18App::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
