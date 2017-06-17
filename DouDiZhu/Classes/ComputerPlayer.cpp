#include "ComputerPlayer.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "CountDownController.h"

void ComputerPlayer::callLandlord()
{
	//电脑随机叫分
	int score = rand() % 4;	//不叫，一分，两分，三分

	setCallScore(score);

	//叫分后发送消息更新叫分顺序
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void ComputerPlayer::outPokers(OutPokers* lastOutPokers_)
{
	//首先，将上一把出的牌从场景删除
	//先判断电脑玩家是1还是2
	//如果是电脑玩家1
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
			nullptr);
	}
	else if (this == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_TWO_OUTPOKERS,
			nullptr);
	}

	//根据游戏上一手牌查找符合要求的牌
	_outedPokers = this->searchOutPokers(lastOutPokers_);

	//如果该玩家找到可以出的牌，那么更新上一手牌
	if (_outedPokers.size() != 0)
	{
		auto lastOutPokers = createLastOutPokers(_outedPokers);
		//下一行造成引用次数紊乱，造成对象不正确被析构
		//lastOutPokers_ = lastOutPokers;		//这里简单的更新游戏循环的上一手牌
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_LAST_OUTPOKERS,
			(cocos2d::Ref*)(lastOutPokers));
	}

	//更新用于消息传递的打出的牌（下一个玩家的上一手牌）
// 	_outedPokersForPost.clear();
// 	for (int i = 0; i < _outedPokers.size(); ++i)
// 	{
// 		_outedPokersForPost.pushBack(&_outedPokers.at(i));
// 	}

	//在持有的牌中删除要出的牌
	for (int i = 0; i < _outedPokers.size(); ++i)
	{
		for (auto iter = _holdPokers.begin(); iter != _holdPokers.end();)
		{
			if (*iter == _outedPokers[i])
			{
				iter = _holdPokers.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
		}
	}

	CountDownController::getInstance()->startCountDown(this);

// 	//显示要打出的牌
// 	if (this == ComputerPlayerInstanceOne::getInstance())
// 	{
// 		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_ONE_OUTPOKERS,
// 			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
// 	}
// 	else if (this == ComputerPlayerInstanceTwo::getInstance())
// 	{
// 		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_TWO_OUTPOKERS,
// 			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
// 	}
// 
// 	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}

void ComputerPlayer::outPokersCallback()
{
	//显示要打出的牌
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_ONE_OUTPOKERS,
			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	}
	else if (this == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_TWO_OUTPOKERS,
			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	}

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}
