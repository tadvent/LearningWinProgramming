// Lesson18PropPage.cpp : CLesson18PropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "Lesson18.h"
#include "Lesson18PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CLesson18PropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CLesson18PropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CLesson18PropPage, "LESSON18.Lesson18PropPage.1",
	0x93b26659, 0x2e7e, 0x4cd4, 0xbd, 0xf5, 0x47, 0xbe, 0x26, 0x8, 0xd3, 0xac)



// CLesson18PropPage::CLesson18PropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CLesson18PropPage ��ϵͳע�����

BOOL CLesson18PropPage::CLesson18PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_LESSON18_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CLesson18PropPage::CLesson18PropPage - ���캯��

CLesson18PropPage::CLesson18PropPage() :
	COlePropertyPage(IDD, IDS_LESSON18_PPG_CAPTION)
{
}

// CLesson18PropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CLesson18PropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CLesson18PropPage ��Ϣ�������
