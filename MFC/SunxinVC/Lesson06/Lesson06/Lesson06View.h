// Lesson06View.h : CLesson06View 类的接口
//


#pragma once


class CLesson06View : public CView
{
protected: // 仅从序列化创建
	CLesson06View();
	DECLARE_DYNCREATE(CLesson06View)

// 属性
public:
	CLesson06Doc* GetDocument() const;

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
	virtual ~CLesson06View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnTest();
public:
    afx_msg void OnTest();
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
//    afx_msg void OnPopupView();
public:
    afx_msg void OnPopupView();
};

#ifndef _DEBUG  // Lesson06View.cpp 中的调试版本
inline CLesson06Doc* CLesson06View::GetDocument() const
   { return reinterpret_cast<CLesson06Doc*>(m_pDocument); }
#endif

