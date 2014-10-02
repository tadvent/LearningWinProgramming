// Lesson05View.cpp : CLesson05View 类的实现
//

#include "stdafx.h"
#include "Lesson05.h"

#include "Lesson05Doc.h"
#include "Lesson05View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson05View

IMPLEMENT_DYNCREATE(CLesson05View, CView)

BEGIN_MESSAGE_MAP(CLesson05View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CLesson05View 构造/析构

CLesson05View::CLesson05View()
: dccolorchange(true)
{
	// TODO: 在此处添加构造代码

}

CLesson05View::~CLesson05View()
{
}

BOOL CLesson05View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson05View 绘制

void CLesson05View::OnDraw(CDC* /*pDC*/)
{
	CLesson05Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    CClientDC dc(this);
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    CString str;
    str.LoadStringW(IDS_MYWORD);
    dc.TextOutW(2,2,str);

    CSize cs=dc.GetTextExtent(str);

    CPoint pt(2,2);
    CreateSolidCaret(1,tm.tmHeight);
    pt.x+=cs.cx;
    SetCaretPos(pt);
    ShowCaret();

    CFont ft;
    ft.CreatePointFont(150,TEXT("幼圆"));
    CFont *p_oldft=dc.SelectObject(&ft);

    dc.TextOutW(2,200,str);

    dc.SelectObject(p_oldft);
}


// CLesson05View 打印

BOOL CLesson05View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLesson05View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLesson05View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CLesson05View 诊断

#ifdef _DEBUG
void CLesson05View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson05View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson05Doc* CLesson05View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson05Doc)));
	return (CLesson05Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson05View 消息处理程序

int CLesson05View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    SetTimer(1,1000,NULL);

    return 0;
}

void CLesson05View::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CClientDC dc(this);
    if(dccolorchange){
//      dc.SetTextColor(RGB(0,0,0));
        dccolorchange=false;
    }
    else {
        dc.SetTextColor(dc.GetBkColor());
        dccolorchange=true;
    }
    CString str;
    str.LoadStringW(IDS_MYWORD02);
    dc.TextOutW(200,100,str);

    CView::OnTimer(nIDEvent);
}
