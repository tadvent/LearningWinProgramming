#include "StdAfx.h"
#include "BoardTry.h"

CBoardTry::CBoardTry(void)
{
}

CBoardTry::CBoardTry(const CBoard &bd){
    CBoard::CBoard(bd);
}

CBoardTry::CBoardTry(const CBoardView &bdv){
    CBoard::CBoard(bdv);
}

CBoardTry::~CBoardTry(void)
{
}



//int CBoardTry::CheckFour(const CPoint &point){
//    TryMove(point);
//    CRect Border;
//    Border.left=(point.x-5<0)?0:point.x-5;
//    Border.right=(point.x+5<BOARD_SIZE)?point.x+5:BOARD_SIZE-1;
//    Border.top=(point.y-5<0)?0:point.y-5;
//    Border.bottom=(point.y+5<BOARD_SIZE)?point.y+5:BOARD_SIZE-1;
//    int fivenum=0;
//    for(int i=Border.left;i<=Border.right;++i)for(int j=Border.top;j<=Border.bottom;++j){
//        if(-1==CheckMove(CPoint(i,j)))continue;
//        int ptstatus=CheckFive(CPoint(i,j),static_cast<Color>(-NextColor));
//        if(ptstatus==5)++fivenum;
//        if(ptstatus==6)if(NextColor==Black)++fivenum;
//    }
//    if(fivenum==1)return 4;
//    if(fivenum>1)return 44;
//
//    TryClear();
//
//    return 0;
//}