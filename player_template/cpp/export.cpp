#include "chessplayer.h"

#define PLAYER_API __declspec(dllexport)

static ChessPlayer *g_inst = nullptr;

extern "C"
{

PLAYER_API void _PlayerCreate()
{
    if(g_inst == nullptr){
        g_inst = new ChessPlayer;
    }
}

PLAYER_API IChessPlayer *_PlayerGet()
{
    return static_cast<IChessPlayer *>(g_inst);
}

PLAYER_API void _PlayerDestory()
{
    if(g_inst != nullptr){
        delete g_inst;
        g_inst = nullptr;
    }
}

}
