#include "StdAfx.h"
#include "Board.h"
#include<combination>
#include<algorithm>
#include<arrange>

//////////////////////////////////////////////////////////////////////////////////

CBoard::CBoard(void){
    //��ʼ������
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        matrix[i][j]=EMPTY;
    }
    //��ʼ���߽�
    for(int i=0;i<BOARD_SIZE+2;++i){
        matrix[i][0]='$';               //�ϱ߽�
        matrix[i][BOARD_SIZE+1]='$';    //�±߽�
        matrix[0][i]='$';               //��߽�
        matrix[BOARD_SIZE+1][i]='$';    //�ұ߽�
    }
    MoveList.clear();
    vcfList.clear();
    nCurrent=0;
}

CBoard::~CBoard(void){
}

void CBoard::Clear(void){//��ʼ������
    for(int i=1;i<BOARD_SIZE+1;++i)for(int j=1;j<BOARD_SIZE+1;++j){
        matrix[i][j]=EMPTY;
    }
    MoveList.clear();
    nCurrent=0;
}

//////////////////////////////////////////////////////////////////////////////////

int CBoard::DoMove(/*char color,*/ const CPoint &point){   //�ƶ�һ������Ч���귵��-1����������0
    if(IsOutBoard(point))return -1;
    if(EMPTY!=matrix[point.x][point.y])return -1;
    if(nCurrent < MoveList.size()){ //��ǰ����С��MoveList�ļ�¼�����Ƴ�MoveList�����¼
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
//�����ж����ֺ���

int CBoard::IsFive(const char color, const int x, const int y, const int nDir){
    //��ĳ�����ϳ���������5�����峤������6�����򷵻�0

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
    //��������5�����峤������6�����򷵻�0

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
    //��ĳ�����ϳ��ķ���4����������40��˫�ķ���44�����򷵻�0

    if(EMPTY!=matrix[x][y]) return 0;
    int line=1,i,j,result=0;
    bool havefour=false;
    TryMove(color,x,y);

    switch(nDir){
        case 1: //���� '-'
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
                if(5 == IsFive(color,i,y,1)){   //����ǳ���
                    if(havefour){   //����һ��Ҳ�г���
                        if(line ==4){   //��������
                            result=40;
                        }
                        else {  //����������
                            result=44;
                        }
                    }
                    else {  //����һ��û�г���
                        result=4;
                    }
                }
                else {  //��߲��ǳ���
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //��߲��ǳ���
                if(havefour){
                    result=4;
                }
            }
            break;
        case 2: //���� '|'
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
                if(5 == IsFive(color,x,j,2)){   //����ǳ���
                    if(havefour){   //����һ��Ҳ�г���
                        if(line ==4){   //��������
                            result=40;
                        }
                        else {  //����������
                            result=44;
                        }
                    }
                    else {  //����һ��û�г���
                        result=4;
                    }
                }
                else {  //��߲��ǳ���
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //��߲��ǳ���
                if(havefour){
                    result=4;
                }
            }
            break;
        case 3: //б�� '\'
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
                if(5 == IsFive(color,i,j,3)){   //����ǳ���
                    if(havefour){   //����һ��Ҳ�г���
                        if(line ==4){   //��������
                            result=40;
                        }
                        else {  //����������
                            result=44;
                        }
                    }
                    else {  //����һ��û�г���
                        result=4;
                    }
                }
                else {  //��߲��ǳ���
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //��߲��ǳ���
                if(havefour){
                    result=4;
                }
            }
            break;
        case 4: //б�� '/'
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
                if(5 == IsFive(color,i,j,4)){   //����ǳ���
                    if(havefour){   //����һ��Ҳ�г���
                        if(line ==4){   //��������
                            result=40;
                        }
                        else {  //����������
                            result=44;
                        }
                    }
                    else {  //����һ��û�г���
                        result=4;
                    }
                }
                else {  //��߲��ǳ���
                    if(havefour){
                        result=4;
                    }
                }
            }
            else {  //��߲��ǳ���
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
    //���ķ���4������������40�����򷵻�0���ѿ��ǽ���

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
    //˫�ķ���1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų������ͳ��������

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
    //��ĳ�����ϻ�������1�����򷵻�0

    if(EMPTY!=matrix[x][y]) return 0;
    int line=1,i,j,result=0;

    TryMove(color,x,y);

    switch(nDir){
        case 1: //���� '-'
            i=x;
            while(color == matrix[--i][y]);
            if(EMPTY == matrix[i][y]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,y,1))if(color == WHITE || !IsFoul(i,y)){
                    result = 1;
                    break;
                }
            }
            else {  //һ��������û�пո񣬲������ǻ���
                //result = -1;
                break;
            }
            i=x;
            while(color == matrix[++i][y]);
            if(EMPTY == matrix[i][y]){  //��һ�������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,y,1))if(color == WHITE || !IsFoul(i,y)){
                    result = 1;
                }
            }
            break;
        case 2: //���� '|'
            j=y;
            while(color == matrix[x][--j]);
            if(EMPTY == matrix[x][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,x,j,2))if(color == WHITE || !IsFoul(x,j)){
                    result = 1;
                    break;
                }
            }
            else {  //һ��������û�пո񣬲������ǻ���
                //result = -1;
                break;
            }
            j=y;
            while(color == matrix[x][++j]);
            if(EMPTY == matrix[x][j]){  //��һ�������пո񣬽�һ���ж�
                if(40 == IsFour(color,x,j,2))if(color == WHITE || !IsFoul(x,j)){
                    result = 1;
                }
            }
            break;
        case 3: //б�� '\'
            i=x;
            j=y;
            while(color == matrix[--i][--j]);
            if(EMPTY == matrix[i][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,j,3))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                    break;
                }
            }
            else {  //һ��������û�пո񣬲������ǻ���
                //result = -1;
                break;
            }
            i=x;
            j=y;
            while(color == matrix[++i][++j]);
            if(EMPTY == matrix[i][j]){  //��һ�������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,j,3))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                }
            }
            break;
        case 4: //б�� '\'
            i=x;
            j=y;
            while(color == matrix[--i][++j]);
            if(EMPTY == matrix[i][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,j,4))if(color == WHITE || !IsFoul(i,j)){
                    result = 1;
                    break;
                }
            }
            else {  //һ��������û�пո񣬲������ǻ���
                //result = -1;
                break;
            }
            i=x;
            j=y;
            while(color == matrix[++i][--j]);
            if(EMPTY == matrix[i][j]){  //��һ�������пո񣬽�һ���ж�
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
    //��������1�����򷵻�0

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
    //˫������1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų�������������˫�ĵ����

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
    //�������ַ���6��˫�ķ���44��˫������33�����򷵻�0 (�ú������Ժ����ж�)

    if(EMPTY != matrix[x][y]) return 0;

    int status=IsFive(BLACK,x,y);
    if(5 == status) return 0;
    else if(6 == status) return 6;

    if(IsDoubleFour(x,y))return 44;

    if(IsDoubleThree(x,y))return 33;

    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
//�����㷨���ֺ���

int CBoard::CheckMove(const int x, const int y){
    //��������5���������ַ���6��˫�ķ���44��˫������33�����򷵻�0

    if(EMPTY != matrix[x][y]) return 0;
    int status;
    switch(nCurrent%2){
        case 0: //�˲��ú���
            if(5 == IsFive(BLACK,x,y))return 5;
            else {
                status=IsFoul(x,y);
                if(status>0)return status;
            }
            return 0;
            break;
        case 1: //�˲��ð���
            if(5 == IsFive(WHITE,x,y))return 5;
            else return 0;
            break;
    }
    return 0;
}

int CBoard::HaveFour(const char color,int &x, int &y){
    //�����򷵻�1�����򷵻�0������ĵ���x,y����
    int leftnum;  //�ո���ߵ���������
    int rightnum; //�ո��ұߵ���������
    bool validempty;//�ո���Ч���
    int i,j;

    switch(color){
        case BLACK: //����
            //������ '-'
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
                        default:    //�߽�
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //������� '|'
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
                        default:    //�߽�
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                }
            }

            //���б�� '\'
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
                        default:    //�߽�
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                    ++i;
                    ++j;
                }
            }

            //���б�� '/'
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
                        default:    //�߽�
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                    --i;
                    ++j;
                }
            }

            break;
        case WHITE: //����
            //������ '-'
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
                        default:    //�߽�
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //������� '|'
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
                        default:    //�߽�
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                }
            }

            //���б�� '\'
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
                        default:    //�߽�
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                    ++i;
                    ++j;
                }
            }

            //���б�� '/'
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
                        default:    //�߽�
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
    //����color��ɫ�����г��ĵ㣬���������أ���������ֵΪ���ĵ����
    //���л�������ƶԷ����������������ش˵㣬��������ֵΪ2000
    vecFourRush.clear();
    //vecDefense.clear();
    int nNum=0;     //����������(�ж��Ƿ���5��)
    int nColor=0;   //��ɫ������(�ж�5����ͬɫ���Ƿ���3��)
    CPoint ept1,ept2;   //�ո�����

    switch(color){
        case BLACK: //����
            //������ '-'
            for(int j=1;j<BOARD_SIZE+1;++j){
                nNum=0;
                nColor=0;
                for(int i=1;i<BOARD_SIZE+1;++i){
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ�������
                        switch(IsFour(BLACK,ept1.x,ept1.y,1)){//�Ե�һ���ո��ж�
                            case 4: //����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,1))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,1)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,1))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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

            //������� '|'
            for(int i=1;i<BOARD_SIZE+1;++i){
                nNum=0;
                nColor=0;
                for(int j=1;j<BOARD_SIZE+1;++j){
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ�������
                        switch(IsFour(BLACK,ept1.x,ept1.y,2)){//�Ե�һ���ո��ж�
                            case 4: //����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,2))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,2)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,2))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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

            //���б�� '\'
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
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ�������
                        switch(IsFour(BLACK,ept1.x,ept1.y,3)){//�Ե�һ���ո��ж�
                            case 4: //����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,3))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,3)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,3))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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

            //���б�� '/'
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
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ�������
                        switch(IsFour(BLACK,ept1.x,ept1.y,4)){//�Ե�һ���ո��ж�
                            case 4: //����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    TryMove(BLACK,ept1.x,ept1.y);
                                    if(5 == IsFive(BLACK,ept2.x,ept2.y,4))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    return 2000;
                                }
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(BLACK,ept2.x,ept2.y,4)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    TryMove(BLACK,ept2.x,ept2.y);
                                    if(5 == IsFive(BLACK,ept1.x,ept1.y,4))   //����һ�㴦�ɳ�����
                                        vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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
            //������ '-'
            for(int j=1;j<BOARD_SIZE+1;++j){
                nNum=0;
                nColor=0;
                for(int i=1;i<BOARD_SIZE+1;++i){
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ����������Ǳƽ���
                        switch(IsFour(WHITE,ept1.x,ept1.y,1)){//�Ե�һ���ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,1)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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

            //������� '|'
            for(int i=1;i<BOARD_SIZE+1;++i){
                nNum=0;
                nColor=0;
                for(int j=1;j<BOARD_SIZE+1;++j){
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ����������Ǳƽ���
                        switch(IsFour(WHITE,ept1.x,ept1.y,2)){//�Ե�һ���ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,2)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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

            //���б�� '\'
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
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ����������Ǳƽ���
                        switch(IsFour(WHITE,ept1.x,ept1.y,3)){//�Ե�һ���ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,3)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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

            //���б�� '/'
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
                    //���뵱ǰ��
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
                    //ȥ���ɸ�
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
                    //�Ƿ��г��ĵ�
                    if(nNum==5 && nColor==3){
                        //�ж��ǳ��Ļ����������Ǳƽ���
                        switch(IsFour(WHITE,ept1.x,ept1.y,4)){//�Ե�һ���ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept1.x,ept1.y);
                                if(IsFoul(ept2.x,ept2.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                vecFourRush.clear();
                                vecFourRush.push_back(FourRush(ept1,ept2));
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,4)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    vecFourRush.clear();
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    vecFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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
    //���color������VCF�����з���1�����򷵻�0��VCF������vcfList������
    int result = 0;
    vcfList.clear();
    vcfTreeVec.clear();
    vcfTNodeQu.clear();

    int x,y;
    //if(HaveFour(color,x,y)){//�Լ��Ѿ������ˣ��򽫳���ĵ����vcfList������true
    //    vcfList.clear();
    //    vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
    //    return true;
    //}

    vcfTreeNode *root = new vcfTreeNode;
    vcfTreeVec.push_back(root);
    vcfTNodeQu.push_back(root);
    root->pParent=NULL;

    if(!HaveFour(-color,x,y)){//�Է��޳��ģ����ʼ���ý��
        if(2000 == GetFourRushPoints(color,root->NewRush)){   //�Լ���ʤ��
            vcfList.push_back(root->NewRush.front());
            delete root;
            return 1;
        }
        else {  //�Լ���ʤ��
            if(root->NewRush.empty()){  //��û�г��ĵ�
                delete root;
                return 0;
            }
            sort(root->NewRush.begin(),root->NewRush.end());
        }
    }

    while(!vcfTNodeQu.empty()){
        if(DoSearchVCF(color)){ //��VCF
            result = 1;
            break;
        }
    }

    //������
    for(vector<vcfTreeNode *>::iterator i=vcfTreeVec.begin();i!=vcfTreeVec.end();++i){
        delete *i;
    }

    return result;
}


int CBoard::DoSearchVCF(const char color){

    vcfTreeNode *pCurrent=vcfTNodeQu.front();
    vcfTNodeQu.pop_front();

    //�ھ�
    PutTreeLayout(color,pCurrent);

    int x,y;

    switch(color){
        case BLACK: //�Ժ��壺
            if(HaveFour(WHITE,x,y)){    //�����г���
                if(IsFoul(x,y)){    //�����ǽ��֣���ֻ�������������Ľ���(���������ӵ�)
                    if(IsFoul(x,y)==6)break;
                    //����Ƿ��п��ܳ���
                    bool four=false;
                    for(int i=1;i<5;++i){
                        if(IsFour(BLACK,x,y,i)){
                            four=true;
                            break;
                        }
                    }
                    if(four){   //�п��ܽ����赲�˳��ģ�����Ƿ���ͨ�����������ӱܽ���
                        vector<FourRush> rush;
                        GetFourRushPoints(BLACK,rush);
                        //ȥ���³���
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
                                //PutTreeLayout(EMPTY,pCurrent);  //�ظ�ԭʼ����
                                while(p!=NULL){
                                    for(vector<FourRush>::iterator finditr=p->NewRush.begin();finditr!=p->NewRush.end();++finditr){
                                        if((*itr) == (*finditr)){//�ҵ��������������ĵ�ʱ����
                                            //��������浽pCurrent��·����ÿ�����涼����������ģ�������������
                                            for(vcfTreeNode *pRushNode=pCurrent;pRushNode!=p;){
                                                //PutTreeLayout(BLACK,pRushNode);
                                                for(vector<FourRush>::iterator tmpitr=pRushNode->RushPath.begin();tmpitr!=pRushNode->RushPath.end();++tmpitr){
                                                    TryMove(EMPTY,tmpitr->rush.x,tmpitr->rush.y);
                                                    TryMove(EMPTY,tmpitr->defense.x,tmpitr->defense.y);
                                                }
                                                pRushNode=pRushNode->pParent;
                                                if(pRushNode->NewRush.empty())continue; //NewRushΪ��˵���˾�������г���
                                                if(IsFour(BLACK,finditr->rush.x,finditr->rush.y)){//���ߣ������½�������ĺ�ľ���

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
                                            PutTreeLayout(BLACK,pCurrent);  //�ص���ǰ����
                                        }
                                    }
                                    p=p->pParent;
                                }
                            }
                        }
                    }
                }
                else {  //���㲻�ǽ���
                    int x1,y1;
                    switch(IsFour(BLACK,x,y)){
                        case 4:     //���ġ��ߴ˵㣬�������
                            TryMove(BLACK,x,y);
                            if(HaveFour(WHITE,x1,y1)){  //������Ȼ�г��ģ�˵����һ����˫�ģ��޽ⷵ��0
                                PutTreeLayout(EMPTY,pCurrent);  //�ظ�ԭʼ����
                                return 0;
                            }
                            HaveFour(BLACK,x1,y1);  //Ѱ�Һ�����ĵĵ���    |||||||||||to update|||||||||||
                            {
                                //�����½��
                                vcfTreeNode *newnode=new vcfTreeNode;
                                vcfTreeVec.push_back(newnode);
                                vcfTNodeQu.push_back(newnode);
                                newnode->pParent=pCurrent;
                                newnode->RushPath.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));

                                if(!IsFour(WHITE,x1,y1)){    //���岻�γ��µķ����ģ�����������³���
                                    TryMove(WHITE,x1,y1);
                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());
                                }
                                TryMove(EMPTY,x,y);
                                TryMove(EMPTY,x1,y1);
                            }

                            break;
                        case 40:    //������ʤ�㡣�г�vcf·��������
                            vcfTreeNode *p=pCurrent;
                            while(NULL != p->pParent){
                                for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                                    vcfList.push_front(*ritr);
                                }
                                vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
                                p=p->pParent;
                            }
                            //����
                            PutTreeLayout(EMPTY,pCurrent);
                            return 1;
                            break;
                    }
                }
            }
            else {  //����û��
                vector<FourRush> vecCurRush;
                if(2000 == GetFourRushPoints(BLACK,vecCurRush)){    //������ʤ��
                    vcfTreeNode *p=pCurrent;
                    while(NULL != p->pParent){
                        for(vector<FourRush>::reverse_iterator ritr=p->RushPath.rbegin();ritr!=p->RushPath.rend();++ritr){
                            vcfList.push_front(*ritr);
                        }
                        vcfList.push_back(vecCurRush.front());
                        p=p->pParent;
                    }
                    //����
                    PutTreeLayout(EMPTY,pCurrent);
                    return 1;
                }
                else {  //��ͨ����������޳��ģ�����Ҳ��ʤ��
                    vector<FourRush> &OldRush(vecCurRush);  //��ⷽ�㣬��������
                    sort(OldRush.begin(),OldRush.end());
                    //ȥ����pCurrent->NewRush���ظ���Ԫ��
                    OldRush.erase(set_difference(OldRush.begin(),OldRush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),OldRush.begin()),OldRush.end());
                    for(int r=1;r<=3;++r){
                        combination comb1,comb2;
                        //if(r > pCurrent->NewRush.size())break;
                        int r1max=min(r,(int)pCurrent->NewRush.size());
                        for(int r1=1;r1<=r1max;++r1){
                            int r2=r-r1;
                            if(r2 > (int)OldRush.size())continue;    //OldRush�ò����㹻��Ԫ����continue
                            comb1.init((int)pCurrent->NewRush.size(),r1);
                            while(comb1.next()){
                                comb2.init((int)OldRush.size(),r2);
                                bool first=true;
                                while(comb2.next() || first){//����NewRush��OldRush��һ�����
                                    //�ֱ�Ϊ pCurrent->NewRush[comb1[0]...comb1[r1]] �� OldRush[comb2[0]...comb2[r2]]
                                    first=false;
                                    vector<FourRush> CombRush;
                                    CombRush.reserve(r);
                                    for(int i=0;i<r1;++i)CombRush.push_back(pCurrent->NewRush[comb1[i]]);
                                    for(int i=0;i<r2;++i)CombRush.push_back(OldRush[comb2[i]]);
                                    //���Űڳ���ǰ��ϣ�
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
                                    if(i<(int)CombRush.size()){//�ϸ�ѭ��δ��ɣ���ǰ�����Ч
                                        for(;i>=0;--i){//��ԭ��Ч���
                                            FourRush tmp=CombRush[i];
                                            TryMove(EMPTY,tmp.rush.x,tmp.rush.y);
                                            TryMove(EMPTY,tmp.defense.x,tmp.defense.y);
                                        }
                                        continue;//ת����һ���
                                    }
                                    //��ǰ�����Ч��
                                    if(HaveFour(WHITE,x,y)){//�����γɳ���
                                        int x1,y1;
                                        TryMove(BLACK,x,y);
                                        if(HaveFour(WHITE,x1,y1)){//���廹�г���(������˫��)
                                            TryMove(EMPTY,x,y);
                                            //�ظ���ǰ����
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
                                                if(!HaveFour(WHITE,x,y)){//�����޳��ģ��½��������³��ĺ�������
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
                                                if(!HaveFour(WHITE,x,y)){//�����޳��ģ��½��������³��ĺ�������
                                                    GetFourRushPoints(BLACK,newnode->NewRush);
                                                    sort(newnode->NewRush.begin(),newnode->NewRush.end());
                                                }
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                            }
                                        }
                                        else {  //����ֻ����һ�����ģ������RushPath˳���½���������У����ü���NewRush
                                            //����Ƿ�ǰCombRush�����г��Ĺ�ͬ��������׵ķ����ģ������򲻼������
                                            TryMove(EMPTY,x,y);
                                            //����ȥ��CombRush�е�ÿ�����ģ���(x,y)�Ƿ����ǰ׵ĳ��ĵ�
                                            vector<FourRush>::iterator itr;
                                            for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                if(IsFive(WHITE,x,y))break;
                                                TryMove(BLACK,itr->rush.x,itr->rush.y);
                                                TryMove(WHITE,itr->defense.x,itr->defense.y);
                                            }
                                            if(itr!=CombRush.end()){//��ʱ����CombRush�е����г��Ĺ�ͬ���ɰ׵ķ����ģ��򲻼������
                                                 //�ظ���ǰ����
                                                for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                            }
                                            else {
                                                //�ظ���ǰ����
                                                for(itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                                if(CheckRushPath(BLACK,CombRush)){  //�ҵ�RushPath��˳��
                                                    vcfTreeNode *newnode=new vcfTreeNode;
                                                    vcfTreeVec.push_back(newnode);
                                                    vcfTNodeQu.push_back(newnode);
                                                    newnode->pParent=pCurrent;
                                                    newnode->RushPath=CombRush;
                                                }
                                            }
                                        }
                                        continue;  //ת����һ���
                                    }
                                    else {  //����ϰ��岻�γɳ���
                                        vector<FourRush> newrush;
                                        if(2000 == GetFourRushPoints(BLACK,newrush)){   //������ʤ��
                                            //�ظ���ǰ����
                                            for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                            }
                                            if(CheckRushPath(BLACK,CombRush)){  //�ҵ�RushPath��˳��
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
                                                //����
                                                PutTreeLayout(EMPTY,pCurrent);
                                                return 1;
                                            }
                                        }
                                        else {  //������ʤ�㣬�ж������³���
                                            sort(newrush.begin(),newrush.end());
                                            newrush.erase(set_difference(newrush.begin(),newrush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),newrush.begin()),newrush.end());
                                            newrush.erase(set_difference(newrush.begin(),newrush.end(),OldRush.begin(),OldRush.end(),newrush.begin()),newrush.end());

                                            if(!newrush.empty()){   //���³���
                                                //�ж��Ƿ���newrush�д���һ����������CombRush�����г��Ĺ�ͬ�γɵ�
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
                                                ////�ж�newrush��ÿ�����Ķ�����CombRush�����г��Ĺ�ͬ�γɵ�
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
                                                //�ظ���ǰ����
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                                if(!newrush.empty() && CheckRushPath(BLACK,CombRush)){  //�ҵ�RushPath��˳�����½����
                                                    vcfTreeNode *newnode=new vcfTreeNode;
                                                    vcfTreeVec.push_back(newnode);
                                                    vcfTNodeQu.push_back(newnode);
                                                    newnode->pParent=pCurrent;
                                                    newnode->RushPath=CombRush;
                                                    newnode->NewRush=newrush;
                                                }
                                            }
                                            else {
                                                //�ظ���ǰ����
                                                for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                                    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                                    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                                }
                                            }
                                        }
                                        //bool win=false;
                                        //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end() && !win;++itr){//������е�ÿ������
                                        //    //ȥ�����ĵĵ㣬���Ƿ�ɻ���
                                        //    //x=itr->rush.x;
                                        //    //y=itr->rush.y;
                                        //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                        //    if(IsOpenThree(BLACK,itr->rush.x,itr->rush.y)){ //���γɻ���
                                        //        win=true;
                                        //        break;
                                        //    }
                                        //    TryMove(BLACK,itr->rush.x,itr->rush.y);
                                        //}
                                        ////�ظ���ǰ����
                                        //for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                        //    TryMove(EMPTY,itr->rush.x,itr->rush.y);
                                        //    TryMove(EMPTY,itr->defense.x,itr->defense.y);
                                        //}
                                        //if(win){
                                        //    if(CheckRushPath(BLACK,CombRush)){  //�ҵ�RushPath��˳��
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
                                        //        //����
                                        //        PutTreeLayout(EMPTY,pCurrent);
                                        //        return 1;
                                        //    }
                                        //}
                                        //else {  //�ڳɵ�ǰ��ϣ����ж������³���
                                        //    //=================================================
                                        //    for(vector<FourRush>::iterator itr=CombRush.begin();itr!=CombRush.end();++itr){
                                        //        TryMove(BLACK,itr->rush.x,itr->rush.y);
                                        //        TryMove(WHITE,itr->defense.x,itr->defense.y);
                                        //    }
                                        //    vector<FourRush> newrush;
                                        //}
                                    }

                                    //�ظ���ǰ����
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

        case WHITE: //�԰���

            break;

        default:
            break;
    }
/*    if(HaveFour(color,x,y)){//�Լ����ģ����VCF���в�����
        //(ʵ�����������ֻ�а����п��ܡ���Ϊ��һ������˵����һ���ĳ�����ʵ��˫�ģ��Ժ�����˵�ǽ���)
        //==================================================================

        //vector<FourRush> vcfVec;
        //for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
        //    for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
        //        vcfVec.push_back(*itr);
        //}
        //PutTreeLayout(EMPTY,pCurrent);//�ظ���ԭʼ����
        //vcfList.clear();
        //if(CheckVcfVec(color,vcfVec)){  //�ҵ���ЧVCF·��
        //    return 1;
        //}
        //else {//δ�ҵ����ظ���ǰ���棬��������ļ���
        //    PutTreeLayout(color,pCurrent);
        //}
    }

    //����ɳ���
    vector<FourRush> OldRush;
    int n;
    if(0 < (n=GetFourRushPoints(color,OldRush))){   //���Լ���ʤ��
        FourRush winpoint(CPoint(0,0),CPoint(0,0));
        if(HaveFour(-color,x,y)){  //���Է����ģ���⵲���Ƿ�����ʤ��
            for(vector<FourRush>::reverse_iterator ritr=OldRush.rbegin();ritr!=OldRush.rbegin()+n;++ritr){
                if(ritr->rush.x == x && ritr->rush.y == y){
                    winpoint=*ritr;
                    break;
                }
            }
        }
        else {  //���Է�û�г���
            winpoint=OldRush.back();
        }
        if(!(FourRush(CPoint(0,0),CPoint(0,0)) == winpoint)){//ȷʵ��ʤ��
            vector<FourRush> vcfVec;
            for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
                for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
                    vcfVec.push_back(*itr);
            }
            vcfVec.push_back(winpoint);
            PutTreeLayout(EMPTY,pCurrent);//�ظ���ԭʼ����
            vcfList.clear();
            if(CheckVcfVec(color,vcfVec)){  //�ҵ���ЧVCF·��
                return 1;
            }
            else {//δ�ҵ����ظ���ǰ���棬��������ļ���
                PutTreeLayout(color,pCurrent);
            }
        }
    }
    int rmax=static_cast<int>(OldRush.size()/2);
    //OldRush��ȥ��pCurrent->NewRush�еĳ���
    sort(OldRush.begin(),OldRush.end());
    OldRush.erase(set_difference(OldRush.begin(),OldRush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),OldRush.begin()),OldRush.end());

    for(int r=1;r<=rmax;++r){
        combination comb1,comb2;
        int r1max=min(r,static_cast<int>(pCurrent->NewRush.size()/2));
        for(int r1=1;r1<=r1max;++r1){
            comb1.init(static_cast<int>(pCurrent->NewRush.size()),r1);
            int r2=r-r1;
            if(r2<0)r2=0;
            else if(r2+r2 > (int)OldRush.size()){    //OldRush�е�Ԫ�ز���������ϣ���continue
                continue;
            }
            while(comb1.next()){
                if(!comb2.init(static_cast<int>(OldRush.size()),r2))continue;
                bool first=true;
                while(comb2.next() || first){    //����NewRush �� OldRush ��һ�����
                    //�ֱ�Ϊ pCurrent->NewRush[comb1[0]...comb1[r1]] �� OldRush[comb2[0]...comb2[r2]]
                    first=false;
                    vector<FourRush> CombRush;
                    CombRush.reserve(r);
                    for(int ii=0;ii<r1;++ii)CombRush.push_back(pCurrent->NewRush[comb1[ii]]);
                    for(int ii=0;ii<r2;++ii)CombRush.push_back(OldRush[comb2[ii]]);
                    //���Űڳ���ǰ��ϣ�
                    int i=0;
                    for(;i<(int)CombRush.size();++i){
                        FourRush tmp=CombRush[i];
                        if(EMPTY != matrix[tmp.rush.x][tmp.rush.y] || EMPTY != matrix[tmp.defense.x][tmp.defense.y]){
                            break;//��ǰ�����Ч
                        }
                        else {
                            TryMove(color,tmp.rush.x,tmp.rush.y);
                            TryMove(-color,tmp.defense.x,tmp.defense.y);
                        }
                    }
                    if(i<(int)CombRush.size()){//�ϸ�ѭ��δ��ɣ���ǰ�����Ч
                        for(;i>=0;--i){//��ԭ��Ч���
                            FourRush tmp=CombRush[i];
                            TryMove(EMPTY,tmp.rush.x,tmp.rush.y);
                            TryMove(EMPTY,tmp.defense.x,tmp.defense.y);
                        }
                        continue;//ת����һ���
                    }
                    //��ǰ�����Ч��
                    bool win=false;
                    if(HaveFour(color,x,y)){//�Լ�����
                        win=true;
                    }
                    else if(!HaveFour(-color,x,y)){ //�Լ�û�ģ��Է�Ҳû��
                        for(i=0;i<(int)CombRush.size() && !win;++i){ //������е�ÿ������
                            //ȥ�����ĵĵ㣬���Ƿ�ɻ��������Ҳ��γɽ���
                            x=CombRush[i].rush.x;
                            y=CombRush[i].rush.y;
                            int x1=CombRush[i].defense.x,y1=CombRush[i].defense.y;
                            TryMove(EMPTY,x,y);
                            if(IsOpenThree(color,x,y)){ //���γɻ���
                                win=true;
                            }
                            else if(WHITE == color){    //���ǰ��壬���ܷ�ƽ���
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
                    else {//�Է����ģ��Լ�û��
                    }
                    if(win){//��ǰ�����Ӯ
                        vector<FourRush> vcfVec;
                        for(vcfTreeNode *p=pCurrent;p->pParent!=NULL;p=p->pParent){
                            for(vector<FourRush>::iterator itr=p->RushPath.begin();itr!=p->RushPath.end();++itr)
                                vcfVec.push_back(*itr);
                        }
                        for(i=0;i<(int)CombRush.size();++i){
                            vcfVec.push_back(CombRush[i]);
                        }
                        //���Ȼص���ǰ����
                        for(i=0;i<(int)CombRush.size();++i){//�ָ���ǰ����
                            TryMove(EMPTY,CombRush[i].rush.x,CombRush[i].rush.y);
                            TryMove(EMPTY,CombRush[i].defense.x,CombRush[i].defense.y);
                        }
                        PutTreeLayout(EMPTY,pCurrent);//Ȼ��ظ���ԭʼ����
                        vcfList.clear();
                        if(CheckVcfVec(color,vcfVec)){  //�ҵ���ЧVCF·��
                            return 1;
                            //==========
                        }
                        else {//δ�ҵ�����˵����ǰ����޷��γɣ�Ϊ�����
                            PutTreeLayout(color,pCurrent);//�ָ���ǰ����
                            continue; //ת����һ���
                        }
                    }
                    else {  //��ǰ��ϲ���Ӯ����������³���
                        vector<FourRush> newrush;
                        GetFourRushPoints(color,newrush);
                        sort(newrush.begin(),newrush.end());
                        //�ֱ�ȥ�� OldRush �� pCurrent->NewRush �е�Ԫ��
                        newrush.erase(set_difference(newrush.begin(),newrush.end(),OldRush.begin(),OldRush.end(),newrush.begin()),newrush.end());
                        newrush.erase(set_difference(newrush.begin(),newrush.end(),pCurrent->NewRush.begin(),pCurrent->NewRush.end(),newrush.begin()),newrush.end());
                        if(!newrush.empty()){//���³���
                            vcfTreeNode *p=new vcfTreeNode;
                            vcfTreeVec.push_back(p);
                            vcfTNodeQu.push_back(p);
                            p->NewRush=newrush;
                            p->pParent=pCurrent;
                            p->RushPath=CombRush;
                        }
                    }
                    //�ظ���ǰ����
                    for(i=0;i<(int)CombRush.size();++i){
                        TryMove(EMPTY,CombRush[i].rush.x,CombRush[i].rush.y);
                        TryMove(EMPTY,CombRush[i].defense.x,CombRush[i].defense.y);
                    }
                }
            }
        }
    }*/

    //����
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
            if(HaveFour(-color,x,y)){   //�Է��г���
                if( x == RushPath[RushOrder[i]].rush.x && y == RushPath[RushOrder[i]].rush.y && IsFour(color,x,y)){
                    TryMove(color,x,y);
                    TryMove(-color,RushPath[RushOrder[i]].defense.x, RushPath[RushOrder[i]].defense.y);
                }
                else break;
            }
            else {  //�Է�û����
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
//    //��vcfVec��Ѱ��һ����Ч��VCF·������������㷨���ҵ�����true�����򷵻�false(���ǽ���)
//    //����˺���ǰ���vcfList
//    int x,y;
//    if(HaveFour(color,x,y)){
//        vcfList.push_back(FourRush(CPoint(x,y),CPoint(0,0)));
//        return true;
//    }
//    if(HaveFour(-color,x,y)){//�Է��г���
//        if(color == BLACK && IsFoul(x,y)){//�Լ����ƽ���
//            return false;
//        }
//        vector<FourRush>::iterator itr=vcfVec.begin();
//        while(itr!=vcfVec.end()){
//            if(x == itr->rush.x && y == itr->rush.y){   //������vcfVec�У��ҵ�
//                if(IsFour(color,x,y)){
//                    TryMove(color,x,y);
//                    int x1,y1,x2,y2;
//                    HaveFour(color,x1,y1);  //Ѱ�ҵ���
//                    if(color == WHITE && IsFoul(x1,y1)){    //�ƶԷ�����
//                        vcfList.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));
//                        TryMove(EMPTY,x,y);
//                        return true;
//                    }
//                    TryMove(-color,x1,y1);
//                    if(HaveFour(color,x2,y2)){//�ⲽ������˫��
//                        vcfList.push_back(FourRush(CPoint(x,y),CPoint(x1,y1)));
//                        TryMove(EMPTY,x,y);
//                        TryMove(EMPTY,x1,y1);
//                        return true;
//                    }
//                    if(x1 != itr->defense.x || y1 != itr->defense.y){   //��������vcfVec�в�һ���򷵻�false
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
//                else return false;  //���Է����ĵĵ��Լ����γɳ��ģ��򷵻�false
//            }
//            ++itr;
//        }
//        return false;   //���㲻��vcfVec��
//    }
//    else {  //�Է��޳���
//        vector<FourRush> Rush;
//        if(0 < GetFourRushPoints(color,Rush)){   //��ǰ��ʤ��
//            vcfList.push_back(Rush.back());
//            return true;
//        }
//        Rush.clear();
//        for(vector<FourRush>::iterator itr=vcfVec.begin();itr!=vcfVec.end();++itr){
//            if(IsFour(color,itr->rush.x,itr->rush.y))Rush.push_back(*itr);
//        }
//        for(vector<FourRush>::iterator itr=Rush.begin();itr!=Rush.end();++itr){//�Ե�ǰ�����ÿ�����ĵ�
//            TryMove(color,itr->rush.x,itr->rush.y);
//            int x1,y1,x2,y2;
//            HaveFour(color,x1,y1);  //Ѱ�ҵ���
//            TryMove(-color,x1,y1);
//            if(HaveFour(color,x2,y2)){//�ⲽ������˫��
//                vcfList.push_back(FourRush(CPoint(itr->rush.x,itr->rush.y),CPoint(x1,y1)));
//                TryMove(EMPTY,itr->rush.x,itr->rush.y);
//                TryMove(EMPTY,x1,y1);
//                return true;
//            }
//            if(x1 != itr->defense.x || y1 != itr->defense.y){   //��������vcfVec�в�һ��ת����һ��
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
//    //�ڱ���color�����ֵ������Ѱ�ҶԳ��ĵ��յ㣬���ҵ�����true���Գ�������icfList���أ����򷵻�false(�����ǽ���)
//    int x,y;
//    if(HaveFour(color,x,y))return true;
//    if(!HaveFour(-color,x,y)){//�Է�û�ģ��򷵻�true
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

