// Lesson06Doc.h : CLesson06Doc ��Ľӿ�
//


#pragma once


class CLesson06Doc : public CDocument
{
protected: // �������л�����
	CLesson06Doc();
	DECLARE_DYNCREATE(CLesson06Doc)

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
	virtual ~CLesson06Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnTest();
public:
    afx_msg void OnTest();
};


