#ifndef					__POKER_CONTROLLER_H__
#define					__POKER_CONTROLLER_H__

#include <vector>
#include <unordered_map>

#include "cocos2d.h"
#include "Poker.h"
#include "PokerSprite.h"

class PokerController : public cocos2d::Ref
{
public:
	static PokerController& getIns();

	static PokerController* getInstance();

public:
	void randomPokers();

	//获取当前局洗牌的结果
	std::vector<Poker> getRandomPokers();

	//扑克精灵生成器，给定Poker生成对应的精灵
	std::vector<PokerSprite*> genPokerSprites(const std::vector<Poker>& pokers_);

	PokerSprite* genPokerSprite(Poker poker_);

private:
	PokerController();

private:
	void initPokers();

	void initPokerSprites();

	int calcImageIndex(const Poker& poker_);

	cocos2d::Sprite* genPokerSprites(const Poker& poker_);

private:
	static cocos2d::SpriteFrameCache*		s_pokerSpriteCache;
	static std::vector<Poker>					s_pokers;
	static std::unordered_map<Poker, PokerSprite*>	s_pokersMap;
};

#endif