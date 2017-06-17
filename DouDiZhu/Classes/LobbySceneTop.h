#ifndef					__LOBBY_SCENE_TOP_H__
#define					__LOBBY_SCENE_TOP_H__

/* 大厅场景顶部---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneTop : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneTop);

	virtual bool init() override;

private:
	bool initView();

private:
	//设置按钮回调函数
	void lobbySetCallback(cocos2d::Ref* sender_);

	//规则按钮回调函数
	void lobbyRuleCallback(cocos2d::Ref* sender_);

	//反馈按钮回调函数
	void lobbyFeedbackCallback(cocos2d::Ref* sender_);
};

#endif