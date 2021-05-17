#ifndef _CHECKERS_CONTROLLER_H_
#define _CHECKERS_CONTROLLER_H_

#include "IBoard.h"
#include "IController.h"

#include <memory>
#include <unordered_map>
#include <vector>

enum Direction {
    UP,
    DOWN
};

enum MoveType {
    INVALID,
    VALID,
    REQUIRED
};

struct Move {
    bool valid;
    MoveType type;
    ISquare *killed;
    ISquare *start;
    ISquare *end;

    Move() : valid(false), type(INVALID), killed(nullptr), start(nullptr), end(nullptr) {}
    Move(MoveType t, ISquare *st, ISquare *end) : valid(false), type(t), killed(nullptr), start(st), end(end) {}
};

class CheckersController : public IController {
public:
    CheckersController(IBoard &board);

    ~CheckersController() = default;
    CheckersController(const CheckersController &) = delete;
    CheckersController(CheckersController &&) = delete;
    CheckersController &operator=(const CheckersController &) = delete;
    CheckersController &operator=(CheckersController &&) = delete;

    void registerPlayer(std::shared_ptr<IPlayer> p) override;
    bool showMoves() override;
    bool prepMove(ISquare *source) override;
    bool doMove(ISquare *dest) override;
    void setup() override;

private:
    void squareDropped(ISquare *source, ISquare *dest);
    void nextPlayer();
    bool checkDirection(int srow, int drow);
    ISquare* getDiag(Position cur, int rowDir, int colDir);
    int getDirScalar();
    void findMoves(std::vector<ISquare*>& squares);
    void checkDiag(ISquare *square, int rowDir, int colDir, Move &m);
    bool checkRequired(std::vector<Move> moves);
    bool checkRequired(ISquare *source);
    std::unique_ptr<std::vector<ISquare*>> getSquares();
    bool chain(ISquare *source, ISquare *dest);

private:
    IBoard &m_board;
    std::shared_ptr<IPlayer> m_p1;
    std::shared_ptr<IPlayer> m_p2;
    Color m_curCol;
    std::unordered_map<Color, Direction> m_dir;
    std::shared_ptr<Move> m_move;
    std::vector<Move> m_moves;
    ISquare *m_prepped;
    bool m_chain;
};

#endif //_CHECKERS_CONTROLLER_H_
