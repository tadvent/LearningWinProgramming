// ChessboardDoc.cpp : CChessboardDoc 类的实现
//

#include "stdafx.h"
#include "Chessboard.h"

#include "ChessboardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChessboardDoc

IMPLEMENT_DYNCREATE(CChessboardDoc, CDocument)

BEGIN_MESSAGE_MAP(CChessboardDoc, CDocument)
END_MESSAGE_MAP()


// CChessboardDoc 构造/析构

CChessboardDoc::CChessboardDoc()
{
	// TODO: 在此添加一次性构造代码

}

CChessboardDoc::~CChessboardDoc()
{
}

BOOL CChessboardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CChessboardDoc 序列化

void CChessboardDoc::Serialize(CArchive& ar)
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


// CChessboardDoc 诊断

#ifdef _DEBUG
void CChessboardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChessboardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CChessboardDoc 命令
