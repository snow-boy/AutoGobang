#ifndef PLAYERLOADER_H
#define PLAYERLOADER_H

#include <QString>
#include <QLibrary>
#include "ichessplayer.h"

class PlayerLoader
{
public:
    PlayerLoader();

    bool LoadPlayer(const QString &player_path);
    void UnloadPlayer();

    QString GetPlayerName();
    IChessPlayer *GetPlayer();

private:
    typedef void (*CreatePlayerFun)();
    typedef void (*DestroyPlayerFun)();
    typedef IChessPlayer *(*GetPlayerFun)();

    CreatePlayerFun create_fun_;
    DestroyPlayerFun destory_fun_;
    GetPlayerFun get_fun_;

    QLibrary lib_;
};

#endif // PLAYERLOADER_H
