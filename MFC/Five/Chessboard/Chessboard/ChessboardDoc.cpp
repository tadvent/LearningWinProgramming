// ChessboardDoc.cpp : CChessboardDoc ���ʵ��
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


// CChessboardDoc ����/����

CChessboardDoc::CChessboardDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CChessboardDoc::~CChessboardDoc()
{
}

BOOL CChessboardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CChessboardDoc ���л�

void CChessboardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CChessboardDoc ���

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


// CChessboardDoc ����
