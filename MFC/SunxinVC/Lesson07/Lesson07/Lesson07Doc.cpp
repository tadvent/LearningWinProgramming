// Lesson07Doc.cpp : CLesson07Doc ���ʵ��
//

#include "stdafx.h"
#include "Lesson07.h"

#include "Lesson07Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson07Doc

IMPLEMENT_DYNCREATE(CLesson07Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson07Doc, CDocument)
END_MESSAGE_MAP()


// CLesson07Doc ����/����

CLesson07Doc::CLesson07Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson07Doc::~CLesson07Doc()
{
}

BOOL CLesson07Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson07Doc ���л�

void CLesson07Doc::Serialize(CArchive& ar)
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


// CLesson07Doc ���

#ifdef _DEBUG
void CLesson07Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson07Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLesson07Doc ����
