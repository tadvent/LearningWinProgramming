// Lesson18PropPage.cpp : CLesson18PropPage 属性页类的实现。

#include "stdafx.h"
#include "Lesson18.h"
#include "Lesson18PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CLesson18PropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CLesson18PropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CLesson18PropPage, "LESSON18.Lesson18PropPage.1",
	0x93b26659, 0x2e7e, 0x4cd4, 0xbd, 0xf5, 0x47, 0xbe, 0x26, 0x8, 0xd3, 0xac)



// CLesson18PropPage::CLesson18PropPageFactory::UpdateRegistry -
// 添加或移除 CLesson18PropPage 的系统注册表项

BOOL CLesson18PropPage::CLesson18PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_LESSON18_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CLesson18PropPage::CLesson18PropPage - 构造函数

CLesson18PropPage::CLesson18PropPage() :
	COlePropertyPage(IDD, IDS_LESSON18_PPG_CAPTION)
{
}

// CLesson18PropPage::DoDataExchange - 在页和属性间移动数据

void CLesson18PropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CLesson18PropPage 消息处理程序
