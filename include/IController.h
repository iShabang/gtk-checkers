#ifndef _CHECKERS_ICONTROLLER_H_
#define _CHECKERS_ICONTROLLER_H_

#include "IPlayer.h"
#include "ISquare.h"

#include <memory>

class IController {
public:
    virtual ~IController() {}

    virtual void registerPlayer(std::shared_ptr<IPlayer> player) = 0;
    virtual void setup() = 0;
    virtual bool showMoves() = 0; 
    virtual bool prepMove(ISquare *source) = 0;
    virtual bool doMove(ISquare *dest) = 0;
};

#endif //_CHECKERS_ICONTROLLER_H_
