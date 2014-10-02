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
    int CheckMove(const CPoint &point); //����������ӷ���-1�����򷵻�0
    inline bool IsOutBoard(const CPoint &point);
    inline bool IsOutBoard(const int x,const int y);
    void DoMove(const CPoint &point);
    int BackMove(void); //�޷�����ʱ����-1
    int CheckFive(const CPoint &point,Color color=Empty); //��������5����������6�����򷵻�0������˺���ǰ��֤��Ч�����ѱ��ų�
    void TryMove(const CPoint &point,Color color=Empty);
    int TryBack(void);  //�޷�����ʱ����-1
    void TryClear(void);
    int CheckFour(const CPoint &point,Color color=Empty);//����˺���ǰҪ��֤�����ͳ�����������ѱ��ų������ķ���4��˫�ķ���44�����򷵻�0
    int CheckThree(const CPoint &point,Color color=Empty);
    int CheckFoul(const CPoint &point);//����������6��˫�ķ���44��˫������33�������������0
    //void MarkFoul(void);//��ForbidRuleΪflase�򲻽����κβ���
    int SearchVCF(Color color=Empty);

    void Clear(void);

private:
    CPoint FindFirstEmpty(const CPoint &center,Color color,const CPoint &direction, const int maxstep);
    int CheckOpenNum(const CPoint &center, const CPoint &direction, Color color);   //�����Ǽ���
    void ClearFoulPoints(void);
    int DoSearchVCF(Color color=Empty);
};
