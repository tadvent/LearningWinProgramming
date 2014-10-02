#pragma once


// CNewButton

class CNewButton : public CButton
{
	DECLARE_DYNAMIC(CNewButton)

public:
	CNewButton();
	virtual ~CNewButton();

    CNewButton *m_pBtn;

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


