// Lesson06.h : Lesson06 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CLesson06App:
// 有关此类的实现，请参阅 Lesson06.cpp
//

class CLesson06App : public CWinApp
{
public:
	CLesson06App();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnTest();
public:
    afx_msg void OnTest();
};

extern CLesson06App theApp;