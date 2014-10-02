#include "StdAfx.h"
#include "BoardView.h"

CBoardView::CBoardView(void)
{
    LeftTopPos.SetPoint(50,50);
    Size.SetSize(300,300);
    for(int i=0;i<BOARD_SIZE+2;++i)for(int j=0;j<BOARD_SIZE+2;++j){
        Foul[i][j]=0;
        IsFoulChanged[i][j]=false;
    }
}

CBoardView::~CBoardView(void)
{
}

void CBoardView::Clear(void){
    CBoard::Clear();
    for(int i=0;i<BOARD_SIZE+2;++i)for(int j=0;j<BOARD_SIZE+2;++j){
        Foul[i][j]=0;
        IsFoulChanged[i][j]=false;
    }
}

int CBoardView::SetLTPos(int X,int Y){
    if(X<0 ||X>200 ||Y<0 ||Y>200)return -1;
    LeftTopPos.SetPoint(X,Y);
    return 0;
}
int CBoardView::SetSize(int CX,int CY){
    if(CX<150 ||CX>1500 ||CY<150 ||CY>1000)return -1;
    Size.SetSize(CX,CY);
    return 0;
}

void CBoardView::PointToIdx(const CPoint &point, CPoint &idx){
    int xx=(point.x-LeftTopPos.x+Size.cx/(BOARD_SIZE-1)/2);
    if(xx<0){idx.x=-1;idx.y=-1;return;}
    int yy=(point.y-LeftTopPos.y+Size.cy/(BOARD_SIZE-1)/2);
    if(yy<0){idx.x=-1;idx.y=-1;return;}
    idx.x=xx*(BOARD_SIZE-1)/Size.cx+1;
    idx.y=yy*(BOARD_SIZE-1)/Size.cy+1;
}

void CBoardView::IdxToPoint(const CPoint &idx, CPoint &point){
    point.x=LeftTopPos.x+(idx.x-1)*Size.cx/(BOARD_SIZE-1);
    point.y=LeftTopPos.y+(idx.y-1)*Size.cy/(BOARD_SIZE-1);
}

CRect CBoardView::IdxToRect(const CPoint &idx){
    CPoint point;
    CRect rect;
    IdxToPoint(idx,point);
    int halfcx=Size.cx/(BOARD_SIZE-1)/2;
    int halfcy=Size.cy/(BOARD_SIZE-1)/2;
    rect.left=point.x-halfcx;
    rect.top=point.y-halfcy;
    rect.right=point.x+halfcx;
    rect.bottom=point.y+halfcy;
    return rect;
}

void CBoardView::Show(CDC *pDC){
    
    for(int i=0;i<BOARD_SIZE;++i){//画网格
        pDC->MoveTo(LeftTopPos.x+Size.cx*i/(BOARD_SIZE-1),LeftTopPos.y);
        pDC->LineTo(LeftTopPos.x+Size.cx*i/(BOARD_SIZE-1),LeftTopPos.y+Size.cy+1);
        pDC->MoveTo(LeftTopPos.x,LeftTopPos.y+Size.cy*i/(BOARD_SIZE-1));
        pDC->LineTo(LeftTopPos.x+Size.cx+1,LeftTopPos.y+Size.cy*i/(BOARD_SIZE-1));
    }
    //画边界
    pDC->MoveTo(LeftTopPos.x+1,LeftTopPos.y+1);
    pDC->LineTo(LeftTopPos.x+1,LeftTopPos.y+Size.cy-1);
    pDC->LineTo(LeftTopPos.x+Size.cx-1,LeftTopPos.y+Size.cy-1);
    pDC->LineTo(LeftTopPos.x+Size.cx-1,LeftTopPos.y+1);
    pDC->LineTo(LeftTopPos.x+1,LeftTopPos.y+1);

    //画关键点
    CBrush blackBrush(RGB(0,0,0));
    CBrush *pOldBrush=pDC->SelectObject(&blackBrush);
    CPoint SpotPoint[5];
    SpotPoint[0].SetPoint(8,8);
    SpotPoint[1].SetPoint(4,4);
    SpotPoint[2].SetPoint(12,12);
    SpotPoint[3].SetPoint(4,12);
    SpotPoint[4].SetPoint(12,4);
    for(int i=0;i<5;++i){
        DrawKeyPoint(SpotPoint[i],RGB(0,0,0),pDC);
    }
    pDC->SelectObject(pOldBrush);

    //画坐标
    // A - O
    pDC->SetBkMode(TRANSPARENT);
    char ch='A';
    for(int i=0;i<15;++ch,++i){
        CSize chsize=pDC->GetTextExtent(CString(ch));
        pDC->TextOutW(LeftTopPos.x-chsize.cx/2+Size.cx*i/(BOARD_SIZE-1),
                      LeftTopPos.y-chsize.cy/2-Size.cy/(BOARD_SIZE-1),CString(ch));
    }
    // 1 - 15
    for(int i=0;i<15;++i){
        CString str;
        str.Format(_T("%d"),i+1);
        CSize chsize=pDC->GetTextExtent(str);
        pDC->TextOutW(LeftTopPos.x-chsize.cx/2-Size.cx/(BOARD_SIZE-1),
                      LeftTopPos.y-chsize.cy/2+Size.cy*i/(BOARD_SIZE-1),str);
    }

    //摆棋子
    for(size_t i=0;i<nCurrent;++i){
        char color;
        if(0 == i%2)color=BLACK;
        else color=WHITE;
        DrawStone(MoveList[i],/*color,*/i+1,pDC);
    }

    //显示禁手
    ShowFoul(pDC);

    //begin debug
    vector<FourRush> rush;
    CBoard::GetFourRushPoints((nCurrent%2)?WHITE:BLACK,rush);
    for(vector<FourRush>::iterator p=rush.begin();p!=rush.end();++p){
        DrawCross(p->rush,pDC,RGB(0,255,0));
    }
    //end debug
}

void CBoardView::ShowFoul(CDC *pDC){
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        if(Foul[i][j])DrawCross(CPoint(i,j),pDC);
    }
}

int CBoardView::DoMove(const CPoint &point, CDC *pDC){   //移动一步
    if(-1 == CBoard::DoMove(point)) return -1;

    //CRgn rgn;
    //rgn.CreateRectRgnIndirect(&IdxToRect(MoveList[nCurrent-1]));
    //pDC->GetWindow()->InvalidateRgn(&rgn);

    ////显示禁手
    MarkFoul();
    //for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
    //    if(IsFoulChanged[i][j]){
    //        CRgn rgnReDraw;
    //        rgnReDraw.CreateRectRgnIndirect(&IdxToRect(CPoint(i,j)));
    //        pDC->GetWindow()->InvalidateRgn(&rgnReDraw);
    //    }
    //}


    pDC->GetWindow()->Invalidate();

    return 0;
}

int CBoardView::BackMove(CDC *pDC){
    if(-1 == CBoard::BackMove())return -1;

    //CRgn rgn;
    //rgn.CreateRectRgnIndirect(&IdxToRect(MoveList[nCurrent]));
    //pDC->GetWindow()->InvalidateRgn(&rgn);
    //
    ////显示禁手
    MarkFoul();
    //for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
    //    if(IsFoulChanged[i][j]){
    //        CRgn rgnReDraw;
    //        rgnReDraw.CreateRectRgnIndirect(&IdxToRect(CPoint(i,j)));
    //        pDC->GetWindow()->InvalidateRgn(&rgnReDraw);
    //    }
    //}


    pDC->GetWindow()->Invalidate();

    return 0;
}

int CBoardView::ForwardMove(CDC *pDC){
    if(-1 == CBoard::ForwardMove())return -1;

    CRgn rgn;
    rgn.CreateRectRgnIndirect(&IdxToRect(MoveList[nCurrent-1]));
    pDC->GetWindow()->InvalidateRgn(&rgn);

    //显示禁手
    MarkFoul();
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        if(IsFoulChanged[i][j]){
            CRgn rgnReDraw;
            rgnReDraw.CreateRectRgnIndirect(&IdxToRect(CPoint(i,j)));
            pDC->GetWindow()->InvalidateRgn(&rgnReDraw);
        }
    }
    return 0;
}

