// Lesson06_2View.h : CLesson06_2View 类的接口
//


#pragma once


class CLesson06_2View : public CView
{
protected: // 仅从序列化创建
	CLesson06_2View();
	DECLARE_DYNCREATE(CLesson06_2View)

// 属性
public:
	CLesson06_2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLesson06_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnWpop();
    afx_msg void OnAhah();
};

#ifndef _DEBUG  // Lesson06_2View.cpp 中的调试版本
inline CLesson06_2Doc* CLesson06_2View::GetDocument() const
   { return reinterpret_cast<CLesson06_2Doc*>(m_pDocument); }
#endif

