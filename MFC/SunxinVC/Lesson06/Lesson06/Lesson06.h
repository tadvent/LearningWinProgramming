// Lesson06.h : Lesson06 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLesson06App:
// �йش����ʵ�֣������ Lesson06.cpp
//

class CLesson06App : public CWinApp
{
public:
	CLesson06App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnTest();
public:
    afx_msg void OnTest();
};

extern CLesson06App theApp;