// Lesson06Doc.cpp : CLesson06Doc 类的实现
//

#include "stdafx.h"
#include "Lesson06.h"

#include "Lesson06Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson06Doc

IMPLEMENT_DYNCREATE(CLesson06Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson06Doc, CDocument)
//    ON_COMMAND(ID_TEST, &CLesson06Doc::OnTest)
ON_COMMAND(ID_TEST, &CLesson06Doc::OnTest)
END_MESSAGE_MAP()


// CLesson06Doc 构造/析构

CLesson06Doc::CLesson06Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson06Doc::~CLesson06Doc()
{
}

BOOL CLesson06Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson06Doc 序列化

void CLesson06Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CLesson06Doc 诊断

#ifdef _DEBUG
void CLesson06Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson06Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CLesson06Doc::OnTest()
{
    // TODO: 在此添加命令处理程序代码
    AfxMessageBox(_T("CDoc clicked!"));
}
