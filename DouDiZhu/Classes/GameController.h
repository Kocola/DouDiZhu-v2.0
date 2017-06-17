#ifndef					__GAME_CONTROLLER_H__
#define					__GAME_CONTROLLER_H__

/* 游戏控制器 --- 2017.6.7 
*/

#include "cocos2d.h"
#include "State.h"

class GameController : private cocos2d::Ref
{
public:
	static GameController& getIns();

	static GameController* getInstance();

public:
	State* getStartState() const;

	State* getReadyState() const;

	State* getDealState() const;

	State* getCalllLandlordState() const;

	State* getOutPokerState() const;

	State* getOverState() const;

public:
	void setState(State* state_);

	void start();	//开始游戏状态运行

	void runState();		//运行当前状态

	void updateState();	//切换至下一个状态

private:
	GameController();

private:
	bool initContent();

	void update(float delta_);

private:
	void updateStateCallback(cocos2d::Ref*);	//切换至下一个状态回调

private:
	State*				_state;

	State*				_startState;			//开始状态
	State*				_readyState;			//准备状态
	State*				_dealState;			//发牌状态
	State*				_callLandlordState;//叫地主状态
	State*				_outPokerState;		//出牌状态
	State*				_overState;			//结束状态
};

#endif