#include "CountDownController.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "HolderPlayerInstance.h"
#include "Player.h"

void CountDownController::startCountDown(Player* player_)
{
	//传递玩家对象的原因是，等计时器计时结果，可以通过玩家对象
	//调用其出牌回调函数
	if (player_ == HolderPlayerInstance::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(HOLDER_START_COUNTDOWN,
			player_);
	}
	else if (player_ == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(COMPUTER_ONE_START_COUNTDOWN,
			player_);
	}
	else if (player_ == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(COMPUTER_TWO_START_COUNTDOWN,
			player_);
	}
}

void CountDownController::stopCountDown(Player* player_)
{
	//主动结束计时（手动玩家点击出牌或者不出按钮后，
	//应该停止计时器）
	if (player_ == HolderPlayerInstance::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(HOLDER_STOP_COUNTDOWN,
			nullptr);
	}
}
