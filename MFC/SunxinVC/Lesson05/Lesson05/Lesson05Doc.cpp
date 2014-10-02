// Lesson05Doc.cpp : CLesson05Doc 类的实现
//

#include "stdafx.h"
#include "Lesson05.h"

#include "Lesson05Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson05Doc

IMPLEMENT_DYNCREATE(CLesson05Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson05Doc, CDocument)
END_MESSAGE_MAP()


// CLesson05Doc 构造/析构

CLesson05Doc::CLesson05Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson05Doc::~CLesson05Doc()
{
}

BOOL CLesson05Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson05Doc 序列化

void CLesson05Doc::Serialize(CArchive& ar)
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


// CLesson05Doc 诊断

#ifdef _DEBUG
void CLesson05Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson05Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson05Doc 命令
