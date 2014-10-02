// Lesson18Ctrl.cpp : CLesson18Ctrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "Lesson18.h"
#include "Lesson18Ctrl.h"
#include "Lesson18PropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CLesson18Ctrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CLesson18Ctrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
    ON_WM_CREATE()
    ON_WM_TIMER()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CLesson18Ctrl, COleControl)
	DISP_FUNCTION_ID(CLesson18Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
    DISP_STOCKPROP_BACKCOLOR()
    DISP_STOCKPROP_FORECOLOR()
    DISP_PROPERTY_NOTIFY_ID(CLesson18Ctrl, "Interval", dispidInterval, m_Interval, OnIntervalChanged, VT_I2)
    DISP_FUNCTION_ID(CLesson18Ctrl, "Hello", dispidHello, Hello, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CLesson18Ctrl, COleControl)
    EVENT_STOCK_CLICK()
    EVENT_CUSTOM_ID("NewMinute", eventidNewMinute, NewMinute, VTS_NONE)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CLesson18Ctrl, 2)
	PROPPAGEID(CLesson18PropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CLesson18Ctrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CLesson18Ctrl, "LESSON18.Lesson18Ctrl.1",
	0x576751f5, 0x7d86, 0x40bd, 0x98, 0x72, 0xea, 0x14, 0x63, 0xed, 0xe, 0x59)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CLesson18Ctrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DLesson18 =
		{ 0x98E6F88F, 0x523, 0x4203, { 0x84, 0x23, 0xE2, 0x37, 0x33, 0xF7, 0x55, 0xA7 } };
const IID BASED_CODE IID_DLesson18Events =
		{ 0x2DD40FD4, 0x7D52, 0x4DD6, { 0xB2, 0x68, 0xB9, 0xC, 0x42, 0x99, 0x8E, 0xF9 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwLesson18OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CLesson18Ctrl, IDS_LESSON18, _dwLesson18OleMisc)



// CLesson18Ctrl::CLesson18CtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CLesson18Ctrl ��ϵͳע�����

BOOL CLesson18Ctrl::CLesson18CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_LESSON18,
			IDB_LESSON18,
			afxRegApartmentThreading,
			_dwLesson18OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CLesson18Ctrl::CLesson18Ctrl - ���캯��

CLesson18Ctrl::CLesson18Ctrl()
{
	InitializeIIDs(&IID_DLesson18, &IID_DLesson18Events);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CLesson18Ctrl::~CLesson18Ctrl - ��������

CLesson18Ctrl::~CLesson18Ctrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CLesson18Ctrl::OnDraw - ��ͼ����

void CLesson18Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

    CBrush brush(TranslateColor(GetBackColor()));
    pdc->FillRect(rcBounds,&brush);
    pdc->SetTextColor(TranslateColor(GetForeColor()));
    pdc->SetBkMode(TRANSPARENT);
    CTime time=CTime::GetCurrentTime();
    if(0==time.GetSecond()){
        NewMinute();
    }
    CString str=time.Format(_T("%H:%M:%S"));
    pdc->TextOutW(0,0,str);
}



// CLesson18Ctrl::DoPropExchange - �־���֧��

void CLesson18Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
    PX_Short(pPX,_T("Interval"),m_Interval,2000);
}



// CLesson18Ctrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CLesson18Ctrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CLesson18Ctrl::AboutBox - ���û���ʾ�����ڡ���

void CLesson18Ctrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_LESSON18);
	dlgAbout.DoModal();
}



// CLesson18Ctrl ��Ϣ�������

int CLesson18Ctrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (COleControl::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    SetTimer(1,m_Interval,NULL);

    return 0;
}

void CLesson18Ctrl::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    //Invalidate();
    InvalidateControl();

    COleControl::OnTimer(nIDEvent);
}

void CLesson18Ctrl::OnIntervalChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������
    if(m_Interval < 0 || m_Interval > 6000 ){
        m_Interval=1000;
    }
    else {
        KillTimer(1);
        SetTimer(1,m_Interval,NULL);
    }

    SetModifiedFlag();
}

void CLesson18Ctrl::Hello(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ���ӵ��ȴ���������
    MessageBox(_T("Hello!"),_T("Warning...."));
}
