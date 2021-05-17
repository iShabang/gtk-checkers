#include "Checkers.h"

#include <iostream>

Checkers::Checkers(IController &c, IBoard &b, IFinish &f) : m_con(c), m_state(IDLE), m_current(nullptr),
    m_finish(f) {
    m_selected[WAITING] = [this](ISquare* sq){ waitSelected(sq); };
    m_selected[PREPPING] = [this](ISquare* sq){ prepSelected(sq); };
    m_setup[IDLE] = [this](){ idleSetup(); };
    m_start[READY] = [this](){ readyStart(); };

    b.registerClick([this](ISquare *sq){ squareSelected(sq); });
}

void Checkers::setup() {
    auto f = m_setup.find(m_state);
    if (f != m_setup.end() ) {
        f->second();
    }
}

void Checkers::start() {
    auto f = m_start.find(m_state);
    if (f != m_start.end()) {
        f->second();
    }
}

void Checkers::squareSelected(ISquare *sq) {
    auto f = m_selected.find(m_state);
    if (f != m_selected.end()) {
        f->second(sq);
    }
}

void Checkers::waitSelected(ISquare *sq) {
    if (m_con.prepMove(sq)) {
        m_current = sq;
        m_state = PREPPING;
    }
}

void Checkers::prepSelected(ISquare *sq) {
    if (sq->pos() == m_current->pos() || m_con.doMove(sq)) {
        m_state = WAITING;
        m_current = nullptr;
        if (!m_con.showMoves()){
            m_state = IDLE;
            m_finish.finished();
        }
    }
}


void Checkers::idleSetup() {
    m_con.setup();
    m_state = READY;
}

void Checkers::readyStart() {
    m_con.showMoves();
    m_state = WAITING;
}
