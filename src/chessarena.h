#ifndef CHESSARENA_H
#define CHESSARENA_H

#include <QObject>
#include "chessboard.h"
#include "ichessplayer.h"
#include "chessjudge.h"

class ChessArena : public QObject
{
    Q_OBJECT
public:
    explicit ChessArena(QObject *parent = 0);
    ~ChessArena();

    static ChessArena *Get();

    void InitChessBoard(int width = 16, int height = 16);
    IChessboard *GetChessBoard(){ return chess_board_; }

    void Reset();

    void Fight(IChessPlayer *player1, Chess chess1,
               IChessPlayer *player2, Chess chess2);

    void EndFight(Chess winner_chess);

signals:
    void SigChessChanged(const QVector<QPoint> &highlight_points);
    void SigPlayerSay(Chess chess, const QString &word);
    void SigFightBegin(IChessPlayer *player1, Chess chess1,
                       IChessPlayer *player2, Chess chess2);
    void SigFightEnd(Chess winner);
    void SigChessError(Chess error_chess);

public slots:

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;

private:
    ChessBoard *chess_board_;

    IChessPlayer *player1_;
    Chess chess1_;

    IChessPlayer *player2_;
    Chess chess2_;

    ChessJudge *chess_judge_;
    int timer_id_;
    int round_count_;
};

#endif // CHESSARENA_H
