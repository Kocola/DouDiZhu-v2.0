#include "GameRule.h"

#include "OutPokers.h"
#include "PokerSetType.h"
#include "Util.h"

#define COMPARE_POKER_GREATER(a, b) util::PokerUtil::pokerCmpWithoutType(a, b)
#define COMPARE_POKER_EQUAL(a, b) !util::PokerUtil::pokerCmpWithoutType(a, b) && \
	!util::PokerUtil::pokerCmpWithoutType(b, a)

bool GameRule::isSingle(const std::vector<Poker>& pokers_)
{
	return pokers_.size() == 1;
}

bool GameRule::isPair(const std::vector<Poker>& pokers_)
{
	//两张，均不是王，且牌值一样
	if (pokers_.size() != 2)
	{
		return false;
	}
	else if (isKing(pokers_.at(0)) || isKing(pokers_.at(1)))
	{
		return false;
	}
	else if (pokers_.at(0).value != pokers_.at(1).value)
	{
		return false;
	}

	return true;
}

bool GameRule::isTriple(const std::vector<Poker>& pokers_)
{
	//三张，均不是王，牌值一样
	if (pokers_.size() != 3)
	{
		return false;
	}
	else if (isKing(pokers_.at(0)) || isKing(pokers_.at(1)) || isKing(pokers_.at(2)))
	{
		return false;
	}
	else if (pokers_.at(0).value != pokers_.at(1).value ||
		pokers_.at(1).value != pokers_.at(2).value)
	{
		return false;
	}

	return true;
}

bool GameRule::isTripleWithSingle(std::vector<Poker> pokers_)
{
	//不是4张或者存在炸弹，返回false
	if (pokers_.size() != 4)
	{
		return false;
	}
	else if (isExistBomb(pokers_))
	{
		return false;
	}

	//排序
	util::PokerUtil::sort(pokers_);

	//两种情况，1-3或者3-1
	//3-1
	std::vector<Poker> pokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 3);
	if (isTriple(pokers))
	{
		return true;
	}

	//1-3
	pokers = std::vector<Poker>(pokers_.begin() + 1, pokers_.begin() + 4);
	if (isTriple(pokers))
	{
		return true;
	}

	//均不是，返回false
	return false;
}

bool GameRule::isTripleWithPair(std::vector<Poker> pokers_)
{
	//不是5张，返回false
	if (pokers_.size() != 5)
	{
		return false;
	}

	//排序
	util::PokerUtil::sort(pokers_);

	//两种情况，2-3或者3-2
	//2-3
	std::vector<Poker> pairPokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 2);
	std::vector<Poker> triplePokers = std::vector<Poker>(pokers_.begin() + 2, pokers_.begin() + 5);
	if (isPair(pairPokers) && isTriple(triplePokers))
	{
		return true;
	}

	//3-2
	triplePokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 3);
	pairPokers = std::vector<Poker>(pokers_.begin() + 3, pokers_.begin() + 5);
	if (isTriple(triplePokers) && isPair(pairPokers))
	{
		return true;
	}

	return false;
}

