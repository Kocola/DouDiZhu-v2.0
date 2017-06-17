#include "OutPokerState.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "OutPokers.h"

OutPokerState::OutPokerState(GameController* gameController_)
	: _gameController(gameController_)
{
	init();
}

void OutPokerState::init()
{
	_lastOutPokers = nullptr;	//初始化为nullptr，第一个玩家因此可以出任意牌

	initContent();
}

void OutPokerState::initContent()
{
	//注册更新出牌顺序的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OutPokerState::updateOutOrderCallback),
		UPDATE_OUT_ORDER,
		nullptr);

	//注册更新上一手牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OutPokerState::updateLastOutPokersCallback),
		UPDATE_LAST_OUTPOKERS,
		nullptr);
}

void OutPokerState::handle()
{
	_players.clear();
	_players.push_back(HolderPlayerInstance::getInstance());
	_players.push_back(ComputerPlayerInstanceOne::getInstance());
	_players.push_back(ComputerPlayerInstanceTwo::getInstance());

	//确定_startIndex
	for (int i = 0; i < _players.size(); ++i)
	{
		if (_players.at(i)->getPlayerType() == Player::LANDLORD)
		{
			_startIndex = i;
			break;
		}
	}

	_curOutPlayerIndex = _startIndex;

	//此时让手动玩家持有的牌可以点击
	HolderPlayerInstance::getInstance()->setPokersCanClick(true);

	_players.at(_curOutPlayerIndex)->outPokers(_lastOutPokers);

	//cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS, nullptr);
}

void OutPokerState::update()
{
	//更新游戏状态为下一个状态，结束状态
	this->_gameController->setState(_gameController->getOverState());

	//运行下一个状态
	this->_gameController->runState();
}

void OutPokerState::updateOutOrderCallback(cocos2d::Ref*)
{
	//如果已经有玩家出完牌，转入结束状态
	if (_players.at(_curOutPlayerIndex)->isWinner())
	{
		//延迟两秒，进行该状态结束的相关操作
		auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
		scheduleVar->schedule(schedule_selector(OutPokerState::over), this, 2.0, false);
		return;
	}

	_curOutPlayerIndex = (_curOutPlayerIndex + 1) % _players.size();

	_players.at(_curOutPlayerIndex)->outPokers(_lastOutPokers);
}

void OutPokerState::updateLastOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		return;
	}
	//更新上一手牌
	auto tmp = reinterpret_cast<OutPokers*>(sender_);
	_lastOutPokers = tmp;
}

void OutPokerState::over(float delta_)
{
	//仅执行一次over，因此需要unschedule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(OutPokerState::over), this);

	//销毁扑克层
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_POKER_LAYER, nullptr);
	//销毁头像层
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_HEADIMAGE_LAYER, nullptr);

	//更新状态
	update();
}
