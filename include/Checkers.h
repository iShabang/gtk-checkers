#ifndef _CHECKERS_CHECKERS_H_
#define _CHECKERS_CHECKERS_H_

#include "IController.h"
#include "ISquare.h"
#include "IBoard.h"
#include "IGame.h"
#include "IFinish.h"

#include <unordered_map>
#include <functional>

enum State {
    IDLE,
    READY,
    WAITING,
    PREPPING,
    FINISHED
};

class Checkers : public IGame {
public:
    Checkers(IController &c, IBoard &b, IFinish &f);

    ~Checkers() = default;
    Checkers(const Checkers &) = delete;
    Checkers(Checkers &&) = delete;
    Checkers &operator=(const Checkers &) = delete;
    Checkers &operator=(Checkers &&) = delete;

    //EVENTS
    void setup() override;
    void start() override;
    void squareSelected(ISquare *sq);

private:
    std::unordered_map<State,std::function<void(ISquare*)>> m_selected;
    std::unordered_map<State,std::function<void()>> m_setup;
    std::unordered_map<State,std::function<void()>> m_start;
    IController &m_con;
    State m_state;
    ISquare *m_current;
    IFinish &m_finish;


//  State Functions
    void waitSelected(ISquare *sq);
    void prepSelected(ISquare *sq);
    void idleSetup();
    void readyStart();
};

#endif //_CHECKERS_CHECKERS_H_
