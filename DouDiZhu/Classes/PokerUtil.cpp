#include "PokerUtil.h"

bool util::PokerUtil::pokerCmp(const Poker& lhs_, const Poker& rhs_, bool withType_)
{
	//如果是大小王，那么直接判断并返回比较结果
	if (lhs_.type == Poker::REDJOKER)
	{
		return true;
	}
	else if (rhs_.type == Poker::REDJOKER)
	{
		return false;
	}
	else if (lhs_.type == Poker::BLACKJOKER)
	{
		return true;
	}
	else if (rhs_.type == Poker::BLACKJOKER)
	{
		return false;
	}

	//非大小王
	int lhsValue = lhs_.value;
	int rhsValue = rhs_.value;
	//如果扑克的牌面值相同，那么直接根据花色排序
	if (lhsValue == rhsValue)
	{
		if (withType_ == true)
		{
			return lhs_.type > rhs_.type;
		}
		else if (withType_ == false)
		{
			return false;	//相等就不是 >,因此返回false
		}
	}
	else
	{
		//如果扑克的牌面值不等，那么首先将A和2的情况排序，然后根据牌面值大小排序即可
		if (lhsValue == 2)
		{
			return true;
		}
		else if (rhsValue == 2)
		{
			return false;
		}
		else if (lhsValue == 1)
		{
			return true;
		}
		else if (rhsValue == 1)
		{
			return false;
		}
		
		return lhsValue > rhsValue;
	}
}

bool util::PokerUtil::pokerCmpWithType(const Poker& lhs_, const Poker& rhs_)
{
	return pokerCmp(lhs_, rhs_, true);
}

bool util::PokerUtil::pokerCmpWithoutType(const Poker& lhs_, const Poker& rhs_)
{
	return pokerCmp(lhs_, rhs_, false);
}

void util::PokerUtil::sort(std::vector<Poker>& pokers_)
{
	std::sort(pokers_.begin(), pokers_.end(), pokerCmpWithType);
}

Poker util::PokerUtil::getGreaterPoker(Poker poker_, int increaseValue /*= 1*/)
{
	//不允许查找的牌比当前小
	CC_ASSERT(increaseValue >= 0);

	int curValue = poker_.value;
	int needValue = curValue + increaseValue;
	if (needValue >= 3 && needValue <= 13)
	{
		poker_.value = needValue;
		return poker_;
	}
	switch (needValue)
	{
	case 14:
		poker_.value = 1;
		break;
	case 15:
		poker_.value = 2;
		break;
	case 16:
		poker_.type = Poker::BLACKJOKER;
		poker_.value = 0;
		break;
	case 17:
		poker_.type = Poker::REDJOKER;
		poker_.value = 0;
		break;
	default:
		poker_.type = Poker::NONE;
		break;
	}

	return poker_;
}



