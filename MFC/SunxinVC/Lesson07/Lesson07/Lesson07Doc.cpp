// Lesson07Doc.cpp : CLesson07Doc 类的实现
//

#include "stdafx.h"
#include "Lesson07.h"

#include "Lesson07Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson07Doc

IMPLEMENT_DYNCREATE(CLesson07Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson07Doc, CDocument)
END_MESSAGE_MAP()


// CLesson07Doc 构造/析构

CLesson07Doc::CLesson07Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLesson07Doc::~CLesson07Doc()
{
}

BOOL CLesson07Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLesson07Doc 序列化

void CLesson07Doc::Serialize(CArchive& ar)
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


// CLesson07Doc 诊断

#ifdef _DEBUG
void CLesson07Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson07Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson07Doc 命令
