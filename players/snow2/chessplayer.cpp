#include "chessplayer.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <QtDebug>
#include <QVector>

void ChessPlayer::Start(Chess assigned_chess)
{
    my_chess_ = assigned_chess;
    srand((int)time(0));
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
    int64_t best_black_weight = 0;
    int best_black_x = 0;
    int best_black_y = 0;
    PlaceToAnEmptyPosition(chess_board, &best_black_x, &best_black_y);

    int64_t best_white_weight = 0;
    int best_white_x = 0;
    int best_white_y = 0;
    PlaceToAnEmptyPosition(chess_board, &best_white_x, &best_white_y);

    for(int i = 0; i < chess_board->GetWidth(); ++i)
    {
        for(int j = 0; j < chess_board->GetHeight(); ++j)
        {
            if(chess_board->GetChess(i, j) != Chess::Empty){
                continue;
            }

            int64_t black_weight = 0;
            int64_t white_weight = 0;
            calculateWeight(chess_board, i, j, black_weight, Chess::Black);
            calculateWeight(chess_board, i, j, white_weight, Chess::White);

            if(black_weight > best_black_weight)
            {
                best_black_weight = black_weight;
                best_black_x = i;
                best_black_y = j;
            }
            else if(black_weight == best_black_weight)
            {
                if(rand() % 2 == 0){
                    best_black_x = i;
                    best_black_y = j;
                }
            }

            if(white_weight > best_white_weight)
            {
                best_white_weight = white_weight;
                best_white_x = i;
                best_white_y = j;
            }
            else if(white_weight == best_white_weight)
            {
                if(rand() % 2 == 0){
                    best_white_x = i;
                    best_white_y = j;
                }
            }
        }
    }

    word_say = std::string("black weight: ") + std::to_string(best_black_weight) +
            std::string(", white weight: ") + std::to_string(best_white_weight);

    if(my_chess_ == Chess::Black)
    {
        if(best_black_weight >= best_white_weight)
        {
            *x = best_black_x;
            *y = best_black_y;
            word_say += ", place black";
        }
        else
        {
            *x = best_white_x;
            *y = best_white_y;
            word_say += ", place white";
        }
    }
    else if(my_chess_ == Chess::White)
    {
        if(best_black_weight <= best_white_weight)
        {
            *x = best_white_x;
            *y = best_white_y;
            word_say += ", place white";
        }
        else
        {
            *x = best_black_x;
            *y = best_black_y;
            word_say += ", place black";
        }
    }

    word_say += std::string(", (") + std::to_string(*x) + std::string(",") +
            std::to_string(*y) + std::string(")");
}

void ChessPlayer::calculateWeight(const IChessboard *chess_board,
                                  int x, int y,
                                  int64_t &win_weight,
                                  Chess chess)
{
    win_weight = 0;
    if(chess_board->GetChess(x, y) != Chess::Empty){
        return;
    }

    std::vector<int> v_horizontal_line;
    std::vector<int> v_vertical_line;
    std::vector<int> v_backslash_line;
    std::vector<int> v_slash_line;
    for(int i = -4; i <= 4; ++i)
    {
        if(x + i < 0 || x + i >= chess_board->GetWidth())
        {
            v_horizontal_line.push_back(-1);
        }
        else
        {
            v_horizontal_line.push_back(static_cast<int>(chess_board->GetChess(x + i, y)));
        }

        if(y + i < 0 || y + i >= chess_board->GetHeight())
        {
            v_vertical_line.push_back(-1);
        }
        else
        {
            v_vertical_line.push_back(static_cast<int>(chess_board->GetChess(x, y + i)));
        }

        if(y + i < 0 || y + i >= chess_board->GetHeight() ||
                x + i < 0 || x + i >= chess_board->GetWidth())
        {
            v_backslash_line.push_back(-1);
        }
        else
        {
            v_backslash_line.push_back(static_cast<int>(chess_board->GetChess(x + i, y + i)));
        }

        if(y + i < 0 || y + i >= chess_board->GetHeight() ||
                x - i < 0 || x - i >= chess_board->GetWidth())
        {
            v_slash_line.push_back(-1);
        }
        else
        {
            v_slash_line.push_back(static_cast<int>(chess_board->GetChess(x - i, y + i)));
        }
    }

    win_weight = AssignWeight(v_horizontal_line, chess) +
                 AssignWeight(v_vertical_line, chess) +
                 AssignWeight(v_backslash_line, chess) +
                 AssignWeight(v_slash_line, chess);
}

int64_t ChessPlayer::AssignWeight(std::vector<int> &chess_vector, Chess dst_chess)
{
    assert(chess_vector.size() == 9);

    int left_continue_count = 0;
    for(int i = 1; i < 5; ++i){
        if(chess_vector[4 - i] == static_cast<int>(dst_chess)){
            left_continue_count ++;
        }
        else{
            break;
        }
    }

    int left_empty_count = 0;
    for(int i = left_continue_count + 1; i < 5; ++i)
    {
        if(chess_vector[4 - i] == static_cast<int>(Chess::Empty)){
            left_empty_count ++;
        }
        else{
            break;
        }
    }

    int right_continue_count = 0;
    for(int i = 1; i < 5; ++i){
        if(chess_vector[4 + i] == static_cast<int>(dst_chess)){
            right_continue_count ++;
        }
        else{
            break;
        }
    }

    int right_empty_count = 0;
    for(int i = right_continue_count + 1; i < 5; ++i)
    {
        if(chess_vector[4 - i] == static_cast<int>(Chess::Empty)){
            right_empty_count ++;
        }
        else{
            break;
        }
    }

    if(left_continue_count + left_empty_count +
            right_continue_count + right_empty_count + 1 < 5)
    {
        return 0;
    }

    int continue_count = left_continue_count + right_continue_count + 1;
    if(continue_count >= 5){
        return 10000000;
    }

    if(continue_count == 4){
        int64_t weight = 100000;
        if(left_empty_count > 0){
            weight += 100000;
        }

        if(right_empty_count > 0){
            weight += 100000;
        }

        return weight;
    }

    if(continue_count == 3){
        int64_t weight = 1000;
        if(left_empty_count > 0){
            weight += 1000;
        }

        if(right_empty_count > 0){
            weight += 1000;
        }

        return weight;
    }

    if(continue_count == 2){
        int64_t weight = 10;
        if(left_empty_count > 0){
            weight += 10;
        }

        if(right_empty_count > 0){
            weight += 10;
        }

        return weight;
    }

    return 0;
}
