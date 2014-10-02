// Lesson05View.h : CLesson05View 类的接口
//


#pragma once


class CLesson05View : public CView
{
protected: // 仅从序列化创建
	CLesson05View();
	DECLARE_DYNCREATE(CLesson05View)

// 属性
public:
	CLesson05Doc* GetDocument() const;

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
	virtual ~CLesson05View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
    bool dccolorchange;
};

#ifndef _DEBUG  // Lesson05View.cpp 中的调试版本
inline CLesson05Doc* CLesson05View::GetDocument() const
   { return reinterpret_cast<CLesson05Doc*>(m_pDocument); }
#endif

