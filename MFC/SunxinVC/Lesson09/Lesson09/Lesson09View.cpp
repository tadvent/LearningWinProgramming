// Lesson09View.cpp : CLesson09View ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLesson09View ����/����

CLesson09View::CLesson09View()
{
	// TODO: �ڴ˴���ӹ������

}

CLesson09View::~CLesson09View()
{
}

BOOL CLesson09View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson09View ����

void CLesson09View::OnDraw(CDC* /*pDC*/)
{
	CLesson09Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CLesson09View ��ӡ

BOOL CLesson09View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLesson09View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLesson09View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLesson09View ���

#ifdef _DEBUG
void CLesson09View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson09View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson09Doc* CLesson09View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson09Doc)));
	return (CLesson09Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson09View ��Ϣ�������
