// Chessboard.h : Chessboard Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChessboardApp:
// �йش����ʵ�֣������ Chessboard.cpp
//

class CChessboardApp : public CWinApp
{
public:
	CChessboardApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChessboardApp theApp;