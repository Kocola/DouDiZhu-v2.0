#include "OverState.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "LobbyScene.h"
#include "Player.h"

OverState::OverState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void OverState::handle()
{
	//创建结束层
	cocos2d::NotificationCenter::getInstance()->postNotification(CREATE_OVER_LAYER,
		nullptr);

	//判断玩家是否胜利

	//找到胜利玩家的类型（地主OR农民）
	Player::Type winnerPlayerType;
	if (HolderPlayerInstance::getInstance()->isWinner())
	{
		winnerPlayerType = HolderPlayerInstance::getInstance()->getPlayerType();
	}
	else if (ComputerPlayerInstanceOne::getInstance()->isWinner())
	{
		winnerPlayerType = ComputerPlayerInstanceOne::getInstance()->getPlayerType();
	}
	else if (ComputerPlayerInstanceTwo::getInstance()->isWinner())
	{
		winnerPlayerType = ComputerPlayerInstanceTwo::getInstance()->getPlayerType();
	}

	//根据胜利玩家类型和手动玩家类型是否相同，来决定是否胜利
	if (winnerPlayerType == HolderPlayerInstance::getInstance()->getPlayerType())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(RUN_WIN_ANIMATION, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(RUN_LOST_ANIMATION, nullptr);
	}
}

void OverState::update()
{
	//恢复游戏状态至开始状态
	this->_gameController->setState(_gameController->getStartState());
}

