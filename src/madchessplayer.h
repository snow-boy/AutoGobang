#ifndef MADCHESSPLAYER_H
#define MADCHESSPLAYER_H

#include "ichessplayer.h"

class MadChessPlayer: public IChessPlayer
{
public:
    MadChessPlayer();

    // IChessPlayer interface
public:
    virtual void Start(Chess assigned_chess) override;
    virtual void End(Chess winner_chess) override;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) override;
};

#endif // MADCHESSPLAYER_H
