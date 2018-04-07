#ifndef MADCHESSPLAYER_H
#define MADCHESSPLAYER_H

#include "ichessplayer.h"

class MadChessPlayer: public IChessPlayer
{
public:
    MadChessPlayer();

    // IChessPlayer interface
public:
    virtual void AssignChess(Chess chess) override;
    virtual void Start() override;
    virtual void End() override;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) override;
};

#endif // MADCHESSPLAYER_H
