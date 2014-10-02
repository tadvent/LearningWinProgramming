// Lesson05View.cpp : CLesson05View ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CLesson05View ����/����

CLesson05View::CLesson05View()
: dccolorchange(true)
{
	// TODO: �ڴ˴���ӹ������

}

CLesson05View::~CLesson05View()
{
}

BOOL CLesson05View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson05View ����

void CLesson05View::OnDraw(CDC* /*pDC*/)
{
	CLesson05Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
    ft.CreatePointFont(150,TEXT("��Բ"));
    CFont *p_oldft=dc.SelectObject(&ft);

    dc.TextOutW(2,200,str);

    dc.SelectObject(p_oldft);
}


// CLesson05View ��ӡ

BOOL CLesson05View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLesson05View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLesson05View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLesson05View ���

#ifdef _DEBUG
void CLesson05View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson05View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson05Doc* CLesson05View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson05Doc)));
	return (CLesson05Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson05View ��Ϣ�������

int CLesson05View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    SetTimer(1,1000,NULL);

    return 0;
}

void CLesson05View::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
