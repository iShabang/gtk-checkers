#ifndef _CHECKERS_GAME_MANAGER_H_
#define _CHECKERS_GAME_MANAGER_H_

#include "IFinish.h"
#include "IGame.h"
#include "FinishDialog.h"

#include <memory>

class GameManager : public IFinish {
public:
    GameManager();

    ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager(GameManager &&) = delete;
    GameManager &operator=(const GameManager &) = delete;
    GameManager &operator=(GameManager &&) = delete;

    void finished() override;
    
    void setGame(std::unique_ptr<IGame> &&g);
    bool play();
    sigc::signal<void> signalQuit();

private:
    void onPlayAgain(int response);

private:
    std::unique_ptr<IGame> m_game;
    std::unique_ptr<FinishDialog> m_dialog;
    sigc::signal<void> m_signal_quit;
};

#endif //_CHECKERS_GAME_MANAGER_H_
