// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Chessboard.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
    ON_COMMAND(IDM_VIEW_TOOLBAR, &CMainFrame::OnViewToolbar)
    ON_UPDATE_COMMAND_UI(IDM_VIEW_TOOLBAR, &CMainFrame::OnUpdateViewToolbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
    IDS_POSITION,
    IDS_FORBIDRULE,
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

    m_wndMyToolBar.Create(this,WS_CHILD |  WS_VISIBLE | CBRS_TOP,123);
    m_wndMyToolBar.LoadToolBar(IDR_MYTOOLBAR1);
    m_wndMyToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndMyToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
    cs.cx=400;
    cs.cy=480;
    cs.style &= ~FWS_ADDTOTITLE;
    cs.lpszName=_T("智能五子 by Tadvent(USTC)");

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序




void CMainFrame::OnViewToolbar()
{
    // TODO: 在此添加命令处理程序代码
    ShowControlBar(&m_wndMyToolBar,!m_wndMyToolBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
    pCmdUI->SetCheck(m_wndMyToolBar.IsWindowVisible());
}
