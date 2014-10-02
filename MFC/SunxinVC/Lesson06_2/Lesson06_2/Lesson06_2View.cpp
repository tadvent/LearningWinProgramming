// Lesson06_2View.cpp : CLesson06_2View ���ʵ��
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

// CLesson06_2View ����/����

CLesson06_2View::CLesson06_2View()
{
	// TODO: �ڴ˴���ӹ������

}

CLesson06_2View::~CLesson06_2View()
{
}

BOOL CLesson06_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson06_2View ����

void CLesson06_2View::OnDraw(CDC* /*pDC*/)
{
	CLesson06_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CLesson06_2View ���

#ifdef _DEBUG
void CLesson06_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson06_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson06_2Doc* CLesson06_2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson06_2Doc)));
	return (CLesson06_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson06_2View ��Ϣ�������

void CLesson06_2View::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CMenu menu;
    menu.CreatePopupMenu();
    menu.AppendMenuW(MF_STRING,IDM_WPOP,_T("Windows pop!!..o(��_��)o...~~~~"));
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