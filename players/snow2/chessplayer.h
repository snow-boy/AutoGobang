#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include "ichessplayer.h"
#include <stdint.h>
#include <vector>

class ChessPlayer: public IChessPlayer
{
public:
    virtual void Start(Chess assigned_chess) override;
    virtual void End(Chess winner_chess, const IChessboard *chess_board) override;

    virtual void PlaceChess(const IChessboard *chess_board,
                            int *x, int *y,
                            std::string &word_say) override;

private:
    void calculateWeight(const IChessboard *chess_board,
                         int x, int y,
                         int64_t &win_weight,
                         Chess chess);

    void SearchContinues(std::vector<int> &chess_vector, Chess dst_chess,
                         int &left_empty, int &continue_count,
                         int &right_empty);

    int SearchPlaceTimeToWin(std::vector<int> &chess_vector, Chess dst_chess);


    Chess my_chess_;
};

#endif // CHESSPLAYER_H
