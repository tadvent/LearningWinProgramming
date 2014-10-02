#pragma once

// Lesson18Ctrl.h : CLesson18Ctrl ActiveX �ؼ����������


// CLesson18Ctrl : �й�ʵ�ֵ���Ϣ������� Lesson18Ctrl.cpp��

class CLesson18Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CLesson18Ctrl)

// ���캯��
public:
	CLesson18Ctrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CLesson18Ctrl();

	DECLARE_OLECREATE_EX(CLesson18Ctrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CLesson18Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CLesson18Ctrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CLesson18Ctrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

