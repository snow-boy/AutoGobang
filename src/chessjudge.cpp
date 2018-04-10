#include "chessjudge.h"
#include <assert.h>

ChessJudge::ChessJudge(IChessboard *chess_board):
    chess_board_(chess_board)
{

}

GameResult ChessJudge::DoJudge(int last_x, int last_y)
{
    QVector<QPoint> cojoint_points;
    return DoJudge(last_x, last_y, cojoint_points);
}

GameResult ChessJudge::DoJudge(int last_x, int last_y, QVector<QPoint> &cojoint_points)
{
    cojoint_points.clear();
    GameResult result = VerticalJudge(last_x, last_y, cojoint_points);
    if(result != GameResult::NoResult){
        return result;
    }

    cojoint_points.clear();
    result = HorizontalJudge(last_x, last_y, cojoint_points);
    if(result != GameResult::NoResult){
        return result;
    }

    cojoint_points.clear();
    result = SlashJudge(last_x, last_y, cojoint_points);
    if(result != GameResult::NoResult){
        return result;
    }

    cojoint_points.clear();
    result = BlackSlashJudge(last_x, last_y, cojoint_points);
    if(result != GameResult::NoResult){
        return result;
    }

    cojoint_points.clear();
    return GameResult::NoResult;
}

GameResult ChessJudge::VerticalJudge(int last_x, int last_y, QVector<QPoint> &cojoint_points)
{
    Chess chess = chess_board_->GetChess(last_x, last_y);
    assert(chess != Chess::Empty);

    int cojoint_count = 1;
    cojoint_points.append(QPoint(last_x, last_y));

    for(int i = last_y - 1; i >= 0; i--){
        if(chess_board_->GetChess(last_x, i) == chess){
            cojoint_points.append(QPoint(last_x, i));
            cojoint_count++;
        }
        else{
            break;
        }
    }
    for(int i = last_y + 1; i < chess_board_->GetHeight(); i++){
        if(chess_board_->GetChess(last_x, i) == chess){
            cojoint_points.append(QPoint(last_x, i));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    GameResult result = GameResult::NoResult;
    if(cojoint_count >= 5){
        result = GameResult::Win;
    }

    return result;
}

GameResult ChessJudge::HorizontalJudge(int last_x, int last_y, QVector<QPoint> &cojoint_points)
{
    Chess chess = chess_board_->GetChess(last_x, last_y);
    assert(chess != Chess::Empty);

    int cojoint_count = 1;
    cojoint_points.append(QPoint(last_x, last_y));

    for(int i = last_x - 1; i >= 0; i--){
        if(chess_board_->GetChess(i, last_y) == chess){
            cojoint_points.append(QPoint(i, last_y));
            cojoint_count++;
        }
        else{
            break;
        }
    }
    for(int i = last_x + 1; i < chess_board_->GetWidth(); ++i){
        if(chess_board_->GetChess(i, last_y) == chess){
            cojoint_points.append(QPoint(i, last_y));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    GameResult result = GameResult::NoResult;
    if(cojoint_count >= 5){
        result = GameResult::Win;
    }

    return result;
}

GameResult ChessJudge::SlashJudge(int last_x, int last_y, QVector<QPoint> &cojoint_points)
{
    Chess chess = chess_board_->GetChess(last_x, last_y);
    assert(chess != Chess::Empty);

    int cojoint_count = 1;
    cojoint_points.append(QPoint(last_x, last_y));

    for(int i = last_x + 1, j = last_y - 1;
        (i < chess_board_->GetWidth())&&(j >= 0);
        i++, j--)
    {
        if(chess_board_->GetChess(i, j) == chess){
            cojoint_points.append(QPoint(i, j));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    for(int i = last_x - 1, j = last_y + 1;
        (i >= 0)&&(j < chess_board_->GetHeight());
        --i, ++j)
    {
        if(chess_board_->GetChess(i, j) == chess){
            cojoint_points.append(QPoint(i, j));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    GameResult result = GameResult::NoResult;
    if(cojoint_count >= 5){
        result = GameResult::Win;
    }

    return result;
}

GameResult ChessJudge::BlackSlashJudge(int last_x, int last_y, QVector<QPoint> &cojoint_points)
{
    Chess chess = chess_board_->GetChess(last_x, last_y);
    assert(chess != Chess::Empty);

    int cojoint_count = 1;
    cojoint_points.append(QPoint(last_x, last_y));

    for(int i = last_x + 1, j = last_y + 1;
        (i < chess_board_->GetWidth())&&(j < chess_board_->GetHeight());
        ++i, ++j)
    {
        if(chess_board_->GetChess(i, j) == chess){
            cojoint_points.append(QPoint(i, j));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    for(int i = last_x - 1, j = last_y - 1;
        (i >= 0)&&(j >= 0);
        --i, --j)
    {
        if(chess_board_->GetChess(i, j) == chess){
            cojoint_points.append(QPoint(i, j));
            cojoint_count++;
        }
        else{
            break;
        }
    }

    GameResult result = GameResult::NoResult;
    if(cojoint_count >= 5){
        result = GameResult::Win;
    }

    return result;
}
