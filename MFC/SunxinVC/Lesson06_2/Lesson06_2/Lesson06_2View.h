// Lesson06_2View.h : CLesson06_2View ��Ľӿ�
//


#pragma once


class CLesson06_2View : public CView
{
protected: // �������л�����
	CLesson06_2View();
	DECLARE_DYNCREATE(CLesson06_2View)

// ����
public:
	CLesson06_2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CLesson06_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnWpop();
    afx_msg void OnAhah();
};

#ifndef _DEBUG  // Lesson06_2View.cpp �еĵ��԰汾
inline CLesson06_2Doc* CLesson06_2View::GetDocument() const
   { return reinterpret_cast<CLesson06_2Doc*>(m_pDocument); }
#endif

