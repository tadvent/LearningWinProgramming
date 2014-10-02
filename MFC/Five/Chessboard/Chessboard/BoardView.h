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
    inline int SetLTPos(int X,int Y);  //无效参数时返回-1
    inline int SetSize(int CX,int CY); //无效参数时返回-1
    void PointToIdx(const CPoint &point, CPoint &idx);  //将鼠标点击的位置转换为棋盘坐标
    void IdxToPoint(const CPoint &idx, CPoint &point);
    void ShowFoul(CDC *pDC);//显示所有黑棋禁手点
    void ShowFoulOnly(CDC *pDC);//仅显示，不检测
    void ErasePoint(const CPoint &point,CDC *pDC);
    //void EraseAllFoul(CDC *pDC);
    void Clear(void);

private:
    void DrawStone(const CPoint &point,Color color,size_t num,CDC *pDC);
    void DrawCross(const CPoint &point,CDC *pDC);
    void DrawKeyPoint(const CPoint &point,COLORREF color,CDC *pDC);
    void DrawFoul(const CPoint &point,CDC *pDC);
};
