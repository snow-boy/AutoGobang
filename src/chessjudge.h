#ifndef CHESSJUDGE_H
#define CHESSJUDGE_H

#include <QVector>
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

    GameResult DoJudge(int last_x, int last_y,
                       QVector<QPoint> &cojoint_points);

private:
    GameResult VerticalJudge(int last_x, int last_y,
                             QVector<QPoint> &cojoint_points);

    GameResult HorizontalJudge(int last_x, int last_y,
                               QVector<QPoint> &cojoint_points);

    GameResult SlashJudge(int last_x, int last_y,
                          QVector<QPoint> &cojoint_points);

    GameResult BlashSlashJudge(int last_x, int last_y,
                               QVector<QPoint> &cojoint_points);

    IChessboard *chess_board_;
};

#endif // CHESSJUDGE_H
