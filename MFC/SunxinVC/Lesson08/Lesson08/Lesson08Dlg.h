// Lesson08Dlg.h : ͷ�ļ�
//

#pragma once
#include "newbutton.h"


// CLesson08Dlg �Ի���
class CLesson08Dlg : public CDialog
{
// ����
public:
	CLesson08Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LESSON08_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CNewButton m_btn1;
public:
    CNewButton m_btn2;
};
