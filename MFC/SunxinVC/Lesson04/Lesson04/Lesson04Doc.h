// Lesson04Doc.h : CLesson04Doc ��Ľӿ�
//


#pragma once


class CLesson04Doc : public CDocument
{
protected: // �������л�����
	CLesson04Doc();
	DECLARE_DYNCREATE(CLesson04Doc)

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
	virtual ~CLesson04Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


