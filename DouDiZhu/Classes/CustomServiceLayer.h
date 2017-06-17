#ifndef					__CUSTOMSERVICE_LAYER_H__
#define					__CUSTOMSERVICE_LAYER_H__

/* 客服对话框 --- 2017.6.7
*/

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

class CustomServiceLayer : public cocos2d::Layer
{
public:
	static void createLayer();

private:
	CREATE_FUNC(CustomServiceLayer);

public:
	virtual bool init() override;

private:
	//初始化对话框界面
	bool initView();

	//监听器和成员变量初始化
	bool initContent();

private:
	bool onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	//android平台下的返回键监听
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_);

private:
	//返回按钮回调
	void backCallback(cocos2d::Ref* sender_);

	void funcBackCallback();

	//拨打电话按钮回调
	void callServiceCallback(cocos2d::Ref* sender_);

	//切换账号按钮回调
	void feedbackCallback(cocos2d::Ref* sender_);

private:
	cocos2d::ui::Scale9Sprite* _middleBgSprite;
};

#endif