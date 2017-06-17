#include "GameScene.h"

#include "CallLandlordLayer.h"
#include "Common.h"
#include "GameController.h"
#include "HeadImageLayer.h"
#include "OverLayer.h"
#include "PokerLayer.h"
#include "ReadyStateLayer.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
		
	return scene;
}

bool GameScene::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	if (initContent() == false)
	{
		return false;
	}

	//如果不这样做，因为Scene还没有完全初始化，导致当前RunningScene
	//不是该Scene，导致出错
	//this->scheduleOnce(schedule_selector(GameScene::start), 1.0f);

	return true;
}

bool GameScene::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//游戏场景背景
	auto sceneBg = cocos2d::ui::Scale9Sprite::create(GAME_SCENE_BG);
	auto sceneBgSize = sceneBg->getContentSize();
	sceneBg->setCapInsets(cocos2d::Rect(sceneBgSize.width / 4, sceneBgSize.height / 4,
		sceneBgSize.width / 4, sceneBgSize.height / 4));
	sceneBg->setContentSize(cocos2d::Size(winSize));
	sceneBg->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBg);

	//游戏场景四周边框
	auto sceneBorder = cocos2d::ui::Scale9Sprite::create(GAME_SCENE_BORDER);
	auto sceneBorderSize = sceneBorder->getContentSize();
	sceneBorder->setCapInsets(cocos2d::Rect(sceneBorderSize.width / 4, sceneBorderSize.height / 4,
		sceneBorderSize.width / 4, sceneBorderSize.height / 4));
	sceneBorder->setContentSize(cocos2d::Size(winSize.width, winSize.height));
	sceneBorder->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBorder);

	//游戏场景左上角叶子
	auto leftLeaf = cocos2d::Sprite::create(GAME_SCENE_LEFT_LEAF);
	leftLeaf->setScale(MIDDLE_SCALE);
	leftLeaf->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	leftLeaf->setPosition(cocos2d::Point(0, winSize.height));
	this->addChild(leftLeaf);

	//游戏场景右上角叶子
	auto rightLeaf = cocos2d::Sprite::create(GAME_SCENE_RIGHT_LEAF);
	rightLeaf->setScale(MIDDLE_SCALE);
	rightLeaf->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
	rightLeaf->setPosition(cocos2d::Point(winSize.width, winSize.height));
	this->addChild(rightLeaf);

	return true;
}

bool GameScene::initContent()
{
	//注册添加头像层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createHeadImageLayerCallback),
		CREATE_HEADIMAGE_LAYER, nullptr);

	//注册销毁头像层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyHeadImageLayerCallback),
		DESTROY_HEADIMAGE_LAYER, nullptr);

	//注册添加准备层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createReadyLayerCallback),
		CREATE_READY_LAYER, nullptr);

	//注册销毁准备层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyReadyLayerCallback),
		DESTROY_READY_LAYER, nullptr);

	//注册添加扑克层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createPokerLayerCallback),
		CREATE_POKER_LAYER, nullptr);

	//注册销毁扑克层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyPokerLayerCallback),
		DESTROY_POKER_LAYER, nullptr);

	//注册添加叫地主层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createCallLandlordLayerCallback),
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//注册销毁扑克层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyCallLandlordLayerCallback),
		DESTROY_CALL_LANDLORD_LAYER, nullptr);

	//注册添加结束层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createOverLayerCallback),
		CREATE_OVER_LAYER,
		nullptr);

	//注册销毁结束层消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyOverLayerCallback),
		DESTROY_OVER_LAYER,
		nullptr);

	return true;
}

void GameScene::createHeadImageLayerCallback(cocos2d::Ref*)
{
	//创建头像层
	HeadImageLayer::createLayer();
}

void GameScene::destroyHeadImageLayerCallback(cocos2d::Ref*)
{
	//销毁头像层
	HeadImageLayer::destroyLayer();
}

void GameScene::createReadyLayerCallback(cocos2d::Ref*)
{
	//创建准备层
	ReadyStateLayer::createLayer();
}

void GameScene::destroyReadyLayerCallback(cocos2d::Ref*)
{
	//销毁准备层
	ReadyStateLayer::destroyLayer();
}

void GameScene::createPokerLayerCallback(cocos2d::Ref*)
{
	//创建扑克层
	PokerLayer::createLayer();
}

void GameScene::destroyPokerLayerCallback(cocos2d::Ref*)
{
	//销毁扑克层
	PokerLayer::destroyLayer();
}

void GameScene::createCallLandlordLayerCallback(cocos2d::Ref*)
{
	//创建叫地主层
	CallLandlordLayer::createLayer();
}

void GameScene::destroyCallLandlordLayerCallback(cocos2d::Ref*)
{
	//销毁叫地主层
	CallLandlordLayer::destroyLayer();
}

void GameScene::createOverLayerCallback(cocos2d::Ref*)
{
	//创建结束层
	OverLayer::createLayer();
}

void GameScene::destroyOverLayerCallback(cocos2d::Ref*)
{
	//销毁结束层
	OverLayer::destroyLayer();
}

