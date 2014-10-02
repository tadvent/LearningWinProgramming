// RenjuBoardView.h : CRenjuBoardView 类的接口
//


#pragma once

#include "BoardView.h"


class CRenjuBoardView : public CView
{
protected: // 仅从序列化创建
	CRenjuBoardView();
	DECLARE_DYNCREATE(CRenjuBoardView)

// 属性
public:
	CRenjuBoardDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CRenjuBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // RenjuBoardView.cpp 中的调试版本
inline CRenjuBoardDoc* CRenjuBoardView::GetDocument() const
   { return reinterpret_cast<CRenjuBoardDoc*>(m_pDocument); }
#endif

