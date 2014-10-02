// Prop1.cpp : 实现文件
//

#include "stdafx.h"
#include "Lesson08_2.h"
#include "Prop1.h"
#include "PropSheet.h"


// CProp1 对话框

IMPLEMENT_DYNAMIC(CProp1, CPropertyPage)

CProp1::CProp1()
	: CPropertyPage(CProp1::IDD)
    , m_occupation(-1)
    , m_workAddress(_T(""))
{

}

CProp1::~CProp1()
{
}

void CProp1::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RADIO1, m_occupation);
    DDX_LBString(pDX, IDC_LIST1, m_workAddress);
}


BEGIN_MESSAGE_MAP(CProp1, CPropertyPage)
END_MESSAGE_MAP()


// CProp1 消息处理程序

BOOL CProp1::OnSetActive()
{
    // TODO: 在此添加专用代码和/或调用基类
    ((CPropSheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);

    return CPropertyPage::OnSetActive();
}

LRESULT CProp1::OnWizardNext()
{
    // TODO: 在此添加专用代码和/或调用基类
    UpdateData();
    CString str;
    str.Format(_T("m_occupation=%d"),m_occupation);
    MessageBox(str);

    if(-1 == m_occupation)return -1;
    if(_T("")==m_workAddress){
        MessageBox(_T("选你的窝!"));
        return -1;
    }
    return CPropertyPage::OnWizardNext();
}

BOOL CProp1::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("澄空学园"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("渔场"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("cnBeta"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("USTC"));

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
