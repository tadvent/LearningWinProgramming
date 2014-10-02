// Prop2.cpp : 实现文件
//

#include "stdafx.h"
#include "Lesson08_2.h"
#include "Prop2.h"
#include "PropSheet.h"


// CProp2 对话框

IMPLEMENT_DYNAMIC(CProp2, CPropertyPage)

CProp2::CProp2()
	: CPropertyPage(CProp2::IDD)
    , m_computer(FALSE)
    , m_acg(FALSE)
    , m_sport(FALSE)
    , m_music(FALSE)
{

}

CProp2::~CProp2()
{
}

void CProp2::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK1, m_computer);
    DDX_Check(pDX, IDC_CHECK2, m_acg);
    DDX_Check(pDX, IDC_CHECK3, m_sport);
    DDX_Check(pDX, IDC_CHECK4, m_music);
}


BEGIN_MESSAGE_MAP(CProp2, CPropertyPage)
END_MESSAGE_MAP()


// CProp2 消息处理程序

BOOL CProp2::OnSetActive()
{
    // TODO: 在此添加专用代码和/或调用基类
    ((CPropSheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);

    return CPropertyPage::OnSetActive();
}

LRESULT CProp2::OnWizardNext()
{
    // TODO: 在此添加专用代码和/或调用基类
    UpdateData();
    if(m_acg||m_computer||m_music||m_sport){
        return CPropertyPage::OnWizardNext();
    }
    else {
        MessageBox(_T("请选择你的兴趣爱好!"));
        return -1;
    }
}
