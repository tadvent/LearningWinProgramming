// Lesson07View.cpp : CLesson07View ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(IDM_DIALOG, &CLesson07View::OnDialog)
END_MESSAGE_MAP()

// CLesson07View ����/����

CLesson07View::CLesson07View()
{
	// TODO: �ڴ˴���ӹ������

}

CLesson07View::~CLesson07View()
{
}

BOOL CLesson07View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson07View ����

void CLesson07View::OnDraw(CDC* /*pDC*/)
{
	CLesson07Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CLesson07View ��ӡ

BOOL CLesson07View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLesson07View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLesson07View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLesson07View ���

#ifdef _DEBUG
void CLesson07View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson07View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson07Doc* CLesson07View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson07Doc)));
	return (CLesson07Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson07View ��Ϣ�������

void CLesson07View::OnDialog()
{
    // TODO: �ڴ���������������
    CTestDlg dlg;
    dlg.DoModal();

    //CTestDlg *pDlg=new CTestDlg;
    //pDlg->Create(IDD_DIALOG1,NULL);
    //pDlg->ShowWindow(SW_SHOWNORMAL);
}
