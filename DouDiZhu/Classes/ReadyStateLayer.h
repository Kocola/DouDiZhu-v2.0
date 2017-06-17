#ifndef					__READY_STATE_LAYER_H__
#define					__READY_STATE_LAYER_H__

/*	准备状态层	---	2017.6.8 
*/

#include "cocos2d.h"

class ScalableMenuItemSprite;

class ReadyStateLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(ReadyStateLayer);

private:
	virtual bool init() override;

private:
	bool initView();

private:
	void updateState(float delta_);

private:
	void readyBtnCallback(cocos2d::Ref*);

private:
	cocos2d::Sprite*		_computerOneReady;
	cocos2d::Sprite*		_computerTwoReady;
	cocos2d::Sprite*		_holderReady;
	ScalableMenuItemSprite*	_holderReadyBtn;	//开始按钮
};

#endif