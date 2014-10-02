#pragma once
#include "afxwin.h"


// CTestDlg 对话框

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
