#ifndef					__OUT_POKERS_H__
#define					__OUT_POKERS_H__

/* 出牌集合（管理玩家所出的牌）		---	2017.6.10
*/

#include "cocos2d.h"

#include "Poker.h"
#include "PokerSetType.h"

class Player;

class OutPokers : public cocos2d::Ref
{
public:
	OutPokers(Player* pokerOwner_, Poker poker_, size_t totalLen_, PokersType pokersType_);

public:
	PokersType getPokersType() const;

	void setPokersType(PokersType pokersType_);

	size_t getTotalLen() const;

	void setTotalLen(size_t totalLen_);

	Poker getLowestPoker() const;

	void setLowestPoker(Poker poker_);

	Player* getPokerOwner() const;

private:
	PokersType	_pokersType;	//当前的牌型
	size_t				_totalLen;		//整个牌面的长度，例如334455的长度是6
	Poker				_lowestPoker;	//整个牌面牌值最小的牌
	Player*				_outPokersOwner;	//当前扑克持有者
};

#endif