#include "PokerSprite.h"

const float UP_DISTANCE = 10.0f;	//点击后上移的距离

PokerSprite::PokerSprite(cocos2d::Sprite* pokerSprite_, const Poker& poker_)
	:_pokerSprite(pokerSprite_), _poker(poker_)
{
}

PokerSprite::~PokerSprite()
{
	//CC_ASSERT(1 == 0, "PokerSprite::~PokerSprite()");
}

PokerSprite* PokerSprite::create(cocos2d::Sprite* pokerSprite_, const Poker& poker_)
{
	auto pRet = new PokerSprite(pokerSprite_, poker_);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		pRet = nullptr;
		return pRet;
	}
}

bool PokerSprite::init()
{
	if (initView() == false)
	{
		return false;
	}

	if (initContent() == false)
	{
		return false;
	}

	return true;
}

bool PokerSprite::initView()
{
	this->addChild(_pokerSprite);

	//将无长宽的Node设置成和Sprite一样长宽
	this->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	this->setContentSize(cocos2d::Size(_pokerSprite->getContentSize()));

	//将精灵的位置和Node本身一致
	_pokerSprite->setPosition(cocos2d::Point(this->getContentSize() / 2));

	return true;
}

bool PokerSprite::initContent()
{
	this->setIsSelected(false);
	this->setCanClick(false);

	return true;
}

PokerSprite* PokerSprite::clone()
{
	auto pokerSprites = cocos2d::Sprite::createWithSpriteFrame(_pokerSprite->getSpriteFrame());
	auto poker = _poker;
	return PokerSprite::create(pokerSprites, poker);
}

void PokerSprite::selectedPokersOut()
{
	this->setIsSelected(true);
	auto position = this->getPosition();
	this->setPosition(cocos2d::Point(position.x, position.y + UP_DISTANCE));
	
	cocos2d::NotificationCenter::getInstance()->postNotification(ADD_POKER_IN_HOLDER_POKERSWAITFOROUT, &_poker);
}

void PokerSprite::selectedPokerBack()
{
	//从待出牌集合中移除该张牌
	this->setIsSelected(false);
	auto position = this->getPosition();
	this->setPosition(cocos2d::Point(position.x, position.y - UP_DISTANCE));

	cocos2d::NotificationCenter::getInstance()->postNotification(DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT, &_poker);
}
