// RenjuBoardView.cpp : CRenjuBoardView 类的实现
//

#include "stdafx.h"
#include "RenjuBoard.h"

#include "RenjuBoardDoc.h"
#include "RenjuBoardView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRenjuBoardView

IMPLEMENT_DYNCREATE(CRenjuBoardView, CView)

BEGIN_MESSAGE_MAP(CRenjuBoardView, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILE_NEW, &CRenjuBoardView::OnFileNew)
    ON_COMMAND(ID_OPR_BKMOVE, &CRenjuBoardView::OnOprBkmove)
    ON_COMMAND(ID_OPR_FWMOVE, &CRenjuBoardView::OnOprFwmove)
END_MESSAGE_MAP()

// CRenjuBoardView 构造/析构

CRenjuBoardView::CRenjuBoardView()
{
	// TODO: 在此处添加构造代码

}

CRenjuBoardView::~CRenjuBoardView()
{
}

BOOL CRenjuBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CRenjuBoardView 绘制

void CRenjuBoardView::OnDraw(CDC* pDC)
{
	CRenjuBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    theBoard.Show(pDC);
}


// CRenjuBoardView 诊断

#ifdef _DEBUG
void CRenjuBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CRenjuBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRenjuBoardDoc* CRenjuBoardView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRenjuBoardDoc)));
	return (CRenjuBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CRenjuBoardView 消息处理程序

void CRenjuBoardView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CClientDC dc(this);
    CPoint idx;
    theBoard.PointToIdx(point,idx);

    int status=theBoard.CheckMove(idx.x,idx.y);
    theBoard.DoMove(idx,&dc);
    switch(status){
        case 5:
            if(theBoard.nCurrent%2){ //黑棋
                MessageBox(_T("五连，黑胜！"));
            }
            else {  //白棋
                MessageBox(_T("五连，白胜！"));
            }
            break;
        case 6:
            MessageBox(_T("黑方长连禁手，白胜！"));
            break;
        case 44:
            MessageBox(_T("黑方四四禁手，白胜！"));
            break;
        case 33:
            MessageBox(_T("黑方三三禁手，白胜！"));
            break;
        default:
            if(theBoard.SearchVCF((theBoard.nCurrent%2)?WHITE:BLACK)){
                theBoard.DoMove(theBoard.vcfList.front().rush,&dc);
            }
            break;
    }

    //int Status=theBoard.IsDoubleFour(idx.x,idx.y);
    //theBoard.DoMove(idx,&dc);
    //if(Status == 1)MessageBox(_T("Double Four!"));

    //int Status=theBoard.IsFive((theBoard.nCurrent%2)?WHITE:BLACK,idx.x,idx.y);
    //theBoard.DoMove(idx,&dc);
    //if(Status == 5)MessageBox(_T("Five !"));
    //else if(Status == 6)MessageBox(_T("Overline !"));

    //int x,y;
    //CString str;
    //theBoard.DoMove(idx,&dc);
    //if(theBoard.HaveFour(BLACK,x,y)){
    //    str.Format(_T("Black Four! idx= %c%d"),64+x,y);
    //    MessageBox(str);
    //}
    //if(theBoard.HaveFour(WHITE,x,y)){
    //    str.Format(_T("White Four! idx= %c%d"),64+x,y);
    //    MessageBox(str);
    //}

    CView::OnLButtonDown(nFlags, point);
}

void CRenjuBoardView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CClientDC dc(this);
    CPoint idx;
    theBoard.BackMove(&dc);

    CView::OnRButtonDown(nFlags, point);
}

void CRenjuBoardView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CPoint idx;
    theBoard.PointToIdx(point,idx);
    if(!theBoard.IsOutBoard(idx)){
        CString str;
        str.Format(_T("%c%d"),64+idx.x,idx.y);
        int index=((CMainFrame*)GetParent())->m_wndStatusBar.CommandToIndex(ID_INDICATOR_INDEX);
        ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneText(index,str);
    }

    CView::OnMouseMove(nFlags, point);
}

void CRenjuBoardView::OnFileNew()
{
    // TODO: 在此添加命令处理程序代码
    theBoard.Clear();
    Invalidate();
}

void CRenjuBoardView::OnOprBkmove()
{
    // TODO: 在此添加命令处理程序代码
    CClientDC dc(this);
    theBoard.BackMove(&dc);
}

void CRenjuBoardView::OnOprFwmove()
{
    // TODO: 在此添加命令处理程序代码
    CClientDC dc(this);
    theBoard.ForwardMove(&dc);
}
