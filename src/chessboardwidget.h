#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include "ichessboard.h"

class ChessBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoardWidget(IChessboard *chess_board, QWidget *parent = 0);

    void SetHighlightPoints(const QVector<QPoint> &highlight_points);
    void ClearHighlightPoints();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QRect GetPaintRect();

    IChessboard *chess_board_;
    QVector<QPoint> highlight_points_;
};

#endif // CHESSBOARDWIDGET_H
