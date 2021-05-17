#ifndef _CHECKERS_CHECKER_SQUARE_H_
#define _CHECKERS_CHECKER_SQUARE_H_

#include "IPiece.h"
#include "ISquare.h"
#include "ColorMapper.h"

#include <gtkmm/drawingarea.h>

class Square : public Gtk::DrawingArea, public ISquare{
public:
    Square(Position pos, ColorMapper &cm);

    virtual ~Square() = default;
    Square(const Square &) = delete;
    Square(Square &&) = delete;
    Square &operator=(const Square &) = delete;
    Square &operator=(Square &&) = delete;

    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    sigc::signal<void, Square *, Square *> signalSquareDrop();
    sigc::signal<void, Square *> signalSquareClick();

private:
    bool hasPiece();
    void setPiece(std::shared_ptr<IPiece> p);
    std::shared_ptr<IPiece> removePiece();
    const Position pos() const;
    const std::shared_ptr<IPiece> piece() const;
    void setMovable(bool value);
    void setPrepped(bool value);
    void setValid(bool value);
    bool movable();
    bool valid();
    bool prepped();


private:
    bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext> &ctx, int x, int y, guint time);
    bool on_button_press_event(GdkEventButton *button);
    bool on_button_release_event(GdkEventButton *button);
    void on_click();
    void drawBorder(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color);
    void drawPiece(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color, bool king);
    void setColor(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color);
    void drawKing(const Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int width, int height);

    static Glib::RefPtr<Gdk::Pixbuf> setupCrown();

private:
    sigc::signal<void, Square *, Square *> m_square_drop_signal;
    sigc::signal<void, Square *> m_square_click_signal;

private:
    std::shared_ptr<IPiece> m_piece;
    Position m_pos;
    ColorMapper &m_cm;
    bool m_movable;
    bool m_prepped;
    bool m_valid;
    bool m_pressed;
    static Glib::RefPtr<Gdk::Pixbuf> m_crown;
};

#endif //_CHECKERS_CHECKER_SQUARE_H_
