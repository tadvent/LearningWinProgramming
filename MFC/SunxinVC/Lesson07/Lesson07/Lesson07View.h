// Lesson07View.h : CLesson07View 类的接口
//


#pragma once


class CLesson07View : public CView
{
protected: // 仅从序列化创建
	CLesson07View();
	DECLARE_DYNCREATE(CLesson07View)

// 属性
public:
	CLesson07Doc* GetDocument() const;

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
	virtual ~CLesson07View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnDialog();
};

#ifndef _DEBUG  // Lesson07View.cpp 中的调试版本
inline CLesson07Doc* CLesson07View::GetDocument() const
   { return reinterpret_cast<CLesson07Doc*>(m_pDocument); }
#endif

