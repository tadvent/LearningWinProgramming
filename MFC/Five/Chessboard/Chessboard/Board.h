#pragma once
#include<vector>
//#include<set>
#include<atltypes.h>
using namespace std;

enum Color {White=-1, Empty=0, Black=1};
const int BOARD_SIZE=15;

//class Step{
//    Color color;
//    CPoint point;
//}

class CBoardView;

class CBoard
{
public:
    CBoard(void);
    CBoard(const CBoard &bd);
    CBoard(const CBoardView &bdv);
    ~CBoard(void);
private:
    vector<CPoint> TryList;
public:
    vector<CPoint> MoveList;
    vector<CPoint> vcfList;
    //int FoulPoints[BOARD_SIZE][BOARD_SIZE];
    Color matrix[BOARD_SIZE][BOARD_SIZE];
    Color NextColor;
    bool ForbidRule;

public:
    int CheckMove(const CPoint &point); //出界或已有子返回-1，否则返回0
    inline bool IsOutBoard(const CPoint &point);
    inline bool IsOutBoard(const int x,const int y);
    void DoMove(const CPoint &point);
    int BackMove(void); //无法回退时返回-1
    int CheckFive(const CPoint &point,Color color=Empty); //五连返回5，长连返回6，否则返回0，进入此函数前保证无效坐标已被排除
    void TryMove(const CPoint &point,Color color=Empty);
    int TryBack(void);  //无法回退时返回-1
    void TryClear(void);
    int CheckFour(const CPoint &point,Color color=Empty);//进入此函数前要保证五连和长连的情况都已被排除，冲四返回4，双四返回44，否则返回0
    int CheckThree(const CPoint &point,Color color=Empty);
    int CheckFoul(const CPoint &point);//若长连返回6，双四返回44，双三返回33，其余情况返回0
    //void MarkFoul(void);//若ForbidRule为flase则不进行任何操作
    int SearchVCF(Color color=Empty);

    void Clear(void);

private:
    CPoint FindFirstEmpty(const CPoint &center,Color color,const CPoint &direction, const int maxstep);
    int CheckOpenNum(const CPoint &center, const CPoint &direction, Color color);   //查找是几连
    void ClearFoulPoints(void);
    int DoSearchVCF(Color color=Empty);
};
