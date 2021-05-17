#ifndef _CHECKERS_IGAME_H_
#define _CHECKERS_IGAME_H_

class IGame {
public:
    virtual ~IGame() {}

    virtual void setup() = 0;
    virtual void start() = 0;
};

#endif //_CHECKERS_IGAME_H_
