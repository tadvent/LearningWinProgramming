// Lesson09Doc.cpp : CLesson09Doc ���ʵ��
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


// CLesson09Doc ����/����

CLesson09Doc::CLesson09Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson09Doc::~CLesson09Doc()
{
}

BOOL CLesson09Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson09Doc ���л�

void CLesson09Doc::Serialize(CArchive& ar)
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


// CLesson09Doc ���

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


// CLesson09Doc ����
