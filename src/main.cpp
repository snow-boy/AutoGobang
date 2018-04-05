#include <QApplication>

#include "chessboard.h"
#include "chessboardwidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    ChessBoard chess_board;

    chess_board.PlaceChess(1, 2, Chess::Black);
    chess_board.PlaceChess(2, 1, Chess::Black);
    chess_board.PlaceChess(3, 2, Chess::Black);
    chess_board.PlaceChess(7, 3, Chess::White);
    chess_board.PlaceChess(6, 5, Chess::White);
    chess_board.PlaceChess(4, 2, Chess::White);

    ChessBoardWidget widget(&chess_board);
    widget.show();

    return a.exec();
}

