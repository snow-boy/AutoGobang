#include "chessplayer.h"
#include <QtGlobal>
#include <QString>

void ChessPlayer::Start(Chess assigned_chess)
{
    my_chess_ = assigned_chess;
}

void ChessPlayer::End(Chess winner_chess, const IChessboard *chess_board)
{

}

static void PlaceToAnEmptyPosition(const IChessboard *chess_board,
                                 int *x, int *y)
{
    for(int i = 0; i < chess_board->GetWidth(); ++i){
        for(int j = 0; j < chess_board->GetHeight(); ++j){
            if(chess_board->GetChess(i, j) == Chess::Empty){
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

void ChessPlayer::PlaceChess(const IChessboard *chess_board,
                             int *x, int *y,
                             std::string &word_say)
{
    int best_black_sum = -1;
    int best_black_x = 0;
    int best_black_y = 0;

    int best_white_sum = -1;
    int best_white_x = 0;
    int best_white_y = 0;

    // horizontal search
    for(int temp_y = 0; temp_y < chess_board->GetHeight(); ++temp_y)
    {
        int last_empty_x = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_x = 0; temp_x < chess_board->GetWidth(); ++temp_x){
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;
                last_empty_x = temp_x;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = last_empty_x;
                    best_black_y = temp_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = last_empty_x;
                    best_white_y = temp_y;
                }
            }
        }
    }

    // vertical search
    for(int temp_x = 0; temp_x < chess_board->GetWidth(); ++temp_x)
    {
        int last_empty_y = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_y = 0; temp_y < chess_board->GetHeight(); ++temp_y){
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;
                last_empty_y = temp_y;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x, temp_y - i) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = temp_x;
                    best_black_y = last_empty_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x, temp_y - i) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = temp_x;
                    best_white_y = last_empty_y;
                }
            }
        }
    }

    // blackslash search (\)
    for(int x_start = 0; x_start < chess_board->GetWidth(); ++x_start)
    {
        int last_empty_x = -1;
        int last_empty_y = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_y = 0, temp_x = x_start;
            (temp_y < chess_board->GetHeight())&&(temp_x < chess_board->GetWidth());
            ++temp_y, ++temp_x)
        {
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;

                last_empty_x = temp_x;
                last_empty_y = temp_y;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y - i) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = last_empty_x;
                    best_black_y = last_empty_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y - i) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = last_empty_x;
                    best_white_y = last_empty_y;
                }
            }
        }
    }

    for(int y_start = 1; y_start < chess_board->GetHeight(); ++y_start)
    {
        int last_empty_x = -1;
        int last_empty_y = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_y = y_start, temp_x = 0;
            (temp_y < chess_board->GetHeight())&&(temp_x < chess_board->GetWidth());
            ++temp_y, ++temp_x)
        {
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;

                last_empty_x = temp_x;
                last_empty_y = temp_y;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y - i) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = last_empty_x;
                    best_black_y = last_empty_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x - i, temp_y - i) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = last_empty_x;
                    best_white_y = last_empty_y;
                }
            }
        }
    }

    // slash search (/)
    for(int y_start = 0; y_start < chess_board->GetHeight(); ++y_start)
    {
        int last_empty_x = -1;
        int last_empty_y = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_y = y_start, temp_x = chess_board->GetWidth() - 1;
            (temp_y < chess_board->GetHeight())&&(temp_x >= 0);
            ++temp_y, --temp_x)
        {
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;

                last_empty_x = temp_x;
                last_empty_y = temp_y;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x + i, temp_y - i) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = last_empty_x;
                    best_black_y = last_empty_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x + i, temp_y - i) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = last_empty_x;
                    best_white_y = last_empty_y;
                }
            }
        }
    }

    for(int x_start = 1; x_start < chess_board->GetWidth(); ++x_start)
    {
        int last_empty_x = -1;
        int last_empty_y = -1;
        int black_pos_count = 0;
        int white_pos_count = 0;
        for(int temp_y = 0, temp_x = x_start;
            (temp_y < chess_board->GetHeight())&&(temp_x >= 0);
            ++temp_y, --temp_x)
        {
            Chess chess = chess_board->GetChess(temp_x, temp_y);
            if(chess == Chess::Black){
                white_pos_count = 0;
                black_pos_count ++;
            }
            else if(chess == Chess::White){
                black_pos_count = 0;
                white_pos_count ++;
            }
            else if(chess == Chess::Empty){
                black_pos_count ++;
                white_pos_count ++;

                last_empty_x = temp_x;
                last_empty_y = temp_y;
            }

            if(black_pos_count >= 5){
                int black_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x + i, temp_y - i) == Chess::Black){
                        black_chess_sum ++;
                    }
                }
                if(black_chess_sum > best_black_sum){
                    best_black_sum = black_chess_sum;
                    best_black_x = last_empty_x;
                    best_black_y = last_empty_y;
                }
            }

            if(white_pos_count >= 5){
                int white_chess_sum = 0;
                for(int i = 0; i < 5; ++i){
                    if(chess_board->GetChess(temp_x + i, temp_y - i) == Chess::White){
                        white_chess_sum ++;
                    }
                }
                if(white_chess_sum > best_white_sum){
                    best_white_sum = white_chess_sum;
                    best_white_x = last_empty_x;
                    best_white_y = last_empty_y;
                }
            }
        }
    }

    if((best_black_sum < 0) && (best_white_sum < 0)){
        word_say = "I have no chance to win...";
        PlaceToAnEmptyPosition(chess_board, x, y);
        return;
    }

    if(my_chess_ == Chess::Black){
        if(best_black_sum > best_white_sum){
            *x = best_black_x;
            *y = best_black_y;
            word_say = "Attack!!!";
        }
        else{
            *x = best_white_x;
            *y = best_white_y;
            word_say = "Defend...";
        }
    }
    else if(my_chess_ == Chess::White){
        if(best_black_sum < best_white_sum){
            *x = best_white_x;
            *y = best_white_y;
            word_say = "Attack!!!";
        }
        else{
            *x = best_black_x;
            *y = best_black_y;
            word_say = "Defend...";
        }
    }
}
