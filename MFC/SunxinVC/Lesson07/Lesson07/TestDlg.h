#pragma once
#include "afxwin.h"


// CTestDlg �Ի���

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
//    virtual void PostNcDestroy();
//    virtual void OnCancel();
//    virtual void OnOK();
public:
    afx_msg void OnBnClickedBtnAdd();
    CButton m_btn;
    bool m_bIsCreated;
public:
    afx_msg void OnStnClickedNumber1();
    //int m_num1;
    //int m_num2;
    //int m_num3;
private:
    int m_num1;
private:
    int m_num2;
private:
    int m_num3;
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
