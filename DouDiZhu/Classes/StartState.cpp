#include "StartState.h"

#include "Common.h"
#include "GameController.h"

StartState::StartState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void StartState::handle()
{
	//显示头像层
	cocos2d::NotificationCenter::getInstance()
		->postNotification(CREATE_HEADIMAGE_LAYER);

	//显示头像层后，立即显示准备状态
	this->update();
}

void StartState::update()
{
	//更新至下一个状态，准备状态
	_gameController->setState(_gameController->getReadyState());

	//运行下一个状态
	_gameController->runState();
}

