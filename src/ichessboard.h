#ifndef ICHESSBOARD_H
#define ICHESSBOARD_H

enum class Chess
{
    Empty,
    Black,
    White
};

class IChessboard
{
public:
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual Chess GetChess(int x, int y) const = 0;

    // place new chess, return old chess
    virtual Chess PlaceChess(int x, int y, Chess chess) = 0;

    virtual int GetStepNo(int x, int y){ return 0; }
};

#endif // ICHESSBOARD_H
