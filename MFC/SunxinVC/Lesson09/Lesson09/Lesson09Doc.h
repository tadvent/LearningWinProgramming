// Lesson09Doc.h : CLesson09Doc ��Ľӿ�
//


#pragma once


class CLesson09Doc : public CDocument
{
protected: // �������л�����
	CLesson09Doc();
	DECLARE_DYNCREATE(CLesson09Doc)

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
	virtual ~CLesson09Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


