#include "chessboardwidget.h"
#include <QPainter>

#define LINE_WIDTH 2

ChessBoardWidget::ChessBoardWidget(IChessboard *chess_board, QWidget *parent) :
    QWidget(parent),
    chess_board_(chess_board)
{

}

void ChessBoardWidget::paintEvent(QPaintEvent *event)
{
    QRect space = rect();

    int h_step = space.width()/(chess_board_->GetWidth() + 1);
    int v_step = space.height()/(chess_board_->GetHeight() + 1);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(space, Qt::darkRed);

    QPen pen(Qt::darkGreen, LINE_WIDTH);
    painter.setPen(pen);

    // draw vertical lines
    for(int i = 0; i < chess_board_->GetHeight(); ++i)
    {
        painter.drawLine(0, v_step*(i+1), space.width(), v_step*(i+1));
    }

    // draw horizontal lines
    for(int i = 0; i < chess_board_->GetWidth(); ++i)
    {
        painter.drawLine(h_step*(i+1), 0, h_step*(i+1), space.height());
    }

    // draw chess
    painter.setBrush(Qt::black);
    int chess_radius = std::min(h_step, v_step)/2 - LINE_WIDTH*2 + 2;
    for(int x = 0; x < chess_board_->GetWidth(); ++x)
    {
        for(int y = 0; y < chess_board_->GetHeight(); ++y)
        {
            if(chess_board_->GetChess(x, y) == Chess::Black)
            {
                painter.setBrush(Qt::black);
                painter.drawEllipse(QPoint(h_step*(x+1), v_step*(y+1)),
                                    chess_radius, chess_radius);
            }
            else if(chess_board_->GetChess(x, y) == Chess::White)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(h_step*(x+1), v_step*(y+1)),
                                    chess_radius, chess_radius);
            }
        }
    }
}
