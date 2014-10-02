// Lesson03View.h : CLesson03View 类的接口
//


#pragma once
#include "afxwin.h"


class CLesson03View : public CView
{
protected: // 仅从序列化创建
	CLesson03View();
	DECLARE_DYNCREATE(CLesson03View)

// 属性
public:
	CLesson03Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLesson03View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
    CButton m_btn;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // Lesson03View.cpp 中的调试版本
inline CLesson03Doc* CLesson03View::GetDocument() const
   { return reinterpret_cast<CLesson03Doc*>(m_pDocument); }
#endif

