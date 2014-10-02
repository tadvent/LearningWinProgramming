#pragma once

// Lesson18PropPage.h : CLesson18PropPage 属性页类的声明。


// CLesson18PropPage : 有关实现的信息，请参阅 Lesson18PropPage.cpp。

class CLesson18PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CLesson18PropPage)
	DECLARE_OLECREATE_EX(CLesson18PropPage)

// 构造函数
public:
	CLesson18PropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LESSON18 };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

