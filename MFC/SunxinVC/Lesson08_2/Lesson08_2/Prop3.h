#pragma once


// CProp3 对话框

class CProp3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CProp3)

public:
	CProp3();
	virtual ~CProp3();

// 对话框数据
	enum { IDD = IDD_PROP3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
public:
    virtual BOOL OnInitDialog();
public:
    virtual BOOL OnWizardFinish();
public:
    CString m_strSalary;
};
