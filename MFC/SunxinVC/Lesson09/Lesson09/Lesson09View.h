// Lesson09View.h : CLesson09View ��Ľӿ�
//


#pragma once


class CLesson09View : public CView
{
protected: // �������л�����
	CLesson09View();
	DECLARE_DYNCREATE(CLesson09View)

// ����
public:
	CLesson09Doc* GetDocument() const;

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
	virtual ~CLesson09View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Lesson09View.cpp �еĵ��԰汾
inline CLesson09Doc* CLesson09View::GetDocument() const
   { return reinterpret_cast<CLesson09Doc*>(m_pDocument); }
#endif

