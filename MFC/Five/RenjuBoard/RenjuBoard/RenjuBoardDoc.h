// RenjuBoardDoc.h : CRenjuBoardDoc ��Ľӿ�
//


#pragma once


class CRenjuBoardDoc : public CDocument
{
protected: // �������л�����
	CRenjuBoardDoc();
	DECLARE_DYNCREATE(CRenjuBoardDoc)

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
	virtual ~CRenjuBoardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


