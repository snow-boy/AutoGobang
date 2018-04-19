#include "chessboard.h"

ChessBoard::ChessBoard(int width, int height):
    width_(width),
    height_(height),
    current_step_(1)
{
    chess_tank_.resize(width*height);
    chess_tank_.fill(Chess::Empty);

    steps_no_.resize(width*height);
    steps_no_.fill(0);
}

int ChessBoard::GetWidth() const
{
    return width_;
}

int ChessBoard::GetHeight() const
{
    return height_;
}

Chess ChessBoard::GetChess(int x, int y) const
{
    Q_ASSERT(x < width_);
    Q_ASSERT(y < height_);

    return chess_tank_[y*width_ + x];
}

Chess ChessBoard::PlaceChess(int x, int y, Chess chess)
{
    Q_ASSERT(x < width_);
    Q_ASSERT(y < height_);

    Chess old_chess = chess_tank_[y*width_ + x];
    chess_tank_[y*width_ + x] = chess;
    steps_no_[y*width_ + x] = current_step_;
    current_step_++;

    return old_chess;
}

int ChessBoard::GetStepNo(int x, int y)
{
    return steps_no_[y*width_ + x];
}

void ChessBoard::Reset()
{
    steps_no_.fill(0);
    chess_tank_.fill(Chess::Empty);
    current_step_ = 1;
}
