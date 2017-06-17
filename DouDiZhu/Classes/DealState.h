#ifndef					__DEAL_STATE_H__
#define					__DEAL_STATE_H__

/*	·¢ÅÆ×´Ì¬	---	2017.6.8
*/

#include "State.h"
#include "Poker.h"

class GameController;

class DealState : public State
{
public:
	DealState(GameController* gameController_);

public:
	virtual void handle();

	virtual void update();

protected:
	void updateStateCallback(cocos2d::Ref*);

private:
	void dealPokers(const std::vector<Poker>& randomPokers_);

	void displayLandlordPokers(std::vector<Poker>& pokers_);

private:
	GameController* _gameController;

	std::vector<Poker>	_randomPokers;
};

#endif