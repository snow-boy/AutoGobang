#include "chessboard.h"

ChessBoard::ChessBoard(int width, int height):
    width_(width),
    height_(height)
{
    chess_tank_.resize(width*height);
    chess_tank_.fill(Chess::Empty);
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
    return old_chess;
}
