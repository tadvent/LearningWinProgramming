// ChessboardDoc.h : CChessboardDoc ��Ľӿ�
//


#pragma once


class CChessboardDoc : public CDocument
{
protected: // �������л�����
	CChessboardDoc();
	DECLARE_DYNCREATE(CChessboardDoc)

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
	virtual ~CChessboardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


