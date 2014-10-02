// Lesson03Doc.cpp : CLesson03Doc 类的实现
//

#include "stdafx.h"
#include "Lesson03.h"

#include "Lesson03Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson03Doc

IMPLEMENT_DYNCREATE(CLesson03Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson03Doc, CDocument)
END_MESSAGE_MAP()


// CLesson03Doc 构造/析构

CLesson03Doc::CLesson03Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson03Doc::~CLesson03Doc()
{
}

BOOL CLesson03Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson03Doc 序列化

void CLesson03Doc::Serialize(CArchive& ar)
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


// CLesson03Doc 诊断

#ifdef _DEBUG
void CLesson03Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson03Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson03Doc 命令
