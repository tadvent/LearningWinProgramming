#include "StdAfx.h"
#include "BoardView.h"

CBoardView::CBoardView(void)
{
    LeftTopPos.SetPoint(50,50);
    Size.SetSize(300,300);
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j)FoulState[i][j]=false;
}

CBoardView::~CBoardView(void)
{
}

void CBoardView::DoMove(const CPoint &point, CDC *pDC){   //移动一步，不做任何检查
    DrawStone(point,NextColor,MoveList.size()+1,pDC);

    CBoard::DoMove(point);

    //显示禁手
    ShowFoul(pDC);
}

void CBoardView::ErasePoint(const CPoint &point,CDC *pDC){
    //设置画刷和画笔为背景色
    COLORREF BkColor=(COLORREF)::GetSysColor(COLOR_WINDOW);
    CBrush brush(BkColor);
    CPen pen(PS_SOLID,1,BkColor);
    CBrush *pOldBrush=pDC->SelectObject(&brush);
    CPen *pOldPen=pDC->SelectObject(&pen);
    //擦除棋子区域
    pDC->Rectangle(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)-Size.cx/2/(BOARD_SIZE-1),
                   LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)-Size.cy/2/(BOARD_SIZE-1),
                   LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)+Size.cx/2/(BOARD_SIZE-1),
                   LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)+Size.cy/2/(BOARD_SIZE-1));
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);

    //画十字叉
    DrawCross(point,pDC);

    //画关键点
    if(point==CPoint(3,3) || point==CPoint(11,11) ||
       point==CPoint(3,11) || point==CPoint(11,3) ||
       point==CPoint(7,7)){
           DrawKeyPoint(point,RGB(0,0,0),pDC);
    }
}

//void CBoardView::EraseAllFoul(CDC *pDC){
//    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j)if(matrix[i][j]==Empty){
//        ErasePoint(CPoint(i,j),pDC);
//    }
//}

int CBoardView::BackMove(CDC *pDC){
    if(MoveList.empty())return -1;

    ErasePoint(MoveList.back(),pDC);

    CBoard::BackMove();
    
    //显示禁手
    ShowFoul(pDC);

    return 0;
}

void CBoardView::DrawCross(const CPoint &point,CDC *pDC){
    int border1=LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)-Size.cx/2/(BOARD_SIZE-1);
    if(border1<LeftTopPos.x)border1=LeftTopPos.x;
    pDC->MoveTo(border1,
                LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1));
    int border2=LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)+Size.cx/2/(BOARD_SIZE-1);
    if(border2>LeftTopPos.x+Size.cx+1)border2=LeftTopPos.x+Size.cx+1;
    pDC->LineTo(border2,
                LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1));
    if(point.y==0){   //上边界
        pDC->MoveTo(border1,LeftTopPos.y+1);
        pDC->LineTo(border2,LeftTopPos.y+1);
    }
    if(point.y==BOARD_SIZE-1){   //下边界
        pDC->MoveTo(border1,LeftTopPos.y+Size.cy-1);
        pDC->LineTo(border2,LeftTopPos.y+Size.cy-1);
    }

    border1=LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)-Size.cy/2/(BOARD_SIZE-1);
    if(border1<LeftTopPos.y)border1=LeftTopPos.y;
    pDC->MoveTo(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1),
                border1);
    border2=LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)+Size.cy/2/(BOARD_SIZE-1);
    if(border2>LeftTopPos.y+Size.cy+1)border2=LeftTopPos.y+Size.cy+1;
    pDC->LineTo(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1),
                border2);
    if(point.x==0){   //左边界
        pDC->MoveTo(LeftTopPos.x+1,border1);
        pDC->LineTo(LeftTopPos.x+1,border2);
    }
    if(point.x==BOARD_SIZE-1){   //右边界
        pDC->MoveTo(LeftTopPos.x+Size.cx-1,border1);
        pDC->LineTo(LeftTopPos.x+Size.cx-1,border2);
    }
}

void CBoardView::DrawKeyPoint(const CPoint &point,COLORREF color,CDC *pDC){
    CBrush blackBrush(color);
    CBrush *pOldBrush=pDC->SelectObject(&blackBrush);
    pDC->Rectangle(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)-1,
                   LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)-1,
                   LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)+2,
                   LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)+2);
    pDC->SelectObject(pOldBrush);
}

