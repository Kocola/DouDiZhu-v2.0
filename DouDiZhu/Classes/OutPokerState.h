#ifndef					__OUT_POKER_STATE_H__
#define					__OUT_POKER_STATE_H__

/* 出牌状态	---	2017.6.10
*/

#include "State.h"

class CountDownController;
class GameController;
class OutPokers;
class Player;

class OutPokerState : public State
{
public:
	OutPokerState(GameController* gameController_);

public:
	virtual void handle();

	virtual void update();

private:
	void init();

	void initContent();

	void over(float delta_);

private:
	//更新出牌顺序
	void updateOutOrderCallback(cocos2d::Ref*);

	//更新上一手牌回调，用于外部修改上一手牌
	void updateLastOutPokersCallback(cocos2d::Ref* sender_);

private:
	GameController*			_gameController;
	std::vector<Player*>		_players;
	int								_startIndex;			//开始出牌的玩家下标
	int								_curOutPlayerIndex;	//当前出牌的玩家下标
	OutPokers*					_lastOutPokers;		//玩家当前出牌，用于给下一个玩家决定出牌，初始化必须为nullptr
	const int HOLDER_PLAYER_INDEX = 0;		//手动玩家在玩家数组里的下标
};

#endif