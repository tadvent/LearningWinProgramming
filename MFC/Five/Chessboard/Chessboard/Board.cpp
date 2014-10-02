#include "StdAfx.h"
#include "Board.h"
#include <list>
#include"BoardView.h"
#include"BoardTry.h"
using namespace std;

CBoard::CBoard(void)
{
    MoveList.clear();
    TryList.clear();
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){
        matrix[i][j]=Empty;
    }
    NextColor=Black;
    ForbidRule=true;
    vcfList.clear();
}

CBoard::CBoard(const CBoard &bd):MoveList(bd.MoveList),TryList(bd.TryList),NextColor(bd.NextColor),ForbidRule(bd.ForbidRule){
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){
        matrix[i][j]=bd.matrix[i][j];
    }
}

CBoard::CBoard(const CBoardView &bdv):MoveList(bdv.MoveList),TryList(bdv.TryList),NextColor(bdv.NextColor),ForbidRule(bdv.ForbidRule){
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){
        matrix[i][j]=bdv.matrix[i][j];
    }
}

CBoard::~CBoard(void)
{
}

void CBoard::DoMove(const CPoint &point){   //移动一步，不做任何检查
    MoveList.push_back(point);
    matrix[point.x][point.y]=NextColor;
    NextColor=static_cast<Color>(-NextColor);
    TryList.clear();

}

int CBoard::BackMove(void){
    if(MoveList.empty())return -1;
    matrix[MoveList.back().x][MoveList.back().y]=Empty;
    NextColor=static_cast<Color>(-NextColor);
    MoveList.pop_back();
    TryList.clear();
    return 0;
}

int CBoard::CheckFive(const CPoint &point,Color color){
    int openline[4]={0,0,0,0};
    if(Empty==color)color=NextColor;

    CPoint Direction[4];    //四个方向向量
    Direction[0].SetPoint(1,0);//水平
    Direction[1].SetPoint(0,1);//竖直
    Direction[2].SetPoint(1,1);//右下
    Direction[3].SetPoint(1,-1);//右上

    for(int i=0;i<4;++i){
        openline[i]=CheckOpenNum(point,Direction[i],color);
        if(5==openline[i])return 5;
    }

    for(int i=0;i<4;++i){
        if(openline[i]>5)return 6;
    }

    return 0;
}

int CBoard::CheckMove(const CPoint &point){
    if(IsOutBoard(point))return -1;  //出界
    if(Empty != matrix[point.x][point.y])
        return -1;  //已有子
    //其他情况
    return 0;
}

inline bool CBoard::IsOutBoard(const CPoint &point){
    if(point.x<0 || point.x>=BOARD_SIZE || point.y<0 || point.y>=BOARD_SIZE)return true;
    return false;
}

inline bool CBoard::IsOutBoard(const int x,const int y){
    if(x<0 || x>=BOARD_SIZE || y<0 || y>=BOARD_SIZE)return true;
    return false;
}

void CBoard::TryMove(const CPoint &point,Color color){
    if(Empty==color)color=NextColor;
    TryList.push_back(point);
    matrix[point.x][point.y]=color;
    NextColor=static_cast<Color>(-NextColor);
}

int CBoard::TryBack(void){
    if(TryList.empty())return -1;
    matrix[TryList.back().x][TryList.back().y]=Empty;
    NextColor=static_cast<Color>(-NextColor);
    TryList.pop_back();
    return 0;
}

void CBoard::TryClear(void){
    while(!TryList.empty()){
        matrix[TryList.back().x][TryList.back().y]=Empty;
        TryList.pop_back();
    }
    NextColor = (0==(MoveList.size()%2))?Black:White;
}

int CBoard::CheckOpenNum(const CPoint &center, const CPoint &direction, Color color){
    int open=1;
    int x=center.x-direction.x;
    int y=center.y-direction.y;
    for(;!IsOutBoard(x,y);x-=direction.x,y-=direction.y,++open){
        if(matrix[x][y]!=color)break;
    }
    x=center.x+direction.x;
    y=center.y+direction.y;
    for(;!IsOutBoard(x,y);x+=direction.x,y+=direction.y,++open){
        if(matrix[x][y]!=color)break;
    }
    return open;
}

