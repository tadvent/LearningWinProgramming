// Lesson08_2View.h : CLesson08_2View ��Ľӿ�
//


#pragma once


class CLesson08_2View : public CView
{
protected: // �������л�����
	CLesson08_2View();
	DECLARE_DYNCREATE(CLesson08_2View)

// ����
public:
	CLesson08_2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CLesson08_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Lesson08_2View.cpp �еĵ��԰汾
inline CLesson08_2Doc* CLesson08_2View::GetDocument() const
   { return reinterpret_cast<CLesson08_2Doc*>(m_pDocument); }
#endif

