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
//            else if(black_weight == best_black_weight)
//            {
//                if(rand() % 2 == 0){
//                    best_black_x = i;
//                    best_black_y = j;
//                }
//            }

            if(white_weight > best_white_weight)
            {
                best_white_weight = white_weight;
                best_white_x = i;
                best_white_y = j;
            }
//            else if(white_weight == best_white_weight)
//            {
//                if(rand() % 2 == 0){
//                    best_white_x = i;
//                    best_white_y = j;
//                }
//            }
        }
    }

    word_say = std::string("black weight: ") + std::to_string(best_black_weight) +
            std::string(", white weight: ") + std::to_string(best_white_weight);

    if(my_chess_ == Chess::Black)
    {
        if(best_black_weight > best_white_weight)
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
        if(best_black_weight < best_white_weight)
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

    std::vector<int> features;

    int v_continue = 0;
    int v_l_empty = 0;
    int v_r_empty = 0;
    int v_step_to_win = SearchPlaceTimeToWin(v_horizontal_line, chess);
    SearchContinues(v_horizontal_line, chess, v_l_empty, v_continue, v_r_empty);
    features.push_back(v_continue);
    features.push_back(v_l_empty);
    features.push_back(v_r_empty);
    features.push_back(v_step_to_win);

    int h_continue = 0;
    int h_l_empty = 0;
    int h_r_empty = 0;
    int h_step_to_win = SearchPlaceTimeToWin(v_vertical_line, chess);
    SearchContinues(v_vertical_line, chess, h_l_empty, h_continue, h_r_empty);
    features.push_back(h_continue);
    features.push_back(h_l_empty);
    features.push_back(h_r_empty);
    features.push_back(h_step_to_win);

    int s_continue = 0;
    int s_l_empty = 0;
    int s_r_empty = 0;
    int s_step_to_win = SearchPlaceTimeToWin(v_slash_line, chess);
    SearchContinues(v_slash_line, chess, s_l_empty, s_continue, s_r_empty);
    features.push_back(s_continue);
    features.push_back(s_l_empty);
    features.push_back(s_r_empty);
    features.push_back(s_step_to_win);

    int b_continue = 0;
    int b_l_empty = 0;
    int b_r_empty = 0;
    int b_step_to_win = SearchPlaceTimeToWin(v_backslash_line, chess);
    SearchContinues(v_backslash_line, chess, b_l_empty, b_continue, b_r_empty);
    features.push_back(b_continue);
    features.push_back(b_l_empty);
    features.push_back(b_r_empty);
    features.push_back(b_step_to_win);

    // 5 continues
    for(int i = 0; i < features.size(); i += 4)
    {
        if(features[i] >= 5)
        {
            win_weight = 100;
            return;
        }
    }

    // 4 continues
    for(int i = 0; i < features.size(); i += 4)
    {
        if(features[i] == 4 && features[i + 1] > 0 && features[i + 2] > 0)
        {
            win_weight = 90;
            return;
        }
    }

    int count4 = 0;
    for(int i = 0; i < features.size(); i += 4)
    {
        if(features[i] == 4 && features[3] <= 1)
        {
            count4 ++;
        }
        if(count4 >= 2)
        {
            win_weight = 90;
            return;
        }
    }

    // 3 continue
    int count32 = 0;
    for(int i = 0; i < features.size(); i += 4)
    {
        if(features[i] == 3 && features[i + 1] > 1 && features[i + 2] > 1)
        {
            count32++;
        }

        if((count32 > 0 && count4 > 0) || count32 > 1)
        {
            win_weight = 80;
            return;
        }
    }

    int count31 = 0;
    for(int i = 0; i < features.size(); i += 4)
    {
        if(features[i] == 3 && ((features[i + 1] > 1 && features[i + 2] > 2)||
                                (features[i + 1] > 2 && features[i + 2] > 1)))
        {
            count31 ++;
        }

        if(count31 > 1)
        {
            win_weight = 80;
            return;
        }
    }

    win_weight = count32 * 8 + count31*7;

    if(s_continue == 2 && s_l_empty > 2 && s_r_empty > 2 &&
            b_continue == 2 && b_l_empty > 2 && b_r_empty > 2)
    {
        win_weight += 10;
        return;
    }

    for(int i = 0; i < features.size(); i+=4)
    {
        if(features[i] == 2 && ((features[i + 1] > 2 && features[i + 2] > 1)||
                             (features[i + 1] > 1 && features[i + 2] > 2)))
        {
            win_weight += 5;
        }
    }

    for(int i = 0; i < features.size(); i+=4)
    {
        if(features[i] == 1 && ((features[i + 1] > 3 && features[i + 2] > 2)||
                             (features[i + 1] > 2 && features[i + 2] > 3)))
        {
            win_weight += 2;
        }
    }
}

void ChessPlayer::SearchContinues(std::vector<int> &chess_vector, Chess dst_chess,
                                  int &left_empty, int &continue_count, int &right_empty)
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
        if(chess_vector[4 + i] == static_cast<int>(Chess::Empty)){
            right_empty_count ++;
        }
        else{
            break;
        }
    }

    left_empty = left_empty_count;
    right_empty = right_empty_count;
    continue_count = left_continue_count + right_continue_count + 1;
}

int ChessPlayer::SearchPlaceTimeToWin(std::vector<int> &chess_vector, Chess dst_chess)
{
    int min_time = 5;
    for(int i = 0; i < 5; ++i)
    {
        int current_min = 5;
        for(int j = 0; j < 5; ++j)
        {
            if(i + j == 4)
            {
                current_min--;
                continue;
            }
            if((chess_vector[i + j] != static_cast<int>(dst_chess)) &&
                    (chess_vector[i + j] != static_cast<int>(Chess::Empty)))
            {
                current_min = 5;
                break;
            }

            if(chess_vector[i + j] == static_cast<int>(dst_chess))
            {
                current_min --;
            }
        }

        if(current_min < min_time)
        {
            min_time = current_min;
        }
    }

    return min_time;
}
