// ChessboardView.h : CChessboardView 类的接口
//


#pragma once
#include "Board.h"
#include "BoardView.h"


class CChessboardView : public CView
{
protected: // 仅从序列化创建
	CChessboardView();
	DECLARE_DYNCREATE(CChessboardView)

// 属性
public:
	CChessboardDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CChessboardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ChessboardView.cpp 中的调试版本
inline CChessboardDoc* CChessboardView::GetDocument() const
   { return reinterpret_cast<CChessboardDoc*>(m_pDocument); }
#endif

