// Lesson04View.h : CLesson04View ��Ľӿ�
//


#pragma once
#include "atltypes.h"


class CLesson04View : public CView
{
protected: // �������л�����
	CLesson04View();
	DECLARE_DYNCREATE(CLesson04View)

// ����
public:
	CLesson04Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CLesson04View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Lesson04View.cpp �еĵ��԰汾
inline CLesson04Doc* CLesson04View::GetDocument() const
   { return reinterpret_cast<CLesson04Doc*>(m_pDocument); }
#endif
