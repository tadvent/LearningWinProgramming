// Lesson05Doc.h : CLesson05Doc ��Ľӿ�
//


#pragma once


class CLesson05Doc : public CDocument
{
protected: // �������л�����
	CLesson05Doc();
	DECLARE_DYNCREATE(CLesson05Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CLesson05Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


