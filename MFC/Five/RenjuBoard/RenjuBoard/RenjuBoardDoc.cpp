// RenjuBoardDoc.cpp : CRenjuBoardDoc ���ʵ��
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


// CRenjuBoardDoc ����/����

CRenjuBoardDoc::CRenjuBoardDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CRenjuBoardDoc::~CRenjuBoardDoc()
{
}

BOOL CRenjuBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CRenjuBoardDoc ���л�

void CRenjuBoardDoc::Serialize(CArchive& ar)
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


// CRenjuBoardDoc ���

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


// CRenjuBoardDoc ����
