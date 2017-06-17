#include "CountDown.h"

#include "Common.h"

//默认倒计时上限是15秒
const float DEFAULT_COUNTDOWN_TIMEUP = 20.0f;

bool CountDown::init()
{
	_totalSpriteNum = 2;
	_curSpriteIndex = 0;
	_countDownUp = DEFAULT_COUNTDOWN_TIMEUP;//倒计时默认是15S
	_counting = _countDownUp;

	_callbackFunc = [](){
		cocos2d::log("CountDown Callbackfunc!");
	};

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool CountDown::initView()
{
	auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile(COUNTDOWN_IMAGE_LIST, 
		COUNTDOWN_IMAGES);

	_sprite = cocos2d::Sprite::create();
	this->addChild(_sprite, 0);
	auto spriteFrame = spriteFrameCache->getSpriteFrameByName(
		cocos2d::StringUtils::format("clock%d.png", _curSpriteIndex));
	_sprite->setSpriteFrame(spriteFrame);

	_labelAltas = cocos2d::LabelAtlas::create(cocos2d::StringUtils::format("%d", _countDownUp),
		COUNTDOWN_NUMS, 38, 37, '0');
	_labelAltas->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	this->addChild(_labelAltas, 1);

	return true;
}

void CountDown::countDown(float delta_)
{
	_counting -= delta_;

	//倒计时<= 5S时，显示闪烁效果
	if (_counting > 0 && _counting <= 5)
	{
		_curSpriteIndex = (_curSpriteIndex + 1) % _totalSpriteNum;
		auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
		_sprite->setSpriteFrame(spriteFrameCache->getSpriteFrameByName(
			cocos2d::StringUtils::format("clock%d.png", _curSpriteIndex)));
	}

	//计时时间已到
	if (_counting <= 0)
	{
		stopCountDown();
		_callbackFunc();
	}
	else
	{
		_labelAltas->setString(cocos2d::StringUtils::format("%d", (int)_counting));
	}
}

void CountDown::startCountDown()
{
	//显示计时器
	this->setVisible(true);

	//每次显示前都要重置计数
	this->_counting = _countDownUp;

	//每0.2s调用一次countDown，用于更新计时信息
	this->schedule(schedule_selector(CountDown::countDown), 0.2f);
}

void CountDown::stopCountDown()
{
	this->setVisible(false);
	//关闭计时schedule
	this->unschedule(schedule_selector(CountDown::countDown));
	//恢复默认计时时间
	_countDownUp = DEFAULT_COUNTDOWN_TIMEUP;
}

void CountDown::setCallbackFunc(const std::function<void(void)>& func_)
{
	this->_callbackFunc = func_;
}

void CountDown::setCountDownUpper(float upper_)
{
	this->_countDownUp = upper_;
}
