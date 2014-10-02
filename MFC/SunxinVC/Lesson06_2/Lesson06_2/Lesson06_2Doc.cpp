// Lesson06_2Doc.cpp : CLesson06_2Doc 类的实现
//

#include "stdafx.h"
#include "Lesson06_2.h"

#include "Lesson06_2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson06_2Doc

IMPLEMENT_DYNCREATE(CLesson06_2Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson06_2Doc, CDocument)
END_MESSAGE_MAP()


// CLesson06_2Doc 构造/析构

CLesson06_2Doc::CLesson06_2Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson06_2Doc::~CLesson06_2Doc()
{
}

BOOL CLesson06_2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson06_2Doc 序列化

void CLesson06_2Doc::Serialize(CArchive& ar)
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


// CLesson06_2Doc 诊断

#ifdef _DEBUG
void CLesson06_2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson06_2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson06_2Doc 命令
