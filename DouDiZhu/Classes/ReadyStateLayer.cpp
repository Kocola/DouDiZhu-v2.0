#include "ReadyStateLayer.h"

#include "Common.h"
#include "GameController.h"
#include "ScalableMenuItemSprite.h"
#include "Util.h"

const std::string layerName = "readyStateLayer";

void ReadyStateLayer::createLayer()
{
	auto layer = ReadyStateLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void ReadyStateLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool ReadyStateLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool ReadyStateLayer::initView()
{
	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	const auto computerOnePos = cocos2d::Point(BASE_WIDTH * 0.8 * SCALE_X, 
		BASE_HEIGHT * 0.72 * SCALE_Y);
	const auto computerTwoPos = cocos2d::Point(BASE_WIDTH * 0.2 * SCALE_X, 
		BASE_HEIGHT * 0.72 * SCALE_Y);
	const auto holderPos = cocos2d::Point(BASE_WIDTH * 0.5 * SCALE_X, 
		BASE_HEIGHT * 0.4 * SCALE_Y);

	//电脑玩家1准备状态（开始直接设置成准备显示）
	_computerOneReady = cocos2d::Sprite::create(gameStateReady);
	_computerOneReady->setScale(MAX_SCALE);
	_computerOneReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOneReady->setPosition(computerOnePos);
	this->addChild(_computerOneReady);

	//电脑玩家2准备状态（开始直接设置成准备显示）
	_computerTwoReady = cocos2d::Sprite::create(gameStateReady);
	_computerTwoReady->setScale(MAX_SCALE);
	_computerTwoReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoReady->setPosition(computerTwoPos);
	this->addChild(_computerTwoReady);

	//手动玩家准备状态（开始设置不显示）
	_holderReady = cocos2d::Sprite::create(gameStateReady);
	_holderReady->setScale(MAX_SCALE);
	_holderReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderReady->setPosition(holderPos);

	_holderReady->setVisible(false);

	this->addChild(_holderReady);

	//手动玩家准备按钮（开始设置显示）
	_holderReadyBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(gameStateReadyBtn),
		nullptr,
		CC_CALLBACK_1(ReadyStateLayer::readyBtnCallback, this));
	_holderReadyBtn->setScale(MAX_SCALE);
	_holderReadyBtn->setAnchorPoint(cocos2d::Point(cocos2d::Vec2::ANCHOR_MIDDLE));
	_holderReadyBtn->setPosition(holderPos);
	
	auto menu = cocos2d::Menu::create(_holderReadyBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);
	this->addChild(menu);

	return true;
}

void ReadyStateLayer::updateState(float delta_)
{
	//将所有准备标识隐藏，并切换到下一个状态
	_holderReady->setVisible(false);

	_computerOneReady->setVisible(false);
	_computerTwoReady->setVisible(false);
	_holderReadyBtn->setVisible(false);

	GameController::getInstance()->updateState();

	//销毁该层
	this->removeFromParent();
}

void ReadyStateLayer::readyBtnCallback(cocos2d::Ref*)
{
	//准备按钮隐藏
	_holderReadyBtn->setVisible(false);
	//显示手动玩家准备状态
	_holderReady->setVisible(true);

	//1.0秒后切换状态
	this->scheduleOnce(schedule_selector(ReadyStateLayer::updateState), 1.0f);
}
