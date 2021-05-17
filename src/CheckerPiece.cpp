#include "CheckerPiece.h"

Piece::Piece(Color color, int type) : m_color(color), m_type(type) {
}

Color Piece::color() {
    return m_color;
}

int Piece::type() {
    return m_type;
}

void Piece::type(int t) {
    m_type = t;
}
