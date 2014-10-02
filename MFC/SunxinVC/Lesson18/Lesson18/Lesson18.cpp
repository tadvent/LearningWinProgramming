// Lesson18.cpp : CLesson18App 和 DLL 注册的实现。

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



// CLesson18App::InitInstance - DLL 初始化

BOOL CLesson18App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CLesson18App::ExitInstance - DLL 终止

int CLesson18App::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
