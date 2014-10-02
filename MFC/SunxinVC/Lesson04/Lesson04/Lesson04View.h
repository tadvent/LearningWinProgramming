// Lesson04View.h : CLesson04View 类的接口
//


#pragma once
#include "atltypes.h"


class CLesson04View : public CView
{
protected: // 仅从序列化创建
	CLesson04View();
	DECLARE_DYNCREATE(CLesson04View)

// 属性
public:
	CLesson04Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLesson04View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CPoint m_pto;
public:
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    CPoint m_ptOld;
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    bool m_btdown;
};

#ifndef _DEBUG  // Lesson04View.cpp 中的调试版本
inline CLesson04Doc* CLesson04View::GetDocument() const
   { return reinterpret_cast<CLesson04Doc*>(m_pDocument); }
#endif

