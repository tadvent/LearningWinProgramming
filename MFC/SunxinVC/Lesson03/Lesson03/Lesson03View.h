// Lesson03View.h : CLesson03View ��Ľӿ�
//


#pragma once
#include "afxwin.h"


class CLesson03View : public CView
{
protected: // �������л�����
	CLesson03View();
	DECLARE_DYNCREATE(CLesson03View)

// ����
public:
	CLesson03Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CLesson03View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
private:
    CButton m_btn;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // Lesson03View.cpp �еĵ��԰汾
inline CLesson03Doc* CLesson03View::GetDocument() const
   { return reinterpret_cast<CLesson03Doc*>(m_pDocument); }
#endif

