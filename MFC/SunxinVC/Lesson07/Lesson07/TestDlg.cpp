// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lesson07.h"
#include "TestDlg.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
    , m_bIsCreated(false)
    , m_num1(0)
    , m_num2(0)
    , m_num3(0)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_num1);
    DDX_Text(pDX, IDC_EDIT2, m_num2);
    DDX_Text(pDX, IDC_EDIT3, m_num3);
	DDV_MinMaxInt(pDX, m_num1, 0, 100);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
    ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnBnClickedBtnAdd)
    ON_STN_CLICKED(IDC_NUMBER1, &CTestDlg::OnStnClickedNumber1)
    ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

//void CTestDlg::PostNcDestroy()
//{
//    // TODO: �ڴ����ר�ô����/����û���
//    delete this;
//
//    CDialog::PostNcDestroy();
//}

//void CTestDlg::OnCancel()
//{
//    // TODO: �ڴ����ר�ô����/����û���
//    DestroyWindow();
//
//    //CDialog::OnCancel();
//}

//void CTestDlg::OnOK()
//{
//    // TODO: �ڴ����ר�ô����/����û���
//    DestroyWindow();
//
//    //CDialog::OnOK();
//}

void CTestDlg::OnBnClickedBtnAdd()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //if(m_bIsCreated == false){
    //    m_btn.Create(_T("��ť"),BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,121);
    //    m_bIsCreated=true;
    //}
    //else {
    //    m_btn.DestroyWindow();
    //    m_bIsCreated=false;
    //}

    //int num1,num2,num3;
    //num1=GetDlgItemInt(IDC_EDIT1);
    //num2=GetDlgItemInt(IDC_EDIT2);
    //num3=num1+num2;
    //SetDlgItemInt(IDC_EDIT3,num3);
    SetDlgItemInt(IDC_EDIT3,GetDlgItemInt(IDC_EDIT1)+GetDlgItemInt(IDC_EDIT2));

    //UpdateData();
    //m_num3=m_num1+m_num2;
    //UpdateData(FALSE);
}

void CTestDlg::OnStnClickedNumber1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    if(GetDlgItem(IDC_NUMBER1)->GetWindowText(str),str == _T("Number1:")){
        GetDlgItem(IDC_NUMBER1)->SetWindowText(_T("��ֵ1:"));
    }
    else {
        GetDlgItem(IDC_NUMBER1)->SetWindowText(_T("Number1:"));
    }
}

void CTestDlg::OnBnClickedButton1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    if(GetDlgItemText(IDC_BUTTON1,str),str==">>"){
        SetDlgItemText(IDC_BUTTON1,_T("<<"));
    }
    else {
        SetDlgItemText(IDC_BUTTON1,_T(">>"));
    }
    static CRect rectLarge;
    static CRect rectSmall;

    if(rectLarge.IsRectNull()){
        CRect rectSeparator;
        GetWindowRect(&rectLarge);
        GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);
        rectSmall.left=rectLarge.left;
        rectSmall.top=rectLarge.top;
        rectSmall.right=rectLarge.right;
        rectSmall.bottom=rectSeparator.bottom;
    }

    if(str=="<<"){
        SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
    }
    else {
        SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),SWP_NOMOVE|SWP_NOZORDER);
    }
}

void CTestDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    GetNextDlgTabItem(GetFocus())->SetFocus();
    //OnOK();
}


WNDPROC prevProc;
static LRESULT CALLBACK NewEditProc(
HWND hWnd,
UINT uMsg,
WPARAM wParam,
LPARAM lParam 
){
   if(uMsg==WM_CHAR && wParam==0x0d){
       //::SetFocus(GetNextWindow(hWnd,GW_HWNDNEXT));
       SetFocus(GetWindow(hWnd,GW_HWNDNEXT));
       return 1;
   }else {
       return prevProc(hWnd,uMsg,wParam,lParam);
   }
}

BOOL CTestDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    prevProc=(WNDPROC)SetWindowLong(GetDlgItem(IDC_EDIT1)->m_hWnd,
        GWL_WNDPROC,(LONG)(NewEditProc));

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
