#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QVector>
#include "ichessboard.h"

class ChessBoard: public IChessboard
{
public:
    ChessBoard(int width = 8, int height = 8);

    virtual int GetWidth() const override;
    virtual int GetHeight() const override;
    virtual Chess GetChess(int x, int y) const override;
    virtual Chess PlaceChess(int x, int y, Chess chess) override;

private:
    int width_;
    int height_;
    QVector<Chess> chess_tank_;
};

#endif // CHESSBOARD_H
