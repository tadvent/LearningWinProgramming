#pragma once


// CProp1 �Ի���

class CProp1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CProp1)

public:
	CProp1();
	virtual ~CProp1();

// �Ի�������
	enum { IDD = IDD_PROP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
public:
    int m_occupation;
public:
    virtual LRESULT OnWizardNext();
public:
    virtual BOOL OnInitDialog();
public:
    CString m_workAddress;
};
