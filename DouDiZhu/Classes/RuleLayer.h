#ifndef					__RULE_LAYER_H__
#define					__RULE_LAYER_H__

/* 规则对话框 2017.6.7 
*/

#include "cocos2d.h"
#include "ui/UIListView.h"
#include "ui/UIScale9Sprite.h"

class RuleLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(RuleLayer);

	static void createLayer();

public:
	virtual bool init() override;

private:
	//初始化游戏界面
	bool initView();

	//初始化监听器等
	bool initContent();

	//初始化ListView
	bool initListView();

private:
	bool onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_);

private:
	//返回按钮回调
	void backCallback(cocos2d::Ref* sender_);

	void funcBackCallback();

	//ListView监听器
	void selectedItemEvent(cocos2d::Ref* sender_, cocos2d::ui::ListView::EventType type_);

	void selectedItemEventScrollView(cocos2d::Ref* sender_, cocos2d::ui::ScrollView::EventType type_);

private:
	cocos2d::ui::Scale9Sprite* _dialogMiddleBg;
};

#endif