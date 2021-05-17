#include "controller.h"
#include "CheckerType.h"

#include <iostream>


CheckersController::CheckersController(IBoard &board) : m_board(board) {
}

void CheckersController::setup() {
    if (m_p1.get() != nullptr && m_p2.get() != nullptr) {
        m_board.setup(m_p1->color(), m_p2->color());
    }
}

void CheckersController::registerPlayer(std::shared_ptr<IPlayer> p) {
    if (m_p1.get() == nullptr) {
        m_p1 = p;
        m_curCol = m_p1->color();
        m_dir[m_p1->color()] = DOWN;
        return;
    }

    if (m_p2.get() == nullptr) {
        m_p2 = p;
        m_dir[m_p2->color()] = UP;
        return;
    }

    std::cerr << "CheckersController: Too many players registered";
}

void CheckersController::squareDropped(ISquare *source, ISquare *dest) {
    if (true) {
        m_board.move(source->pos(), dest->pos());
        nextPlayer();
        m_move.reset();
    }
}

void CheckersController::nextPlayer() {
    if (m_curCol == m_p1->color()) {
        m_curCol = m_p2->color();
        return;
    }
    m_curCol = m_p1->color();
}

ISquare* CheckersController::getDiag(Position cur, int rowDir, int colDir) {
    Position pos(cur.row + rowDir, cur.col + colDir);
    if (m_board.inBounds(pos)) {
        ISquare *square = m_board.get(pos);
        return square;
    }
    return nullptr;
}

void CheckersController::findMoves(std::vector<ISquare*>& squares) {
    m_moves.clear();
    auto process = [this](ISquare *prev, ISquare *cur, int rowDir, int colDir) {
        if (prev != nullptr && cur != nullptr) {
            Move m;
            m.start = prev;
            checkDiag(cur, rowDir, colDir, m);
            if (m.type > INVALID) {
                m_moves.push_back(m);
            }
        }
    };

    for (ISquare *sq : squares) {
        int rowDir = getDirScalar();
        auto left = getDiag(sq->pos(),rowDir, -1);
        auto right = getDiag(sq->pos(),rowDir, 1);
        process(sq,left,rowDir,-1);
        process(sq,right,rowDir,1);
        if (sq->hasPiece() && sq->piece()->type() == KING) {
            rowDir = -rowDir;
            auto botLeft = getDiag(sq->pos(), rowDir, -1);
            auto botRight = getDiag(sq->pos(), rowDir, 1);
            process(sq,botLeft,rowDir,-1);
            process(sq,botRight,rowDir,1);
        }
    }

    if (checkRequired(m_moves)) {
        auto i = m_moves.begin();
        while (i != m_moves.end()) {
            if (i->type != REQUIRED) {
                i = m_moves.erase(i);
            } else {
                ++i;
            }
        }
    }
}

int CheckersController::getDirScalar() {
    return m_dir[m_curCol] == UP ? -1 : 1;
}

void CheckersController::checkDiag(ISquare *square, int rowDir, int colDir, Move &m) {
    if (!square->hasPiece()) {
        m.type = VALID;
        m.end = square;
        return;
    }

    if (square->piece()->color() != m_curCol) {
        auto next = getDiag(square->pos(), rowDir, colDir);
        if (next != nullptr && !next->hasPiece()) {
            m.type = REQUIRED;
            m.killed = square;
            m.end = next;
            return;
        }
    }

    m.type = INVALID;
    return;
}

bool CheckersController::showMoves() {
    if (!m_chain) {
        auto squares = getSquares();
        findMoves(*squares.get());
    }
    if (m_moves.empty()) {
        return false;
    }
    bool required = checkRequired(m_moves);
    for (auto &&m : m_moves) {
        if (m.type == REQUIRED || (!required && m.type == VALID) ) {
            m.start->setMovable(true);
        }
    }
    return true;
}

bool CheckersController::checkRequired(std::vector<Move> moves) {
    for (Move &m : moves) {
        if (m.type == REQUIRED) {
            return true;
        }
    }
    return false;
}

bool CheckersController::checkRequired(ISquare *source) {
    for (auto &&m : m_moves) {
        if (m.start->pos() == source->pos() && m.type == REQUIRED) {
            return true;
        }
    }
    return false;
}

bool CheckersController::prepMove(ISquare *source) {
    bool prepped = false;
    for (auto &&m : m_moves) {
        if (m.start->pos() == source->pos()) {
            m_prepped = source;
            prepped = true;
            m.start->setMovable(false);
            m.start->setPrepped(true);
            m.end->setValid(true);
        }
    }
    return prepped;
}

bool CheckersController::doMove(ISquare *dest) {
    if (m_prepped == nullptr) {
        return false;
    }

    //Find the move
    Move *move = nullptr;
    for (auto &&m : m_moves) {
        if (m.start->pos() == m_prepped->pos() && m.end->pos() == dest->pos() && m.type > INVALID) {
            move = &m;
            break;
        }
    }
    if (move == nullptr) {
        return false;
    }

    Boundary bounds = m_board.getBoundary();
    int row = move->end->pos().row;
    int rowBoundary = m_dir[m_curCol] == UP ? 0 : bounds.row;
    if (row == rowBoundary) {
        move->start->piece()->type(KING);
    }

    m_board.move(move->start->pos(), move->end->pos());
    bool kill = false;
    if (move->killed != nullptr) {
        kill = true;
        m_board.remove(move->killed->pos());
    }
    for (auto &&m : m_moves) {
        m.start->setMovable(false);
        m.start->setPrepped(false);
        m.end->setValid(false);
    }
    m_prepped = nullptr;
    m_chain = false;
    ISquare *source = move->start;
    m_moves.clear();
    if (!kill || !chain(source,dest)) {
        nextPlayer();
    }
    return true;
}

std::unique_ptr<std::vector<ISquare*>> CheckersController::getSquares() {

    std::unique_ptr<std::vector<ISquare*>> squares = std::make_unique<std::vector<ISquare*>>();
    Position p(0,0);
    Boundary b = m_board.getBoundary();
    for (;p.row<=b.row; p.row++) {
        for (p.col=0; p.col<=b.col; p.col++) {
            ISquare *s = m_board.get(p);
            if (s != nullptr) {
                s->setMovable(false);
                s->setPrepped(false);
                s->setValid(false);
                if (s->hasPiece() && s->piece()->color() == m_curCol) {
                    squares->push_back(s);
                }
            } 
        }
    }
    return squares;
}

bool CheckersController::chain(ISquare *source, ISquare *dest) {
    int colDir = dest->pos().col - source->pos().col > 0 ? 1 : -1;
    int rowDir = dest->pos().row - source->pos().row > 0 ? 1 : -1;
    auto diag = getDiag(dest->pos(), rowDir, colDir);
    Move m;
    if (diag != nullptr) {
        checkDiag(diag,rowDir,colDir,m);
    }
    return m.type == REQUIRED;
}
