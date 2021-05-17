#ifndef _CHECKERS_IPLAYER_H_
#define _CHECKERS_IPLAYER_H_

#include "colors.h"

class IPlayer {
public:
    virtual Color color() = 0;  
};

#endif //_CHECKERS_IPLAYER_H_
