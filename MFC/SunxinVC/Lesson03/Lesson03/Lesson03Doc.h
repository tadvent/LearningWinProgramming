// Lesson03Doc.h : CLesson03Doc ��Ľӿ�
//


#pragma once


class CLesson03Doc : public CDocument
{
protected: // �������л�����
	CLesson03Doc();
	DECLARE_DYNCREATE(CLesson03Doc)

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
	virtual ~CLesson03Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


