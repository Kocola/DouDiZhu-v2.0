#include "CallLandlordState.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "Player.h"

CallLandlordState::CallLandlordState(GameController* gameController_)
	: _gameController(gameController_),
	_calledNum(0), _maxScore(3)	//这里可以叫的最高分是3
{
	srand((unsigned)time(nullptr));

	_players.push_back(HolderPlayerInstance::getInstance());
	_players.push_back(ComputerPlayerInstanceOne::getInstance());
	_players.push_back(ComputerPlayerInstanceTwo::getInstance());

	//随机随着开始叫地主的玩家
	_startIndex = rand() % _players.size();
	_curCallIndex = _startIndex;

	initContent();
}

void CallLandlordState::handle()
{
	//发送消息，创建叫地主层
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//开始叫地主循环
	callLandlordDelayed();
}

void CallLandlordState::update()
{
	//更新游戏状态为下一个状态，出牌状态
	this->_gameController->setState(_gameController->getOutPokerState());

	//运行下一个状态
	_gameController->runState();
}

bool CallLandlordState::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordState::updateCallIndexCallback),
		UPDATE_CALL_LANDLORD_INDEX, nullptr);

	return true;
}

void CallLandlordState::callLandlordDelayed()
{
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->schedule(schedule_selector(CallLandlordState::callLandlordDelayed), this, 1.0, false);
}

void CallLandlordState::callLandlordDelayed(float delta_)
{
	//每个玩家仅执行一次，故unschdule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(CallLandlordState::callLandlordDelayed), this);

	_players.at(_curCallIndex)->callLandlord();
}

void CallLandlordState::decideLandlord()
{
	//找出叫分最高的人
	int maxScore = 0;
	int landlordIndex = _startIndex;
	//从随机开始的顺序遍历
	for (int i = 0, playerIndex = _startIndex; i < _players.size();
		++i, playerIndex = (playerIndex + 1) % _players.size())
	{
		int score = _players.at(playerIndex)->getCallScore();
		if (score > maxScore)
		{
			maxScore = score;
			landlordIndex = playerIndex;
		}
	}

	//设置玩家类型（地主Or农民）
	for (int i = 0; i < _players.size(); ++i)
	{
		if (i == landlordIndex)
		{
			_players.at(i)->setPlayerType(Player::LANDLORD);
		}
		else
		{
			_players.at(i)->setPlayerType(Player::FARMER);
		}
	}

	this->_landlordIndex = landlordIndex;

	//cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER, nullptr);
	//获取地主获得者后的操作（预留的地主牌发给该获得者）
	setLandlord();
}

void CallLandlordState::setLandlord()
{
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	//延迟2秒，避免最后一个叫分的玩家的叫分状态无法看到
	scheduleVar->schedule(schedule_selector(CallLandlordState::setLandlordDelayed), this, 2.0, false);
}

void CallLandlordState::setLandlordDelayed(float delta_)
{
	//仅执行一次，故unschdule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(CallLandlordState::setLandlordDelayed), this);

	//更新头像
	updateHeadImage(_landlordIndex);

	//将预留的地主牌发给地主获得者
	auto pokers = PokerController::getInstance()->getRandomPokers();
	//std::vector<Poker> landlordPokers;
	for (int i = pokers.size() - 3; i < pokers.size(); ++i)
	{
		//landlordPokers.push_back(pokers[i]);
		_players.at(_landlordIndex)->pushPoker(pokers[i]);
	}

	//手动玩家刷新一次需要显示的牌
	HolderPlayerInstance::getInstance()->displayPokers();

	//销毁叫地主层，进入出牌状态
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER);

	//进入下一个游戏状态
	this->update();
}

void CallLandlordState::updateHeadImage(int landlordIndex_)
{
	if (landlordIndex_ == 0)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_HOLDER_HEADIMAGE, nullptr);
	}
	else if (landlordIndex_ == 1)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_COMPUTERONE_HEADIMAHE, nullptr);
	}
	else if (landlordIndex_ == 2)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_COMPUTERTWO_HEADIMAGE, nullptr);
	}
}

void CallLandlordState::updateCallIndexCallback(cocos2d::Ref*)
{
	//显示玩家叫分信息
	if (_curCallIndex == 1)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			DISPLAY_COMPUTE_ONE_CALLLANDLORD_STATE, nullptr);
	}
	else if (_curCallIndex == 2)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			DISPLAY_COMPUTE_TWO_CALLLANDLORD_STATE, nullptr);
	}

	_calledNum++;
	if (_calledNum == _players.size())
	{
		//叫分结束，决定谁是地主
		decideLandlord();
		return;		//上下两个return导致一个错误调试很久...
	}
	int lastCallIndex = _curCallIndex;
	if (_players.at(lastCallIndex)->getCallScore() == _maxScore)
	{
		//已经有人叫到最高分，因此直接叫分结束，设置该人为地主
		decideLandlord();
		return;
	}
	_curCallIndex = (_curCallIndex + 1) % _players.size();

	callLandlordDelayed();
}
