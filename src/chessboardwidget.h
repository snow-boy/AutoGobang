#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include "ichessboard.h"

class ChessBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoardWidget(IChessboard *chess_board, QWidget *parent = 0);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    IChessboard *chess_board_;

};

#endif // CHESSBOARDWIDGET_H
