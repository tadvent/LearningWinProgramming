// Lesson03Doc.cpp : CLesson03Doc ���ʵ��
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


// CLesson03Doc ����/����

CLesson03Doc::CLesson03Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson03Doc::~CLesson03Doc()
{
}

BOOL CLesson03Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson03Doc ���л�

void CLesson03Doc::Serialize(CArchive& ar)
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


// CLesson03Doc ���

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


// CLesson03Doc ����
