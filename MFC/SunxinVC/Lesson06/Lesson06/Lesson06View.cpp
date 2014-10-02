// Lesson06View.cpp : CLesson06View ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_TEST, &CLesson06View::OnTest)
    ON_WM_RBUTTONDOWN()
//    ON_COMMAND(ID__VIEW, &CLesson06View::OnPopupView)
ON_COMMAND(ID__VIEW, &CLesson06View::OnPopupView)
END_MESSAGE_MAP()

// CLesson06View ����/����

CLesson06View::CLesson06View()
{
	// TODO: �ڴ˴���ӹ������

}

CLesson06View::~CLesson06View()
{
}

BOOL CLesson06View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson06View ����

void CLesson06View::OnDraw(CDC* /*pDC*/)
{
	CLesson06Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CLesson06View ��ӡ

BOOL CLesson06View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLesson06View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLesson06View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLesson06View ���

#ifdef _DEBUG
void CLesson06View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson06View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson06Doc* CLesson06View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson06Doc)));
	return (CLesson06Doc*)m_pDocument;
}
#endif //_DEBUG

void CLesson06View::OnTest()
{
    // TODO: �ڴ���������������
    MessageBox(_T("CView clicked!"));
}

void CLesson06View::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CMenu PopMenu;
    PopMenu.LoadMenuW(IDR_POPUP);
    ClientToScreen(&point);
    PopMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,GetParent());

    CView::OnRButtonDown(nFlags, point);
}

void CLesson06View::OnPopupView()
{
    // TODO: �ڴ���������������
    MessageBox(_T("Popup View Clicked!"));
}
