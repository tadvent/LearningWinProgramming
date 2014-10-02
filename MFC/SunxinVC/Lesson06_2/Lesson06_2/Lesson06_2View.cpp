// Lesson06_2View.cpp : CLesson06_2View 类的实现
//

#include "stdafx.h"
#include "Lesson06_2.h"

#include "Lesson06_2Doc.h"
#include "Lesson06_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson06_2View

IMPLEMENT_DYNCREATE(CLesson06_2View, CView)

BEGIN_MESSAGE_MAP(CLesson06_2View, CView)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(IDM_WPOP,OnWpop)
    ON_COMMAND(IDM_AHAH,OnAhah)
END_MESSAGE_MAP()

// CLesson06_2View 构造/析构

CLesson06_2View::CLesson06_2View()
{
	// TODO: 在此处添加构造代码

}

CLesson06_2View::~CLesson06_2View()
{
}

BOOL CLesson06_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson06_2View 绘制

void CLesson06_2View::OnDraw(CDC* /*pDC*/)
{
	CLesson06_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLesson06_2View 诊断

#ifdef _DEBUG
void CLesson06_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson06_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson06_2Doc* CLesson06_2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson06_2Doc)));
	return (CLesson06_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson06_2View 消息处理程序

void CLesson06_2View::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CMenu menu;
    menu.CreatePopupMenu();
    menu.AppendMenuW(MF_STRING,IDM_WPOP,_T("Windows pop!!..o(∩_∩)o...~~~~"));
    menu.AppendMenuW(MF_STRING,IDM_AHAH,_T("Ah AH aH....."));
    ClientToScreen(&point);
    menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
    menu.Detach();

    CView::OnRButtonDown(nFlags, point);
}

void CLesson06_2View::OnWpop(){
    MessageBox(_T("No Anime, No life!"));
}

void CLesson06_2View::OnAhah(){
    MessageBox(_T("NTLEA is Great!"));
}