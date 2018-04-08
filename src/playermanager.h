#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QMap>
#include "ichessplayer.h"
#include "playerloader.h"

class PlayerManager : public QObject
{
    Q_OBJECT
public:
    explicit PlayerManager(QObject *parent = 0);
    ~PlayerManager();

    static PlayerManager *Get();
    void InitPlayerList(const QString &player_dir);

    QList<QString> GetPlayerList();
    IChessPlayer *GetPlayerByName(const QString &name);

signals:

public slots:

private:
    QMap<QString, IChessPlayer *> player_map_;
};

#endif // PLAYERMANAGER_H
