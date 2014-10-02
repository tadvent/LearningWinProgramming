// Lesson09Doc.cpp : CLesson09Doc 类的实现
//

#include "stdafx.h"
#include "Lesson09.h"

#include "Lesson09Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson09Doc

IMPLEMENT_DYNCREATE(CLesson09Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson09Doc, CDocument)
END_MESSAGE_MAP()


// CLesson09Doc 构造/析构

CLesson09Doc::CLesson09Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson09Doc::~CLesson09Doc()
{
}

BOOL CLesson09Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson09Doc 序列化

void CLesson09Doc::Serialize(CArchive& ar)
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


// CLesson09Doc 诊断

#ifdef _DEBUG
void CLesson09Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson09Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson09Doc 命令
