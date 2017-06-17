#include "ScalableMenuItemSprite.h"

//点击按钮时按钮的缩放倍数
const float scaleFactorWhenSelected = 0.8f;

ScalableMenuItemSprite* ScalableMenuItemSprite::create(
	cocos2d::Node* normalSprite_, cocos2d::Node* seletedSprite,
	const cocos2d::ccMenuCallback& callback_)
{
	auto ret = new (std::nothrow) ScalableMenuItemSprite();
	ret->initWithNormalSprite(normalSprite_, seletedSprite, nullptr, callback_);
	ret->autorelease();

	return ret;
}

void ScalableMenuItemSprite::selected()
{
	MenuItemSprite::selected();
	this->setScale(this->getScale() * scaleFactorWhenSelected);
}

void ScalableMenuItemSprite::unselected()
{
	MenuItemSprite::unselected();
	this->setScale(this->getScale() / scaleFactorWhenSelected);
}