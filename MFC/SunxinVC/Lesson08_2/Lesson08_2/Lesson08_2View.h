// Lesson08_2View.h : CLesson08_2View 类的接口
//


#pragma once


class CLesson08_2View : public CView
{
protected: // 仅从序列化创建
	CLesson08_2View();
	DECLARE_DYNCREATE(CLesson08_2View)

// 属性
public:
	CLesson08_2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CLesson08_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPropsheet();

private:
    int m_occupation;
    CString m_workAddr;
    BOOL m_like[4];
    CString m_strSalary;
};

#ifndef _DEBUG  // Lesson08_2View.cpp 中的调试版本
inline CLesson08_2Doc* CLesson08_2View::GetDocument() const
   { return reinterpret_cast<CLesson08_2Doc*>(m_pDocument); }
#endif

