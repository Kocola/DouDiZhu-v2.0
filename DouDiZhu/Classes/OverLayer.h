#ifndef					__OVER_LAYER_H__
#define					__OVER_LAYER_H__

/*	游戏结束层	---	2017.6.13
*/

#include "cocos2d.h"

class ScalableMenuItemSprite;

class OverLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(OverLayer);

private:
	virtual bool init() override;

	bool initView();

	void initWinAnimation();

	void initLostAnimation();

	bool initContent();

private:
	//运行胜利动画回调
	void runWinActionCallback(cocos2d::Ref*);

	//运行失败动画回调
	void runLostActionCallback(cocos2d::Ref*);

	//返回大厅回调
	void returnToLobbyBtnCallback(cocos2d::Ref*);

	//显示返回大厅按钮
	void showReturnToBtn();

private:
	cocos2d::Animate*	_winAnimation;	//胜利的动画
	cocos2d::Animate*	_lostAnimation;	//失败的动画

	cocos2d::Sprite*					_winSprite;
	cocos2d::Sprite*					_lostSprite;
	ScalableMenuItemSprite*		_returnToLobbyBtn;	//返回大厅按钮
};

#endif