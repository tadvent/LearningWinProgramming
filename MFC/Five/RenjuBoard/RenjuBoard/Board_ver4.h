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
    
/*    deque<vcfTreeNode *> vcfTNodeQu;*/    //����VCFʱ����״̬�Ķ���
    list<FourRush> vcfList;             //����VCFʱ������ȷ��VCF·��
/*    vector<vcfTreeNode *> vcfTreeVec;*/   //����ָ�����VCFʱ��������ÿ���洢��Ԫ��ָ�룬�Ա�ɾ��

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
    //���ķ���4������������40�����򷵻�0
    int IsFour(const char color, const int x, const int y);
    //˫�ķ���1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų������ͳ��������
    int IsDoubleFour(const int x, const int y);
    //��ĳ�����ϻ�������1�����򷵻�0
    int IsOpenThree(const char color, const int x, const int y, const int nDir);
    //��������1�����򷵻�0
    int IsOpenThree(const char color, const int x, const int y);
    //˫������1�����򷵻�0 (�ú������Ժ����ж�)���ڽ���˺���ǰӦ�ų�������������˫�ĵ����
    int IsDoubleThree(const int x, const int y);
    //���ַ���1�����򷵻�0 (�ú������Ժ����ж�)
    int IsFoul(const int x, const int y);

    //////�����㷨���ֺ���//////

    //��������5�����ַ���1�����򷵻�0
    int CheckMove(const int x, const int y);

    //���ķ���1�����򷵻�0������ĵ���x,y����
    int HaveFour(const char color,int &x, int &y);

/*    //�л�����VCF����1�����򷵻�0��VCF����˳�򼰵�����VCF��������(�赲�Է�ʱ��)
    int HaveOpenThree(const char color, vector<CPoint> &VCF);*/

    //����color��ɫ�����г��ĵ㣬�������أ���������ֵΪ���ĵ����
    //���л�������ƶԷ���������������ش˵㣬��ʱ��������ֵΪ2000
    int GetFourRushPoints(const char color, list<FourRush> &lstFourRush);

    //���color������VCF�����з���1�����򷵻�0��VCF������vcfList������
    int SearchVCF(const char color, const bool clean = false);
    int DoSearchVCF(const char color/*, list<FourRush> &vcfList*/);
private:
    void DoCleanVCF(const char color);
    bool CheckVcfList(const char color);
};
