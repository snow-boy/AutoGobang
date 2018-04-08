#include "playerloader.h"

PlayerLoader::PlayerLoader():
    create_fun_(nullptr),
    destory_fun_(nullptr),
    get_fun_(nullptr)
{

}

bool PlayerLoader::LoadPlayer(const QString &player_path)
{
    return true;
}

void PlayerLoader::UnloadPlayer()
{

}

QString PlayerLoader::GetPlayerName()
{
    return QString();
}

IChessPlayer *PlayerLoader::GetPlayer()
{
    return nullptr;
}
