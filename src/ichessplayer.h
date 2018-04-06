#ifndef ICHESSPLAYER_H
#define ICHESSPLAYER_H

#include "ichessboard.h"

class IChessPlayer
{
public:
    virtual void AssignChess(Chess chess) = 0;
    virtual void Start() = 0;
    virtual void End() = 0;
    virtual void PlaceChess(const IChessboard *chess_board, int *x, int *y) = 0;
};

#endif // ICHESSPLAYER_H
