// Lesson04View.cpp : CLesson04View 类的实现
//

#include "stdafx.h"
#include "Lesson04.h"

#include "Lesson04Doc.h"
#include "Lesson04View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson04View

IMPLEMENT_DYNCREATE(CLesson04View, CView)

BEGIN_MESSAGE_MAP(CLesson04View, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CLesson04View 构造/析构

CLesson04View::CLesson04View()
: m_pto(0)
, m_ptOld(0)
, m_btdown(false)
{
	// TODO: 在此处添加构造代码

}

CLesson04View::~CLesson04View()
{
}

BOOL CLesson04View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson04View 绘制

void CLesson04View::OnDraw(CDC* /*pDC*/)
{
	CLesson04Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLesson04View 诊断

#ifdef _DEBUG
void CLesson04View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson04View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson04Doc* CLesson04View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson04Doc)));
	return (CLesson04Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson04View 消息处理程序

void CLesson04View::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    //MessageBox(TEXT("点左键了"),"鼠标");
    m_ptOld=m_pto=point;
    m_btdown=true;

    CView::OnLButtonDown(nFlags, point);
}

void CLesson04View::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    //HDC hdc;
    //hdc=::GetDC(m_hWnd);
    //::MoveToEx(hdc,m_pto.x,m_pto.y,NULL);
    //::LineTo(hdc,point.x,point.y);
    //::ReleaseDC(m_hWnd,hdc);

    //CDC dc;
    //dc.SetOutputDC(::GetDC(m_hWnd));
    //dc.MoveTo(m_pto);
    //dc.LineTo(point);
    //dc.ReleaseOutputDC();

	//CDC *pDC=GetDC();
	//pDC->MoveTo(m_pto);
	//pDC->LineTo(point);
	//ReleaseDC(pDC);

    //CClientDC cdc(this);
    ////CClientDC cdc(GetParent());
    //cdc.MoveTo(m_pto);
    //cdc.LineTo(point);

    //CWindowDC wdc(GetParent());
    //CWindowDC wdc(GetDesktopWindow());
    //ClientToScreen(&m_pto);
    //ClientToScreen(&point);
    //wdc.MoveTo(m_pto/*+CPoint(-300,-300)*/);
    //wdc.LineTo(point/*+CPoint(300,300)*/);
    m_btdown=false;

    CView::OnLButtonUp(nFlags, point);
}

void CLesson04View::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    static int r=1,g=1,b=1;
    if(m_btdown){
        CClientDC cdc(this);
        CPen pen(PS_SOLID,10,RGB(r,g,b));
        cdc.SelectObject(&pen);
        cdc.MoveTo(m_ptOld);
        cdc.LineTo(point);
        m_ptOld=point;
        if((g+19)%255!=g+1)r=(r+37)%255+1;
        if((b+3)%255!=b+3)g=(g+19)%255+1;
        b=(b+3)%255+1;
    }

    CView::OnMouseMove(nFlags, point);
}
