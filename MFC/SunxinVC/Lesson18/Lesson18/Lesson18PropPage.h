#pragma once

// Lesson18PropPage.h : CLesson18PropPage ����ҳ���������


// CLesson18PropPage : �й�ʵ�ֵ���Ϣ������� Lesson18PropPage.cpp��

class CLesson18PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CLesson18PropPage)
	DECLARE_OLECREATE_EX(CLesson18PropPage)

// ���캯��
public:
	CLesson18PropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LESSON18 };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

