#include "StdAfx.h"
#include "Board.h"

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
    //���ķ���4������������40�����򷵻�0

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
                if(40 == IsFour(color,i,y,1))if(!IsFoul(i,y)){
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
                if(40 == IsFour(color,i,y,1))if(!IsFoul(i,y)){
                    result = 1;
                }
            }
            break;
        case 2: //���� '|'
            j=y;
            while(color == matrix[x][--j]);
            if(EMPTY == matrix[x][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,x,j,2))if(!IsFoul(x,j)){
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
                if(40 == IsFour(color,x,j,2))if(!IsFoul(x,j)){
                    result = 1;
                }
            }
            break;
        case 3: //б�� '\'
            i=x;
            j=y;
            while(color == matrix[--i][--j]);
            if(EMPTY == matrix[i][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,j,3))if(!IsFoul(i,j)){
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
                if(40 == IsFour(color,i,j,3))if(!IsFoul(i,j)){
                    result = 1;
                }
            }
            break;
        case 4: //б�� '\'
            i=x;
            j=y;
            while(color == matrix[--i][++j]);
            if(EMPTY == matrix[i][j]){  //�˷������пո񣬽�һ���ж�
                if(40 == IsFour(color,i,j,4))if(!IsFoul(i,j)){
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

    switch(color){
        case BLACK: //����
            //������ '-'
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
                        default:    //�߽�
                            if(validempty && 4==leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //������� '|'
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
                        default:    //�߽�
                            if(validempty && 4<=leftnum+rightnum)
                                return 1;
                    }
                }
            }
            //������� '|'
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

//int CBoard::GetFourRushPoints(const char color, vector<CPoint> &vecFourRush, vector<CPoint> &vecDefense){
int CBoard::GetFourRushPoints(const char color, list<FourRush> &lstFourRush){
    //����color��ɫ�����г��ĵ㣬���������أ���������ֵΪ���ĵ����
    //���л�������ƶԷ����������������ش˵㣬��������ֵΪ2000
    lstFourRush.clear();
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
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
                        switch(IsFour(BLACK,ept2.x,ept2.y,1)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
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
                        switch(IsFour(BLACK,ept2.x,ept2.y,2)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
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
                        switch(IsFour(BLACK,ept2.x,ept2.y,3)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    //vecDefense.push_back(ept2);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept1.x,ept1.y)){//���ǽ���
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
                        switch(IsFour(BLACK,ept2.x,ept2.y,4)){//�Եڶ����ո��ж�
                            case 4: //����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    //vecDefense.push_back(ept1);
                                }
                                break;
                            case 40://����
                                if(!IsFoul(ept2.x,ept2.y)){//���ǽ���
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,1)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,2)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,3)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                    //vecDefense.push_back(ept2);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept1,ept2));
                                    TryMove(EMPTY,ept1.x,ept1.y);
                                }
                                break;
                            case 40://����
                                lstFourRush.clear();
                                lstFourRush.push_back(FourRush(ept1,ept2));
                                //vecDefense.clear();
                                //vecDefense.push_back(ept2);
                                return 2000;
                                break;
                            default:
                                break;
                        }
                        switch(IsFour(WHITE,ept2.x,ept2.y,4)){//�Եڶ����ո��ж�
                            case 4: //����
                                TryMove(WHITE,ept2.x,ept2.y);
                                if(IsFoul(ept1.x,ept1.y)){//�ƽ���
                                    lstFourRush.clear();
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                    //vecDefense.push_back(ept1);
                                    return 2000;
                                }
                                else {  //���Ǳƽ���
                                    lstFourRush.push_back(FourRush(ept2,ept1));
                                    TryMove(EMPTY,ept2.x,ept2.y);
                                }
                                break;
                            case 40://����
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
    //���color������VCF�����з���1�����򷵻�0��VCF������vcfList������

    vcfStateQu.clear();
    list<FourRush> TryList;
    vcfStateQu.push_back(TryList);
    while(!vcfStateQu.empty()){
        if(DoSearchVCF(color/*,vcfList*/)){ //��VCF
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

    //�ھ�
    for(list<FourRush>::iterator i=TryList.begin();i!=TryList.end();++i){
        TryMove(color,(i->rush).x,(i->rush).y);
        TryMove(-color,(i->defense).x,(i->defense).y);
    }

    int x,y,status;
    if(HaveFour(-color,x,y)){   //�Է�����
        status=IsFour(color,x,y);
        if(4 == status){    //��������
            int defx,defy;
            TryMove(color,x,y);

            HaveFour(color,defx,defy);
            if(color == WHITE && IsFoul(defx,defy)){    //�����ǰ��岢���ⲽ���ıƺ������
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
        else if(40 == status){  //��������
            int defx,defy;
            TryMove(color,x,y);

            HaveFour(color,defx,defy);
            vcfList=TryList;
            vcfList.push_back(FourRush(CPoint(x,y),CPoint(defx,defy)));
            result = 1;

            TryMove(EMPTY,x,y);
        }
    }
    else {  //�Է�û��
        list<FourRush> rushlist;
        if(2000 == GetFourRushPoints(color,rushlist)){  //��ʤ��
            vcfList=TryList;
            vcfList.push_back(rushlist.front());
            result = 1;
        }
        else {  //��ʤ��
            for(list<FourRush>::iterator i=rushlist.begin();i!=rushlist.end();++i){
                TryList.push_back(*i);
                vcfStateQu.push_back(TryList);
                TryList.pop_back();
            }
        }
    }

    //����
    for(list<FourRush>::iterator i=TryList.begin();i!=TryList.end();++i){
        TryMove(EMPTY,(i->rush).x,(i->rush).y);
        TryMove(EMPTY,(i->defense).x,(i->defense).y);
    }
    return result;
}