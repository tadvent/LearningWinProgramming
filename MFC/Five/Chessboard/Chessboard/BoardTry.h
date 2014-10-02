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
    //int TryBack(void);  //无法回退时返回-1
    //void TryClear(void);
    /*int CheckFour(const CPoint &point);*/ //冲四返回4，双四或更多四返回44，否则返回0
};