int CBoard::CheckFour(const CPoint &point,Color color){
    if(Empty==color)color=NextColor;
    //进入此函数前要保证五连和长连的情况都已被排除，冲四返回4，双四返回44
    int fivenum[4]={0,0,0,0};
    TryMove(point,color);
    CPoint Direction[4];    //四个方向向量
    Direction[0].SetPoint(1,0);//水平
    Direction[1].SetPoint(0,1);//竖直
    Direction[2].SetPoint(1,1);//右下
    Direction[3].SetPoint(1,-1);//右上

    for(int ii=0;ii<4;++ii){//对四个方向循环
        CPoint direction=Direction[ii];
        CPoint tmpPoint=FindFirstEmpty(point,color,direction,5);
        if(point!=tmpPoint){
            int openline=CheckOpenNum(tmpPoint,direction,color);
            if(openline==5)++fivenum[ii];
            else if(openline>5 && (!ForbidRule || color==White))++fivenum[ii];
        }
        tmpPoint=FindFirstEmpty(point,color,-direction,5);
        if(point!=tmpPoint){
            int openline=CheckOpenNum(tmpPoint,direction,color);

            if(openline==5)++fivenum[ii];
            else if(openline>5 && (!ForbidRule || color==White))++fivenum[ii];
        }
        if(fivenum[ii]==2){
            //检查是否是四连
            int openline=CheckOpenNum(point,direction,color);
            if(openline>=4)--fivenum[ii];
        }
    }

    TryBack();
    //综合以上各种情况：
    for(int i=1;i<4;++i)fivenum[0]+=fivenum[i];
    if(fivenum[0]==1)return 4;
    else if(fivenum[0]>1)return 44;

    return 0;
}

CPoint CBoard::FindFirstEmpty(const CPoint &center,Color color,const CPoint &direction, const int maxstep){
    //在direction方向上maxstep内寻找第一个空位，若找到返回空位坐标，否则返回center坐标
    CPoint tmpPoint(center);
    for(int i=1;i<maxstep;++i){
        tmpPoint+=direction;
        if(IsOutBoard(tmpPoint))return center;
        if(matrix[tmpPoint.x][tmpPoint.y]==static_cast<Color>(-color))return center;
        if(matrix[tmpPoint.x][tmpPoint.y]==Empty)return tmpPoint;
    }
    return center;
}

