#ifndef					__HOLDER_PLAYER_INSTANCE_H__
#define					__HOLDER_PLAYER_INSTANCE_H__

/* 手动玩家实例	---	2017.6.9
*/

#include "HolderPlayer.h"
#include "Singleton.h"

class HolderPlayerInstance : public Singleton<HolderPlayer>
{
};

#endif