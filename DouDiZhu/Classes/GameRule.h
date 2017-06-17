#ifndef					__GAME_RULE_H__
#define					__GAME_RULE_H__

/*	游戏规则（出牌相关）	---	2017.6.11
*/

#include <vector>

#include "Poker.h"
#include "PokerSetType.h"
#include "Singleton.h"

class OutPokers;

//单例类
class GameRule : public Singleton < GameRule >
{
public:
	//根据当前待出牌和上一手牌，判断当前牌是否可出
	bool canOutPokers(std::vector<Poker> waitOutPokers, const OutPokers& lastOutPokers);

	//电脑在自己可以任意出牌时，找到一张合适的牌
	//（这里为了赶时间，只是简单地由单张，对子，三张，顺子，炸弹）
	//若要AI做得更好，这个函数需要更新
	std::vector<Poker> searchProperPokers(const std::vector<Poker>& pokers_);

	//过滤掉XX带Y里的Y
	std::vector<Poker> filterAccessoryPokers(const std::vector<Poker>& pokers_);

public:
	//分析给定扑克的牌型
	PokersType analysePokersType(std::vector<Poker> pokers_);

	//是否是扑克类型
	bool isPokerValueType(const std::vector<Poker>& pokers_);

	//给定的扑克是否是某种牌型
	bool isSpecifiedPokerType(const std::vector<Poker>& pokers_, PokersType pokerType_);

	//获取扑克里值最小的扑克
	Poker getLowestPoker(const std::vector<Poker>& pokers_, PokersType pokerType_);

	/* 获取指定的类型的扑克，返回Vector为空时表示查找失败
	第一个参数是玩家拥有的扑克，第三个参数是返回的类型的扑克里最小的牌，如果是nullptr，表明可以出任意值的该类型扑克
	第四个参数是针对顺子时的长度 */
	//不可拆牌
	std::vector<Poker> calcPokersWithType(std::vector<Poker> pokers_, PokersType pokersType_, 
		const Poker* poker_ = nullptr, int length = 0);

	//可拆牌
	std::vector<Poker> calcPokersWithTypeInSplit(std::vector<Poker> pokers_, PokersType pokersType_, 
		const Poker* poker_ = nullptr, int length = 0);

private:
	/* 第一个参数是玩家的牌面，第二个是上家对应出牌的最小扑克的指针，默认为nullptr，
	表示查找任意对应的牌型即可，否则需要 大于 poker_的对应牌型才可以 */
	//查找单张
	std::vector<Poker> searchSingle(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找对子
	std::vector<Poker> searchPair(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找三张
	std::vector<Poker> searchTriple(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找炸弹
	std::vector<Poker> searchBomb(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找王炸
	std::vector<Poker> searchKingBomb(const std::vector<Poker>& pokers_);

	//查找固定值的单张，对子，三张
	std::vector<Poker> searchSpecifiedSingle(const std::vector<Poker>& pokers_, const Poker* poker_);

	std::vector<Poker> searchSpecifiedPair(const std::vector<Poker>& pokers_, const Poker* poker_);

	std::vector<Poker> searchSpecifiedTriple(const std::vector<Poker>& pokers_, const Poker* poker_);

	/* searchStraight是查找三种顺子的基本函数，其它三种都要调用这个函数,
	length用于限制顺子的长度是多少，例如56789 长度就是5
	单顺长度至少是5，双顺和三顺的长度至少是3*/
	//查找顺子
	std::vector<Poker> searchSingleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

	//查找双顺
	std::vector<Poker> searchPairStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

	//查找三顺
	std::vector<Poker> searchTripleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

private:
	//拆牌查找
	//查找单张
	std::vector<Poker> searchSingleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找对子
	std::vector<Poker> searchPairInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//查找三张
	std::vector<Poker> searchTripleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);
	
private:
	//是否是单张
	bool isSingle(const std::vector<Poker>& pokers_);

	//是否是对子
	bool isPair(const std::vector<Poker>& pokers_);

	//是否是三张
	bool isTriple(const std::vector<Poker>& pokers_);

	//是否是3带1
	bool isTripleWithSingle(std::vector<Poker> pokers_);

	//是否是3带2
	bool isTripleWithPair(std::vector<Poker> pokers_);

	//是否是单顺子
	bool isSingleStraight(std::vector<Poker> pokers_);

	//是否是双顺
	bool isPairStraight(std::vector<Poker> pokers_);

	//是否是无单张或双张的三顺
	bool isTripleStraight(std::vector<Poker> pokers_);

	//是否是带同数量单张的三顺
	bool isTripleStraightWithSingle(std::vector<Poker> pokers_);

	//是否是带通数量双张的三顺
	bool isTripleStraightWithPair(std::vector<Poker> pokers_);

	//是否是炸弹
	bool isBomb(const std::vector<Poker>& pokers_);

	//是否是王炸
	bool isKingBomb(const std::vector<Poker>& pokers_);

	//是否是大小王
	bool isKing(const Poker& poker_);

private:
	//是否存在炸弹，用于分离三张时避免分离炸弹造成的问题
	bool isExistBomb(const std::vector<Poker>& pokers_);

	//是否牌值都相等
	bool isValueEqual(const std::vector<Poker>& pokers_);

	//是否都为对子
	bool isAllPair(const std::vector<Poker>& pokers_);

	//从pokers_中的扑克获取所有的三张，返回的是一个pair
	//第一个是分离的三张
	//第二个是剩下的牌
	std::pair<std::vector<Poker>, std::vector<Poker>>
		splitTriplesInPokers(const std::vector<Poker>& pokers_);

	/* 例如单张，返回SINGLE，三带1和三带2，三张都返回TRIPLE，
		三顺带1，三顺带2，三顺都返回TRIPLESTRAIGHT，这样做的目的是为了兼容牌型非完全一致，但是
		基本牌型却是一致的情况，不然的话，三张和三带1就无法等价，可是如果把三带一直接返回TRIPLE，
		又会导致其它问题，现在这种办法是折中的办法*/
	PokersType getBasePokersType(PokersType pokersType_);

	//获取三顺带1中三顺最小的牌
	Poker getTripleStraightWithSingleLowestPoker(const std::vector<Poker>& pokers_);

	//获取三顺带2中三顺最小的牌
	Poker getTripleStraightWithPairLowestPoker(const std::vector<Poker>& pokers_);
};

#endif