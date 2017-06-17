#ifndef					__COUNT_DOWN_H__
#define					__COUNT_DOWN_H__

/*	计时器（用于显示）	---	2017.6.13
*/

#include "cocos2d.h"

class CountDown : public cocos2d::Node
{
public:
	CREATE_FUNC(CountDown);

private:
	virtual bool init() override;

	bool initView();

private:
	void countDown(float delta_);

public:
	//开始计时
	void startCountDown();

	//结束计时
	void stopCountDown();

	//设置计时时间
	void setCountDownUpper(float upper_); 

	//设置回调函数
	void setCallbackFunc(const std::function<void(void)>& func_);

private:
	int				_totalSpriteNum;	//共有计时图片的数目
	int				_curSpriteIndex;	//当前计时图片的下标
	float				_countDownUp;	//计时上限
	float				_counting;				//正在计时

private:
	cocos2d::Sprite*	_sprite;	//计时图片精灵
	cocos2d::LabelAtlas*	_labelAltas;	//计时素材里的数字

private:
	std::function<void(void)>		_callbackFunc;
};

#endif