int CBoard::CheckThree(const CPoint &point,Color color){
    if(Empty==color)color=NextColor;
    //进入此函数前要保证五连、长连和双四的情况都已被排除，活三返回3，双三返回33
    int fivenum,fivesum=0;
    TryMove(point,color);
    CPoint Direction[4];    //四个方向向量
    Direction[0].SetPoint(1,0);//水平
    Direction[1].SetPoint(0,1);//竖直
    Direction[2].SetPoint(1,1);//右下
    Direction[3].SetPoint(1,-1);//右上

    for(int ii=0;ii<4 && fivesum<2;++ii,fivesum+=fivenum){//对四个方向循环
        fivenum=0;
        CPoint direction=Direction[ii];
        CPoint tmpPoint=FindFirstEmpty(point,color,direction,4);//找空位
        if(point!=tmpPoint){//若找到则判断是否是两边都无阻挡的四连
            int line=1;
            CPoint tmplPoint=tmpPoint-direction;
            while(!IsOutBoard(tmplPoint)){
                if(matrix[tmplPoint.x][tmplPoint.y]!=color)break;
                tmplPoint-=direction;
                ++line;
            }
            CPoint tmprPoint=tmpPoint+direction;
            while(!IsOutBoard(tmprPoint)){
                if(matrix[tmprPoint.x][tmprPoint.y]!=color)break;
                tmprPoint+=direction;
                ++line;
            }
            if(line==4){
                if(!IsOutBoard(tmplPoint) && !IsOutBoard(tmprPoint))if(matrix[tmplPoint.x][tmplPoint.y]==Empty && matrix[tmprPoint.x][tmprPoint.y]==Empty)
                    if(!CheckFoul(tmpPoint)){
                        TryMove(tmpPoint,color);
                        if(/*CheckFive(tmplPoint,color)!=6 && CheckFive(tmprPoint,color)!=6*/
                           CheckOpenNum(tmplPoint,direction,color)<6 && CheckOpenNum(tmprPoint,direction,color)<6)++fivenum;
                        TryBack();
                    }
            }
        }
        if(fivenum>0)continue;  //若一个方向上找到活三则不用再判定相反方向，因为同一条直线上不会出现双三
        tmpPoint=FindFirstEmpty(point,color,-direction,4);//找空位
        if(point!=tmpPoint){//若找到则判断是否是两边都无阻挡的四连
            int line=1;
            CPoint tmplPoint=tmpPoint-direction;
            while(!IsOutBoard(tmplPoint)){
                if(matrix[tmplPoint.x][tmplPoint.y]!=color)break;
                tmplPoint-=direction;
                ++line;
            }
            CPoint tmprPoint=tmpPoint+direction;
            while(!IsOutBoard(tmprPoint)){
                if(matrix[tmprPoint.x][tmprPoint.y]!=color)break;
                tmprPoint+=direction;
                ++line;
            }
            if(line==4){
                if(!IsOutBoard(tmplPoint) && !IsOutBoard(tmprPoint))if(matrix[tmplPoint.x][tmplPoint.y]==Empty && matrix[tmprPoint.x][tmprPoint.y]==Empty)
                    if(!CheckFoul(tmpPoint)){
                        TryMove(tmpPoint,color);
                        if(CheckOpenNum(tmplPoint,direction,color)!=6 && CheckOpenNum(tmprPoint,direction,color)!=6)++fivenum;
                        TryBack();
                    }
            }
        }
    }

    TryBack();
    //综合以上各种情况：
    if(fivesum==1)return 3;
    else if(fivesum>1)return 33;

    return 0;
}

int CBoard::CheckFoul(const CPoint &point){
    if(IsOutBoard(point))return 0;
    if(Empty!=matrix[point.x][point.y])return 0;
    int Status=CheckFive(point,Black);
    if(5==Status)return 0;
    if(6==Status)return 6;
    Status=CheckFour(point,Black);
    if(44==Status)return 44;
    Status=CheckThree(point,Black);
    if(33==Status)return 33;
    //检查双三...

    return 0;
}

//void CBoard::MarkFoul(void){
//    if(!ForbidRule)return;
//    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){
//        if(CheckFoul(CPoint(i,j)))matrix[i][j]=Foul;
//        else if(matrix[i][j]==Foul)matrix[i][j]=Empty;
//    }
//}

void CBoard::Clear(){
    ForbidRule=true;
    for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j)
        matrix[i][j]=Empty;
    MoveList.clear();
    NextColor=Black;
    TryList.clear();
}

int CBoard::SearchVCF(Color color){
    if(Empty==color)color=NextColor;
    if(DoSearchVCF(color)){
        vcfList=TryList;
        TryClear();
        return 1;
    }
    TryClear();
    return 0;
}

