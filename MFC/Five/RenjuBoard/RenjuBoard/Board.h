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
    bool operator==(const FourRush &fr){
        return (rush == fr.rush && defense == fr.defense);
    }
    bool operator<(const FourRush &fr){
        if(rush.x < fr.rush.x)return true;
        else if(rush.x > fr.rush.x) return false;
        else if(rush.y < fr.rush.y) return true;
        else if(rush.y > fr.rush.y) return false;
        else if(defense.x < fr.defense.x) return true;
        else if(defense.x > fr.defense.x) return false;
        else return defense.y < fr.defense.y;
    }
};

class vcfTreeNode{
public:
    vector<FourRush> RushPath;
    vector<FourRush> NewRush;
    vcfTreeNode *pParent;

    vcfTreeNode(void):pParent(NULL){}
};

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
    
    deque<vcfTreeNode *> vcfTNodeQu;    //查找VCF时保存状态的队列
    list<FourRush> vcfList;             //查找VCF时返回正确的VCF路径
    vector<vcfTreeNode *> vcfTreeVec;   //保存指向查找VCF时生成树的每个存储单元的指针，以备删除

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
    //冲四返回4，活四连返回40，否则返回0，已考虑禁手
    int IsFour(const char color, const int x, const int y);
    //双四返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连和长连的情况
    int IsDoubleFour(const int x, const int y);
    //在某方向上活三返回1，否则返回0
    int IsOpenThree(const char color, const int x, const int y, const int nDir);
    //活三返回1，否则返回0(考虑禁手)
    int IsOpenThree(const char color, const int x, const int y);
    //双三返回1，否则返回0 (该函数仅对黑棋判断)；在进入此函数前应排除五连、长连和双四的情况
    int IsDoubleThree(const int x, const int y);
    //长连禁手返回6、双四返回44、双三返回33，否则返回0 (该函数仅对黑棋判断)
    int IsFoul(const int x, const int y);

    //////走棋算法部分函数//////

    //五连返回5，禁手返回1，否则返回0
    int CheckMove(const int x, const int y);

    //有四返回1，否则返回0，成五的点由x,y返回
    int HaveFour(const char color,int &x, int &y);

/*    //有活三或VCF返回1，否则返回0，VCF走棋顺序及挡点由VCF向量返回(阻挡对方时用)
    int HaveOpenThree(const char color, vector<CPoint> &VCF);*/

    //计算color颜色的所有冲四点，由向量返回，函数返回值为冲四点个数(考虑禁手)
    //若有活四连或逼对方禁手则向量仅返回此点，函数返回值为2000
    int GetFourRushPoints(const char color, vector<FourRush> &vecFourRush);

    //检查color方有无VCF，若有返回1，否则返回0；VCF序列由vcfList链表返回
    int SearchVCF(const char color);
    int DoSearchVCF(const char color);
private:
//    void DoCleanVCF(const char color);
//    bool CheckVcfList(const char color);
    void PutTreeLayout(const char color, vcfTreeNode *pCurrent);
    //寻找RushPath的路径，找到返回true，否则返回false。顺序由RushPath向量返回
    bool CheckRushPath(const char color, vector<FourRush> &RushPath);
    //在vcfVec中寻找一条有效的VCF路径，深度优先算法，找到返回true，否则返回false(考虑禁手)
    //bool CheckVcfVec(const char color, vector<FourRush> &vcfVec);
    //void EmptyLayout(const vcfTreeNode *pCurrent);
    //在保持color方先手的情况下寻找对冲四的终点，若找到返回true，对冲序列由icfList返回；否则返回false(不考虑禁手)
    //bool FindIcfEnd(const char color, list<FourRush> &icfList);
};
