// NewButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Lesson08.h"
#include "NewButton.h"


// CNewButton

IMPLEMENT_DYNAMIC(CNewButton, CButton)

CNewButton::CNewButton()
{

}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CNewButton 消息处理程序



void CNewButton::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    ShowWindow(SW_HIDE);
    m_pBtn->ShowWindow(SW_SHOW);

    CButton::OnMouseMove(nFlags, point);
}