void CBoardView::DrawStone(const CPoint &point,/*char color,*/size_t num,CDC *pDC){//待修改，用上坐标转换函数
    CBrush brush;   //棋子画刷
    COLORREF OldTextColor;
    char color=matrix[point.x][point.y];
    if(BLACK == color){//设置黑棋和数字颜色
        brush.CreateSolidBrush(RGB(0,0,0));
        OldTextColor=pDC->SetTextColor(RGB(255,255,255));
    }
    else if(WHITE == color){//设置白棋和数字颜色
        brush.CreateSolidBrush(RGB(255,255,255));
        OldTextColor=pDC->SetTextColor(RGB(0,0,0));
    }
    else return;
    CBrush *pOldBrush=pDC->SelectObject(&brush);
    pDC->Ellipse(LeftTopPos.x+Size.cx*(point.x-1)/(BOARD_SIZE-1)-Size.cx*20/41/(BOARD_SIZE-1),
                 LeftTopPos.y+Size.cy*(point.y-1)/(BOARD_SIZE-1)-Size.cy*20/41/(BOARD_SIZE-1),
                 LeftTopPos.x+Size.cx*(point.x-1)/(BOARD_SIZE-1)+Size.cx*20/41/(BOARD_SIZE-1),
                 LeftTopPos.y+Size.cx*(point.y-1)/(BOARD_SIZE-1)+Size.cy*20/41/(BOARD_SIZE-1));
    //设置字体
    CFont font;
    font.CreatePointFont(80,_T("Arial"),NULL);
    CFont *pOldFont=pDC->SelectObject(&font);
    //显示数字
    CString str;
    str.Format(_T("%d"),num);
    CSize strsz=pDC->GetTextExtent(str);
    pDC->SetBkMode(TRANSPARENT);
    pDC->TextOutW(LeftTopPos.x+Size.cx*(point.x-1)/(BOARD_SIZE-1)-strsz.cx/2,
                  LeftTopPos.y+Size.cy*(point.y-1)/(BOARD_SIZE-1)-strsz.cy/2,str);

    //收尾工作
    font.DeleteObject();
    pDC->SelectObject(pOldFont);
    pDC->SetTextColor(OldTextColor);
    pDC->SelectObject(pOldBrush);
}

void CBoardView::DrawCross(const CPoint &point,CDC *pDC, COLORREF clr){
    CPoint block(Size.cx/(BOARD_SIZE-1),Size.cy/(BOARD_SIZE-1));
    CPoint center;
    IdxToPoint(point,center);
    CPen pen(PS_SOLID,2,clr);
    CPen *pOldPen=pDC->SelectObject(&pen);
    pDC->MoveTo(center.x-block.x*1/4,
                center.y-block.y*1/4);
    pDC->LineTo(center.x+block.x*1/4,
                center.y+block.y*1/4);

    pDC->MoveTo(center.x-block.x*1/4,
                center.y+block.y*1/4);
    pDC->LineTo(center.x+block.x*1/4,
                center.y-block.y*1/4);

    pDC->SelectObject(pOldPen);
}

void CBoardView::DrawKeyPoint(const CPoint &point,COLORREF color,CDC *pDC){ //待修改，用上坐标转换函数
    CBrush blackBrush(color);
    CBrush *pOldBrush=pDC->SelectObject(&blackBrush);
    pDC->Rectangle(LeftTopPos.x+Size.cx*(point.x-1)/(BOARD_SIZE-1)-1,
                   LeftTopPos.y+Size.cy*(point.y-1)/(BOARD_SIZE-1)-1,
                   LeftTopPos.x+Size.cx*(point.x-1)/(BOARD_SIZE-1)+2,
                   LeftTopPos.y+Size.cy*(point.y-1)/(BOARD_SIZE-1)+2);
    pDC->SelectObject(pOldBrush);
}

void CBoardView::MarkFoul(void){
    bool status;
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        if(IsFoul(i,j))status=true;
        else status=false;
        //status=static_cast<bool>(IsFoul(i,j));
        if(status == Foul[i][j]){
            IsFoulChanged[i][j]=false;
        }
        else {
            IsFoulChanged[i][j]=true;
            Foul[i][j]=status;
        }
    }
}