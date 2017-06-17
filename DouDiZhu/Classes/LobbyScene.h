#ifndef					__LOBBY_SCENE_H__
#define					__LOBBY_SCENE_H__

#include "cocos2d.h"

class LobbyScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(LobbyScene);

public:
	virtual bool init() override;

private:
	bool initContent();
	//初始化大厅场景模块，分为顶部，中部和底部
	bool initSceneModule();
};

#endif