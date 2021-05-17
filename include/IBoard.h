#ifndef _CHECKERS_IBOARD_H_
#define _CHECKERS_IBOARD_H_

#include "ISquare.h"

#include <memory>
#include <functional>

struct Boundary {
    int row;
    int col;
    Boundary(int r, int c) : row(r), col(c) {}
};


class IBoard {
public:
    virtual ~IBoard() {}
    virtual void setup(Color c1, Color c2) = 0;
    virtual void move(Position source, Position dest) = 0;
    virtual void remove(Position pos) = 0;
    virtual ISquare* get(Position pos) = 0;
    virtual Boundary getBoundary() = 0;
    virtual void registerDrop(std::function<void(ISquare*, ISquare*)>) = 0;
    virtual void registerClick(std::function<void(ISquare*)>) = 0;
    virtual bool inBounds(Position pos) = 0;
}; 

#endif //_CHECKERS_IBOARD_H_
