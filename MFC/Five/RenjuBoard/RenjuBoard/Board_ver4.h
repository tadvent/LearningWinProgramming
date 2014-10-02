#pragma once

#include<vector>
#include<list>
#include<deque>
#include<atltypes.h>

using namespace std;

const int BOARD_SIZE=15;
const char BLACK=1;
const char WHITE=-1;
const char EMPTY=0;

class FourRush{
public:
    CPoint rush;
    CPoint defense;

    FourRush(const CPoint &pt1, const CPoint &pt2):rush(pt1),defense(pt2){}
};

//class vcfTreeNode{
//public:
//    FourRush frRush;
//    vcfTreeNode *pParent;
//
//    vcfTreeNode(void):frRush(CPoint(),CPoint()),pParent(NULL){}
//};

//class vcfState{
//public:
//    list<FourRush> Try;
//    list<FourRush> Rush;
//
//    vcfState(const list<FourRush> &lstTry, const list<FourRush> &lstRush):Try(lstTry),Rush(lstRush){}
//};

class CBoard
{
    //构造、析构
public:
    CBoard(void);
    ~CBoard(void);
    void Clear(void);

    //数据成员
public:
    char matrix[BOARD_SIZE+2][BOARD_SIZE+2];
    vector<CPoint> MoveList;
    UINT nCurrent;
    
/*    deque<vcfTreeNode *> vcfTNodeQu;*/    //查找VCF时保存状态的队列
    list<FourRush> vcfList;             //查找VCF时返回正确的VCF路径
/*    vector<vcfTreeNode *> vcfTreeVec;*/   //保存指向查找VCF时生成树的每个存储单元的指针，以备删除

    //成员函数
public:
    int DoMove(const CPoint &point);
    int BackMove(void); //无法回退时返回-1
    int ForwardMove(void); //无法前进时返回-1

public:
    inline bool IsOutBoard(const CPoint &point);
    inline bool IsOutBoard(const int x,const int y);
    inline void TryMove(const char color, const int x, const int y);

    //////禁手判定部分函数//////

    //在某方向上成五连返回5，黑棋长连返回6，否则返回0
    int IsFive(const char color, const int x, const int y, const int nDir);
    //五连返回5，黑棋长连返回6，否则返回0
    int IsFive(const char color, const int x, const int y);
    //在某方向上冲四返回4，活四连返回40，双四返回44
    int IsFour(const char color, const int x, const int y, const int nDir);
    //冲四返回4，活四连返回40，否则返回0
    int IsFour(const char color, const int x, const int y);
    //双四返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连和长连的情况
    int IsDoubleFour(const int x, const int y);
    //在某方向上活三返回1，否则返回0
    int IsOpenThree(const char color, const int x, const int y, const int nDir);
    //活三返回1，否则返回0
    int IsOpenThree(const char color, const int x, const int y);
    //双三返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连、长连和双四的情况
    int IsDoubleThree(const int x, const int y);
    //禁手返回1，否则返回0 (该函数仅对黑棋判断)
    int IsFoul(const int x, const int y);

    //////走棋算法部分函数//////

    //五连返回5，禁手返回1，否则返回0
    int CheckMove(const int x, const int y);

    //有四返回1，否则返回0，成五的点由x,y返回
    int HaveFour(const char color,int &x, int &y);

/*    //有活三或VCF返回1，否则返回0，VCF走棋顺序及挡点由VCF向量返回(阻挡对方时用)
    int HaveOpenThree(const char color, vector<CPoint> &VCF);*/

    //计算color颜色的所有冲四点，由链表返回，函数返回值为冲四点个数
    //若有活四连或逼对方禁手则链表仅返回此点，此时函数返回值为2000
    int GetFourRushPoints(const char color, list<FourRush> &lstFourRush);

    //检查color方有无VCF，若有返回1，否则返回0；VCF序列由vcfList链表返回
    int SearchVCF(const char color, const bool clean = false);
    int DoSearchVCF(const char color/*, list<FourRush> &vcfList*/);
private:
    void DoCleanVCF(const char color);
    bool CheckVcfList(const char color);
};
