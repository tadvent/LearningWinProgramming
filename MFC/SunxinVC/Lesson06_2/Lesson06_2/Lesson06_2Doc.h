// Lesson06_2Doc.h : CLesson06_2Doc 类的接口
//


#pragma once


class CLesson06_2Doc : public CDocument
{
protected: // 仅从序列化创建
	CLesson06_2Doc();
	DECLARE_DYNCREATE(CLesson06_2Doc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CLesson06_2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


