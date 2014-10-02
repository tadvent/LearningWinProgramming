// RenjuBoardView.cpp : CRenjuBoardView ���ʵ��
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

// CRenjuBoardView ����/����

CRenjuBoardView::CRenjuBoardView()
{
	// TODO: �ڴ˴���ӹ������

}

CRenjuBoardView::~CRenjuBoardView()
{
}

BOOL CRenjuBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CRenjuBoardView ����

void CRenjuBoardView::OnDraw(CDC* pDC)
{
	CRenjuBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
    theBoard.Show(pDC);
}


// CRenjuBoardView ���

#ifdef _DEBUG
void CRenjuBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CRenjuBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRenjuBoardDoc* CRenjuBoardView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRenjuBoardDoc)));
	return (CRenjuBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CRenjuBoardView ��Ϣ�������

void CRenjuBoardView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CClientDC dc(this);
    CPoint idx;
    theBoard.PointToIdx(point,idx);

    int status=theBoard.CheckMove(idx.x,idx.y);
    theBoard.DoMove(idx,&dc);
    switch(status){
        case 5:
            if(theBoard.nCurrent%2){ //����
                MessageBox(_T("��������ʤ��"));
            }
            else {  //����
                MessageBox(_T("��������ʤ��"));
            }
            break;
        case 6:
            MessageBox(_T("�ڷ��������֣���ʤ��"));
            break;
        case 44:
            MessageBox(_T("�ڷ����Ľ��֣���ʤ��"));
            break;
        case 33:
            MessageBox(_T("�ڷ��������֣���ʤ��"));
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
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CClientDC dc(this);
    CPoint idx;
    theBoard.BackMove(&dc);

    CView::OnRButtonDown(nFlags, point);
}

void CRenjuBoardView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
    // TODO: �ڴ���������������
    theBoard.Clear();
    Invalidate();
}

void CRenjuBoardView::OnOprBkmove()
{
    // TODO: �ڴ���������������
    CClientDC dc(this);
    theBoard.BackMove(&dc);
}

void CRenjuBoardView::OnOprFwmove()
{
    // TODO: �ڴ���������������
    CClientDC dc(this);
    theBoard.ForwardMove(&dc);
}
