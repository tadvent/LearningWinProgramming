// Lesson08_2Doc.h : CLesson08_2Doc ��Ľӿ�
//


#pragma once


class CLesson08_2Doc : public CDocument
{
protected: // �������л�����
	CLesson08_2Doc();
	DECLARE_DYNCREATE(CLesson08_2Doc)

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
	virtual ~CLesson08_2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


