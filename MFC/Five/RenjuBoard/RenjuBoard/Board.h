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
    //���졢����
public:
    CBoard(void);
    ~CBoard(void);
    void Clear(void);

    //���ݳ�Ա
public:
    char matrix[BOARD_SIZE+2][BOARD_SIZE+2];
    vector<CPoint> MoveList;
    UINT nCurrent;
    
    deque<vcfTreeNode *> vcfTNodeQu;    //����VCFʱ����״̬�Ķ���
    list<FourRush> vcfList;             //����VCFʱ������ȷ��VCF·��
    vector<vcfTreeNode *> vcfTreeVec;   //����ָ�����VCFʱ��������ÿ���洢��Ԫ��ָ�룬�Ա�ɾ��

    //��Ա����
public:
    int DoMove(const CPoint &point);
    int BackMove(void); //�޷�����ʱ����-1
    int ForwardMove(void); //�޷�ǰ��ʱ����-1

public:
    inline bool IsOutBoard(const CPoint &point);
    inline bool IsOutBoard(const int x,const int y);
    inline void TryMove(const char color, const int x, const int y);

    //////�����ж����ֺ���//////

    //��ĳ�����ϳ���������5�����峤������6�����򷵻�0
    int IsFive(const char color, const int x, const int y, const int nDir);
    //��������5�����峤������6�����򷵻�0
    int IsFive(const char color, const int x, const int y);
    //��ĳ�����ϳ��ķ���4������������40��˫�ķ���44
    int IsFour(const char color, const int x, const int y, const int nDir);
    //���ķ���4������������40�����򷵻�0���ѿ��ǽ���
    int IsFour(const char color, const int x, const int y);
    //˫�ķ���1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų������ͳ��������
    int IsDoubleFour(const int x, const int y);
    //��ĳ�����ϻ�������1�����򷵻�0
    int IsOpenThree(const char color, const int x, const int y, const int nDir);
    //��������1�����򷵻�0(���ǽ���)
    int IsOpenThree(const char color, const int x, const int y);
    //˫������1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų�������������˫�ĵ����
    int IsDoubleThree(const int x, const int y);
    //�������ַ���6��˫�ķ���44��˫������33�����򷵻�0 (�ú������Ժ����ж�)
    int IsFoul(const int x, const int y);

    //////�����㷨���ֺ���//////

    //��������5�����ַ���1�����򷵻�0
    int CheckMove(const int x, const int y);

    //���ķ���1�����򷵻�0������ĵ���x,y����
    int HaveFour(const char color,int &x, int &y);

/*    //�л�����VCF����1�����򷵻�0��VCF����˳�򼰵�����VCF��������(�赲�Է�ʱ��)
    int HaveOpenThree(const char color, vector<CPoint> &VCF);*/

    //����color��ɫ�����г��ĵ㣬���������أ���������ֵΪ���ĵ����(���ǽ���)
    //���л�������ƶԷ����������������ش˵㣬��������ֵΪ2000
    int GetFourRushPoints(const char color, vector<FourRush> &vecFourRush);

    //���color������VCF�����з���1�����򷵻�0��VCF������vcfList������
    int SearchVCF(const char color);
    int DoSearchVCF(const char color);
private:
//    void DoCleanVCF(const char color);
//    bool CheckVcfList(const char color);
    void PutTreeLayout(const char color, vcfTreeNode *pCurrent);
    //Ѱ��RushPath��·�����ҵ�����true�����򷵻�false��˳����RushPath��������
    bool CheckRushPath(const char color, vector<FourRush> &RushPath);
    //��vcfVec��Ѱ��һ����Ч��VCF·������������㷨���ҵ�����true�����򷵻�false(���ǽ���)
    //bool CheckVcfVec(const char color, vector<FourRush> &vcfVec);
    //void EmptyLayout(const vcfTreeNode *pCurrent);
    //�ڱ���color�����ֵ������Ѱ�ҶԳ��ĵ��յ㣬���ҵ�����true���Գ�������icfList���أ����򷵻�false(�����ǽ���)
    //bool FindIcfEnd(const char color, list<FourRush> &icfList);
};
