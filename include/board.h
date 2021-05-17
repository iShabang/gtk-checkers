#ifndef _CHECKERS_BOARD_H_
#define _CHECKERS_BOARD_H_

#include "IBoard.h"
#include "ColorMapper.h"

#include <gtkmm/grid.h>
#include <gtkmm/drawingarea.h>

#include <memory>

class Board : public Gtk::Grid, public IBoard {
public:
    Board(ColorMapper &cm, Boundary b);

    virtual ~Board() = default;
    Board(const Board &) = delete;
    Board(Board &&) = delete;
    Board &operator=(const Board &) = delete;
    Board &operator=(Board &&) = delete;

private:
    void registerDrop(std::function<void(ISquare*, ISquare*)>);
    void registerClick(std::function<void(ISquare*)>);
    void setup(Color c1, Color c2);
    void move(Position source, Position dest);
    void remove(Position pos);
    ISquare* get(Position pos);
    bool inBounds(Position pos);
    Boundary getBoundary();

private:
    void drawPieces(int rowStart, int rowEnd, Color color);
    void deletePieces();
    void squareLoop(std::function<void(int row, int col)> f, int rStart = 0, int rEnd = 0);

    ColorMapper &m_cm;
    Boundary m_boundary;
};


#endif //_CHECKERS_BOARD_H_
