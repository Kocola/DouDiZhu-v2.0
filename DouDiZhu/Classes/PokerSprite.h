#ifndef					__POKER_SPRITE_H__
#define					__POKER_SPRITE_H__

/*	扑克精灵（用于在扑克层上显示）	---	2017.6.9
*/

#include "cocos2d.h"
#include "Poker.h"

class PokerSprite : public cocos2d::Node
{
public:
	static PokerSprite* create(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

public:
	PokerSprite* clone();

private:
	PokerSprite(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

	~PokerSprite();

private:
	virtual bool init() override;

	bool initView();

	bool initContent();

public:
	//将该牌上移，表示被点击
	void selectedPokersOut();

	//点击的牌再次点击，回到未点击位置
	void selectedPokerBack();

public:
	//是否能被点击
	CC_SYNTHESIZE(bool, canClick, CanClick);	
	
	//是否已选
	CC_SYNTHESIZE(bool, isSelected, IsSelected);

private:
	cocos2d::Sprite* _pokerSprite;
	Poker				 _poker;
};

#endif