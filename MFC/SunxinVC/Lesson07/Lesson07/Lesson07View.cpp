// Lesson07View.cpp : CLesson07View 类的实现
//

#include "stdafx.h"
#include "Lesson07.h"

#include "Lesson07Doc.h"
#include "Lesson07View.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson07View

IMPLEMENT_DYNCREATE(CLesson07View, CView)

BEGIN_MESSAGE_MAP(CLesson07View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(IDM_DIALOG, &CLesson07View::OnDialog)
END_MESSAGE_MAP()

// CLesson07View 构造/析构

CLesson07View::CLesson07View()
{
	// TODO: 在此处添加构造代码

}

CLesson07View::~CLesson07View()
{
}

BOOL CLesson07View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson07View 绘制

void CLesson07View::OnDraw(CDC* /*pDC*/)
{
	CLesson07Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLesson07View 打印

BOOL CLesson07View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLesson07View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLesson07View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CLesson07View 诊断

#ifdef _DEBUG
void CLesson07View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson07View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson07Doc* CLesson07View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson07Doc)));
	return (CLesson07Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson07View 消息处理程序

void CLesson07View::OnDialog()
{
    // TODO: 在此添加命令处理程序代码
    CTestDlg dlg;
    dlg.DoModal();

    //CTestDlg *pDlg=new CTestDlg;
    //pDlg->Create(IDD_DIALOG1,NULL);
    //pDlg->ShowWindow(SW_SHOWNORMAL);
}
