#include "GameManager.h"

#include <gtkmm/application.h>

GameManager::GameManager() : m_game(nullptr), m_dialog(nullptr) {}

void GameManager::finished() {
    m_dialog = std::make_unique<FinishDialog>();
    m_dialog->signal_response().connect(sigc::mem_fun(*this, &GameManager::onPlayAgain));
    m_dialog->show_all();
}

void GameManager::onPlayAgain(int response) {
    m_dialog.reset(nullptr);
    if (response == 0) {
        m_game->setup();
        m_game->start();
        return;
    }

    if (response == 1) {
        m_signal_quit.emit();
        return;
    }
}

bool GameManager::play() {
    if (m_game.get() != nullptr) {
        m_game->setup();
        m_game->start();
        return true;
    }
    return false;
}

void GameManager::setGame(std::unique_ptr<IGame> &&g) {
    m_game.reset(g.release());
}

sigc::signal<void> GameManager::signalQuit() {
    return m_signal_quit;
}
