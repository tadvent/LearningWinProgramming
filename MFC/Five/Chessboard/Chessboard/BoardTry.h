#pragma once
#include "board.h"
#include "boardview.h"

class CBoardTry :
    public CBoard
{

public:
    CBoardTry(void);
    CBoardTry(const CBoard &bd);
    CBoardTry(const CBoardView &bdv);
    ~CBoardTry(void);

public:
    //void TryMove(const CPoint &point);
    //int TryBack(void);  //�޷�����ʱ����-1
    //void TryClear(void);
    /*int CheckFour(const CPoint &point);*/ //���ķ���4��˫�Ļ�����ķ���44�����򷵻�0
};
