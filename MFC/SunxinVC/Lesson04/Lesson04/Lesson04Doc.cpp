// Lesson04Doc.cpp : CLesson04Doc ���ʵ��
//

#include "stdafx.h"
#include "Lesson04.h"

#include "Lesson04Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson04Doc

IMPLEMENT_DYNCREATE(CLesson04Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson04Doc, CDocument)
END_MESSAGE_MAP()


// CLesson04Doc ����/����

CLesson04Doc::CLesson04Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson04Doc::~CLesson04Doc()
{
}

BOOL CLesson04Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson04Doc ���л�

void CLesson04Doc::Serialize(CArchive& ar)
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


// CLesson04Doc ���

#ifdef _DEBUG
void CLesson04Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson04Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson04Doc ����
