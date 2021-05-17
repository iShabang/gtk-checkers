#ifndef _CHECKERS_POSITION_H_
#define _CHECKERS_POSITION_H_

struct Position {
    int row;
    int col;
    Position(int r, int c) : row(r), col(c) {}

    friend bool operator==(const Position &a, const Position &b) {
        return a.row == b.row && a.col == b.col;
    }

    friend bool operator!=(const Position &a, const Position &b) {
        return a.row != b.row || a.col != b.col;
    }

};

#endif //_CHECKERS_POSITION_H_

