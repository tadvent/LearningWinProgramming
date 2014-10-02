// ChessboardView.h : CChessboardView ��Ľӿ�
//


#pragma once
#include "Board.h"
#include "BoardView.h"


class CChessboardView : public CView
{
protected: // �������л�����
	CChessboardView();
	DECLARE_DYNCREATE(CChessboardView)

// ����
public:
	CChessboardDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CChessboardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

private:

    CBoardView theBoard;
    //CBoard tryBoard;

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnFileNew();
    afx_msg void OnOpBack();
    //afx_msg void OnViewToolbar();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ChessboardView.cpp �еĵ��԰汾
inline CChessboardDoc* CChessboardView::GetDocument() const
   { return reinterpret_cast<CChessboardDoc*>(m_pDocument); }
#endif

