#ifndef ICHESSPLAYER_H
#define ICHESSPLAYER_H

#include <string>
#include "ichessboard.h"

class IChessPlayer
{
public:
    virtual ~IChessPlayer(){}
    virtual void Start(Chess assigned_chess) = 0;
    virtual void End(Chess winner_chess) = 0;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) = 0;
};

#endif // ICHESSPLAYER_H
