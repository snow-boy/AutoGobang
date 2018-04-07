#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>

class PlayerManager : public QObject
{
    Q_OBJECT
public:
    explicit PlayerManager(QObject *parent = 0);

signals:

public slots:
};

#endif // PLAYERMANAGER_H