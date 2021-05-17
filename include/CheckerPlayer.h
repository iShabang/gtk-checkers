#ifndef _CHECKERS_CHECKER_PLAYER_H_
#define _CHECKERS_CHECKER_PLAYER_H_

#include "IPlayer.h"

class CheckerPlayer : public IPlayer {
public:
    CheckerPlayer(Color color);

    virtual ~CheckerPlayer() = default;
    CheckerPlayer(const CheckerPlayer  &) = delete;
    CheckerPlayer(CheckerPlayer  &&) = delete;
    CheckerPlayer &operator=(const CheckerPlayer  &) = delete;
    CheckerPlayer &operator=(CheckerPlayer  &&) = delete;

    Color color();

private:
    Color m_color;
};

#endif // _CHECKERS_CHECKER_PLAYER_H_
