// Lesson09.h : Lesson09 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CLesson09App:
// 有关此类的实现，请参阅 Lesson09.cpp
//

class CLesson09App : public CWinApp
{
public:
	CLesson09App();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLesson09App theApp;