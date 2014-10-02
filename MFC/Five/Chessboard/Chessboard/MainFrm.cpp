// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
    IDS_POSITION,
    IDS_FORBIDRULE,
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
    cs.cx=400;
    cs.cy=480;
    cs.style &= ~FWS_ADDTOTITLE;
    cs.lpszName=_T("�������� by Tadvent(USTC)");

	return TRUE;
}


// CMainFrame ���

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


// CMainFrame ��Ϣ�������




void CMainFrame::OnViewToolbar()
{
    // TODO: �ڴ���������������
    ShowControlBar(&m_wndMyToolBar,!m_wndMyToolBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI)
{
    // TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(m_wndMyToolBar.IsWindowVisible());
}
