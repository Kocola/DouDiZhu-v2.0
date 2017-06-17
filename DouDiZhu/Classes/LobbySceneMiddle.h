#ifndef					__LOBBY_SCENE_MIDDLE_H__
#define					__LOBBY_SCENE_MIDDLE_H__

/* 大厅场景中间---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneMiddle : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneMiddle);

public:
	virtual bool init() override;

private:
	bool initView();

private:
	//创建房间回调函数
	void createRoomCallback(cocos2d::Ref* sender_);

	//加入房间回调函数
	void joinRoomCallback(cocos2d::Ref* sender_);

	//开始游戏回调
	void startGameCallback(cocos2d::Ref* sender_);
};

#endif