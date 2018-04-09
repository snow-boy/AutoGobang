#include "playermanager.h"
#include <QDir>

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

    for(auto val: player_loader_list_){
        val->UnloadPlayer();
        delete val;
    }
    player_loader_list_.clear();
    player_map_.clear();
}

PlayerManager *PlayerManager::Get()
{
    return g_inst;
}

void PlayerManager::InitPlayerList(const QString &player_dir)
{
    QDir dir(player_dir);
    QFileInfoList file_info_list = dir.entryInfoList(QDir::Files);
    for(QFileInfo file_info: file_info_list)
    {
        if(file_info.suffix() == "dll"){
            PlayerLoader *loader = new PlayerLoader;
            if(loader->LoadPlayer(file_info.absoluteFilePath())){
                player_map_[loader->GetPlayerName()] = loader->GetPlayer();
                player_loader_list_.append(loader);
            }
            else{
                delete loader;
            }
        }
    }
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
