#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include "ichessplayer.h"

class ChessPlayer: public IChessPlayer
{
public:
    virtual void Start(Chess assigned_chess) override;
    virtual void End(Chess winner_chess, const IChessboard *chess_board) override;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) override;

private:
    Chess my_chess_;
};

#endif // CHESSPLAYER_H
