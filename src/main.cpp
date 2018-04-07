#include <QApplication>
#include <QtDebug>

#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessjudge.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    ChessBoard chess_board(16, 16);
    ChessJudge judge(&chess_board);

    QVector<QPoint> place_point_list =
    {
        {1, 2},
        {2, 2},
        {3, 2},
        {4, 2},
        {5, 2}
    };

    for(QPoint point: place_point_list){
        qDebug() << point;
        chess_board.PlaceChess(point.x(), point.y(), Chess::Black);
        if(judge.DoJudge(point.x(), point.y()) == GameResult::Win){
            qDebug("judge black win!!");
        }
    }

    QVector<QPoint> place_point_list2 =
    {
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 4},
        {5, 4}
    };

    for(QPoint point: place_point_list2){
        qDebug() << point;
        chess_board.PlaceChess(point.x(), point.y(), Chess::White);
        if(judge.DoJudge(point.x(), point.y()) == GameResult::Win){
            qDebug("judge black win!!");
        }
    }

    ChessBoardWidget widget(&chess_board);
    widget.SetHighlightPoints(place_point_list);
    widget.show();

    return a.exec();
}

