#include "board.h"
#include "controller.h"
#include "colors.h"
#include "ColorMapper.h"
#include "CheckerPlayer.h"
#include "Checkers.h"
#include "GameManager.h"

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>

#include <iostream>
#include <memory>

void closeApp(Gtk::Window &w) {
    w.close();
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "checkers");

    try {
        Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();
        provider->load_from_path("../main.css");
        Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), provider,GTK_STYLE_PROVIDER_PRIORITY_USER);
    } catch (Gtk::CssProviderError &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    ColorMapper cm;
    Gdk::RGBA red;
    red.set_rgba(0.8,0,0,1);
    cm.registerColor(RED, red);
    Gdk::RGBA blue;
    blue.set_rgba(0,0,0.8,1);
    cm.registerColor(BLUE,blue);

    auto p1 = std::make_shared<CheckerPlayer>(RED);
    auto p2 = std::make_shared<CheckerPlayer>(BLUE);

    Boundary bounds(7,7);
    Board *b = Gtk::make_managed<Board>(cm,bounds);
    IBoard *ib = b;

    Gtk::Window window;
    window.add(*b);
    b->show();

    CheckersController controller(*ib);
    controller.registerPlayer(p1);
    controller.registerPlayer(p2);
    IController& ic = controller;

    GameManager gm;

    auto ch = std::make_unique<Checkers>(ic, *ib, gm);
    gm.setGame(std::move(ch));

    gm.signalQuit().connect([&window](){
            closeApp(window); });
    gm.play();

    app->run(window,argc,argv);
    return 0;
}
