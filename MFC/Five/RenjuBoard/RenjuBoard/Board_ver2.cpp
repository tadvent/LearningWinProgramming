#include "StdAfx.h"
#include "Board.h"

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
    //冲四返回4，活四连返回40，否则返回0

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
                if(40 == IsFour(color,i,y,1))if(!IsFoul(i,y)){
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
                if(40 == IsFour(color,i,y,1))if(!IsFoul(i,y)){
                    result = 1;
                }
            }
            break;
        case 2: //竖向 '|'
            j=y;
            while(color == matrix[x][--j]);
            if(EMPTY == matrix[x][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,x,j,2))if(!IsFoul(x,j)){
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
                if(40 == IsFour(color,x,j,2))if(!IsFoul(x,j)){
                    result = 1;
                }
            }
            break;
        case 3: //斜向 '\'
            i=x;
            j=y;
            while(color == matrix[--i][--j]);
            if(EMPTY == matrix[i][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,3))if(!IsFoul(i,j)){
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
                if(40 == IsFour(color,i,j,3))if(!IsFoul(i,j)){
                    result = 1;
                }
            }
            break;
        case 4: //斜向 '\'
            i=x;
            j=y;
            while(color == matrix[--i][++j]);
            if(EMPTY == matrix[i][j]){  //此方向上有空格，进一步判断
                if(40 == IsFour(color,i,j,4))if(!IsFoul(i,j)){
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
                if(40 == IsFour(color,i,j,4))if(!IsFoul(i,j)){
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

    switch(color){
        case BLACK: //黑棋
            //检查横行 '-'
            for(int j=1;j<BOARD_SIZE+1;++j){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(int i=1;i<BOARD_SIZE+2;++i){
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
            for(int i=1;i<BOARD_SIZE+1;++i){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(int j=1;j<BOARD_SIZE+2;++j){
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
                int i,j;
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
                int i,j;
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
            for(int j=1;j<BOARD_SIZE+1;++j){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(int i=1;i<BOARD_SIZE+2;++i){
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
            for(int i=1;i<BOARD_SIZE+1;++i){
                leftnum=0;
                rightnum=0;
                validempty=false;
                for(int j=1;j<BOARD_SIZE+2;++j){
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
                int i,j;
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
                int i,j;
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

//int CBoard::GetFourRushPoints(const char color, vector<CPoint> &vecFourRush, vector<CPoint> &vecDefense){
int CBoard::GetFourRushPoints(const char color, list<FourRush> &lstFourRush){
    //计算color颜色的所有冲四点，由向量返回，函数返回值为冲四点个数
    //若有活四连或逼对方禁手则向量仅返回此点，函数返回值为2000
    lstFourRush.clear();
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,1)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept1);
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,2)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept1);
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,3)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept1);
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept1.x,ept1.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,4)){//对第二个空格判断
                            case 4: //冲四
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://四连
                                if(!IsFoul(ept2.x,ept2.y)){//不是禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.clear();
                                    //vecDefense.push_back(ept1);
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,1)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept2,ept1));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept1);
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,2)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept2,ept1));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept1);
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,3)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept2,ept1));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept1);
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,4)){//对第二个空格判断
                            case 4: //冲四
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//逼禁手
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //不是逼禁手
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://四连
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept2,ept1));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept1);
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

    return (int)lstFourRush.size();
}

int CBoard::SearchVCF(const char color/*, list<FourRush> &vcfList*/){
    //检查color方有无VCF，若有返回1，否则返回0；VCF序列由vcfList链表返回

    vcfStateQu.clear();
    list<FourRush> TryList;
    vcfStateQu.push_back(TryList);
    while(!vcfStateQu.empty()){
        if(DoSearchVCF(color/*,vcfList*/)){ //有VCF
            return 1;
        }
    }
    return 0;
}

int CBoard::DoSearchVCF(const char color/*, list<FourRush> &vcfList*/){
    //if(vcfStateQu.empty())return 0;
    int result=0;
    list<FourRush> TryList=vcfStateQu.front();
    vcfStateQu.pop_front();

    //摆局
    for(list<FourRush>::iterator i=TryList.begin();i!=TryList.end();++i){
        TryMove(color,(i->rush).x,(i->rush).y);
        TryMove(-color,(i->defense).x,(i->defense).y);
    }

    int x,y,status;
    if(HaveFour(-color,x,y)){   //对方有四
        status=IsFour(color,x,y);
        if(4 == status){    //己方冲四
            int defx,defy;
            TryMove(color,x,y);

            HaveFour(color,defx,defy);
            if(color == WHITE && IsFoul(defx,defy)){    //己方是白棋并且这步冲四逼黑棋禁手
                vcfList=TryList;
                vcfList.push_back(FourRush(CPoint(x,y),CPoint(defx,defy)));
                result = 1;
            }
            else {
                TryList.push_back(FourRush(CPoint(x,y),CPoint(defx,defy)));
                vcfStateQu.push_back(TryList);
                TryList.pop_back();
            }

            TryMove(EMPTY,x,y);
        }
        else if(40 == status){  //己方四连
            int defx,defy;
            TryMove(color,x,y);

            HaveFour(color,defx,defy);
            vcfList=TryList;
            vcfList.push_back(FourRush(CPoint(x,y),CPoint(defx,defy)));
            result = 1;

            TryMove(EMPTY,x,y);
        }
    }
    else {  //对方没四
        list<FourRush> rushlist;
        if(2000 == GetFourRushPoints(color,rushlist)){  //有胜点
            vcfList=TryList;
            vcfList.push_back(rushlist.front());
            result = 1;
        }
        else {  //无胜点
            for(list<FourRush>::iterator i=rushlist.begin();i!=rushlist.end();++i){
                TryList.push_back(*i);
                vcfStateQu.push_back(TryList);
                TryList.pop_back();
            }
        }
    }

    //撤局
    for(list<FourRush>::iterator i=TryList.begin();i!=TryList.end();++i){
        TryMove(EMPTY,(i->rush).x,(i->rush).y);
        TryMove(EMPTY,(i->defense).x,(i->defense).y);
    }
    return result;
}