// Lesson07Doc.h : CLesson07Doc ��Ľӿ�
//


#pragma once


class CLesson07Doc : public CDocument
{
protected: // �������л�����
	CLesson07Doc();
	DECLARE_DYNCREATE(CLesson07Doc)

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
	virtual ~CLesson07Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


