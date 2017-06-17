#include "PokerController.h"

#include "Common.h"

cocos2d::SpriteFrameCache*		PokerController::s_pokerSpriteCache;
std::vector<Poker>					PokerController::s_pokers;
std::unordered_map<Poker, PokerSprite*>		PokerController::s_pokersMap;

PokerController::PokerController()
{
	srand((unsigned)time(nullptr));	//开启随机种子

	//将打包好的图片经过SpriteFrameCache处理，然后可以直接获取
	s_pokerSpriteCache = cocos2d::SpriteFrameCache::getInstance();
	s_pokerSpriteCache->addSpriteFramesWithFile(POKER_IMAGE_LIST, POKER_IMAGES);

	initPokers();
	randomPokers();	//洗牌
	initPokerSprites();
}

PokerController& PokerController::getIns()
{
	static PokerController pokerController;
	return pokerController;
}

PokerController* PokerController::getInstance()
{
	return &getIns();
}

void PokerController::initPokers()
{
	s_pokers.clear();
	//方块DIAMOND
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::DIAMOND, i);
		s_pokers.push_back(poker);
	}

	//梅花HEART
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::HEART, i);
		s_pokers.push_back(poker);
	}

	//红桃CLUB
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::CLUB, i);
		s_pokers.push_back(poker);
	}

	//黑桃SPADE
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::SPADE, i);
		s_pokers.push_back(poker);
	}

	//大小王
	s_pokers.push_back(Poker(Poker::BLACKJOKER));
	s_pokers.push_back(Poker(Poker::REDJOKER));
}

void PokerController::initPokerSprites()
{
	s_pokersMap.clear();

	//生成Poker和对应的Sprite的Map，相当于是Cache，提升程序效率
	for (int i = 0; i < s_pokers.size(); ++i)
	{
		auto poker = s_pokers.at(i);
		int index = calcImageIndex(s_pokers.at(i));
		std::string str = cocos2d::StringUtils::format("%d.png", index);
		auto sprite = cocos2d::Sprite::createWithSpriteFrameName(str);
		auto pokerSprite = PokerSprite::create(sprite, poker);

		//----------------------------------------
		pokerSprite->retain();

		s_pokersMap.insert(std::pair<decltype(poker), decltype(pokerSprite)>(poker, pokerSprite));
	}
}

std::vector<Poker> PokerController::getRandomPokers()
{
	return s_pokers;
}

void PokerController::randomPokers()
{
	//srand((unsigned)time(nullptr));	//开启随机种子
	for (int i = s_pokers.size(); i > 0; --i)
	{
		auto randomIndex = rand() % i;
		std::swap(s_pokers[i - 1], s_pokers[randomIndex]);
	}
}

std::vector<PokerSprite*> PokerController::genPokerSprites(const std::vector<Poker>& pokers_)
{
	std::vector<PokerSprite*> result;
	for (int i = 0; i < pokers_.size(); ++i)
	{
		auto sprite = s_pokersMap.at(pokers_.at(i));
		result.push_back(sprite);
	}

	return result;
}

PokerSprite* PokerController::genPokerSprite(Poker poker_)
{
	return s_pokersMap.at(poker_);
}

int PokerController::calcImageIndex(const Poker& poker_)
{
	int result = 0;

	switch (poker_.type)
	{
	case Poker::BLACKJOKER:
	case Poker::REDJOKER:
	case Poker::BACK:	result = poker_.type; break;
	default:
		result = poker_.type * SINGLE_TYPE_CARD_NUM + poker_.value - 1;
		break;
	}

	return result;
}
