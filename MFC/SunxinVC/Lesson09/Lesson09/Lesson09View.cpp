// Lesson09View.cpp : CLesson09View 类的实现
//

#include "stdafx.h"
#include "Lesson09.h"

#include "Lesson09Doc.h"
#include "Lesson09View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson09View

IMPLEMENT_DYNCREATE(CLesson09View, CView)

BEGIN_MESSAGE_MAP(CLesson09View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLesson09View 构造/析构

CLesson09View::CLesson09View()
{
	// TODO: 在此处添加构造代码

}

CLesson09View::~CLesson09View()
{
}

BOOL CLesson09View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson09View 绘制

void CLesson09View::OnDraw(CDC* /*pDC*/)
{
	CLesson09Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLesson09View 打印

BOOL CLesson09View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLesson09View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLesson09View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CLesson09View 诊断

#ifdef _DEBUG
void CLesson09View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson09View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson09Doc* CLesson09View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson09Doc)));
	return (CLesson09Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson09View 消息处理程序
