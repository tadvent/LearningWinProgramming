// Lesson06View.h : CLesson06View ��Ľӿ�
//


#pragma once


class CLesson06View : public CView
{
protected: // �������л�����
	CLesson06View();
	DECLARE_DYNCREATE(CLesson06View)

// ����
public:
	CLesson06Doc* GetDocument() const;

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
	virtual ~CLesson06View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Lesson06View.cpp �еĵ��԰汾
inline CLesson06Doc* CLesson06View::GetDocument() const
   { return reinterpret_cast<CLesson06Doc*>(m_pDocument); }
#endif

