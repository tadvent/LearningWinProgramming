// Lesson06_2.h : Lesson06_2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLesson06_2App:
// �йش����ʵ�֣������ Lesson06_2.cpp
//

class CLesson06_2App : public CWinApp
{
public:
	CLesson06_2App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLesson06_2App theApp;