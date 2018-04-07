#ifndef ICHESSPLAYER_H
#define ICHESSPLAYER_H

#include <string>
#include "ichessboard.h"

class IChessPlayer
{
public:
    virtual ~IChessPlayer(){}
    virtual void AssignChess(Chess chess) = 0;
    virtual void Start() = 0;
    virtual void End() = 0;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) = 0;
};

#endif // ICHESSPLAYER_H
