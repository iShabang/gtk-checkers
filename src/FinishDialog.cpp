#include "FinishDialog.h"

#include <gtkmm/label.h>

FinishDialog::FinishDialog() {
    add_button("Play Again", 0);
    add_button("Quit",1);
    auto label = Gtk::make_managed<Gtk::Label>("Game Over");
    get_content_area()->add(*label);
}
