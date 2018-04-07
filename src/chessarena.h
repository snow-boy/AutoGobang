#ifndef CHESSARENA_H
#define CHESSARENA_H

#include <QObject>

class ChessArena : public QObject
{
    Q_OBJECT
public:
    explicit ChessArena(QObject *parent = 0);

signals:

public slots:
};

#endif // CHESSARENA_H