// Lesson08_2View.cpp : CLesson08_2View ���ʵ��
//

#include "stdafx.h"
#include "Lesson08_2.h"

#include "Lesson08_2Doc.h"
#include "Lesson08_2View.h"
#include "PropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson08_2View

IMPLEMENT_DYNCREATE(CLesson08_2View, CView)

BEGIN_MESSAGE_MAP(CLesson08_2View, CView)
    ON_COMMAND(IDM_PROPSHEET, &CLesson08_2View::OnPropsheet)
END_MESSAGE_MAP()

// CLesson08_2View ����/����

CLesson08_2View::CLesson08_2View()
{
	// TODO: �ڴ˴���ӹ������
    m_occupation=-1;
    m_workAddr=_T("");
    memset(m_like,0,sizeof(m_like));
    m_strSalary="";

}

CLesson08_2View::~CLesson08_2View()
{
}

BOOL CLesson08_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLesson08_2View ����

void CLesson08_2View::OnDraw(CDC* pDC)
{
	CLesson08_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
    CFont font;
    font.CreatePointFont(300,_T("@����Ҧ��"));

    CFont *pOldFont;
    pOldFont=pDC->SelectObject(&font);

    CString strTemp;
    strTemp=_T("���ְҵ��");

    switch(m_occupation){
        case 0:
            strTemp+=_T("����Ա");
            break;
        case 1:
            strTemp+=_T("ϵͳ����ʦ");
            break;
        case 2:
            strTemp+=_T("��Ŀ����");
            break;
        default:
            break;
    }
    pDC->TextOutW(10,10,strTemp);

    strTemp=_T("��Ĺ����ص㣺")+m_workAddr;
    TEXTMETRIC tm;

    pDC->GetTextMetrics(&tm);
    pDC->TextOutW(10,10+tm.tmHeight,strTemp);

    strTemp=_T("�����Ȥ���ã�");
    if(m_like[0])strTemp+=_T(" ����");
    if(m_like[1])strTemp+=_T(" ACG");
    if(m_like[2])strTemp+=_T(" ����");
    if(m_like[3])strTemp+=_T(" ����");
    pDC->TextOutW(10,10+2*tm.tmHeight,strTemp);

    strTemp=_T("������룺")+m_strSalary;
    pDC->TextOutW(10,10+3*tm.tmHeight,strTemp);

    pDC->SelectObject(pOldFont);
}


// CLesson08_2View ���

#ifdef _DEBUG
void CLesson08_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson08_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson08_2Doc* CLesson08_2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson08_2Doc)));
	return (CLesson08_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson08_2View ��Ϣ�������

void CLesson08_2View::OnPropsheet()
{
    // TODO: �ڴ���������������
    CPropSheet propSheet(_T("���Ա�"));
    propSheet.SetWizardMode();
    if(ID_WIZFINISH==propSheet.DoModal()){
        m_occupation=propSheet.m_prop1.m_occupation;
        m_workAddr=propSheet.m_prop1.m_workAddress;
        m_like[0]=propSheet.m_prop2.m_computer;
        m_like[1]=propSheet.m_prop2.m_acg;
        m_like[2]=propSheet.m_prop2.m_sport;
        m_like[3]=propSheet.m_prop2.m_music;
        m_strSalary=propSheet.m_prop3.m_strSalary;
        Invalidate();
    }
}
