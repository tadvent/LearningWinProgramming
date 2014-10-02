// RenjuBoardDoc.cpp : CRenjuBoardDoc 类的实现
//

#include "stdafx.h"
#include "RenjuBoard.h"

#include "RenjuBoardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRenjuBoardDoc

IMPLEMENT_DYNCREATE(CRenjuBoardDoc, CDocument)

BEGIN_MESSAGE_MAP(CRenjuBoardDoc, CDocument)
END_MESSAGE_MAP()


// CRenjuBoardDoc 构造/析构

CRenjuBoardDoc::CRenjuBoardDoc()
{
	// TODO: 在此添加一次性构造代码

}

CRenjuBoardDoc::~CRenjuBoardDoc()
{
}

BOOL CRenjuBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CRenjuBoardDoc 序列化

void CRenjuBoardDoc::Serialize(CArchive& ar)
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


// CRenjuBoardDoc 诊断

#ifdef _DEBUG
void CRenjuBoardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRenjuBoardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRenjuBoardDoc 命令
