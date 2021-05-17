#ifndef _CHECKERS_CHECKER_PIECE_H_
#define _CHECKERS_CHECKER_PIECE_H_

#include "IPiece.h"

class Piece : public IPiece {
public:
    Piece(Color color, int type = 0);
    ~Piece() = default;

    Piece(const Piece &) = delete;
    Piece(Piece &&) = delete;
    Piece &operator=(const Piece &) = delete;
    Piece &operator=(Piece &&) = delete;

    Color color();
    int type();
    void type(int t);

private:
    Color m_color;
    int m_type;
};

#endif //_CHECKERS_CHECKER_PIECE_H_
