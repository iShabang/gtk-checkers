#ifndef _CHECKERS_IPIECE_H_
#define _CHECKERS_IPIECE_H_

#include "colors.h"

class IPiece {
public:
    virtual Color color() = 0;
    virtual int type() = 0;
    virtual void type(int) = 0;
    virtual ~IPiece() {}
};

#endif //_CHECKERS_IPIECE_H_



