// ChessboardView.cpp : CChessboardView 类的实现
//

#include "stdafx.h"
#include "Chessboard.h"

#include "ChessboardDoc.h"
#include "ChessboardView.h"
#include "Board.h"
#include "BoardTry.h"
#include "MainFrm.h"

//#include<stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChessboardView

IMPLEMENT_DYNCREATE(CChessboardView, CView)

BEGIN_MESSAGE_MAP(CChessboardView, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_FILE_NEW, &CChessboardView::OnFileNew)
    ON_COMMAND(IDM_OP_BACK, &CChessboardView::OnOpBack)
    //ON_COMMAND(IDM_VIEW_TOOLBAR, &CChessboardView::OnViewToolbar)
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CChessboardView 构造/析构

CChessboardView::CChessboardView()
//: m_nMove(0),interval(30),r(interval/2-2)
{
	// TODO: 在此处添加构造代码
    //m_nMove=1;
    //for(int i=0;i<15;++i)for(int j=0;j<15;++j)hold[i][j]=0;

}

CChessboardView::~CChessboardView()
{
}

BOOL CChessboardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChessboardView 绘制

void CChessboardView::OnDraw(CDC* pDC)
{
	CChessboardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    theBoard.Show(pDC);

    CString str;
    str=theBoard.ForbidRule?_T("有禁手"):_T("无禁手");
    CSize sz=pDC->GetTextExtent(str);
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneInfo(2,123,SBPS_NORMAL,sz.cx);
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneText(2,str);

}


// CChessboardView 诊断

#ifdef _DEBUG
void CChessboardView::AssertValid() const
{
	CView::AssertValid();
}

void CChessboardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChessboardDoc* CChessboardView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessboardDoc)));
	return (CChessboardDoc*)m_pDocument;
}
#endif //_DEBUG


// CChessboardView 消息处理程序

void CChessboardView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CPoint idx;
    theBoard.PointToIdx(point,idx);
    if(theBoard.CheckMove(idx)!=-1){
        int FiveStatus=theBoard.CheckFive(idx);
        //int FourStatus=theBoard.CheckFour(idx);
        CClientDC dc(this);
        theBoard.DoMove(idx,&dc);
        switch(FiveStatus){
            case 5:MessageBox(_T("Five!"));break;
            case 6:MessageBox(_T("More than five!"));break;
            default:
                if(theBoard.SearchVCF()){//找到VCF
                    theBoard.DoMove(theBoard.vcfList[0],&dc);
                }
                break;
        }
    }

    CView::OnLButtonDown(nFlags, point);
}

void CChessboardView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if(!theBoard.MoveList.empty()){
        CClientDC dc(this);
        theBoard.BackMove(&dc);
    }

    CView::OnRButtonDown(nFlags, point);
}

void CChessboardView::OnFileNew()
{
    // TODO: 在此添加命令处理程序代码
    theBoard.Clear();
    Invalidate();
}

void CChessboardView::OnOpBack()
{
    // TODO: 在此添加命令处理程序代码
    if(!theBoard.MoveList.empty()){
        CClientDC dc(this);
        theBoard.BackMove(&dc);
    }
}
//
//void CChessboardView::OnViewToolbar()
//{
//    // TODO: 在此添加命令处理程序代码
//    ((CMainFrame*)GetParent())->ShowControlBar(&m_wnd
//}

void CChessboardView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CPoint idx;
    theBoard.PointToIdx(point,idx);
    CString str;
    str.Format(_T("%c%d"),'A'+idx.x,idx.y+1);
    if(idx.x>BOARD_SIZE-1 || idx.y>BOARD_SIZE-1 || idx.x<0 || idx.y<0)str.Empty();
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneText(1,str);

    CView::OnMouseMove(nFlags, point);
}
