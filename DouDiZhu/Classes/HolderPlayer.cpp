#include "HolderPlayer.h"

#include "CountDownController.h"
#include "GameRule.h"
#include "HolderPlayerInstance.h"
#include "OutPokers.h"
#include "Util.h"

HolderPlayer::HolderPlayer()
{
	init();
}

bool HolderPlayer::init()
{
	//_lastOutPokers = nullptr;

	if (initContent() == false)
	{
		return false;
	}

	return true;
}

bool HolderPlayer::initContent()
{
	//注册在手动玩家待出牌中添加牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::addPokerWaitForOutCallback),
		ADD_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	//注册在手动玩家待出牌中删除牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::deletePokerWaitForOutCallback),
		DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	//注册手动玩家出牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::holderOutPokersCallback),
		HOLDER_OUTPOKERS,
		nullptr);

	//注册提示按钮点击后手动玩家需要做出回应的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::clickHintBtnCallback),
		CLICK_HINT_BTN,
		nullptr);

	return true;
}


void HolderPlayer::displayPokers()
{
	// 	cocos2d::Vector<Poker*> pokers;
	// 	for (int i = 0; i < _holdPokers.size(); ++i)
	// 	{
	// 		pokers.pushBack(&_holdPokers[i]);
	// 	}

	cocos2d::NotificationCenter::getInstance()->postNotification(
		DISPLAY_HOLDER_POKERS, (cocos2d::Ref*)(&_holdPokers));
}

void HolderPlayer::callLandlord()
{
	//显示叫地主按钮
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_CALL_LANDLORD_BTN, nullptr);
}

void HolderPlayer::outPokers(OutPokers* lastOutPokers_)
{
	CountDownController::getInstance()->startCountDown(this);
	//_pokersWaitForOut.clear();
	this->_lastOutPokers = lastOutPokers_;

	//获取提示的牌，确实提示按钮是否可按，以及"没有打得过上家的牌"是否显示
	this->_hintPokers = searchOutPokers(lastOutPokers_);
	//存在可以打得过上家的牌
	if (_hintPokers.size() != 0)
	{
		//令提示按钮可按
		cocos2d::NotificationCenter::getInstance()->postNotification(HINT_BTN_ENABLED,
			nullptr);
	}
	else
	{
		//显示"没有打得过上家的牌"
		cocos2d::NotificationCenter::getInstance()->postNotification(SHOW_PASSHINT,
			nullptr);
	}

	//销毁上一手打出的牌
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_HOLDER_OUTPOKERS, nullptr);
	//显示出牌相关按钮
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS_BTNS, nullptr);
}

void HolderPlayer::outPokersCallback()
{
	//在PokerLayer里实现更加方便，这里不做任何处理，仅作为一个接口保存
}

bool HolderPlayer::isPokerWaitForOutCanOut()
{
	auto pokersType = GameRule::getInstance()->analysePokersType(_pokersWaitForOut);
	if (pokersType == NONE)
	{
		return false;
	}

	std::vector<Poker> pokers;
	//如果上一手牌是空的（手动玩家为第一轮第一个出牌者）,或者上一手牌也是手动玩家的
	if (_lastOutPokers == nullptr || _lastOutPokers->getPokerOwner() == this)
	{
		return true;
	}
	else
	{
		return GameRule::getInstance()->canOutPokers(_pokersWaitForOut, *_lastOutPokers);
	}
}

void HolderPlayer::checkOutPokerBtnEnabled()
{
	//判断当前选择的牌是否可以出（用来决定出牌按钮是否可按）
	//如果可以，发送消息令出牌按钮可以按
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::deletePokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr");
		return;
	}
	for (auto iter = _pokersWaitForOut.begin(); iter != _pokersWaitForOut.end();)
	{
		bool isEqual = *iter == *poker;
		if (isEqual)
		{
			iter = _pokersWaitForOut.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//删除牌不需要重新排序

	//判断当前选择的牌是否可以出（用来决定出牌按钮是否可按）
	//如果可以，发送消息令出牌按钮可以按
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::addPokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr!");
		return;
	}
	_pokersWaitForOut.push_back(*poker);
	util::PokerUtil::sort(_pokersWaitForOut);

	//判断当前选择的牌是否可以出（用来决定出牌按钮是否可按）
	//如果可以，发送消息令出牌按钮可以按
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::holderOutPokersCallback(cocos2d::Ref*)
{
	_outedPokers = _pokersWaitForOut;
	//如果出的牌不为空，更新上一手牌
	if (_pokersWaitForOut.size() != 0)
	{
		auto lastOutPokers = createLastOutPokers(_outedPokers);
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

	//更新用于消息传递的玩家持有的牌
	// 	_holderPokerForPost.clear();
	// 	for (int i = 0; i < _holdPokers.size(); ++i)
	// 	{
	// 		_holderPokerForPost.pushBack(&_holdPokers.at(i));
	// 	}

	//准备出的牌清空
	_pokersWaitForOut.clear();
	//该局提示的牌清空
	_hintPokers.clear();

	// 	//显示手动玩家出的牌
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS,
		reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	//更新手动玩家持有的牌
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_POKERS,
		reinterpret_cast<cocos2d::Ref*>(&_holdPokers));
	//更新出牌顺序
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}

std::vector<Poker> HolderPlayer::searchOutPokers(OutPokers* lastOutPokers_)
{
	std::vector<Poker> result;

	//如果上一手牌是自己的
	if (lastOutPokers_ == nullptr || lastOutPokers_->getPokerOwner() == this ||
		lastOutPokers_->getPokersType() == NONE)
	{
		result = GameRule::getInstance()->searchProperPokers(_holdPokers);
	}
	else
	{
		//static Poker poker = lastOutPokers_->getLowestPoker();	//这样写会导致赋值操作仅执行一次，因而产生BUG
		static Poker poker;
		poker = lastOutPokers_->getLowestPoker();	//NDK编译不允许传递临时变量地址，这里是为了解决这个问题

		result = GameRule::getInstance()->calcPokersWithTypeInSplit(
			_holdPokers, lastOutPokers_->getPokersType(), &poker,//lastOutPokers_->getLowestPoker(),
			lastOutPokers_->getTotalLen());

		if (result.size() == 0) //如果找不到对应的牌，就找炸弹
		{
			result = GameRule::getInstance()->calcPokersWithTypeInSplit(_holdPokers, BOMB);
			if (result.size() == 0)//如果找不到普通的炸，就找王炸
			{
				result = GameRule::getInstance()->calcPokersWithTypeInSplit(_holdPokers, KINGBOMB);
			}
		}
	}

	return result;
}

void HolderPlayer::clickHintBtnCallback(cocos2d::Ref*)
{
	cocos2d::NotificationCenter::getInstance()->postNotification(MAKE_HINT_POKERS_SELECTED,
		(cocos2d::Ref*)(&_hintPokers));
}
