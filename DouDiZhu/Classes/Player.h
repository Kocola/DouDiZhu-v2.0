#ifndef					__PLAYER_H__
#define					__PLAYER_H__

/* 玩家类	---	2017.6.7
*/

#include "cocos2d.h"
#include "PokerController.h"

class OutPokers;

class Player : public cocos2d::Ref
{
public:
	enum Type
	{
		LANDLORD,
		FARMER
	};
public:
	void setPokers(const std::vector<Poker>& pokers_);

	void pushPoker(const Poker& poker_);

	int getCallScore() const;

	void setCallScore(int score_);

	//玩家类型相关
	Type getPlayerType() const;

	void setPlayerType(Type type_);

	void setPokersCanClick(bool canClick_);

	bool isWinner() const;	//根据是否出完牌判断是否是赢家

public:
	//叫地主
	virtual void callLandlord() = 0;

	//出牌
	virtual void outPokers(OutPokers* lastOutPokers_) = 0;

	//出牌回调（提供给计时器计时结束调用）
	virtual void outPokersCallback() = 0;

	//根据上一手玩家出的牌查找合适的牌
	virtual std::vector<Poker> searchOutPokers(OutPokers* lastOutPokers_);

	//根据出的牌，创建一个OutPokers对象，用于记录上一手牌信息
	OutPokers* createLastOutPokers(const std::vector<Poker>& pokers_);

protected:
	std::vector<Poker>	_holdPokers;		//持有的牌
	std::vector<Poker>	 _outedPokers;	//当前打出的牌
	//cocos2d::Vector<Poker*>	_outedPokersForPost;	//当前打出的牌，用于消息传递，避免使用局部变量传递消息被回收
	int							 _callScore;
	Type							 _type;				//玩家类型
	//OutPokers*				_lastOutPokers;	//上一手扑克，初始化为nullptr，轮到其出牌时获取，出完牌后必须置nullptr
};

#endif