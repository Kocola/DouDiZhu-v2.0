#include "DealState.h"

#include <vector>

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "PokerController.h"

const int TOTAL_POKER_NUM = 54;	//扑克总数

DealState::DealState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void DealState::handle()
{
	//添加扑克层
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_POKER_LAYER, nullptr);

	//获取洗好的牌
	_randomPokers = PokerController::getInstance()->getRandomPokers();
	//发牌
	dealPokers(_randomPokers);
	//显示预留给地主的牌
	displayLandlordPokers(_randomPokers);

	//在场景中手动玩家的牌（利用消息机制传递数据）
	HolderPlayerInstance::getInstance()->displayPokers();

	//发送更新游戏状态消息
	cocos2d::NotificationCenter::getInstance()->postNotification(
		UPDATE_GAME_STATE, nullptr);
}

void DealState::update()
{
	//更新至下一个状态，叫地主状态
	this->_gameController->setState(_gameController->getCalllLandlordState());

	//运行下一个状态
	_gameController->runState();
}

void DealState::updateStateCallback(cocos2d::Ref*)
{
}

void DealState::dealPokers(const std::vector<Poker>& randomPokers_)
{
	std::vector<Poker> pokers;
	//对手动玩家发牌
	for (int i = 0; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	HolderPlayerInstance::getInstance()->setPokers(pokers);

	//对电脑玩家1发牌
	pokers.clear();
	for (int i = 1; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	ComputerPlayerInstanceOne::getInstance()->setPokers(pokers);

	//对电脑玩家2发牌
	pokers.clear();
	for (int i = 2; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	ComputerPlayerInstanceTwo::getInstance()->setPokers(pokers);
}

void DealState::displayLandlordPokers(std::vector<Poker>& pokers_)
{
	//获取留给地主的牌
	static std::vector<Poker> landlordPokers;	//用于消息传递的变量必须是非局部变量
	landlordPokers.clear();
	for (int i = pokers_.size() - 3; i < pokers_.size(); ++i)
	{
		landlordPokers.push_back(pokers_.at(i));
	}

	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_LANDLORD_POKERS,
		(cocos2d::Ref*)(&landlordPokers));
}

