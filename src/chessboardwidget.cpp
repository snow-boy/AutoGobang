#include "chessboardwidget.h"
#include <QPainter>

#define LINE_WIDTH 2

ChessBoardWidget::ChessBoardWidget(QWidget *parent):
    QWidget(parent),
    chess_board_(nullptr)
{

}

ChessBoardWidget::ChessBoardWidget(IChessboard *chess_board, QWidget *parent) :
    QWidget(parent),
    chess_board_(chess_board)
{

}

void ChessBoardWidget::SetChessBoard(IChessboard *chess_board)
{
    chess_board_ = chess_board;
}

void ChessBoardWidget::SetHighlightPoints(const QVector<QPoint> &highlight_points)
{
    highlight_points_ = highlight_points;
}

void ChessBoardWidget::ClearHighlightPoints()
{
    highlight_points_.clear();
}

void ChessBoardWidget::paintEvent(QPaintEvent *e)
{
    if(chess_board_ == nullptr){
        return QWidget::paintEvent(e);
    }

    QRect paint_rect = GetPaintRect();

    int h_step = paint_rect.width()/(chess_board_->GetWidth() + 1);
    int v_step = paint_rect.height()/(chess_board_->GetHeight() + 1);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawPixmap(paint_rect, QPixmap(":/resources/chess_board_background.jpg"));

    QPen grid_pen(Qt::darkGray, LINE_WIDTH);
    painter.setPen(grid_pen);

    // draw vertical lines
    for(int i = 0; i < chess_board_->GetHeight(); ++i)
    {
        painter.drawLine(paint_rect.left(), v_step*(i+1) + paint_rect.top(),
                         paint_rect.right(), v_step*(i+1) + paint_rect.top());
    }

    // draw horizontal lines
    for(int i = 0; i < chess_board_->GetWidth(); ++i)
    {
        painter.drawLine(h_step*(i+1) + paint_rect.left(), paint_rect.top(),
                         h_step*(i+1) + paint_rect.left(), paint_rect.bottom());
    }


    // draw chess
    QPen highlight_border_pen(QColor(255, 0, 0));
    highlight_border_pen.setWidth(LINE_WIDTH*2);

    QPen general_text_pen(Qt::darkGreen);
    painter.setBrush(Qt::transparent);

    int chess_radius = std::min(h_step, v_step)/2 - LINE_WIDTH*2 + 2;
    for(int x = 0; x < chess_board_->GetWidth(); ++x)
    {
        for(int y = 0; y < chess_board_->GetHeight(); ++y)
        {
            if(chess_board_->GetChess(x, y) == Chess::Empty){
                continue;
            }

            QRect chess_rect(0, 0, chess_radius * 2, chess_radius * 2);
            chess_rect.moveCenter(QPoint(h_step*(x+1) + paint_rect.left(),
                                        v_step*(y+1) + paint_rect.top()));

            if(highlight_points_.contains(QPoint(x, y)))
            {
                painter.setPen(highlight_border_pen);
            }
            else
            {
                painter.setPen(Qt::transparent);
            }

            if(chess_board_->GetChess(x, y) == Chess::Black)
            {
                painter.setBrush(Qt::black);

                painter.drawEllipse(QPoint(h_step*(x+1) + paint_rect.left(),
                                           v_step*(y+1) + paint_rect.top()),
                                    chess_radius, chess_radius);
                painter.drawPixmap(chess_rect, QPixmap(""));


            }
            else if(chess_board_->GetChess(x, y) == Chess::White)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(h_step*(x+1) + paint_rect.left(),
                                           v_step*(y+1) + paint_rect.top()),
                                    chess_radius, chess_radius);

            }

            if(!highlight_points_.contains(QPoint(x, y)))
            {
                painter.setPen(general_text_pen);
            }


            QTextOption option;
            option.setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            painter.drawText(chess_rect,
                             QString::number(chess_board_->GetStepNo(x, y)),
                             option);
        }
    }
}

QRect ChessBoardWidget::GetPaintRect()
{
    QRect paint_rect = rect();
    int square_length = qMin(paint_rect.width(), paint_rect.height());

    int margin_v = (paint_rect.height() - square_length)/2;
    int margin_h = (paint_rect.width() - square_length)/2;

    QMargins margins(margin_h, margin_v, margin_h, margin_v);
    return paint_rect.marginsRemoved(margins);
}

