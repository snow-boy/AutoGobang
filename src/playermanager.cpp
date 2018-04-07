#include "playermanager.h"
#include "madchessplayer.h"

static PlayerManager *g_inst = nullptr;

PlayerManager::PlayerManager(QObject *parent) : QObject(parent)
{
    Q_ASSERT(g_inst == nullptr);
    g_inst = this;
}

PlayerManager::~PlayerManager()
{
    Q_ASSERT(g_inst != nullptr);
    g_inst = nullptr;

    for(auto val: player_map_.values()){
        delete val;
    }
    player_map_.clear();
}

PlayerManager *PlayerManager::Get()
{
    return g_inst;
}

void PlayerManager::InitPlayerList(const QString &player_dir)
{
    player_map_["madman"] = new MadChessPlayer;
}

QList<QString> PlayerManager::GetPlayerList()
{
    return player_map_.keys();
}

IChessPlayer *PlayerManager::GetPlayerByName(const QString &name)
{
    Q_ASSERT(player_map_.contains(name));
    return player_map_[name];
}
