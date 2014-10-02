#pragma once
#include "Board.h"

class CBoardView :
    public CBoard
{
private:
    CPoint LeftTopPos;
    CSize Size;
    bool FoulState[BOARD_SIZE][BOARD_SIZE];

public:
    CBoardView(void);
    ~CBoardView(void);

public:
    void DoMove(const CPoint &point, CDC *pDC);
    int BackMove(CDC *pDC);
    void Show(CDC *pDC);
    inline int SetLTPos(int X,int Y);  //��Ч����ʱ����-1
    inline int SetSize(int CX,int CY); //��Ч����ʱ����-1
    void PointToIdx(const CPoint &point, CPoint &idx);  //���������λ��ת��Ϊ��������
    void IdxToPoint(const CPoint &idx, CPoint &point);
    void ShowFoul(CDC *pDC);//��ʾ���к�����ֵ�
    void ShowFoulOnly(CDC *pDC);//����ʾ�������
    void ErasePoint(const CPoint &point,CDC *pDC);
    //void EraseAllFoul(CDC *pDC);
    void Clear(void);

private:
    void DrawStone(const CPoint &point,Color color,size_t num,CDC *pDC);
    void DrawCross(const CPoint &point,CDC *pDC);
    void DrawKeyPoint(const CPoint &point,COLORREF color,CDC *pDC);
    void DrawFoul(const CPoint &point,CDC *pDC);
};
