// Lesson08_2View.cpp : CLesson08_2View 类的实现
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

// CLesson08_2View 构造/析构

CLesson08_2View::CLesson08_2View()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLesson08_2View 绘制

void CLesson08_2View::OnDraw(CDC* pDC)
{
	CLesson08_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    CFont font;
    font.CreatePointFont(300,_T("@方正姚体"));

    CFont *pOldFont;
    pOldFont=pDC->SelectObject(&font);

    CString strTemp;
    strTemp=_T("你的职业：");

    switch(m_occupation){
        case 0:
            strTemp+=_T("程序员");
            break;
        case 1:
            strTemp+=_T("系统工程师");
            break;
        case 2:
            strTemp+=_T("项目经理");
            break;
        default:
            break;
    }
    pDC->TextOutW(10,10,strTemp);

    strTemp=_T("你的工作地点：")+m_workAddr;
    TEXTMETRIC tm;

    pDC->GetTextMetrics(&tm);
    pDC->TextOutW(10,10+tm.tmHeight,strTemp);

    strTemp=_T("你的兴趣爱好：");
    if(m_like[0])strTemp+=_T(" 电脑");
    if(m_like[1])strTemp+=_T(" ACG");
    if(m_like[2])strTemp+=_T(" 体育");
    if(m_like[3])strTemp+=_T(" 音乐");
    pDC->TextOutW(10,10+2*tm.tmHeight,strTemp);

    strTemp=_T("你的收入：")+m_strSalary;
    pDC->TextOutW(10,10+3*tm.tmHeight,strTemp);

    pDC->SelectObject(pOldFont);
}


// CLesson08_2View 诊断

#ifdef _DEBUG
void CLesson08_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLesson08_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLesson08_2Doc* CLesson08_2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLesson08_2Doc)));
	return (CLesson08_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLesson08_2View 消息处理程序

void CLesson08_2View::OnPropsheet()
{
    // TODO: 在此添加命令处理程序代码
    CPropSheet propSheet(_T("属性表单"));
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
