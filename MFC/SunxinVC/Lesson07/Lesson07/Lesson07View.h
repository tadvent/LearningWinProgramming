// Lesson07View.h : CLesson07View ��Ľӿ�
//


#pragma once


class CLesson07View : public CView
{
protected: // �������л�����
	CLesson07View();
	DECLARE_DYNCREATE(CLesson07View)

// ����
public:
	CLesson07Doc* GetDocument() const;

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
	virtual ~CLesson07View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnDialog();
};

#ifndef _DEBUG  // Lesson07View.cpp �еĵ��԰汾
inline CLesson07Doc* CLesson07View::GetDocument() const
   { return reinterpret_cast<CLesson07Doc*>(m_pDocument); }
#endif