void CBoardView::DrawFoul(const CPoint &point,CDC *pDC){
    CPoint block(Size.cx/(BOARD_SIZE-1),Size.cy/(BOARD_SIZE-1));
    CPoint center;
    IdxToPoint(point,center);
    CPen pen(PS_SOLID,2,RGB(255,0,0));
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
    SpotPoint[0].SetPoint(7,7);
    SpotPoint[1].SetPoint(3,3);
    SpotPoint[2].SetPoint(11,11);
    SpotPoint[3].SetPoint(3,11);
    SpotPoint[4].SetPoint(11,3);
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
    for(size_t i=0;i<MoveList.size();++i){
        Color color;
        if(0 == i%2)color=Black;
        else color=White;
        DrawStone(MoveList[i],color,i+1,pDC);
    }

    //显示禁手
    ShowFoulOnly(pDC);
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
    idx.x=(point.x-LeftTopPos.x+Size.cx/(BOARD_SIZE-1)/2)/(Size.cx/(BOARD_SIZE-1));
    idx.y=(point.y-LeftTopPos.y+Size.cy/(BOARD_SIZE-1)/2)/(Size.cy/(BOARD_SIZE-1));
}

void CBoardView::IdxToPoint(const CPoint &idx, CPoint &point){
    point.x=LeftTopPos.x+idx.x*Size.cx/(BOARD_SIZE-1);
    point.y=LeftTopPos.y+idx.y*Size.cy/(BOARD_SIZE-1);
}

void CBoardView::ShowFoul(CDC *pDC){
    //EraseAllFoul(pDC);
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){
        if(CheckFoul(CPoint(i,j))){
            DrawFoul(CPoint(i,j),pDC);
            FoulState[i][j]=true;
        }
        else if(FoulState[i][j]){
            if(matrix[i][j]==Empty)ErasePoint(CPoint(i,j),pDC);
            FoulState[i][j]=false;
        }
    }
}

void CBoardView::ShowFoulOnly(CDC *pDC){
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j)
        if(FoulState[i][j])DrawFoul(CPoint(i,j),pDC);
}

void CBoardView::DrawStone(const CPoint &point,Color color,size_t num,CDC *pDC){
    CBrush brush;   //棋子画刷
    COLORREF OldTextColor;
    if(Black == color){//设置黑棋和数字颜色
        brush.CreateSolidBrush(RGB(0,0,0));
        OldTextColor=pDC->SetTextColor(RGB(255,255,255));
    }
    else {//设置白棋和数字颜色
        brush.CreateSolidBrush(RGB(255,255,255));
        OldTextColor=pDC->SetTextColor(RGB(0,0,0));
    }
    CBrush *pOldBrush=pDC->SelectObject(&brush);
    pDC->Ellipse(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)-Size.cx*20/41/(BOARD_SIZE-1),
                 LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)-Size.cy*20/41/(BOARD_SIZE-1),
                 LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)+Size.cx*20/41/(BOARD_SIZE-1),
                 LeftTopPos.y+Size.cx*point.y/(BOARD_SIZE-1)+Size.cy*20/41/(BOARD_SIZE-1));
    //设置字体
    CFont font;
    font.CreatePointFont(80,_T("Arial"),NULL);
    CFont *pOldFont=pDC->SelectObject(&font);
    //显示数字
    CString str;
    str.Format(_T("%d"),num);
    CSize strsz=pDC->GetTextExtent(str);
    pDC->SetBkMode(TRANSPARENT);
    pDC->TextOutW(LeftTopPos.x+Size.cx*point.x/(BOARD_SIZE-1)-strsz.cx/2,
                  LeftTopPos.y+Size.cy*point.y/(BOARD_SIZE-1)-strsz.cy/2,str);

    //收尾工作
    font.DeleteObject();
    pDC->SelectObject(pOldFont);
    pDC->SetTextColor(OldTextColor);
    pDC->SelectObject(pOldBrush);
}

void CBoardView::Clear(void){
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j)
        FoulState[i][j]=false;
    CBoard::Clear();
}