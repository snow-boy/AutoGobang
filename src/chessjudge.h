#ifndef CHESSJUDGE_H
#define CHESSJUDGE_H

#include "ichessboard.h"

enum class GameResult
{
    Win,
    Failed,
    NoResult
};

class ChessJudge
{
public:
    ChessJudge(IChessboard *chess_board);

    GameResult DoJudge(int last_x, int last_y);

private:
    GameResult VerticalJudge(int last_x, int last_y);
    GameResult HorizontalJudge(int last_x, int last_y);
    GameResult SlashJudge(int last_x, int last_y);
    GameResult BlashSlashJudge(int last_x, int last_y);

    IChessboard *chess_board_;
};

#endif // CHESSJUDGE_H
