#pragma once
#include "board.h"

class CBoardView :
    public CBoard
{
    //���졢����
public:
    CBoardView(void);
    ~CBoardView(void);
    void Clear(void);

    //���ݳ�Ա
private:
    CPoint LeftTopPos;
    CSize Size;
    bool Foul[BOARD_SIZE+2][BOARD_SIZE+2];
    bool IsFoulChanged[BOARD_SIZE+2][BOARD_SIZE+2];

    //��Ա����
public:
    inline int SetLTPos(int X,int Y);  //�����������Ͻ�λ�ã���Ч����ʱ����-1
    inline int SetSize(int CX,int CY); //�������̳ߴ磻��Ч����ʱ����-1
    CRect IdxToRect(const CPoint &idx);
    void PointToIdx(const CPoint &point, CPoint &idx);  //���������λ��ת��Ϊ��������
    void IdxToPoint(const CPoint &idx, CPoint &point);
    void Show(CDC *pDC);    //��ʾ���̡����Ӽ����ֱ��
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
