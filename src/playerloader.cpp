#include "playerloader.h"
#include <QFileInfo>

#define CREATE_FUN_NAME "_PlayerCreate"
#define DESTORY_FUN_NAME "_PlayerDestory"
#define GET_FUN_NAME "_PlayerGet"

PlayerLoader::PlayerLoader():
    create_fun_(nullptr),
    destory_fun_(nullptr),
    get_fun_(nullptr)
{

}

bool PlayerLoader::LoadPlayer(const QString &player_path)
{
    lib_.setFileName(player_path);
    if(!lib_.load()){
        return false;
    }

    create_fun_ = (CreatePlayerFun)lib_.resolve(CREATE_FUN_NAME);
    if(create_fun_ == nullptr){
        return false;
    }

    get_fun_ = (GetPlayerFun)lib_.resolve(GET_FUN_NAME);
    if(get_fun_ == nullptr){
        return false;
    }

    destory_fun_ = (DestroyPlayerFun)lib_.resolve(DESTORY_FUN_NAME);
    if(destory_fun_ == nullptr){
        return false;
    }

    create_fun_();

    return true;
}

void PlayerLoader::UnloadPlayer()
{
    if(!lib_.isLoaded()){
        return;
    }

    destory_fun_();
    lib_.unload();

    create_fun_ = nullptr;
    get_fun_ = nullptr;
    destory_fun_ = nullptr;
}

QString PlayerLoader::GetPlayerName()
{
    return QFileInfo(lib_.fileName()).baseName();
}

IChessPlayer *PlayerLoader::GetPlayer()
{
    if(get_fun_ != nullptr){
        return get_fun_();
    }

    return nullptr;
}
