// Lesson06Doc.cpp : CLesson06Doc ���ʵ��
//

#include "stdafx.h"
#include "Lesson06.h"

#include "Lesson06Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLesson06Doc

IMPLEMENT_DYNCREATE(CLesson06Doc, CDocument)

BEGIN_MESSAGE_MAP(CLesson06Doc, CDocument)
//    ON_COMMAND(ID_TEST, &CLesson06Doc::OnTest)
ON_COMMAND(ID_TEST, &CLesson06Doc::OnTest)
END_MESSAGE_MAP()


// CLesson06Doc ����/����

CLesson06Doc::CLesson06Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLesson06Doc::~CLesson06Doc()
{
}

BOOL CLesson06Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLesson06Doc ���л�

void CLesson06Doc::Serialize(CArchive& ar)
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


// CLesson06Doc ���

#ifdef _DEBUG
void CLesson06Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLesson06Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CLesson06Doc::OnTest()
{
    // TODO: �ڴ���������������
    AfxMessageBox(_T("CDoc clicked!"));
}
