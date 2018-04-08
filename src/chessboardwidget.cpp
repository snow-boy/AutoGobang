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

    if(highlight_points_.size() > 0){
        QBrush brush(Qt::darkRed);
        {
            QColor color = brush.color();
            color.setAlpha(100);
            brush.setColor(color);
        }
        painter.fillRect(paint_rect, brush);

        QPen pen(Qt::darkGreen, LINE_WIDTH);
        {
            QColor color = pen.color();
            color.setAlpha(100);
            pen.setColor(color);
        }
        painter.setPen(pen);
    }
    else{
        painter.fillRect(paint_rect, Qt::darkRed);
        QPen pen(Qt::darkGreen, LINE_WIDTH);
        painter.setPen(pen);
    }

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
    if(highlight_points_.size() > 0)
    {
        QPen pen(Qt::darkGreen, LINE_WIDTH);
        QColor color = pen.color();
        color.setAlpha(100);
        pen.setColor(color);
        painter.setPen(pen);
    }

    int chess_radius = std::min(h_step, v_step)/2 - LINE_WIDTH*2 + 2;
    for(int x = 0; x < chess_board_->GetWidth(); ++x)
    {
        for(int y = 0; y < chess_board_->GetHeight(); ++y)
        {
            if(chess_board_->GetChess(x, y) == Chess::Black)
            {
                if((highlight_points_.size() > 0) && (!highlight_points_.contains(QPoint(x, y))))
                {
                    QBrush brush(QColor(0, 0, 0, 100));
                    painter.setBrush(brush);
                }
                else{
                    painter.setBrush(Qt::black);
                }

                painter.drawEllipse(QPoint(h_step*(x+1) + paint_rect.left(),
                                           v_step*(y+1) + paint_rect.top()),
                                    chess_radius, chess_radius);
            }
            else if(chess_board_->GetChess(x, y) == Chess::White)
            {
                if((highlight_points_.size() > 0) && (!highlight_points_.contains(QPoint(x, y))))
                {
                    QBrush brush(QColor(255, 255, 255, 100));
                    painter.setBrush(brush);
                }
                else{
                    painter.setBrush(Qt::white);
                }
                painter.drawEllipse(QPoint(h_step*(x+1) + paint_rect.left(),
                                           v_step*(y+1) + paint_rect.top()),
                                    chess_radius, chess_radius);
            }
        }
    }

    // highlight cojoint chess
    {
        painter.setBrush(Qt::transparent);

        QPen pen(Qt::red, LINE_WIDTH*2);
        painter.setPen(pen);
    }
    for(QPoint pos: highlight_points_)
    {
        painter.drawEllipse(QPoint(h_step*(pos.x()+1) + paint_rect.left(),
                                   v_step*(pos.y()+1) + paint_rect.top()),
                            chess_radius, chess_radius);
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

