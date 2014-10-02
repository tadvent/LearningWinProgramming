// RenjuBoardView.h : CRenjuBoardView ��Ľӿ�
//


#pragma once

#include "BoardView.h"


class CRenjuBoardView : public CView
{
protected: // �������л�����
	CRenjuBoardView();
	DECLARE_DYNCREATE(CRenjuBoardView)

// ����
public:
	CRenjuBoardDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CRenjuBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
    CBoardView theBoard;
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
    afx_msg void OnFileNew();
public:
    afx_msg void OnOprBkmove();
public:
    afx_msg void OnOprFwmove();
};

#ifndef _DEBUG  // RenjuBoardView.cpp �еĵ��԰汾
inline CRenjuBoardDoc* CRenjuBoardView::GetDocument() const
   { return reinterpret_cast<CRenjuBoardDoc*>(m_pDocument); }
#endif