int CBoard::DoSearchVCF(Color color){
    bool WhiteFour=false,BlackFour=false;
    if(Empty==color)color=NextColor;
    vector<CPoint> FourList;
    switch(color){
        case Black:
            for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){//黑是否有胜点
                if(Empty != matrix[i][j])continue;
                if(CheckFoul(CPoint(i,j)))continue;
                if(5 == CheckFive(CPoint(i,j),Black)){
                    TryMove(CPoint(i,j),Black);
                    return 1;
                }
            }
            //bool WhiteFour=false;
            for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){//找白棋是否有胜点
                if(Empty != matrix[i][j])continue;
                int fivenum=CheckFive(CPoint(i,j),White);
                if( fivenum >= 5){  //找到白棋胜点
                    if(WhiteFour){  //白棋有多于1个胜点
                        return 0;
                    }
                    WhiteFour=true;
                    if(CheckFoul(CPoint(i,j))){//若该点恰是黑棋禁手点
                        return 0;
                    }
                    else {//不是禁手点
                        if(4 == CheckFour(CPoint(i,j),Black)){//黑棋在此点冲四
                            FourList.clear();
                            FourList.push_back(CPoint(i,j));
                        }
                        else {//黑棋在此点不冲四
                            return 0;
                        }
                    }
                }
            }
            if(FourList.empty()){
                for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){  //找齐黑棋所有不是禁手的冲四点
                    if(Empty != matrix[i][j])continue;
                    if(CheckFoul(CPoint(i,j)))continue;
                    if(4 == CheckFour(CPoint(i,j),Black)){
                        FourList.push_back(CPoint(i,j));
                    }
                }
            }
            for(size_t i=0;i<FourList.size();++i){
                TryMove(FourList[i],Black);
                for(int x=0;x<BOARD_SIZE;++x)for(int y=0;y<BOARD_SIZE;++y){
                    if(Empty != matrix[x][y])continue;
                    if(5 == CheckFive(CPoint(x,y),Black)){//寻找黑棋冲四的挡点
                        //if(4 != CheckFour(CPoint(x,y),White)){//白棋挡4时不形成反冲四
                            TryMove(CPoint(x,y),White);
                            if(DoSearchVCF(Black))return 1;
                            TryBack();
                        //}
                        //else {      //白棋挡4时形成反冲四
                        //}
                    }
                }
                TryBack();
            }

            break;

        case White:
            for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){//白是否有胜点
                if(Empty != matrix[i][j])continue;
                if(5 <= CheckFive(CPoint(i,j),White)){
                    TryMove(CPoint(i,j),White);
                    return 1;
                }
            }
            for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){  //找齐白棋所有冲四点
                if(Empty != matrix[i][j])continue;
                if(4 == CheckFour(CPoint(i,j),Black)){
                    FourList.push_back(CPoint(i,j));
                }
            }
            for(size_t i=0;i<FourList.size();++i){ //找能否有使黑棋禁手的冲四
                TryMove(FourList[i],Black);
                for(int x=0;x<BOARD_SIZE;++x)for(int y=0;y<BOARD_SIZE;++y){
                    if(Empty != matrix[x][y])continue;
                    if(5 == CheckFive(CPoint(x,y),White)){//寻找白棋冲四的挡点
                        if(CheckFoul(CPoint(x,y))){  //黑棋挡4时形成禁手
                            return 1;
                        }
                    }
                }
                TryBack();
            }

            //bool BlackFour=false;
            for(int i=0;i<BOARD_SIZE;++i)for(int j=0;j<BOARD_SIZE;++j){//找黑棋是否有胜点
                if(Empty != matrix[i][j])continue;
                if(CheckFoul(CPoint(i,j)))continue;
                int fivenum=CheckFive(CPoint(i,j),Black);
                if( fivenum == 5){  //找到黑棋胜点
                    if(BlackFour){  //黑棋有多于1个胜点
                        return 0;
                    }
                    BlackFour=true;
                    if(4 == CheckFour(CPoint(i,j),White)){//白棋在此点冲四
                        FourList.clear();
                        FourList.push_back(CPoint(i,j));
                    }
                    else {//白棋在此点不冲四
                        return 0;
                    }
                }
            }
            for(size_t i=0;i<FourList.size();++i){
                TryMove(FourList[i],Black);
                for(int x=0;x<BOARD_SIZE;++x)for(int y=0;y<BOARD_SIZE;++y){
                    if(Empty != matrix[x][y])continue;
                    if(5 == CheckFive(CPoint(x,y),White)){//寻找白棋冲四的挡点
                        TryMove(CPoint(x,y),White);
                        if(DoSearchVCF(Black))return 1;
                        TryBack();
                    }
                }
                TryBack();
            }
            break;
    }
    return 0;
}