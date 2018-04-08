#include "madchessplayer.h"
#include <QtGlobal>
#include <QString>

MadChessPlayer::MadChessPlayer()
{

}


void MadChessPlayer::Start(Chess assigned_chess)
{

}

void MadChessPlayer::End(Chess winner_chess, const IChessboard *chess_board)
{

}

void MadChessPlayer::PlaceChess(const IChessboard *chess_board,
                                int *x, int *y, std::string &word_say)
{
    for(int i = 0; i < 100; ++i)
    {
        int temp_x = qrand() % chess_board->GetWidth();
        int temp_y = qrand() % chess_board->GetHeight();

        if(chess_board->GetChess(temp_x, temp_y) == Chess::Empty)
        {
            *x = temp_x;
            *y = temp_y;

            word_say = QString("I place chess to (%1, %2)").arg(temp_x).arg(temp_y).toStdString();
            break;
        }
    }
}
