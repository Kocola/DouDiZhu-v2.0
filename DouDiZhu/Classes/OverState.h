#ifndef					__OVER_STATE_H__
#define					__OVER_STATE_H__

/* ½áÊø×´Ì¬	--- 2017.6.13
*/

#include "State.h"

class GameController;

class OverState : public State
{
public:
	OverState(GameController* gameController_);

public:
	virtual void handle() override;

	virtual void update() override;

private:
	GameController* _gameController;
};

#endif