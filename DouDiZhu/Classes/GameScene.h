#ifndef					__GAME_SCENE_H__
#define					__GAME_SCENE_H__

/* 游戏场景	---	2017.6.7 
*/

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameScene);

public:
	virtual bool init();

private:
	bool initView();

	bool initContent();

private:
	void createHeadImageLayerCallback(cocos2d::Ref*);	//创建头像层回调	

	void destroyHeadImageLayerCallback(cocos2d::Ref*);	//销毁头像层回调

	void createReadyLayerCallback(cocos2d::Ref*);			//创建准备层

	void destroyReadyLayerCallback(cocos2d::Ref*);			//销毁准备层

	void createPokerLayerCallback(cocos2d::Ref*);			//创建扑克层

	void destroyPokerLayerCallback(cocos2d::Ref*);			//销毁扑克层

	void createCallLandlordLayerCallback(cocos2d::Ref*);	//创建叫地主层

	void destroyCallLandlordLayerCallback(cocos2d::Ref*);	//销毁叫地主层

	void createOverLayerCallback(cocos2d::Ref*);		//创建结束层

	void destroyOverLayerCallback(cocos2d::Ref*);	//销毁结束层
};

#endif