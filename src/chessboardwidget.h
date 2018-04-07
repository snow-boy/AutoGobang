#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include "ichessboard.h"

class ChessBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoardWidget(QWidget *parent = 0);
    explicit ChessBoardWidget(IChessboard *chess_board, QWidget *parent = 0);

    void SetChessBoard(IChessboard *chess_board);

    void SetHighlightPoints(const QVector<QPoint> &highlight_points);
    void ClearHighlightPoints();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *e) override;

private:
    QRect GetPaintRect();

    IChessboard *chess_board_;
    QVector<QPoint> highlight_points_;
};

#endif // CHESSBOARDWIDGET_H
