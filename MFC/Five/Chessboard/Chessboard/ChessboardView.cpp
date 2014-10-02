// ChessboardView.cpp : CChessboardView ���ʵ��
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

// CChessboardView ����/����

CChessboardView::CChessboardView()
//: m_nMove(0),interval(30),r(interval/2-2)
{
	// TODO: �ڴ˴���ӹ������
    //m_nMove=1;
    //for(int i=0;i<15;++i)for(int j=0;j<15;++j)hold[i][j]=0;

}

CChessboardView::~CChessboardView()
{
}

BOOL CChessboardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChessboardView ����

void CChessboardView::OnDraw(CDC* pDC)
{
	CChessboardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
    theBoard.Show(pDC);

    CString str;
    str=theBoard.ForbidRule?_T("�н���"):_T("�޽���");
    CSize sz=pDC->GetTextExtent(str);
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneInfo(2,123,SBPS_NORMAL,sz.cx);
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneText(2,str);

}


// CChessboardView ���

#ifdef _DEBUG
void CChessboardView::AssertValid() const
{
	CView::AssertValid();
}

void CChessboardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChessboardDoc* CChessboardView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessboardDoc)));
	return (CChessboardDoc*)m_pDocument;
}
#endif //_DEBUG


// CChessboardView ��Ϣ�������

void CChessboardView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
                if(theBoard.SearchVCF()){//�ҵ�VCF
                    theBoard.DoMove(theBoard.vcfList[0],&dc);
                }
                break;
        }
    }

    CView::OnLButtonDown(nFlags, point);
}

void CChessboardView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!theBoard.MoveList.empty()){
        CClientDC dc(this);
        theBoard.BackMove(&dc);
    }

    CView::OnRButtonDown(nFlags, point);
}

void CChessboardView::OnFileNew()
{
    // TODO: �ڴ���������������
    theBoard.Clear();
    Invalidate();
}

void CChessboardView::OnOpBack()
{
    // TODO: �ڴ���������������
    if(!theBoard.MoveList.empty()){
        CClientDC dc(this);
        theBoard.BackMove(&dc);
    }
}
//
//void CChessboardView::OnViewToolbar()
//{
//    // TODO: �ڴ���������������
//    ((CMainFrame*)GetParent())->ShowControlBar(&m_wnd
//}

void CChessboardView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CPoint idx;
    theBoard.PointToIdx(point,idx);
    CString str;
    str.Format(_T("%c%d"),'A'+idx.x,idx.y+1);
    if(idx.x>BOARD_SIZE-1 || idx.y>BOARD_SIZE-1 || idx.x<0 || idx.y<0)str.Empty();
    ((CMainFrame*)GetParent())->m_wndStatusBar.SetPaneText(1,str);

    CView::OnMouseMove(nFlags, point);
}
