// Lesson05Doc.cpp : CLesson05Doc ���ʵ��
//

#include "stdafx.h"
#include "Lesson05.h"

#include "Lesson05Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson05Doc

IMPLEMENT_DYNCREATE(CLesson05Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson05Doc, CDocument)
END_MESSAGE_MAP()


// CLesson05Doc ����/����

CLesson05Doc::CLesson05Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson05Doc::~CLesson05Doc()
{
}

BOOL CLesson05Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson05Doc ���л�

void CLesson05Doc::Serialize(CArchive& ar)
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


// CLesson05Doc ���

#ifdef _DEBUG
void CLesson05Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson05Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson05Doc ����
