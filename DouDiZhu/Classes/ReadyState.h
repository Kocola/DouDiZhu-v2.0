#ifndef					__READYSTATE_H__
#define					__READYSTATE_H__

/*	×¼±¸×´Ì¬ --- 2017.6.7
*/

#include "State.h"

class GameController;

class ReadyState : public State
{
public:
	ReadyState(GameController* gameController_);

public:
	virtual void handle();

	virtual void update();

private:
	GameController* _gameController;
};

#endif
