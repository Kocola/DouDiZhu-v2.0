#ifndef					__LOBBY_SCENE_H__
#define					__LOBBY_SCENE_H__

#include "cocos2d.h"

class LobbyScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(LobbyScene);

public:
	virtual bool init();
};

#endif