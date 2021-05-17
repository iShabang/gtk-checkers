#include "CheckerSquare.h"
#include "CheckerType.h"

#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <iostream>

Square::Square(Position pos, ColorMapper &cm) : m_pos(pos), m_cm(cm), m_movable(false), m_prepped(false), m_valid(false), m_pressed(false) {
    std::vector<Gtk::TargetEntry> targets;
    targets.push_back(Gtk::TargetEntry("square"));
    Gdk::EventMask events = get_events();
    events |= Gdk::BUTTON_PRESS_MASK;
    events |= Gdk::BUTTON_RELEASE_MASK;
    set_events(events);
    //drag_source_set(targets);
    //drag_dest_set(targets);

    if (m_getCrown) {
        m_crown = setupCrown();
    }
}

bool Square::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    auto allo = get_allocation();
    int width = allo.get_width();
    int height = allo.get_height();

    //draw background
    auto sctx = get_style_context();
    sctx->render_background(cr,0,0,width,height);
    cr->fill();

    cr->set_source_rgba(1,1,1,1);
    cr->set_line_width(2);

    //draw piece
    if (m_piece.get() != nullptr) {
        drawPiece(cr, m_cm.getColor(m_piece->color()), m_piece->type() == KING);
    }

    if (m_movable) {
        Gdk::RGBA moveColor;
        moveColor.set_rgba(1,0.98,0.2,1);
        drawBorder(cr, moveColor);
    }

    if (m_prepped) {
        Gdk::RGBA prepColor;
        prepColor.set_rgba(0.87,0.2,1,1);
        drawBorder(cr, prepColor);
    }

    if (m_valid) {
        Gdk::RGBA validColor;
        validColor.set_rgba(0.09,0.94,0.33,1);
        drawBorder(cr, validColor);
    }

    return true;
}

void Square::drawBorder(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color) {
    auto allo = get_allocation();
    int width = allo.get_width();
    int height = allo.get_height();
    cr->save();
    setColor(cr, color);
    cr->set_line_width(10);
    cr->move_to(0,0);
    cr->line_to(width,0);
    cr->line_to(width,height);
    cr->line_to(0,height);
    cr->line_to(0,0);
    cr->stroke();
    cr->restore();
}

void Square::drawPiece(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color, bool king) {
    auto allo = get_allocation();
    int width = allo.get_width();
    int height = allo.get_height();
    cr->save();
    Gdk::RGBA pieceColor = m_cm.getColor(m_piece->color());
    setColor(cr, color);
    double radius = width/5;
    cr->arc(width/2,height/2,radius,0, 2.0*M_PI);
    cr->fill_preserve();
    cr->restore();
    cr->stroke();

    if (king) {
        double kingSize = radius * 1.5;
        int kingOffset = kingSize / 2;
        drawKing(cr, width/2 - kingOffset, height/2 - kingOffset, kingSize, kingSize);
    }
}

void Square::drawKing(const Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int width, int height) {
    if (m_crown.get() == nullptr) {
        return;
    }
    if (m_crown->get_width() != width) {
        m_crown = m_crown->scale_simple(width, height, Gdk::INTERP_BILINEAR);
    }
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr,m_crown,x,y);
    cr->rectangle(x,y,width,height);
    cr->fill();
    cr->restore();
}

void Square::setColor(const Cairo::RefPtr<Cairo::Context> &cr, Gdk::RGBA color) {
    cr->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
}

bool Square::hasPiece() {
    return m_piece.get() != nullptr;
}

void Square::setPiece(std::shared_ptr<IPiece> p) {
    m_piece = p;
    queue_draw();
}

std::shared_ptr<IPiece> Square::removePiece() {
    std::shared_ptr<IPiece> t = m_piece;
    m_piece.reset();
    m_piece = nullptr;
    queue_draw();
    return t;
}

const std::shared_ptr<IPiece> Square::piece() const {
    return m_piece;
}

sigc::signal<void, Square *, Square *> Square::signalSquareDrop() {
    return m_square_drop_signal;
}

sigc::signal<void, Square *> Square::signalSquareClick() {
    return m_square_click_signal;
}

bool Square::on_button_press_event(GdkEventButton *) {
    m_pressed = true;
    return true;
}

bool Square::on_button_release_event(GdkEventButton *b) {
    auto a = get_allocation();
    int w = a.get_width();
    int h = a.get_height();
    if ((b->x < 0 || b->x > w) || (b->y < 0 || b->y > h)) {
        m_pressed = false;
        return false;
    }

    if (m_pressed) {
        m_square_click_signal.emit(this);
    }

    m_pressed = false;
    return true;
}

bool Square::on_drag_drop(const Glib::RefPtr<Gdk::DragContext> &ctx, int, int, guint) {
    auto w = drag_get_source_widget(ctx);
    if (w == nullptr) return false;
    try {
        auto s = dynamic_cast<Square*>(w);
        m_square_drop_signal.emit(s,this);
        return true;
    } catch (std::bad_cast &e) {
        std::cerr << "Square: on_drag_drop: " << e.what();
        return false;
    }
}

const Position Square::pos() const { return m_pos; }

void Square::setMovable(bool value) {
    m_movable = value;
    queue_draw();
}

void Square::setPrepped(bool value) {
    m_prepped = value;
    queue_draw();
}

void Square::setValid(bool value) {
    m_valid = value;
    queue_draw();
}

bool Square::movable() {
    return m_movable;
}

bool Square::valid() {
    return m_valid;
}

bool Square::prepped() {
    return m_prepped;
}

Glib::RefPtr<Gdk::Pixbuf> Square::m_crown = Glib::RefPtr<Gdk::Pixbuf>(nullptr);

bool Square::m_getCrown = true;

Glib::RefPtr<Gdk::Pixbuf> Square::setupCrown() {
    try {
        auto pb = Gdk::Pixbuf::create_from_file("../crown.png");
        return pb;
    } catch (Glib::FileError &e) {
        std::cerr << "Failed to open crown file: " << e.what();
    } catch (Gdk::PixbufError &e) {
        std::cerr << "Failed to open crown file: " << e.what();
    }
    m_getCrown = false;
    return Glib::RefPtr<Gdk::Pixbuf>(nullptr);
}

