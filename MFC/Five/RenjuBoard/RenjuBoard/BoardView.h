#pragma once
#include "board.h"

class CBoardView :
    public CBoard
{
    //构造、析构
public:
    CBoardView(void);
    ~CBoardView(void);
    void Clear(void);

    //数据成员
private:
    CPoint LeftTopPos;
    CSize Size;
    bool Foul[BOARD_SIZE+2][BOARD_SIZE+2];
    bool IsFoulChanged[BOARD_SIZE+2][BOARD_SIZE+2];

    //成员函数
public:
    inline int SetLTPos(int X,int Y);  //设置棋盘左上角位置；无效参数时返回-1
    inline int SetSize(int CX,int CY); //设置棋盘尺寸；无效参数时返回-1
    CRect IdxToRect(const CPoint &idx);
    void PointToIdx(const CPoint &point, CPoint &idx);  //将鼠标点击的位置转换为棋盘坐标
    void IdxToPoint(const CPoint &idx, CPoint &point);
    void Show(CDC *pDC);    //显示棋盘、棋子及禁手标记
    void ShowFoul(CDC *pDC);
    int DoMove(const CPoint &point, CDC *pDC);
    int BackMove(CDC *pDC);
    int ForwardMove(CDC *pDC);

private:
    void DrawStone(const CPoint &point,/*char color,*/size_t num,CDC *pDC);
    void DrawCross(const CPoint &point, CDC *pDC, COLORREF clr=RGB(255,0,0));
    void DrawKeyPoint(const CPoint &point,COLORREF color,CDC *pDC);
    //void DrawFoul(const CPoint &point,CDC *pDC);
    void MarkFoul(void);
};
