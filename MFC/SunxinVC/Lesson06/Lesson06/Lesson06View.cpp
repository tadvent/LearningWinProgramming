// Lesson06View.cpp : CLesson06View 类的实现
//

#include "stdafx.h"
#include "Lesson06.h"

#include "Lesson06Doc.h"
#include "Lesson06View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson06View

IMPLEMENT_DYNCREATE(CLesson06View, CView)

BEGIN_MESSAGE_MAP(CLesson06View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_TEST, &CLesson06View::OnTest)
    ON_WM_RBUTTONDOWN()
//    ON_COMMAND(ID__VIEW, &CLesson06View::OnPopupView)
ON_COMMAND(ID__VIEW, &CLesson06View::OnPopupView)
END_MESSAGE_MAP()

// CLesson06View 构造/析构

CLesson06View::CLesson06View()
{
	// TODO: 在此处添加构造代码

}

CLesson06View::~CLesson06View()
{
}

BOOL CLesson06View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson06View 绘制

void CLesson06View::OnDraw(CDC* /*pDC*/)
{
	CLesson06Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLesson06View 打印

BOOL CLesson06View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLesson06View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLesson06View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CLesson06View 诊断

#ifdef _DEBUG
void CLesson06View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson06View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson06Doc* CLesson06View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson06Doc)));
	return (CLesson06Doc*)m_pDocument;
}
#endif //_DEBUG

void CLesson06View::OnTest()
{
    // TODO: 在此添加命令处理程序代码
    MessageBox(_T("CView clicked!"));
}

void CLesson06View::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CMenu PopMenu;
    PopMenu.LoadMenuW(IDR_POPUP);
    ClientToScreen(&point);
    PopMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,GetParent());

    CView::OnRButtonDown(nFlags, point);
}

void CLesson06View::OnPopupView()
{
    // TODO: 在此添加命令处理程序代码
    MessageBox(_T("Popup View Clicked!"));
}
