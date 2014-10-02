#pragma once

// Lesson18Ctrl.h : CLesson18Ctrl ActiveX 控件类的声明。


// CLesson18Ctrl : 有关实现的信息，请参阅 Lesson18Ctrl.cpp。

class CLesson18Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CLesson18Ctrl)

// 构造函数
public:
	CLesson18Ctrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CLesson18Ctrl();

	DECLARE_OLECREATE_EX(CLesson18Ctrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CLesson18Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CLesson18Ctrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CLesson18Ctrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
        eventidNewMinute = 1L,
        dispidHello = 2L,
        dispidInterval = 1
    };
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
    void OnIntervalChanged(void);
    SHORT m_Interval;
protected:
    void Hello(void);

    void NewMinute(void)
    {
        FireEvent(eventidNewMinute, EVENT_PARAM(VTS_NONE));
    }
};

