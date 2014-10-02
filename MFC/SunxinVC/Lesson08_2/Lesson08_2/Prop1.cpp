// Prop1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lesson08_2.h"
#include "Prop1.h"
#include "PropSheet.h"


// CProp1 �Ի���

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


// CProp1 ��Ϣ�������

BOOL CProp1::OnSetActive()
{
    // TODO: �ڴ����ר�ô����/����û���
    ((CPropSheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);

    return CPropertyPage::OnSetActive();
}

LRESULT CProp1::OnWizardNext()
{
    // TODO: �ڴ����ר�ô����/����û���
    UpdateData();
    CString str;
    str.Format(_T("m_occupation=%d"),m_occupation);
    MessageBox(str);

    if(-1 == m_occupation)return -1;
    if(_T("")==m_workAddress){
        MessageBox(_T("ѡ�����!"));
        return -1;
    }
    return CPropertyPage::OnWizardNext();
}

BOOL CProp1::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("�ο�ѧ԰"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("�泡"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("cnBeta"));
    ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("USTC"));

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
