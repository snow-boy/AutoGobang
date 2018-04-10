#include "chessarena.h"
#include <QTimerEvent>
#include <QTime>

static ChessArena *g_inst = nullptr;

ChessArena::ChessArena(QObject *parent) :
    QObject(parent),
    chess_board_(nullptr),
    player1_(nullptr),
    chess1_(Chess::Empty),
    player2_(nullptr),
    chess2_(Chess::Empty),
    timer_id_(0),
    round_count_(0),
    chess_judge_(nullptr)
{
    Q_ASSERT(g_inst == nullptr);
    g_inst = this;
}

ChessArena::~ChessArena()
{
    Q_ASSERT(g_inst != nullptr);
    g_inst = nullptr;

    if(chess_judge_ != nullptr){
        delete chess_judge_;
        chess_judge_ = nullptr;
    }

    if(chess_board_ != nullptr){
        delete chess_board_;
        chess_board_ = nullptr;
    }
}

void ChessArena::InitChessBoard(int width, int height)
{
    chess_board_ = new ChessBoard(width, height);
    chess_judge_ = new ChessJudge(chess_board_);
}

void ChessArena::Reset()
{
    for(int i = 0; i < chess_board_->GetWidth(); ++i)
    {
        for(int j = 0; j < chess_board_->GetHeight(); ++j){
            chess_board_->PlaceChess(i, j, Chess::Empty);
        }
    }
}

void ChessArena::Fight(IChessPlayer *player1, Chess chess1,
                       IChessPlayer *player2, Chess chess2)
{
    player1_ = player1;
    chess1_ = chess1;
    player2_ = player2;
    chess2_ = chess2;

    player1_->Start(chess1_);
    player2_->Start(chess2_);

    qsrand(QTime::currentTime().msec());
    round_count_ = qrand() % 2;
    emit SigFightBegin(player1, chess1, player2, chess2);
    timer_id_ = startTimer(100);
}

void ChessArena::EndFight(Chess winner_chess)
{
    killTimer(timer_id_);

    player1_->End(winner_chess, chess_board_);
    player2_->End(winner_chess, chess_board_);

    player1_ = nullptr;
    player2_ = nullptr;
    chess1_ = Chess::Empty;
    chess2_ = Chess::Empty;
}

void ChessArena::timerEvent(QTimerEvent *event)
{
    Q_ASSERT(event->timerId() == timer_id_);

    int x = -1;
    int y = -1;
    std::string something_say;

    if(round_count_%2 == 0){
        player2_->PlaceChess(chess_board_, &x, &y, something_say);
        if((x >= 0) && (y >= 0)){
            if(something_say.size() > 0){
                emit SigPlayerSay(chess2_, QString::fromStdString(something_say));
            }

            QVector<QPoint> highlight_points;
            if(chess_board_->GetChess(x, y) != Chess::Empty){
                highlight_points.append(QPoint(x, y));
                emit SigChessError(chess2_);
                emit SigChessChanged(highlight_points);
                EndFight(Chess::Empty);
                return;
            }

            chess_board_->PlaceChess(x, y, chess2_);
            GameResult result = chess_judge_->DoJudge(x, y, highlight_points);
            emit SigChessChanged(highlight_points);
            if(result == GameResult::Win){
                emit SigFightEnd(chess2_);
                EndFight(chess2_);
                return;
            }
        }
        else{
            emit SigFightEnd(Chess::Empty);
            EndFight(Chess::Empty);
        }
    }
    else{
        player1_->PlaceChess(chess_board_, &x, &y, something_say);
        if((x >= 0) && (y >= 0)){
            if(something_say.size() > 0){
                emit SigPlayerSay(chess1_, QString::fromStdString(something_say));
            }

            QVector<QPoint> highlight_points;
            if(chess_board_->GetChess(x, y) != Chess::Empty){
                highlight_points.append(QPoint(x, y));
                emit SigChessError(chess1_);
                emit SigChessChanged(highlight_points);
                EndFight(Chess::Empty);
                return;
            }

            chess_board_->PlaceChess(x, y, chess1_);
            GameResult result = chess_judge_->DoJudge(x, y, highlight_points);
            emit SigChessChanged(highlight_points);
            if(result == GameResult::Win){
                emit SigFightEnd(chess1_);
                EndFight(chess1_);
                return;
            }
        }
        else{
            emit SigFightEnd(Chess::Empty);
            EndFight(Chess::Empty);
        }
    }

    round_count_++;
}

ChessArena *ChessArena::Get()
{
    return g_inst;
}
