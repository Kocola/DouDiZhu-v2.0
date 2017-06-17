#ifndef					__POKER_H__
#define					__POKER_H__

/* 扑克	--- 2017.6.9
*/

#include "cocos2d.h"

#include "Common.h"

struct Poker : public cocos2d::Ref
{
	enum Type
	{
		DIAMOND = 0,			//方块
		CLUB,						//梅花
		HEART,						//红桃
		SPADE = 3,				//黑桃
		BLACKJOKER = 52,	//小王
		REDJOKER = 53,		//大王
		BACK = 54,				//扑克背面
		NONE,						//不存在的牌型（用于返回结果表示所需的牌不存在）
	};

	Poker() = default;

	Poker(Type type_, int value_ = 0);

	bool operator==(const Poker& poker_);

	Type type;		//牌型
	int    value;	//牌值
};

namespace std
{
	template<>
	struct hash < Poker >
	{
		std::size_t operator()(const Poker& poker_) const
		{
			return poker_.type * SINGLE_TYPE_CARD_NUM + poker_.value;
		}
	};

	bool operator==(const Poker& lhs_, const Poker& rhs_);
};

#endif