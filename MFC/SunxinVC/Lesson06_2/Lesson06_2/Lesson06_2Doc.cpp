// Lesson06_2Doc.cpp : CLesson06_2Doc ���ʵ��
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


// CLesson06_2Doc ����/����

CLesson06_2Doc::CLesson06_2Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson06_2Doc::~CLesson06_2Doc()
{
}

BOOL CLesson06_2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson06_2Doc ���л�

void CLesson06_2Doc::Serialize(CArchive& ar)
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


// CLesson06_2Doc ���

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


// CLesson06_2Doc ����
