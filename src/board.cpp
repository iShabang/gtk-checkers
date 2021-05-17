#include "board.h"
#include "CheckerSquare.h"
#include "CheckerPiece.h"

#include <iostream>
#include <cmath>

Board::Board(ColorMapper &cm, Boundary b) : m_cm(cm), m_boundary(b) {
    for (int i=0; i<=m_boundary.row; i++) {
        insert_row(i);
    }

    for (int i=0; i<=m_boundary.col; i++) {
        insert_column(i);
    }

    Square *sq = nullptr;
    for (int i=0; i<=m_boundary.row; i++) {
        for (int j=0; j<=m_boundary.col; j++) {
            if ( (i+j) % 2 == 0 ) {
                //add black square
                sq = Gtk::make_managed<Square>(Position(i,j),m_cm);
                sq->set_size_request(100,100);
                sq->set_hexpand();
                sq->set_vexpand();
                attach(*sq,j,i);
                auto ctx = sq->get_style_context();
                ctx->add_class("black-square");
            }
        }
    }
    show_all();
}

void Board::squareLoop(std::function<void(int row, int col)> f, int rStart, int rEnd) {
    if (rStart == 0 && rEnd == 0) {
        rEnd = m_boundary.row;
    }
    for (int i=rStart; i<=rEnd; i++) {
        for (int j=0; j<=m_boundary.col; j++) {
            if ((i+j) % 2 == 0) {
                f(i,j);
            }
        }
    }
}

void Board::setup(Color c1, Color c2) {
    deletePieces();
    drawPieces(0,2,c1);
    drawPieces(m_boundary.row-2,m_boundary.row,c2);
}

void Board::deletePieces() {
    squareLoop([this](int row, int col){
            auto sq = dynamic_cast<ISquare*>(get_child_at(col,row));
            if (sq->hasPiece()) {
                sq->removePiece();
            }
            });
}

void Board::drawPieces(int rowStart, int rowEnd, Color color) {
    squareLoop([this,color](int row, int col){
                auto square = dynamic_cast<ISquare*>(get_child_at(col,row));
                auto p = std::make_shared<Piece>(color);
                square->setPiece(p);
            }, rowStart, rowEnd);
}

void Board::move(Position source, Position dest) {
    auto w1 = get_child_at(source.col, source.row);
    if (w1 == nullptr) {
        std::cerr << "No child at " << source.row << "," << source.col;
        return;
    }

    auto w2 = get_child_at(dest.col, dest.row);
    if (w2 == nullptr) {
        std::cerr << "No child at " << dest.row << "," << dest.col;
        return;
    }

    auto s1 = dynamic_cast<ISquare*>(w1);
    if (!s1->hasPiece()) {
        std::cerr << "No piece at source";
        return;
    }


    auto s2 = dynamic_cast<ISquare*>(w2);
    if (s2->hasPiece()) {
        std::cerr << "Piece at destination";
        return;
    }

    s2->setPiece(s1->removePiece());
    return;
}

void Board::remove(Position pos) {
    auto w = get_child_at(pos.col, pos.row);
    if (w == nullptr) {
        std::cerr << "No child at " << pos.row << "," << pos.col;
        return;
    }
    auto s = dynamic_cast<ISquare*>(w);
    s->removePiece();
    return;
}

void Board::registerDrop(std::function<void(ISquare*, ISquare*)> func) {
    squareLoop([this,func](int row, int col){
                auto s = dynamic_cast<Square*>(get_child_at(col,row));
                s->signalSquareDrop().connect(func);
            });
}

void Board::registerClick(std::function<void(ISquare*)> func) {
    squareLoop([this,func](int row, int col){
                auto s = dynamic_cast<Square*>(get_child_at(col,row));
                s->signalSquareClick().connect(func);
            });
}

ISquare* Board::get(Position pos) {
    auto s = dynamic_cast<Square*>(get_child_at(pos.col, pos.row));
    return s;
}

bool Board::inBounds(Position pos) {
    return (pos.row >= 0 && pos.row <= m_boundary.row) && (pos.col >= 0 && pos.col <= m_boundary.col); 
}

Boundary Board::getBoundary() {
    return m_boundary;
}
