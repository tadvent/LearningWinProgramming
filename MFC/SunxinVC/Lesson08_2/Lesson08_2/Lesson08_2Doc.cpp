// Lesson08_2Doc.cpp : CLesson08_2Doc ���ʵ��
//

#include "stdafx.h"
#include "Lesson08_2.h"

#include "Lesson08_2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson08_2Doc

IMPLEMENT_DYNCREATE(CLesson08_2Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson08_2Doc, CDocument)
END_MESSAGE_MAP()


// CLesson08_2Doc ����/����

CLesson08_2Doc::CLesson08_2Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson08_2Doc::~CLesson08_2Doc()
{
}

BOOL CLesson08_2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson08_2Doc ���л�

void CLesson08_2Doc::Serialize(CArchive& ar)
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


// CLesson08_2Doc ���

#ifdef _DEBUG
void CLesson08_2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson08_2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson08_2Doc ����
