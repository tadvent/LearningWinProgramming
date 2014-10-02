#include "StdAfx.h"
#include "Board.h"
#include<combination>
#include<algorithm>
#include<arrange>

//////////////////////////////////////////////////////////////////////////////////

CBoard::CBoard(void){
    //初始化棋盘
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        matrix[i][j]=EMPTY;
    }
    //初始化边界
    for(int i=0;i<BOARD_SIZE+2;++i){
        matrix[i][0]='$';               //上边界
        matrix[i][BOARD_SIZE+1]='$';    //下边界
        matrix[0][i]='$';               //左边界
        matrix[BOARD_SIZE+1][i]='$';    //右边界
    }
    MoveList.clear();
    vcfList.clear();
    nCurrent=0;
}

CBoard::~CBoard(void){
}

void CBoard::Clear(void){//初始化棋盘
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        matrix[i][j]=EMPTY;
    }
    MoveList.clear();
    nCurrent=0;
}

//////////////////////////////////////////////////////////////////////////////////

int CBoard::DoMove(/*char color,*/ const CPoint &point){   //移动一步，无效坐标返回-1，正常返回0
    if(IsOutBoard(point))return -1;
    if(EMPTY!=matrix[point.x][point.y])return -1;
    if(nCurrent < MoveList.size()){ //当前步数小于MoveList的记录，则移除MoveList多余记录
        MoveList.resize(nCurrent);
    }
    MoveList.push_back(point);
    ++nCurrent;
    matrix[point.x][point.y]=(nCurrent%2)?BLACK:WHITE;
    //TryList.clear();
    return 0;
}

int CBoard::BackMove(void){
    if(nCurrent<1)return -1;
    --nCurrent;
    matrix[MoveList[nCurrent].x][MoveList[nCurrent].y]=EMPTY;
    vcfList.clear();
    //MoveList.pop_back();
    //TryList.clear();
    return 0;
}

int CBoard::ForwardMove(void){
    if(nCurrent >= MoveList.size())return -1;
    char color= (nCurrent%2)?WHITE:BLACK;
    matrix[MoveList[nCurrent].x][MoveList[nCurrent].y]=color;
    ++nCurrent;
    return 0;
}

inline bool CBoard::IsOutBoard(const CPoint &point){
    if(point.x<1 || point.x>BOARD_SIZE || point.y<1 || point.y>BOARD_SIZE)return true;
    return false;
}

inline bool CBoard::IsOutBoard(const int x,const int y){
    if(x<1 || x>BOARD_SIZE || y<1 || y>BOARD_SIZE)return true;
    return false;
}

inline void CBoard::TryMove(const char color, const int x, const int y){
    matrix[x][y]=color;
    //return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//禁手判定部分函数

int CBoard::IsFive(const char color, const int x, const int y, const int nDir){
    //在某方向上成五连返回5，黑棋长连返回6，否则返回0

    if(EMPTY != matrix[x][y])return 0;
    int line=1,i,j;

    switch(color){
        case BLACK:
            switch(nDir){
                case 1:
                    i=x;
                    while(matrix[--i][y]==BLACK){
                        ++line;
                    }
                    i=x;
                    while(matrix[++i][y]==BLACK){
                        ++line;
                    }
                    if(line == 5)return 5;
                    if(line > 5 )return 6;
                    break;
                case 2:
                    j=y;
                    while(matrix[x][--j]==BLACK){
                        ++line;
                    }
                    j=y;
                    while(matrix[x][++j]==BLACK){
                        ++line;
                    }
                    if(line == 5)return 5;
                    if(line > 5 )return 6;
                    break;
                case 3:
                    i=x;
                    j=y;
                    while(matrix[--i][--j]==BLACK){
                        ++line;
                    }
                    i=x;
                    j=y;
                    while(matrix[++i][++j]==BLACK){
                        ++line;
                    }
                    if(line == 5)return 5;
                    if(line > 5 )return 6;
                    break;
                case 4:
                    i=x;
                    j=y;
                    while(matrix[--i][++j]==BLACK){
                        ++line;
                    }
                    i=x;
                    j=y;
                    while(matrix[++i][--j]==BLACK){
                        ++line;
                    }
                    if(line == 5)return 5;
                    if(line > 5 )return 6;
                    break;
                default:
                    break;
            }

            break;

        case WHITE:
            switch(nDir){
                case 1:
                    i=x;
                    while(matrix[--i][y]==WHITE){
                        ++line;
                    }
                    i=x;
                    while(matrix[++i][y]==WHITE){
                        ++line;
                    }
                    if(line >= 5)return 5;
                    break;
                case 2:
                    j=y;
                    while(matrix[x][--j]==WHITE){
                        ++line;
                    }
                    j=y;
                    while(matrix[x][++j]==WHITE){
                        ++line;
                    }
                    if(line >= 5)return 5;
                    break;
                case 3:
                    i=x;
                    j=y;
                    while(matrix[--i][--j]==WHITE){
                        ++line;
                    }
                    i=x;
                    j=y;
                    while(matrix[++i][++j]==WHITE){
                        ++line;
                    }
                    if(line >= 5)return 5;
                    break;
                case 4:
                    i=x;
                    j=y;
                    while(matrix[--i][++j]==WHITE){
                        ++line;
                    }
                    i=x;
                    j=y;
                    while(matrix[++i][--j]==WHITE){
                        ++line;
                    }
                    if(line >= 5)return 5;
                    break;
                default:
                    break;
            }

            break;

        default:
            break;
    }
    return 0;
}

int CBoard::IsFive(const char color, const int x, const int y){
    //五连返回5，黑棋长连返回6，否则返回0

    if(EMPTY!=matrix[x][y]) return 0;
    if(BLACK == color){
        bool overline=false;
        for(int i=1;i<5;++i){
            int status=IsFive(BLACK,x,y,i);
            if(5 == status)return 5;
            if(6 == status)overline=true;
        }
        if(overline)return 6;
    }
    else if(WHITE == color){
        for(int i=1;i<5;++i){
            if(5 == IsFive(WHITE,x,y,i))return 5;
        }
    }
    return 0;
}

int CBoard::IsFour(const char color, const int x, const int y, const int nDir){
    //在某方向上冲四返回4，四连返回40，双四返回44，否则返回0

    if(EMPTY!=matrix[x][y]) return 0;
    int line=1,i,j,result=0;
    bool havefour=false;
    TryMove(color,x,y);

    switch(nDir){
        case 1: //横向 '-'
            i=x;
            while(color == matrix[--i][y]){
                ++line;
            }
            if(EMPTY == matrix[i][y]){
                if(5 == IsFive(color,i,y,1))havefour=true;
            }
            i=x;
            while(color == matrix[++i][y]){
                ++line;
            }
            if(EMPTY == matrix[i][y]){
                if(5 == IsFive(color,i,y,1)){   //这边是冲四
                    if(havefour){   //若另一边也有冲四
                        if(line ==4){   //若是四连
                            result=40;
                        }
                        else {  //若不是四连
                            result=44;
                        }
                    }
                    else {  //若另一边没有冲四
                        result=4;
                    }
                }
                else {  //这边不是冲四
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //这边不是冲四
                if(havefour){
                    result=4;
                }
            }
            break;
        case 2: //竖向 '|'
            j=y;
            while(color == matrix[x][--j]){
                ++line;
            }
            if(EMPTY == matrix[x][j]){
                if(5 == IsFive(color,x,j,2))havefour=true;
            }
            j=y;
            while(color == matrix[x][++j]){
                ++line;
            }
            if(EMPTY == matrix[x][j]){
                if(5 == IsFive(color,x,j,2)){   //这边是冲四
                    if(havefour){   //若另一边也有冲四
                        if(line ==4){   //若是四连
                            result=40;
                        }
                        else {  //若不是四连
                            result=44;
                        }
                    }
                    else {  //若另一边没有冲四
                        result=4;
                    }
                }
                else {  //这边不是冲四
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //这边不是冲四
                if(havefour){
                    result=4;
                }
            }
            break;
        case 3: //斜向 '\'
            i=x;
            j=y;
            while(color == matrix[--i][--j]){
                ++line;
            }
            if(EMPTY == matrix[i][j]){
                if(5 == IsFive(color,i,j,3))havefour=true;
            }
            i=x;
            j=y;
            while(color == matrix[++i][++j]){
                ++line;
            }
            if(EMPTY == matrix[i][j]){
                if(5 == IsFive(color,i,j,3)){   //这边是冲四
                    if(havefour){   //若另一边也有冲四
                        if(line ==4){   //若是四连
                            result=40;
                        }
                        else {  //若不是四连
                            result=44;
                        }
                    }
                    else {  //若另一边没有冲四
                        result=4;
                    }
                }
                else {  //这边不是冲四
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //这边不是冲四
                if(havefour){
                    result=4;
                }
            }
            break;
        case 4: //斜向 '/'
            i=x;
            j=y;
            while(color == matrix[--i][++j]){
                ++line;
            }
            if(EMPTY == matrix[i][j]){
                if(5 == IsFive(color,i,j,4))havefour=true;
            }
            i=x;
            j=y;
            while(color == matrix[++i][--j]){
                ++line;
            }
            if(EMPTY == matrix[i][j]){
                if(5 == IsFive(color,i,j,4)){   //这边是冲四
                    if(havefour){   //若另一边也有冲四
                        if(line ==4){   //若是四连
                            result=40;
                        }
                        else {  //若不是四连
                            result=44;
                        }
                    }
                    else {  //若另一边没有冲四
                        result=4;
                    }
                }
                else {  //这边不是冲四
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //这边不是冲四
                if(havefour){
                    result=4;
                }
            }
            break;
        default:
            break;
    }

    TryMove(EMPTY,x,y);
    return result;
}

int CBoard::IsFour(const char color, const int x, const int y){
    //冲四返回4，活四连返回40，否则返回0，已考虑禁手

    if(EMPTY!=matrix[x][y]) return 0;

    int nFour=0,status;
    bool openfour=false;
    switch(color){
        case BLACK:
            if(IsFoul(x,y))return 0;
            for(int i=1;i<5;++i){
                status=IsFour(BLACK,x,y,i);
                if(4 == status)++nFour;
                else if(40 == status){++nFour;openfour=true;}
            }
            if(openfour)return 40;
            else if(nFour>0)return 4;
            else return 0;

            break;

        case WHITE:
            for(int i=1;i<5;++i){
                status=IsFour(WHITE,x,y,i);
                if(4 == status)++nFour;
                else if(40 == status){++nFour;openfour=true;}
            }
            if(openfour)return 40;
            else if(nFour>0)return 4;
            else return 0;

            break;

        default:
            break;
    }
    return 0;
}

int CBoard::IsDoubleFour(const int x, const int y){
    //双四返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连和长连的情况

    if(EMPTY!=matrix[x][y]) return 0;

    int nFour=0,status;
    for(int i=1;i<5;++i){
        status=IsFour(BLACK,x,y,i);
        if(4 == status || 40 == status)++nFour;
        else if(44 == status) nFour+=2;
        if(nFour>1)return 1;
    }
    return 0;
}

int CBoard::IsOpenThree(const char color, const int x, const int y, const int nDir){
    //在某方向上活三返回1，否则返回0

    if(EMPTY!=matrix[x][y]) return 0;
    int line=1,i,j,result=0;

    TryMove(color,x,y);

    switch(nDir){
        case 1: //横向 '-'
            i=x;
            while(color == matrix[--i][y]);
            if(EMPTY == matrix[i][y]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,i,y,1))if(color == WHITE || !IsFoul(i,y)){
                    result = 1;
                    break;
                }
            }
            else {  //一个方向上没有空格，不可能是活三
                //result = -1;
                break;
            }
            i=x;
            while(color == matrix[++i][y]);
            if(EMPTY == matrix[i][y]){  //另一方向上有空格，进一步判断
                if(40 == IsFour(color,i,y,1))if(color == WHITE || !IsFoul(i,y)){
                    result = 1;
                }
            }
            break;
        case 2: //竖向 '|'
            j=y;
            while(color == matrix[x][--j]);
            if(EMPTY == matrix[x][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,x,j,2))if(color == WHITE || !IsFoul(x,j)){
                    result = 1;
                    break;
                }
            }
            else {  //一个方向上没有空格，不可能是活三
                //result = -1;
                break;
            }
            j=y;
            while(color == matrix[x][++j]);
            if(EMPTY == matrix[x][j]){  //另一方向上有空格，进一步判断
                if(40 == IsFour(color,x,j,2))if(color == WHITE || !IsFoul(x,j)){
                    result = 1;
                }
            }
            break;
        case 3: //斜向 '\'
            i=x;
            j=y;
            while(color == matrix[--i][--j]);
            if(EMPTY == matrix[i][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,3))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                    break;
                }
            }
            else {  //一个方向上没有空格，不可能是活三
                //result = -1;
                break;
            }
            i=x;
            j=y;
            while(color == matrix[++i][++j]);
            if(EMPTY == matrix[i][j]){  //另一方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,3))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                }
            }
            break;
        case 4: //斜向 '\'
            i=x;
            j=y;
            while(color == matrix[--i][++j]);
            if(EMPTY == matrix[i][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,4))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                    break;
                }
            }
            else {  //一个方向上没有空格，不可能是活三
                //result = -1;
                break;
            }
            i=x;
            j=y;
            while(color == matrix[++i][--j]);
            if(EMPTY == matrix[i][j]){  //另一方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,4))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                }
            }
            break;
        default:
            break;
    }

    TryMove(EMPTY,x,y);
    return result;
}

int CBoard::IsOpenThree(const char color, const int x, const int y){
    //活三返回1，否则返回0

    if(EMPTY != matrix[x][y]) return 0;

    switch(color){
        case BLACK:
            if(IsFoul(x,y))return 0;
            for(int i=1;i<5;++i)if(IsOpenThree(BLACK,x,y,i))return 1;
            break;
        case WHITE:
            for(int i=1;i<5;++i)if(IsOpenThree(WHITE,x,y,i))return 1;
            break;
        default:
            break;
    }
    return 0;
}

int CBoard::IsDoubleThree(const int x, const int y){
    //双三返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连、长连和双四的情况

    if(EMPTY != matrix[x][y]) return 0;

    int nThree=0;
    for(int i=1;i<5;++i){
        if(IsOpenThree(BLACK,x,y,i))
            ++nThree;
    }
    if(nThree>1)return 1;
    return 0;
}

int CBoard::IsFoul(const int x, const int y){
    //长连禁手返回6、双四返回44、双三返回33，否则返回0 (该函数仅对黑棋判断)

    if(EMPTY != matrix[x][y]) return 0;

    int status=IsFive(BLACK,x,y);
    if(5 == status) return 0;
    else if(6 == status) return 6;

    if(IsDoubleFour(x,y))return 44;

    if(IsDoubleThree(x,y))return 33;

    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
//走棋算法部分函数

int CBoard::CheckMove(const int x, const int y){
    //五连返回5，长连禁手返回6，双四返回44，双三返回33，否则返回0

    if(EMPTY != matrix[x][y]) return 0;
    int status;
    switch(nCurrent%2){
        case 0: //此步该黑棋
            if(5 == IsFive(BLACK,x,y))return 5;
            else {
                status=IsFoul(x,y);
                if(status>0)return status;
            }
            return 0;
            break;
        case 1: //此步该白棋
            if(5 == IsFive(WHITE,x,y))return 5;
            else return 0;
            break;
    }
    return 0;
}

int CBoard::HaveFour(const char color,int &x, int &y){
    //有四则返回1，否则返回0，成五的点由x,y返回
    int leftnum;  //空格左边的连续子数
    int rightnum; //空格右边的连续子数
    bool validempty;//空格有效标记
    int i,j;

    switch(color){
        case BLACK: //黑棋
            //检查横行 '-'
            for(j=1;j<BOARD_SIZE+1;++j){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(i=1;i<BOARD_SIZE+2;++i){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case BLACK:
                            ++rightnum;
                            break;
                        case WHITE:
                            if(validempty){
                                if(4==leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //检查竖行 '|'
            for(i=1;i<BOARD_SIZE+1;++i){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(j=1;j<BOARD_SIZE+2;++j){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case BLACK:
                            ++rightnum;
                            break;
                        case WHITE:
                            if(validempty){
                                if(4==leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                }
            }

            //检查斜行 '\'
            for(int ii=-BOARD_SIZE+6;ii<BOARD_SIZE-3;++ii){
                leftnum=0;
                rightnum=0;
                validempty=false;
                if(ii<1){
                    i=1;
                    j=2-ii;
                }
                else {
                    i=ii;
                    j=1;
                }
                while(i<BOARD_SIZE+2 && j<BOARD_SIZE+2){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case BLACK:
                            ++rightnum;
                            break;
                        case WHITE:
                            if(validempty){
                                if(4==leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                    ++i;
                    ++j;
                }
            }

            //检查斜行 '/'
            for(int ii=5;ii<BOARD_SIZE*2-4;++ii){
                leftnum=0;
                rightnum=0;
                validempty=false;
                if(ii<BOARD_SIZE+1){
                    i=ii;
                    j=1;
                }
                else {
                    i=BOARD_SIZE;
                    j=ii-BOARD_SIZE+1;
                }
                while(i>=0 && j<BOARD_SIZE+2){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case BLACK:
                            ++rightnum;
                            break;
                        case WHITE:
                            if(validempty){
                                if(4==leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                    --i;
                    ++j;
                }
            }

            break;
        case WHITE: //白棋
            //检查横行 '-'
            for(j=1;j<BOARD_SIZE+1;++j){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(i=1;i<BOARD_SIZE+2;++i){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case WHITE:
                            ++rightnum;
                            break;
                        case BLACK:
                            if(validempty){
                                if(4<=leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //检查竖行 '|'
            for(i=1;i<BOARD_SIZE+1;++i){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(j=1;j<BOARD_SIZE+2;++j){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case WHITE:
                            ++rightnum;
                            break;
                        case BLACK:
                            if(validempty){
                                if(4<=leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                }
            }

            //检查斜行 '\'
            for(int ii=-BOARD_SIZE+6;ii<BOARD_SIZE-3;++ii){
                leftnum=0;
                rightnum=0;
                validempty=false;
                if(ii<1){
                    i=1;
                    j=2-ii;
                }
                else {
                    i=ii;
                    j=1;
                }
                while(i<BOARD_SIZE+2 && j<BOARD_SIZE+2){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case WHITE:
                            ++rightnum;
                            break;
                        case BLACK:
                            if(validempty){
                                if(4<=leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                    ++i;
                    ++j;
                }
            }

            //检查斜行 '/'
            for(int ii=5;ii<BOARD_SIZE*2-4;++ii){
                leftnum=0;
                rightnum=0;
                validempty=false;
                if(ii<BOARD_SIZE+1){
                    i=ii;
                    j=1;
                }
                else {
                    i=BOARD_SIZE;
                    j=ii-BOARD_SIZE+1;
                }
                while(i>=0 && j<BOARD_SIZE+2){
                    switch(matrix[i][j]){
                        case EMPTY:
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                            validempty=true;
                            x=i;
                            y=j;
                            leftnum=rightnum;
                            rightnum=0;
                            break;
                        case WHITE:
                            ++rightnum;
                            break;
                        case BLACK:
                            if(validempty){
                                if(4<=leftnum+rightnum)return 1;
                                validempty=false;
                            }
                            leftnum=0;
                            rightnum=0;
                            break;
                        default:    //边界
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                    --i;
                    ++j;
                }
            }

            break;
    }
    return 0;
}

int CBoard::GetFourRushPoints(const char color, vector<FourRush> &vecFourRush){
    //计算color颜色的所有冲四点，由向量返回，函数返回值为冲四点个数
    //若有活四连或逼对方禁手则向量仅返回此点，函数返回值为2000
    vecFourRush.clear();
    //vecDefense.clear();
    int nNum=0;     //格数计数器(判断是否满5格)
    int nColor=0;   //颜色计数器(判断5格中同色子是否满3个)
    CPoint ept1,ept2;   //空格坐标

    switch(color){
        case BLACK: //黑棋
            //检查横行 '-'
            for(int j=1;j<BOARD_SIZE+1;++j){
                nNum=0;
                nColor=0;
                for(int i=1;i<BOARD_SIZE+1;++i){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case BLACK:
                            ++nNum;
                            ++nColor;
                            break;
                        case WHITE:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i-5][j]){
                            case EMPTY:
                                --nNum;
                                break;
                            case BLACK:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连
                        switch(IsFour(BLACK,ept1.x,ept1.y,1)){//对第一个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,1))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,1)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,1))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            //检查竖行 '|'
            for(int i=1;i<BOARD_SIZE+1;++i){
                nNum=0;
                nColor=0;
                for(int j=1;j<BOARD_SIZE+1;++j){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case BLACK:
                            ++nNum;
                            ++nColor;
                            break;
                        case WHITE:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case BLACK:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连
                        switch(IsFour(BLACK,ept1.x,ept1.y,2)){//对第一个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,2))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,2)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,2))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            //检查斜行 '\'
            for(int ii=-BOARD_SIZE+6;ii<BOARD_SIZE-3;++ii){
                nNum=0;
                nColor=0;
                int i,j;
                if(ii<1){
                    i=1;
                    j=2-ii;
                }
                else {
                    i=ii;
                    j=1;
                }
                while(i<BOARD_SIZE+1 && j<BOARD_SIZE+1){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case BLACK:
                            ++nNum;
                            ++nColor;
                            break;
                        case WHITE:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i-5][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case BLACK:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连
                        switch(IsFour(BLACK,ept1.x,ept1.y,3)){//对第一个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,3))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,3)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,3))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    ++i;
                    ++j;
                }
            }

            //检查斜行 '/'
            for(int ii=5;ii<BOARD_SIZE*2-4;++ii){
                nNum=0;
                nColor=0;
                int i,j;
                if(ii<BOARD_SIZE+1){
                    i=ii;
                    j=1;
                }
                else {
                    i=BOARD_SIZE;
                    j=ii-BOARD_SIZE+1;
                }
                while(i>0 && j<BOARD_SIZE+1){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case BLACK:
                            ++nNum;
                            ++nColor;
                            break;
                        case WHITE:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i+5][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case BLACK:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连
                        switch(IsFour(BLACK,ept1.x,ept1.y,4)){//对第一个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,4))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,4)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,4))   //且另一点处可成五连
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    --i;
                    ++j;
                }
            }

            break;

        case WHITE:
            //检查横行 '-'
            for(int j=1;j<BOARD_SIZE+1;++j){
                nNum=0;
                nColor=0;
                for(int i=1;i<BOARD_SIZE+1;++i){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case WHITE:
                            ++nNum;
                            ++nColor;
                            break;
                        case BLACK:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i-5][j]){
                            case EMPTY:
                                --nNum;
                                break;
                            case WHITE:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连或是逼禁手
                        switch(IsFour(WHITE,ept1.x,ept1.y,1)){//对第一个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,1)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept2,ept1));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            //检查竖行 '|'
            for(int i=1;i<BOARD_SIZE+1;++i){
                nNum=0;
                nColor=0;
                for(int j=1;j<BOARD_SIZE+1;++j){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case WHITE:
                            ++nNum;
                            ++nColor;
                            break;
                        case BLACK:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case WHITE:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连或是逼禁手
                        switch(IsFour(WHITE,ept1.x,ept1.y,2)){//对第一个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,2)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept2,ept1));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            //检查斜行 '\'
            for(int ii=-BOARD_SIZE+6;ii<BOARD_SIZE-3;++ii){
                nNum=0;
                nColor=0;
                int i,j;
                if(ii<1){
                    i=1;
                    j=2-ii;
                }
                else {
                    i=ii;
                    j=1;
                }
                while(i<BOARD_SIZE+1 && j<BOARD_SIZE+1){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case WHITE:
                            ++nNum;
                            ++nColor;
                            break;
                        case BLACK:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i-5][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case WHITE:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连或是逼禁手
                        switch(IsFour(WHITE,ept1.x,ept1.y,3)){//对第一个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,3)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept2,ept1));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                    }
                    ++i;
                    ++j;
                }
            }

            //检查斜行 '/'
            for(int ii=5;ii<BOARD_SIZE*2-4;++ii){
                nNum=0;
                nColor=0;
                int i,j;
                if(ii<BOARD_SIZE+1){
                    i=ii;
                    j=1;
                }
                else {
                    i=BOARD_SIZE;
                    j=ii-BOARD_SIZE+1;
                }
                while(i>0 && j<BOARD_SIZE+1){
                    //加入当前格
                    switch(matrix[i][j]){
                        case EMPTY:
                            ++nNum;
                            ept1=ept2;
                            ept2=CPoint(i,j);
                            break;
                        case WHITE:
                            ++nNum;
                            ++nColor;
                            break;
                        case BLACK:
                            nNum=0;
                            nColor=0;
                            break;
                        default:
                            break;
                    }
                    //去掉旧格
                    if(nNum>=6){
                        switch(matrix[i+5][j-5]){
                            case EMPTY:
                                --nNum;
                                break;
                            case WHITE:
                                --nNum;
                                --nColor;
                                break;
                            default:
                                break;
                        }
                    }
                    //是否有冲四点
                    if(nNum==5 && nColor==3){
                        //判断是冲四或是四连或是逼禁手
                        switch(IsFour(WHITE,ept1.x,ept1.y,4)){//对第一个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,4)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept2,ept1));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                    }
                    --i;
                    ++j;
                }
            }

            break;
        default:
            break;
    }

    return (int)vecFourRush.size();
}


int CBoard::SearchVCF(const char color){
    //检查color方有无VCF，若有返回1，否则返回0；VCF序列由vcfList链表返回
    int result = 0;
    vcfList.clear();
    vcfTreeVec.clear();
    vcfTNodeQu.clear();

    int x,y;
    //if(HaveFour(color,x,y)){//自己已经有四了，则将成五的点加入vcfList并返回true
    //    vcfList.clear();
    //    vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
    //    return true;
    //}

    vcfTreeNode *root = new vcfTreeNode;
    vcfTreeVec.push_back(root);
    vcfTNodeQu.push_back(root);
    root->pParent=NULL;

    if(!HaveFour(-color,x,y)){//对方无冲四，则初始化该结点
        if(2000 == GetFourRushPoints(color,root->NewRush)){   //自己有胜点
            vcfList.push_back(root->NewRush.front());
            delete root;
            return 1;
        }
        else {  //自己无胜点
            if(root->NewRush.empty()){  //若没有冲四点
                delete root;
                return 0;
            }
            sort(root->NewRush.begin(),root->NewRush.end());
        }
    }

    while(!vcfTNodeQu.empty()){
        if(DoSearchVCF(color)){ //有VCF
            result = 1;
            break;
        }
    }

    //销毁树
    for(vector<vcfTreeNode *>::iterator i=vcfTreeVec.begin();i!=vcfTreeVec.end();++i){
        delete *i;
    }

    return result;
}


int CBoard::DoSearchVCF(const char color){

    vcfTreeNode *pCurrent=vcfTNodeQu.front();
    vcfTNodeQu.pop_front();

    //摆局
    PutTreeLayout(color,pCurrent);

    int x,y;

    switch(color){
        case BLACK: //对黑棋：
            if(HaveFour(WHITE,x,y)){    //白棋有冲四
                if(IsFoul(x,y)){    //挡点是禁手，且只考虑三三和四四禁手(长连不会逃掉)
                    if(IsFoul(x,y)==6)break;
                    //检查是否有可能冲四
                    bool four=false;
                    for(int i=1;i<5;++i){
                        if(IsFour(BLACK,x,y,i)){
                            four=true;
                            break;
                        }
                    }
                    if(four){   //有可能禁手阻挡了冲四，检查是否能通过其他冲四逃避禁手
                        vector<FourRush> rush;
                        GetFourRushPoints(BLACK,rush);
                        //去掉新冲四
                        //sort(rush.begin(),rush.end());
                        //rush.erase(set_difference(rush.begin(),rush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),rush.begin()),rush.end());
                        //vector<FourRush>::iterator itr;
                        for(vector<FourRush>::iterator itr=rush.begin();itr!=rush.end();++itr){
                            bool avoid=false;
                            TryMove(BLACK,itr->rush.x,itr->rush.y);
                            TryMove(WHITE,itr->defense.x,itr->defense.y);
                            if(!IsFoul(x,y))avoid=true;
                            TryMove(EMPTY,itr->rush.x,itr->rush.y);
                            TryMove(EMPTY,itr->defense.x,itr->defense.y);

                            if(avoid){
                                vcfTreeNode *p=pCurrent->pParent;
                                //PutTreeLayout(EMPTY,pCurrent);  //回复原始局面
                                while(p!=NULL){
                                    for(vector<FourRush>::iterator finditr=p->NewRush.begin();finditr!=p->NewRush.end();++finditr){
                                        if((*itr) == (*finditr)){//找到，怎样决定冲四的时机？
                                            //从这个局面到pCurrent的路径上每个局面都尝试这个冲四，能走则加入队列
                                            for(vcfTreeNode *pRushNode=pCurrent;pRushNode!=p;){
                                                //PutTreeLayout(BLACK,pRushNode);
                                                for(vector<FourRush>::iterator tmpitr=pRushNode->RushPath.begin();tmpitr!=pRushNode->RushPath.end();++tmpitr){
                                                    TryMove(EMPTY,tmpitr->rush.x,tmpitr->rush.y);
                                                    TryMove(EMPTY,tmpitr->defense.x,tmpitr->defense.y);
                                                }
                                                pRushNode=pRushNode->pParent;
                                                if(pRushNode->NewRush.empty())continue; //NewRush为空说明此局面白棋有冲四
                                                if(IsFour(BLACK,finditr->rush.x,finditr->rush.y)){//能走，建立新结点加入冲四后的局面

                                                    TryMove(BLACK,finditr->rush.x,finditr->rush.y);
                                                    TryMove(WHITE,finditr->defense.x,finditr->defense.y);

                                                    vcfTreeNode *newnode=new vcfTreeNode;
                                                    vcfTreeVec.push_back(newnode);
                                                    vcfTNodeQu.push_back(newnode);
                                                    newnode->pParent=pRushNode;
                                                    newnode->RushPath.push_back(*finditr);
                                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());

                                                    TryMove(EMPTY,finditr->rush.x,finditr->rush.y);
                                                    TryMove(EMPTY,finditr->defense.x,finditr->defense.y);
                                                }
                                                //PutTreeLayout(EMPTY,pRushNode);
                                            }
                                            PutTreeLayout(BLACK,pCurrent);  //回到当前局面
                                        }
                                    }
                                    p=p->pParent;
                                }
                            }
                        }
                    }
                }
                else {  //挡点不是禁手
                    int x1,y1;
                    switch(IsFour(BLACK,x,y)){
                        case 4:     //冲四。走此点，加入队列
                            TryMove(BLACK,x,y);
                            if(HaveFour(WHITE,x1,y1)){  //白棋仍然有冲四，说明上一步是双四，无解返回0
                                PutTreeLayout(EMPTY,pCurrent);  //回复原始局面
                                return 0;
                            }
                            HaveFour(BLACK,x1,y1);  //寻找黑棋冲四的挡点    |||||||||||to update|||||||||||
                            {
                                //建立新结点
                                vcfTreeNode *newnode=new vcfTreeNode;
                                vcfTreeVec.push_back(newnode);
                                vcfTNodeQu.push_back(newnode);
                                newnode->pParent=pCurrent;
                                newnode->RushPath.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));

                                if(!IsFour(WHITE,x1,y1)){    //白棋不形成新的反冲四，则计算黑棋的新冲四
                                    TryMove(WHITE,x1,y1);
                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());
                                }
                                TryMove(EMPTY,x,y);
                                TryMove(EMPTY,x1,y1);
                            }

                            break;
                        case 40:    //四连，胜点。列出vcf路径并返回
                            vcfTreeNode *p=pCurrent;
                            while(NULL != p->pParent){
                                for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                                    vcfList.push_front(*ritr);
                                }
                                vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
                                p=p->pParent;
                            }
                            //撤局
                            PutTreeLayout(EMPTY,pCurrent);
                            return 1;
                            break;
                    }
                }
            }
            else {  //白棋没四
                vector<FourRush> vecCurRush;
                if(2000 == GetFourRushPoints(BLACK,vecCurRush)){    //黑棋有胜点
                    vcfTreeNode *p=pCurrent;
                    while(NULL != p->pParent){
                        for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                            vcfList.push_front(*ritr);
                        }
                        vcfList.push_back(vecCurRush.front());
                        p=p->pParent;
                    }
                    //撤局
                    PutTreeLayout(EMPTY,pCurrent);
                    return 1;
                }
                else {  //普通情况，白棋无冲四，黑棋也无胜点
                    vector<FourRush> &OldRush(vecCurRush);  //理解方便，创建别名
                    sort(OldRush.begin(),OldRush.end());
                    //去掉与pCurrent->NewRush中重复的元素
                    OldRush.erase(set_difference(OldRush.begin(),OldRush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),OldRush.begin()),OldRush.end());
                    for(int r=1;r<=3;++r){
                        combination comb1,comb2;
                        //if(r > pCurrent->NewRush.size())break;
                        int r1max=min(r,(int)pCurrent->NewRush.size());
                        for(int r1=1;r1<=r1max;++r1){
                            int r2=r-r1;
                            if(r2 > (int)OldRush.size())continue;    //OldRush拿不出足够的元素则continue
                            comb1.init((int)pCurrent->NewRush.size(),r1);
                            while(comb1.next()){
                                comb2.init((int)OldRush.size(),r2);
                                bool first=true;
                                while(comb2.next() || first){//生成NewRush和OldRush的一个组合
                                    //分别为 pCurrent->NewRush[comb1[0]...comb1[r1]] 和 OldRush[comb2[0]...comb2[r2]]
                                    first=false;
                                    vector<FourRush> CombRush;
                                    CombRush.reserve(r);
                                    for(int i=0;i<r1;++i)CombRush.push_back(pCurrent->NewRush[comb1[i]]);
                                    for(int i=0;i<r2;++i)CombRush.push_back(OldRush[comb2[i]]);
                                    //试着摆出当前组合：
                                    int i=0;
                                    for(;i<(int)CombRush.size();++i){
                                        FourRush tmp=CombRush[i];
                                        if(EMPTY != matrix[tmp.rush.x][tmp.rush.y] || EMPTY != matrix[tmp.defense.x][tmp.defense.y])
                                            break;
                                        else {
                                            TryMove(BLACK,tmp.rush.x,tmp.rush.y);
                                            TryMove(WHITE,tmp.defense.x,tmp.defense.y);
                                        }
                                    }
                                    if(i<(int)CombRush.size()){//上个循环未完成，当前组合无效
                                        for(;i>=0;--i){//还原无效组合
                                            FourRush tmp=CombRush[i];
                                            TryMove(EMPTY,tmp.rush.x,tmp.rush.y);
                                            TryMove(EMPTY,tmp.defense.x,tmp.defense.y);
                                        }
                                        continue;//转入下一组合
                                    }
                                    //当前组合有效：
                                    if(HaveFour(WHITE,x,y)){//白棋形成冲四
                                        int x1,y1;
                                        TryMove(BLACK,x,y);
                                        if(HaveFour(WHITE,x1,y1)){//白棋还有冲四(四连或双四)
                                            TryMove(EMPTY,x,y);
                                            //回复当前局面
                                            for(i=0;i<(int)CombRush.size();++i){
                                                TryMove(EMPTY,CombRush[i].rush.x,CombRush[i].rush.y);
                                                TryMove(EMPTY,CombRush[i].defense.x,CombRush[i].defense.y);
                                            }
                                            if(IsFour(BLACK,x,y)){
                                                vector<FourRush>::iterator itr=OldRush.begin();
                                                while(itr!=OldRush.end()){
                                                    if(x == itr->rush.x && y == itr->rush.y)break;
                                                    ++itr;
                                                }
                                                if(itr==OldRush.end()){
                                                    itr=pCurrent->NewRush.begin();
                                                    while(itr!=pCurrent->NewRush.end()){
                                                        if(x == itr->rush.x && y == itr->rush.y)break;
                                                        ++itr;
                                                    }
                                                }
                                                ASSERT(itr != pCurrent->NewRush.end());
                                                TryMove(BLACK,x,y);
                                                TryMove(WHITE,itr->defense.x,itr->defense.y);
                                                vcfTreeNode *newnode=new vcfTreeNode;
                                                vcfTreeVec.push_back(newnode);
                                                vcfTNodeQu.push_back(newnode);
                                                newnode->pParent=pCurrent;
                                                newnode->RushPath.push_back(*itr);
                                                if(!HaveFour(WHITE,x,y)){//白棋无冲四，新建结点计算新冲四后加入队列
                                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());
                                                }
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                            }
                                            if(IsFour(BLACK,x1,y1)){
                                                vector<FourRush>::iterator itr=OldRush.begin();
                                                while(itr!=OldRush.end()){
                                                    if(x1 == itr->rush.x && y1 == itr->rush.y)break;
                                                    ++itr;
                                                }
                                                if(itr==OldRush.end()){
                                                    itr=pCurrent->NewRush.begin();
                                                    while(itr!=pCurrent->NewRush.end()){
                                                        if(x1 == itr->rush.x && y1 == itr->rush.y)break;
                                                        ++itr;
                                                    }
                                                }
                                                ASSERT(itr != pCurrent->NewRush.end());
                                                TryMove(BLACK,x1,y1);
                                                TryMove(WHITE,itr->defense.x,itr->defense.y);
                                                vcfTreeNode *newnode=new vcfTreeNode;
                                                vcfTreeVec.push_back(newnode);
                                                vcfTNodeQu.push_back(newnode);
                                                newnode->pParent=pCurrent;
                                                newnode->RushPath.push_back(*itr);
                                                if(!HaveFour(WHITE,x,y)){//白棋无冲四，新建结点计算新冲四后加入队列
                                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());
                                                }
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                            }
                                        }
                                        else {  //白棋只有这一个冲四，则计算RushPath顺序，新建结点加入队列，不用计算NewRush
                                            //检测是否当前CombRush的所有冲四共同构成这个白的反冲四？若否，则不加入队列
                                            TryMove(EMPTY,x,y);
                                            //依次去掉CombRush中的每个冲四，看(x,y)是否仍是白的冲四点
                                            vector<FourRush>::iterator itr;
                                            for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                if(IsFive(WHITE,x,y))break;
                                                TryMove(BLACK,itr->rush.x,itr->rush.y);
                                                TryMove(WHITE,itr->defense.x,itr->defense.y);
                                            }
                                            if(itr!=CombRush.end()){//此时不是CombRush中的所有冲四共同构成白的反冲四，则不加入队列
                                                 //回复当前局面
                                                for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                            }
                                            else {
                                                //回复当前局面
                                                for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                                if(CheckRushPath(BLACK,CombRush)){  //找到RushPath的顺序
                                                    vcfTreeNode *newnode=new vcfTreeNode;
                                                    vcfTreeVec.push_back(newnode);
                                                    vcfTNodeQu.push_back(newnode);
                                                    newnode->pParent=pCurrent;
                                                    newnode->RushPath=CombRush;
                                                }
                                            }
                                        }
                                        continue;  //转到下一组合
                                    }
                                    else {  //此组合白棋不形成冲四
                                        vector<FourRush> newrush;
                                        if(2000 == GetFourRushPoints(BLACK,newrush)){   //黑棋有胜点
                                            //回复当前局面
                                            for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                            }
                                            if(CheckRushPath(BLACK,CombRush)){  //找到RushPath的顺序
                                                vcfTreeNode *p=pCurrent;
                                                while(NULL != p->pParent){
                                                    for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                                                        vcfList.push_front(*ritr);
                                                    }
                                                    vcfList.push_back(vecCurRush.front());
                                                    p=p->pParent;
                                                }
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    vcfList.push_back(*itr);
                                                }
                                                //撤局
                                                PutTreeLayout(EMPTY,pCurrent);
                                                return 1;
                                            }
                                        }
                                        else {  //黑棋无胜点，判断有无新冲四
                                            sort(newrush.begin(),newrush.end());
                                            newrush.erase(set_difference(newrush.begin(),newrush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),newrush.begin()),newrush.end());
                                            newrush.erase(set_difference(newrush.begin(),newrush.end(),OldRush.begin(),OldRush.end(),newrush.begin()),newrush.end());

                                            if(!newrush.empty()){   //有新冲四
                                                //判断是否在newrush中存在一个冲四是由CombRush中所有冲四共同形成的
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end()/*&&alleffective*/;++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                    //vector<FourRush>::iterator nitr;
                                                    bool havedelete;
                                                    do{
                                                        havedelete=false;
                                                        for(vector<FourRush>::iterator nitr=newrush.begin();nitr!=newrush.end();++nitr){
                                                            if(IsFour(BLACK,nitr->rush.x,nitr->rush.y)){
                                                                newrush.erase(nitr);
                                                                havedelete=true;
                                                                break;
                                                            }
                                                        }
                                                    }while(!newrush.empty() && havedelete);
                                                    TryMove(BLACK,itr->rush.x,itr->rush.y);
                                                    TryMove(WHITE,itr->defense.x,itr->defense.y);
                                                }
                                                ////判断newrush中每个冲四都是由CombRush中所有冲四共同形成的
                                                //bool alleffective=true;
                                                //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end()&&alleffective;++itr){
                                                //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                //    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                //    vector<FourRush>::iterator nitr;
                                                //    for(nitr=newrush.begin();nitr!=newrush.end();++nitr){
                                                //        if(IsFour(BLACK,nitr->rush.x,nitr->rush.y))break;
                                                //    }
                                                //    if(nitr!=newrush.end()){
                                                //        alleffective=false;
                                                //    }
                                                //    TryMove(BLACK,itr->rush.x,itr->rush.y);
                                                //    TryMove(WHITE,itr->defense.x,itr->defense.y);
                                                //}
                                                //回复当前局面
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                                if(!newrush.empty() && CheckRushPath(BLACK,CombRush)){  //找到RushPath的顺序，则新建结点
                                                    vcfTreeNode *newnode=new vcfTreeNode;
                                                    vcfTreeVec.push_back(newnode);
                                                    vcfTNodeQu.push_back(newnode);
                                                    newnode->pParent=pCurrent;
                                                    newnode->RushPath=CombRush;
                                                    newnode->NewRush=newrush;
                                                }
                                            }
                                            else {
                                                //回复当前局面
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                            }
                                        }
                                        //bool win=false;
                                        //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end() && !win;++itr){//对组合中的每个冲四
                                        //    //去掉冲四的点，看是否成活三
                                        //    //x=itr->rush.x;
                                        //    //y=itr->rush.y;
                                        //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                        //    if(IsOpenThree(BLACK,itr->rush.x,itr->rush.y)){ //若形成活三
                                        //        win=true;
                                        //        break;
                                        //    }
                                        //    TryMove(BLACK,itr->rush.x,itr->rush.y);
                                        //}
                                        ////回复当前局面
                                        //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                        //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                        //    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                        //}
                                        //if(win){
                                        //    if(CheckRushPath(BLACK,CombRush)){  //找到RushPath的顺序
                                        //        win=true;
                                        //        vcfTreeNode *p=pCurrent;
                                        //        while(NULL != p->pParent){
                                        //            for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                                        //                vcfList.push_front(*ritr);
                                        //            }
                                        //            vcfList.push_back(vecCurRush.front());
                                        //            p=p->pParent;
                                        //        }
                                        //        for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                        //            vcfList.push_back(*itr);
                                        //        }
                                        //        //撤局
                                        //        PutTreeLayout(EMPTY,pCurrent);
                                        //        return 1;
                                        //    }
                                        //}
                                        //else {  //摆成当前组合，并判断有无新冲四
                                        //    //=================================================
                                        //    for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                        //        TryMove(BLACK,itr->rush.x,itr->rush.y);
                                        //        TryMove(WHITE,itr->defense.x,itr->defense.y);
                                        //    }
                                        //    vector<FourRush> newrush;
                                        //}
                                    }

                                    //回复当前局面
                                    //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                    //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                    //    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                    //}
                                }
                            }
                        }
                    }
                }
            }

            break;

        case WHITE: //对白棋

            break;

        default:
            break;
    }
/*    if(HaveFour(color,x,y)){//自己有四，输出VCF序列并返回
        //(实际上这种情况只有白棋有可能。因为这一步有四说明上一步的冲四其实是双四，对黑棋来说是禁手)
        //==================================================================

        //vector<FourRush> vcfVec;
        //for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
        //    for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
        //        vcfVec.push_back(*itr);
        //}
        //PutTreeLayout(EMPTY,pCurrent);//回复到原始局面
        //vcfList.clear();
        //if(CheckVcfVec(color,vcfVec)){  //找到有效VCF路径
        //    return 1;
        //}
        //else {//未找到，回复当前局面，继续下面的计算
        //    PutTreeLayout(color,pCurrent);
        //}
    }

    //计算旧冲四
    vector<FourRush> OldRush;
    int n;
    if(0 < (n=GetFourRushPoints(color,OldRush))){   //若自己有胜点
        FourRush winpoint(CPoint(0,0),CPoint(0,0));
        if(HaveFour(-color,x,y)){  //若对方有四，检测挡点是否正是胜点
            for(vector<FourRush>::reverse_iterator ritr=OldRush.rbegin();ritr!=OldRush.rbegin()+n;++ritr){
                if(ritr->rush.x == x && ritr->rush.y == y){
                    winpoint=*ritr;
                    break;
                }
            }
        }
        else {  //若对方没有冲四
            winpoint=OldRush.back();
        }
        if(!(FourRush(CPoint(0,0),CPoint(0,0)) == winpoint)){//确实是胜点
            vector<FourRush> vcfVec;
            for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
                for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
                    vcfVec.push_back(*itr);
            }
            vcfVec.push_back(winpoint);
            PutTreeLayout(EMPTY,pCurrent);//回复到原始局面
            vcfList.clear();
            if(CheckVcfVec(color,vcfVec)){  //找到有效VCF路径
                return 1;
            }
            else {//未找到，回复当前局面，继续下面的计算
                PutTreeLayout(color,pCurrent);
            }
        }
    }
    int rmax=static_cast<int>(OldRush.size()/2);
    //OldRush中去除pCurrent->NewRush中的冲四
    sort(OldRush.begin(),OldRush.end());
    OldRush.erase(set_difference(OldRush.begin(),OldRush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),OldRush.begin()),OldRush.end());

    for(int r=1;r<=rmax;++r){
        combination comb1,comb2;
        int r1max=min(r,static_cast<int>(pCurrent->NewRush.size()/2));
        for(int r1=1;r1<=r1max;++r1){
            comb1.init(static_cast<int>(pCurrent->NewRush.size()),r1);
            int r2=r-r1;
            if(r2<0)r2=0;
            else if(r2+r2 > (int)OldRush.size()){    //OldRush中的元素不够拿来组合，则continue
                continue;
            }
            while(comb1.next()){
                if(!comb2.init(static_cast<int>(OldRush.size()),r2))continue;
                bool first=true;
                while(comb2.next() || first){    //生成NewRush 和 OldRush 的一个组合
                    //分别为 pCurrent->NewRush[comb1[0]...comb1[r1]] 和 OldRush[comb2[0]...comb2[r2]]
                    first=false;
                    vector<FourRush> CombRush;
                    CombRush.reserve(r);
                    for(int ii=0;ii<r1;++ii)CombRush.push_back(pCurrent->NewRush[comb1[ii]]);
                    for(int ii=0;ii<r2;++ii)CombRush.push_back(OldRush[comb2[ii]]);
                    //试着摆出当前组合：
                    int i=0;
                    for(;i<(int)CombRush.size();++i){
                        FourRush tmp=CombRush[i];
                        if(EMPTY != matrix[tmp.rush.x][tmp.rush.y] || EMPTY != matrix[tmp.defense.x][tmp.defense.y]){
                            break;//当前组合无效
                        }
                        else {
                            TryMove(color,tmp.rush.x,tmp.rush.y);
                            TryMove(-color,tmp.defense.x,tmp.defense.y);
                        }
                    }
                    if(i<(int)CombRush.size()){//上个循环未完成，当前组合无效
                        for(;i>=0;--i){//还原无效组合
                            FourRush tmp=CombRush[i];
                            TryMove(EMPTY,tmp.rush.x,tmp.rush.y);
                            TryMove(EMPTY,tmp.defense.x,tmp.defense.y);
                        }
                        continue;//转入下一组合
                    }
                    //当前组合有效：
                    bool win=false;
                    if(HaveFour(color,x,y)){//自己有四
                        win=true;
                    }
                    else if(!HaveFour(-color,x,y)){ //自己没四，对方也没四
                        for(i=0;i<(int)CombRush.size() && !win;++i){ //对组合中的每个冲四
                            //去掉冲四的点，看是否成活三，并且不形成禁手
                            x=CombRush[i].rush.x;
                            y=CombRush[i].rush.y;
                            int x1=CombRush[i].defense.x,y1=CombRush[i].defense.y;
                            TryMove(EMPTY,x,y);
                            if(IsOpenThree(color,x,y)){ //若形成活三
                                win=true;
                            }
                            else if(WHITE == color){    //若是白棋，看能否逼禁手
                                TryMove(WHITE,x,y);
                                TryMove(EMPTY,x1,y1);
                                if(IsFoul(x1,y1)){
                                    win=true;
                                }
                            }
                            TryMove(color,x,y);
                            TryMove(-color,x1,y1);
                        }
                    }
                    else {//对方有四，自己没四
                    }
                    if(win){//当前组合能赢
                        vector<FourRush> vcfVec;
                        for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
                            for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
                                vcfVec.push_back(*itr);
                        }
                        for(i=0;i<(int)CombRush.size();++i){
                            vcfVec.push_back(CombRush[i]);
                        }
                        //首先回到当前局面
                        for(i=0;i<(int)CombRush.size();++i){//恢复当前局面
                            TryMove(EMPTY,CombRush[i].rush.x,CombRush[i].rush.y);
                            TryMove(EMPTY,CombRush[i].defense.x,CombRush[i].defense.y);
                        }
                        PutTreeLayout(EMPTY,pCurrent);//然后回复到原始局面
                        vcfList.clear();
                        if(CheckVcfVec(color,vcfVec)){  //找到有效VCF路径
                            return 1;
                            //==========
                        }
                        else {//未找到，则说明当前组合无法形成，为假组合
                            PutTreeLayout(color,pCurrent);//恢复当前局面
                            continue; //转到下一组合
                        }
                    }
                    else {  //当前组合不能赢，检查有无新冲四
                        vector<FourRush> newrush;
                        GetFourRushPoints(color,newrush);
                        sort(newrush.begin(),newrush.end());
                        //分别去除 OldRush 和 pCurrent->NewRush 中的元素
                        newrush.erase(set_difference(newrush.begin(),newrush.end(),OldRush.begin(),OldRush.end(),newrush.begin()),newrush.end());
                        newrush.erase(set_difference(newrush.begin(),newrush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),newrush.begin()),newrush.end());
                        if(!newrush.empty()){//有新冲四
                            vcfTreeNode *p=new vcfTreeNode;
                            vcfTreeVec.push_back(p);
                            vcfTNodeQu.push_back(p);
                            p->NewRush=newrush;
                            p->pParent=pCurrent;
                            p->RushPath=CombRush;
                        }
                    }
                    //回复当前局面
                    for(i=0;i<(int)CombRush.size();++i){
                        TryMove(EMPTY,CombRush[i].rush.x,CombRush[i].rush.y);
                        TryMove(EMPTY,CombRush[i].defense.x,CombRush[i].defense.y);
                    }
                }
            }
        }
    }*/

    //撤局
    PutTreeLayout(EMPTY,pCurrent);
    return 0;
}

void CBoard::PutTreeLayout(const char color, vcfTreeNode *pCurrent){
    for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
        for(vector<FourRush>::iterator i=p->RushPath.begin();i!=p->RushPath.end();++i){
            TryMove(color,i->rush.x,i->rush.y);
            TryMove(-color,i->defense.x,i->defense.y);
        }
    }
}

bool CBoard::CheckRushPath(const char color, vector<FourRush> &RushPath){
    bool result=false;

    arrange RushOrder((int)RushPath.size());
    while(RushOrder.next() && !result){
        int i;
        for(i=0;i<(int)RushPath.size();++i){// RushPath[RushOrder[0]] -> RushPath[RushOrder[1]] -> ...
            int x,y;
            if(HaveFour(-color,x,y)){   //对方有冲四
                if( x == RushPath[RushOrder[i]].rush.x && y == RushPath[RushOrder[i]].rush.y && IsFour(color,x,y)){
                    TryMove(color,x,y);
                    TryMove(-color,RushPath[RushOrder[i]].defense.x, RushPath[RushOrder[i]].defense.y);
                }
                else break;
            }
            else {  //对方没冲四
                if(IsFour(color,RushPath[RushOrder[i]].rush.x,RushPath[RushOrder[i]].rush.y)){
                    TryMove(color,RushPath[RushOrder[i]].rush.x,RushPath[RushOrder[i]].rush.y);
                    TryMove(-color,RushPath[RushOrder[i]].defense.x, RushPath[RushOrder[i]].defense.y);
                }
                else break;
            }
        }
        if(i == (int)RushPath.size()){
            result=true;
        }
        for(--i;i>=0;--i){
            TryMove(EMPTY,RushPath[RushOrder[i]].rush.x,RushPath[RushOrder[i]].rush.y);
            TryMove(EMPTY,RushPath[RushOrder[i]].defense.x, RushPath[RushOrder[i]].defense.y);
        }
    }

    return result;
}

//bool CBoard::CheckVcfVec(const char color, vector<FourRush> &vcfVec){
//    //在vcfVec中寻找一条有效的VCF路径，深度优先算法，找到返回true，否则返回false(考虑禁手)
//    //进入此函数前清空vcfList
//    int x,y;
//    if(HaveFour(color,x,y)){
//        vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
//        return true;
//    }
//    if(HaveFour(-color,x,y)){//对方有冲四
//        if(color == BLACK && IsFoul(x,y)){//自己被逼禁手
//            return false;
//        }
//        vector<FourRush>::iterator itr=vcfVec.begin();
//        while(itr!=vcfVec.end()){
//            if(x == itr->rush.x && y == itr->rush.y){   //挡点在vcfVec中，找到
//                if(IsFour(color,x,y)){
//                    TryMove(color,x,y);
//                    int x1,y1,x2,y2;
//                    HaveFour(color,x1,y1);  //寻找挡点
//                    if(color == WHITE && IsFoul(x1,y1)){    //逼对方禁手
//                        vcfList.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));
//                        TryMove(EMPTY,x,y);
//                        return true;
//                    }
//                    TryMove(-color,x1,y1);
//                    if(HaveFour(color,x2,y2)){//这步冲四是双四
//                        vcfList.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));
//                        TryMove(EMPTY,x,y);
//                        TryMove(EMPTY,x1,y1);
//                        return true;
//                    }
//                    if(x1 != itr->defense.x || y1 != itr->defense.y){   //若挡点与vcfVec中不一致则返回false
//                        TryMove(EMPTY,x,y);
//                        TryMove(EMPTY,x1,y1);
//                        return false;
//                    }
//                    vcfList.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));
//                    bool result=CheckVcfVec(color,vcfVec);
//                    if(!result)vcfList.pop_back();
//                    TryMove(EMPTY,x,y);
//                    TryMove(EMPTY,x1,y1);
//                    return result;
//                }
//                else return false;  //挡对方冲四的点自己不形成冲四，则返回false
//            }
//            ++itr;
//        }
//        return false;   //挡点不在vcfVec中
//    }
//    else {  //对方无冲四
//        vector<FourRush> Rush;
//        if(0 < GetFourRushPoints(color,Rush)){   //当前有胜点
//            vcfList.push_back(Rush.back());
//            return true;
//        }
//        Rush.clear();
//        for(vector<FourRush>::iterator itr=vcfVec.begin();itr!=vcfVec.end();++itr){
//            if(IsFour(color,itr->rush.x,itr->rush.y))Rush.push_back(*itr);
//        }
//        for(vector<FourRush>::iterator itr=Rush.begin();itr!=Rush.end();++itr){//对当前局面的每个冲四点
//            TryMove(color,itr->rush.x,itr->rush.y);
//            int x1,y1,x2,y2;
//            HaveFour(color,x1,y1);  //寻找挡点
//            TryMove(-color,x1,y1);
//            if(HaveFour(color,x2,y2)){//这步冲四是双四
//                vcfList.push_back(FourRush(CPoint(itr->rush.x,itr->rush.y),CPoint(x1,y1)));
//                TryMove(EMPTY,itr->rush.x,itr->rush.y);
//                TryMove(EMPTY,x1,y1);
//                return true;
//            }
//            if(x1 != itr->defense.x || y1 != itr->defense.y){   //若挡点与vcfVec中不一致转到下一点
//                TryMove(EMPTY,itr->rush.x,itr->rush.y);
//                TryMove(EMPTY,x1,y1);
//                continue;
//            }
//            vcfList.push_back(FourRush(CPoint(itr->rush.x,itr->rush.y),CPoint(x1,y1)));
//            bool result=CheckVcfVec(color,vcfVec);
//            TryMove(EMPTY,itr->rush.x,itr->rush.y);
//            TryMove(EMPTY,x1,y1);
//            if(result)return true;
//            vcfList.pop_back();
//        }
//        return false;
//    }
//    return false;
//}

//bool CBoard::FindIcfEnd(const char color, list<FourRush> &icfList){
//    //在保持color方先手的情况下寻找对冲四的终点，若找到返回true，对冲序列由icfList返回；否则返回false(不考虑禁手)
//    int x,y;
//    if(HaveFour(color,x,y))return true;
//    if(!HaveFour(-color,x,y)){//对方没四，则返回true
//        return true;
//    }
//    bool haverush=false;
//    for(int i=1;i<5;++i){
//        if(IsFour(color,x,y,i)){
//            haverush=true;
//            break;
//        }
//    }
//}

//void CBoard::EmptyLayout(const vcfTreeNode *pCurrent){
//    for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
//        for(list<FourRush>::iterator i=p->RushPath.begin();i!=p->RushPath.end();++i){
//            TryMove(EMPTY,(*i).rush.x,(*i).rush.y);
//            TryMove(EMPTY,(*i).defense.x,(*i).defense.y);
//        }
//    }
//}

//void CBoard::DoCleanVCF(const char color){
//    if(vcfList.empty())return;
//    bool doclean;
//    do{
//        doclean=false;
//        list<FourRush>::iterator i=vcfList.begin();
//        while(++list<FourRush>::iterator(i)!=vcfList.end()){
//            list<FourRush>::iterator pos=i;
//            FourRush tmp=*pos;
//            ++i;
//            vcfList.erase(pos);
//            if(CheckVcfList(color)){
//                doclean = true;
//            }
//            else {
//                vcfList.insert(i,tmp);
//            }
//        }
//    }while(doclean);
//}
//
//bool CBoard::CheckVcfList(const char color){
//    int status;
//    if(vcfList.empty())return false;
//    list<FourRush>::iterator i;
//    bool makefoul;
//    switch(color){
//        case BLACK:
//            i=vcfList.begin();
//            do{
//                int x,y;
//                status=IsFour(BLACK,i->rush.x,i->rush.y);
//                if(!status)break;
//                TryMove(BLACK,i->rush.x,i->rush.y);
//                if(HaveFour(WHITE,x,y)){
//                    status=0;
//                    break;
//                }
//                TryMove(WHITE,i->defense.x,i->defense.y);
//            }while((++i)!=vcfList.end());
//            for(i=vcfList.begin();i!=vcfList.end();++i){
//                TryMove(EMPTY,i->rush.x,i->rush.y);
//                TryMove(EMPTY,i->defense.x,i->defense.y);
//            }
//            if(40 == status)return true;
//            else return false;
//
//            break;
//        case WHITE:
//            makefoul=false;
//            i=vcfList.begin();
//            do{
//                int x,y;
//                status=IsFour(WHITE,i->rush.x,i->rush.y);
//                if(!status)break;
//                TryMove(WHITE,i->rush.x,i->rush.y);
//                if(HaveFour(BLACK,x,y)){
//                    status=0;
//                    break;
//                }
//                if(IsFoul(i->defense.x,i->defense.y)){
//                    makefoul=true;
//                    break;
//                }
//                TryMove(BLACK,i->defense.x,i->defense.y);
//            }while((++i)!=vcfList.end());
//            for(i=vcfList.begin();i!=vcfList.end();++i){
//                TryMove(EMPTY,i->rush.x,i->rush.y);
//                TryMove(EMPTY,i->defense.x,i->defense.y);
//            }
//            if(makefoul || 40 == status)return true;
//            else return false;
//
//            break;
//        default:
//            break;
//    }
//    return false;
//}

