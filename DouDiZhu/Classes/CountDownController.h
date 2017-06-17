#ifndef					__COUNT_DOWN_CONTROLLER_H__
#define					__COUNT_DOWN_CONTROLLER_H__

/*	计时控制器	---	2017.6.13
*/

#include "cocos2d.h"
#include "Singleton.h"

class Player;

class CountDownController : public Singleton<CountDownController>
{
public:
	CountDownController() = default;

public:
	//开始计时
	void startCountDown(Player* player_);

	//停止计时
	void stopCountDown(Player* player_);
};

#endif