#ifndef					__LOBBY_SCENE_BOTTOM_H__
#define					__LOBBY_SCENE_BOTTOM_H__

/* 大厅场景底部---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneBottom : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneBottom);

public:
	virtual bool init() override;

private:
	bool initView();

private:
	//分享按钮回调函数
	void lobbyShareCallback(cocos2d::Ref* sender_);

	//活动按钮回调函数
	void lobbyActivityCallback(cocos2d::Ref* sender_);

	//战绩按钮回调函数
	void lobbyRecordCallback(cocos2d::Ref* sender_);
};

#endif