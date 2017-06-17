#include "ReadyState.h"

#include "Common.h"
#include "DealState.h"
#include "GameController.h"
#include "ReadyStateLayer.h"

ReadyState::ReadyState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void ReadyState::handle()
{
	//显示准备层
	cocos2d::NotificationCenter::getInstance()
		->postNotification(CREATE_READY_LAYER);
}

void ReadyState::update()
{
	//更新至下一个状态，发牌状态
	this->_gameController->setState(_gameController->getDealState());

	_gameController->runState();
}
