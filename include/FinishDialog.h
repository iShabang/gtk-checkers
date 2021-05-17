#ifndef _CHECKERS_FINISH_DIALOG_H_
#define _CHECKERS_FINISH_DIALOG_H_

#include "IFinish.h"

#include <gtkmm/dialog.h>

class FinishDialog : public Gtk::Dialog {
public:
    FinishDialog();

    virtual ~FinishDialog() = default;
    FinishDialog(const FinishDialog &) = delete;
    FinishDialog(FinishDialog &&) = delete;
    FinishDialog &operator=(const FinishDialog &) = delete;
    FinishDialog &operator=(FinishDialog &&) = delete;

};

#endif //_CHECKERS_FINISH_DIALOG_H_
