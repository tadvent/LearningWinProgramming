// Lesson08_2.h : Lesson08_2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLesson08_2App:
// �йش����ʵ�֣������ Lesson08_2.cpp
//

class CLesson08_2App : public CWinApp
{
public:
	CLesson08_2App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLesson08_2App theApp;