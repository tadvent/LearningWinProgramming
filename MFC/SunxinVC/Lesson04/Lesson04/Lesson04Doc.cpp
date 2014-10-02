// Lesson04Doc.cpp : CLesson04Doc 类的实现
//

#include "stdafx.h"
#include "Lesson04.h"

#include "Lesson04Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson04Doc

IMPLEMENT_DYNCREATE(CLesson04Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson04Doc, CDocument)
END_MESSAGE_MAP()


// CLesson04Doc 构造/析构

CLesson04Doc::CLesson04Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson04Doc::~CLesson04Doc()
{
}

BOOL CLesson04Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson04Doc 序列化

void CLesson04Doc::Serialize(CArchive& ar)
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


// CLesson04Doc 诊断

#ifdef _DEBUG
void CLesson04Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson04Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson04Doc 命令
