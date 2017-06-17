#ifndef					__SET_LAYER_H__
#define					__SET_LAYER_H__

//#pragma comment(lib, "libExtensions.lib")

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "cocos-ext.h"

class SetLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SetLayer);

	static void createLayer();

public:
	virtual bool init() override;

private:
	//界面初始化
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

	//退出游戏按钮回调
	void quitGameCallback(cocos2d::Ref* sender_);

	//切换账号按钮回调
	void switchAccountCallback(cocos2d::Ref* sender_);

	//音乐滑动条变化回调
	void musicChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_);

	//音效滑动条变化回调
	void effectChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_);

private:
	cocos2d::extension::ControlSlider* _musicSlider;	//音乐滑动条
	cocos2d::extension::ControlSlider* _effectSlider;	//音效滑动条
};

#endif