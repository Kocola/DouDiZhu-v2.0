#include "LobbyScene.h"

cocos2d::Scene* LobbyScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = LobbyScene::create();
	scene->addChild(layer);
	return scene;
}

bool LobbyScene::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	//初始化界面背景
	auto bgSprite = cocos2d::Sprite::create("lobby/lobbyBg.png");
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	bgSprite->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
	auto bgSize = bgSprite->getContentSize();
	bgSprite->setScaleX(winSize.width / bgSize.width);
	bgSprite->setScaleY(winSize.height / bgSize.height);
	this->addChild(bgSprite, 0);

	return true;
}