bool GameRule::isSingleStraight(std::vector<Poker> pokers_)
{
	//排序
	util::PokerUtil::sort(pokers_);

	auto firstPoker = pokers_.front();
	//如果第一张是王，或者2，那么肯定不是顺子
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//如果第一张是A
	if (firstPoker.value == 1)
	{
		//如果第2张不是K，返回false
		if (pokers_.at(1).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 1; i < pokers_.size() - 1; ++i)
			{
				if (pokers_.at(i).value != pokers_.at(i + 1).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	//如果第一张不是A
	else
	{
		for (int i = 0; i < pokers_.size() - 1; ++i)
		{
			if (pokers_.at(i).value != pokers_.at(i + 1).value + 1)
			{
				return false;
			}
		}
		return true;
	}
}

bool GameRule::isPairStraight(std::vector<Poker> pokers_)
{
	//如果扑克数不是偶数，那么肯定不是双顺
	if (pokers_.size() % 2 != 0)
	{
		return false;
	}

	//排序
	util::PokerUtil::sort(pokers_);

	const auto firstPoker = pokers_.front();
	//如果第一张是王，或者2，那么肯定不是双顺
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//判断是否都是对子
	for (int i = 0; i <= pokers_.size() - 2; i += 2)
	{
		auto pairPokers = std::vector<Poker>(pokers_.begin() + i, pokers_.begin() + i + 2);
		if (isPair(pairPokers) == false)
		{
			return false;
		}
	}

	//和单顺一样，判断是否是连续的
	if (firstPoker.value == 1)
	{
		if (pokers_.at(2).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 2; i < pokers_.size() - 2; i += 2)
			{
				if (pokers_.at(i).value != pokers_.at(i + 2).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	else
	{
		for (int i = 0; i < pokers_.size() - 2; i += 2)
		{
			if (pokers_.at(i).value != pokers_.at(i + 2).value + 1)
			{
				return false;
			}
			return true;
		}
	}
}

bool GameRule::isTripleStraight(std::vector<Poker> pokers_)
{
	//如果扑克数不是3的倍数，且倍数至少为2，那么肯定不是三顺
	if (pokers_.size() % 3 != 0 || pokers_.size() < 6)
	{
		return false;
	}

	//排序
	util::PokerUtil::sort(pokers_);

	auto firstPoker = pokers_.front();
	//和单顺的判断逻辑类似
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//判断是否都是三张
	for (int i = 0; i <= pokers_.size() - 3; i += 3)
	{
		auto triplePokers = std::vector<Poker>(pokers_.begin() + i, pokers_.begin() + i + 3);
		if (isTriple(triplePokers) == false)
		{
			return false;
		}
	}

	if (firstPoker.value == 1)
	{
		if (pokers_.at(3).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 3; i < pokers_.size() - 3; i += 3)
			{
				if (pokers_.at(i).value != pokers_.at(i + 3).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	else
	{
		for (int i = 0; i < pokers_.size() - 3; i += 3)
		{
			if (pokers_.at(i).value != pokers_.at(i + 3).value + 1)
			{
				return false;
			}
		}
		return true;
	}
}

bool GameRule::isTripleStraightWithSingle(std::vector<Poker> pokers_)
{
	//如果不是（3+1）*X的形式，且X至少为2，那么肯定不是3带1
	if (pokers_.size() % 4 != 0 || pokers_.size() < 8)
	{
		return false;
	}

	auto tmp = splitTriplesInPokers(pokers_);
	auto triplePokers = tmp.first;
	auto remainedPokers = tmp.second;

	//三张的数目必须和单张的数目相等，否则返回false
	if (triplePokers.size() != 3 * remainedPokers.size())
	{
		return false;
	}

	//三张是不是顺子
	if (isTripleStraight(triplePokers) == false)
	{
		return false;
	}

	return true;
}

bool GameRule::isTripleStraightWithPair(std::vector<Poker> pokers_)
{
	//如果不是（3+2）*X的形式，且X至少2，那么肯定不是3带2
	if (pokers_.size() % 5 != 0 || pokers_.size() < 10)
	{
		return false;
	}

	//拆成三张的集合及两张的集合
	auto tmp = splitTriplesInPokers(pokers_);
	auto triplePokers = tmp.first;
	auto remainedPokers = tmp.second;

	if (triplePokers.size() / 3 != remainedPokers.size() / 2)
	{
		return false;
	}

	//拆分出的remainedPokers是否都是对子
	if (isAllPair(remainedPokers) == false)
	{
		return false;
	}

	if (isTripleStraight(triplePokers) == false)
	{
		return false;
	}

	return true;
}

bool GameRule::isBomb(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() != 4)
	{
		return false;
	}

	return isValueEqual(pokers_);
}

bool GameRule::isKingBomb(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() != 2)
	{
		return false;
	}

	if (isKing(pokers_.at(0)) && isKing(pokers_.at(1)))
	{
		return true;
	}

	return false;
}

bool GameRule::isKing(const Poker& poker_)
{
	if (poker_.type == Poker::BLACKJOKER ||
		poker_.type == Poker::REDJOKER)
	{
		return true;
	}
	return false;
}

bool GameRule::isExistBomb(const std::vector<Poker>& pokers_)
{
	int index = 0;
	while (index <= pokers_.size() - 4)
	{
		auto tmp = std::vector<Poker>(pokers_.begin() + index, pokers_.begin() + index + 4);
		if (isBomb(tmp) == true)
		{
			return true;
		}
		index++;
	}
	return false;
}

bool GameRule::isValueEqual(const std::vector<Poker>& pokers_)
{
	auto firstPoker = pokers_.front();

	if (isKing(firstPoker))
	{
		return false;
	}

	for (int i = 1; i < pokers_.size(); ++i)
	{
		if (pokers_.at(i).value != firstPoker.value)
		{
			return false;
		}
	}

	return true;
}

bool GameRule::isAllPair(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() % 2 != 0)
	{
		return false;
	}
	for (int i = 0; i < pokers_.size() - 1; ++i)
	{
		if (pokers_.at(i).value != pokers_.at(i + 1).value)
		{
			return false;
		}
	}
	return true;
}

std::pair<std::vector<Poker>, std::vector<Poker>> 
	GameRule::splitTriplesInPokers(const std::vector<Poker>& pokers_)
{
	//从原有的牌中拆分三张
	std::vector<Poker> pokers = pokers_;
	std::vector<Poker> triplePokers;
	int index = 0;
	while (index <= ((int)pokers.size() - 3))	//pokers.size()是size_t类型，如果小于3,-3后将不是负数而是一个很大的数，由此导致错误
	{
		auto tmp = std::vector<Poker>(pokers.begin() + index, pokers.begin() + index + 3);
		if (isTriple(tmp) == true)
		{
			for (int i = 0; i < tmp.size(); ++i)
			{
				triplePokers.push_back(tmp[i]);
			}
			pokers.erase(pokers.begin() + index, pokers.begin() + index + 3);
		}
		else
		{
			index += 1;
		}
	}
	//pokers为剩余的牌
	return std::pair<std::vector<Poker>, std::vector<Poker>>(triplePokers, pokers);
}

PokersType GameRule::getBasePokersType(PokersType pokersType_)
{
	switch (pokersType_){
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case BOMB:
	case KINGBOMB:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
		return pokersType_;  break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR: 
		return TRIPLE; break;
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR: 
		return TRIPLESTRAIGHT; break;
	default: 
		return NONE; break;
	}
}

Poker GameRule::getTripleStraightWithSingleLowestPoker(const std::vector<Poker>& pokers_)
{
	std::vector<Poker> tmp = splitTriplesInPokers(pokers_).first;
	Poker result = tmp.back();
	return result;
}

Poker GameRule::getTripleStraightWithPairLowestPoker(const std::vector<Poker>& pokers_)
{
	return getTripleStraightWithSingleLowestPoker(pokers_);
}

bool GameRule::canOutPokers(std::vector<Poker> waitOutPokers, const OutPokers& lastOutPokers)
{
	//排序
	util::PokerUtil::sort(waitOutPokers);

	//两者之一是王炸
	if (isKingBomb(waitOutPokers))
	{
		return true;
	}
	if (lastOutPokers.getPokersType() == PokersType::KINGBOMB)
	{
		return false;
	}

	//两者之一是炸弹
	if (lastOutPokers.getPokersType() == PokersType::BOMB)
	{
		//待出牌是否是炸弹，如果是，那么是否大于上一手牌的炸弹（根据牌面值决定炸弹大小）
		if (isBomb(waitOutPokers) == BOMB &&
			COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (isBomb(waitOutPokers))
	{
		return true;
	}

	//两者牌型必须相同
	//过滤牌型里附带的扑克
	auto filterPokers = filterAccessoryPokers(waitOutPokers);
	PokersType waitOutPokersType = getBasePokersType(analysePokersType(waitOutPokers));
	PokersType lastOutPokersType = getBasePokersType(lastOutPokers.getPokersType());

	//类型不一致，返回false
	if (waitOutPokersType != lastOutPokersType)
	{
		return false;
	}

	//类型一致时
	//如果是顺子
	if (lastOutPokersType == STRAIGHT || lastOutPokersType == PAIRSTRAIGHT ||
		lastOutPokersType == TRIPLESTRAIGHT)
	{
		//牌数是否一致
		if (lastOutPokers.getTotalLen() != waitOutPokers.size())
		{
			return false;
		}
		//待出牌是否大于上一个玩家的牌
		else if (!COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return false;
		}
		return true;
	}

	//不是顺子
	if (lastOutPokers.getTotalLen() == waitOutPokers.size())
	{
		if (COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return true;
		}
	}

	return false;
}

std::vector<Poker> GameRule::searchProperPokers(const std::vector<Poker>& pokers_)
{
	std::vector<Poker> result;
	//先找单张
	result = calcPokersWithType(pokers_, SINGLE);
	if (result.size() == 0)	//没找到单张
	{
		result = calcPokersWithType(pokers_, PAIR);
		if (result.size() == 0)
		{
			result = calcPokersWithType(pokers_, TRIPLE);
			if (result.size() == 0)
			{
				//这里没有找王炸
				result = calcPokersWithType(pokers_, BOMB);
			}
		}
	}

	return result;
}

std::vector<Poker> GameRule::filterAccessoryPokers(const std::vector<Poker>& pokers_)
{
	PokersType pokersType = analysePokersType(pokers_);

	switch (pokersType)
	{
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case BOMB:
	case KINGBOMB:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
		return pokers_;
		break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		return splitTriplesInPokers(pokers_).first;
		break;
	default:
		CC_ASSERT(0 != 0); 
		break;
	}
}

std::vector<Poker> GameRule::calcPokersWithType(std::vector<Poker> pokers_, PokersType pokersType_, 
	const Poker* poker_ /*= nullptr*/, int length /*= 0*/)
{
	//排序
	util::PokerUtil::sort(pokers_);

	switch (pokersType_)
	{
	case SINGLE:
		return searchSingle(pokers_, poker_);
		break;
	case PAIR:
		return searchPair(pokers_, poker_);
		break;
	case TRIPLE:
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//如果是3带1或者3带2，全部查找3张即可
		return searchTriple(pokers_, poker_);
		break;
	case BOMB:
		return searchBomb(pokers_, poker_);
		break;
	case KINGBOMB:
		return searchKingBomb(pokers_);
		break;
	case STRAIGHT:
		return searchSingleStraight(pokers_, length, poker_);
		break;
	case PAIRSTRAIGHT:
		return searchPairStraight(pokers_, length, poker_);
		break;
	case TRIPLESTRAIGHT:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		//如果是三顺带1或者三顺带2，全部查找三顺即可
		return searchTripleStraight(pokers_, length, poker_);
		break;
	default:
		break;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::calcPokersWithTypeInSplit(std::vector<Poker> pokers_, PokersType pokersType_, const Poker* poker_ /*= nullptr*/, int length /*= 0*/)
{
	//排序
	util::PokerUtil::sort(pokers_);

	switch (pokersType_)
	{
	case SINGLE:
		return searchSingleInSplit(pokers_, poker_);
		break;
	case PAIR:
		return searchPairInSplit(pokers_, poker_);
		break;
	case TRIPLE:
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//如果是3带1或者3带2，全部查找3张即可
		return searchTripleInSplit(pokers_, poker_);
		break;
	case BOMB:
		return searchBomb(pokers_, poker_);
		break;
	case KINGBOMB:
		return searchKingBomb(pokers_);
		break;
	case STRAIGHT:
		return searchSingleStraight(pokers_, length, poker_);
		break;
	case PAIRSTRAIGHT:
		return searchPairStraight(pokers_, length, poker_);
		break;
	case TRIPLESTRAIGHT:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		//如果是三顺带1或者三顺带2，全部查找三顺即可
		return searchTripleStraight(pokers_, length, poker_);
		break;
	default:
		break;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingle(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.empty())
	{
		return std::vector<Poker>();
	}

	//因为牌面从大到小排序的，因此需要从高位来查找
	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		/* 首先判断是否牌面值大于要找的牌，如果是，那就可以进一步判断是对子，三张，炸弹等，这样可以减轻计算量
		判断对子等的作用是防止拆牌，在非顺子的前提下，不可以拆牌*/
		if (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_))
		{
			if (index - 1 >= 0)
			{
				tmp.push_back(pokers_.at(index - 1));
				if (isPair(tmp))
				{
					if (index - 2 >= 0)
					{
						tmp.push_back(pokers_.at(index - 2));
						if (isTriple(tmp))
						{
							if (index - 3 >= 0)
							{
								tmp.push_back(pokers_.at(index - 3));
								if (isBomb(tmp))
								{
									index = index - 4;
									continue;
								}
								tmp.pop_back();//如果不是炸弹，那么要当前最后一张popBack
							}
							index = index - 3;
							continue;
						}
						tmp.pop_back();//如果不是三张，那么要当前最后一张popBack
					}
					index = index - 2;
					continue;
				}
				tmp.pop_back();
			}
			return tmp;
		}
		index = index - 1;
		tmp.clear();
	}

	//存在的一个问题，为了不拆牌，可能出现333444555这种情况时，不会出单张
	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchPair(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	//>= 1的目的是，保证每轮循环至少有两张牌
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			if (index - 2 >= 0)
			{
				tmp.push_back(pokers_.at(index - 2));
				if (isTriple(tmp) == true)
				{
					if (index - 3 >= 0)
					{
						tmp.push_back(pokers_.at(index - 3));
						if (isBomb(tmp) == true)
						{
							index = index - 4;
							continue;
						}
						tmp.pop_back();
					}
					index = index - 3;
					continue;
				}
				tmp.pop_back();//如果不是三张，那么要当前最后一张popBack
			}
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchTriple(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 3)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));

		if (isTriple(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			if (index - 3 >= 0)
			{
				tmp.push_back(pokers_.at(index - 3));
				if (isBomb(tmp) == true)
				{
					index = index - 4;
					continue;
				}
				tmp.pop_back();	//如果不是炸弹，那么要当前最后一张popBack
			}
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchBomb(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 4)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index - 3 >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		tmp.push_back(pokers_.at(index - 3));
		if (isBomb(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchKingBomb(const std::vector<Poker>& pokers_)
{
	//如果扑克的张数小于2，那么肯定不是王炸
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	//两张王肯定是整个牌面的第一第二张，
	//因此直接将前两张牌放入一个vector，调用isKingBomb函数来判断
	std::vector<Poker> tmp{ pokers_.at(0), pokers_.at(1) };

	if (isKingBomb(tmp))
	{
		return tmp;
	}
	
	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedSingle(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.empty() || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
		{
			return tmp;
		}
		//如果当前扑克已经大于要找的扑克，那么直接break
		if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
		{
			break;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedPair(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.size() < 2 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true)
		{
			if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
			{
				return tmp;
			}
			if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
			{
				break;
			}
			index = index - 2;
		}
		else
		{
			index = index - 1;
		}
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedTriple(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.size() < 3 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		if (isTriple(tmp) == true)
		{
			if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
			{
				return tmp;
			}
			if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
			{
				break;
			}
			index = index - 3;
		}
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	//如果length参数出错（小于5张，或大于12张），
	//或者扑克的张数不足所需的length，那么直接返回空
	if (length_ < 5 || length_ > 12 || pokers_.size() < length_ || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	//如果查找的顺子的最小的牌面值是1或者2，
	//以及所需顺子牌面最低值+顺子长度（此时就是顺子牌面的最大值）> A（14）,那么直接返回空
	int pokerValue = poker_->value;
	//如果查找的牌值是0，表明是大王或者小王
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		return std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			//没有符合要求的牌
			if (tmpPoker.type == Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedSingle(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.front());
			}
		}
		//查询所得的结果，是递增的，和规定的递减相反，因此这里排序一次
		if (result.size() == length_)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		//当前已经查找失败，将index+1，从下一个开始查找
		index++;
	}

	return std::vector<Poker>();
}

//length这里是顺子的不同牌的个数
std::vector<Poker> GameRule::searchPairStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	if (length_ < 2 || length_ >= 12 || pokers_.size() < length_ * 2 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int pokerValue = poker_->value;
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		return std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			if (tmpPoker.type = Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedPair(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.at(0));
				result.push_back(tmpPokers.at(1));
			}
		}
		if (result.size() == length_ * 2)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		//当前已经查找失败，将index + 1，从下一个开始查找
		index++;
	}

	return std::vector<Poker>();
}

//length这里是顺子的不同牌的个数
std::vector<Poker> GameRule::searchTripleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	if (length_ < 3 || length_ > 12 || pokers_.size() < length_ * 3)
	{
		return std::vector<Poker>();
	}

	int pokerValue = poker_->value;
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			if (tmpPoker.type == Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedTriple(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.at(0));
				result.push_back(tmpPokers.at(1));
				result.push_back(tmpPokers.at(2));
			}
		}
		if (result.size() == length_ * 3)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		index++;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() == 0)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		if (poker_ == nullptr || COMPARE_POKER_GREATER(pokers_.at(index), *poker_))
		{
			std::vector<Poker> tmp;
			tmp.push_back(pokers_.at(index));
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchPairInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true && (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchTripleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 3)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		if (isTriple(tmp) == true && (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

PokersType GameRule::analysePokersType(std::vector<Poker> pokers_)
{
	if (pokers_.empty())
	{
		return NONE;
	}

	//排序
	util::PokerUtil::sort(pokers_);

	if (pokers_.size() < 5)
	{
		if (isSingle(pokers_))
		{
			return SINGLE;
		}

		if (isKingBomb(pokers_))
		{
			return KINGBOMB;
		}

		if (isPair(pokers_))
		{
			return PAIR;
		}

		if (isTriple(pokers_))
		{
			return TRIPLE;
		}

		if (isTripleWithSingle(pokers_))
		{
			return TRIPLEWITHSINGLE;
		}

		if (isBomb(pokers_))
		{
			return BOMB;
		}
	}
	else
	{
		if (isTripleWithPair(pokers_))
		{
			return TRIPLEWITHPAIR;
		}

		if (isSingleStraight(pokers_))
		{
			return STRAIGHT;
		}

		if (isPairStraight(pokers_))
		{
			return PAIRSTRAIGHT;
		}

		if (isTripleStraight(pokers_))
		{
			return TRIPLESTRAIGHT;
		}

		if (isTripleStraightWithSingle(pokers_))
		{
			return TRIPLESTRAIGHTWITHSINGLE;
		}

		if (isTripleStraightWithPair(pokers_))
		{
			return TRIPLESTRAIGHTWITHPAIR;
		}
	}

	return NONE;
}

bool GameRule::isPokerValueType(const std::vector<Poker>& pokers_)
{
	return !(analysePokersType(pokers_) == NONE);
}

bool GameRule::isSpecifiedPokerType(const std::vector<Poker>& pokers_, PokersType pokerType_)
{
	auto pokerType = analysePokersType(pokers_);
	return pokerType_ != NONE && pokerType_ == pokerType;
}

Poker GameRule::getLowestPoker(const std::vector<Poker>& pokers_, PokersType pokerType_)
{
	CC_ASSERT(pokerType_ != NONE);

	int pokersSize = pokers_.size();
	Poker result;

	switch (pokerType_)
	{
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
	case BOMB:
	case KINGBOMB:
		result = pokers_.back();
		break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//3带1或者3带2的三张肯定有一张在扑克的第3张
		result = pokers_.at(2);
		break;
	case TRIPLESTRAIGHTWITHSINGLE:
		result = getTripleStraightWithSingleLowestPoker(pokers_);
		break;
	case TRIPLESTRAIGHTWITHPAIR:
		result = getTripleStraightWithPairLowestPoker(pokers_);
		break;
	default:
		CC_ASSERT(0 != 0);
		break;
	}

	return result;
}
