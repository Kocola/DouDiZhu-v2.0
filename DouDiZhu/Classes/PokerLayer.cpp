#include "PokerLayer.h"

#include "Common.h"
#include "CountDown.h"
#include "CountDownController.h"
#include "HolderPlayerInstance.h"
#include "Player.h"
#include "Poker.h"
#include "PokerController.h"
#include "ScalableMenuItemSprite.h"
#include "Util.h"

const std::string layerName = "pokerLayer";

const float MIMIUM_CARDS_OVERLAPWIDTH = 20.0f;
const float COUNTDOWN_SCALE = 0.5f;

void PokerLayer::createLayer()
{
	auto layer = PokerLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void PokerLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool PokerLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	if (initContent() == false)
	{
		return false;
	}

	if (initListener() == false)
	{
		return false;
	}

	return true;
}

bool PokerLayer::initView()
{
	//auto winSize = cocos2d::Director::getInstance()->getWinSize();
	const auto computerOnePos = cocos2d::Point(BASE_WIDTH * 0.8 * SCALE_X,
		BASE_HEIGHT * 0.72 * SCALE_Y);
	const auto computerTwoPos = cocos2d::Point(BASE_WIDTH * 0.2 * SCALE_X,
		BASE_HEIGHT * 0.72 * SCALE_Y);
	const auto holderPos = cocos2d::Point(BASE_WIDTH * 0.2 * SCALE_X,
		BASE_HEIGHT * 0.4 * SCALE_Y);

	_holderPassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_holderPassSprite->setScale(MAX_SCALE);
	_holderPassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderPassSprite->setPosition(holderPos);
	_holderPassSprite->setVisible(false);	//初始不显示
	this->addChild(_holderPassSprite);

	_computerOnePassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_computerOnePassSprite->setScale(MAX_SCALE);
	_computerOnePassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOnePassSprite->setPosition(computerOnePos);
	_computerOnePassSprite->setVisible(false);
	this->addChild(_computerOnePassSprite);

	_computerTwoPassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_computerTwoPassSprite->setScale(MAX_SCALE);
	_computerTwoPassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoPassSprite->setPosition(computerTwoPos);
	_computerTwoPassSprite->setVisible(false);
	this->addChild(_computerTwoPassSprite);

	//出牌相关按钮（不出，出牌，提示，没有牌打得过上家）
	const auto btnInterval = 10.0f * SCALE_X;
	const auto btnWidth = cocos2d::Sprite::create(PASS_BTN)->getContentSize().width * MAX_SCALE;
	const auto btnPos = cocos2d::Point(BASE_WIDTH * 0.5f * SCALE_X, BASE_HEIGHT * 0.35 * SCALE_Y);
	//不出按钮
	auto passBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(PASS_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::passBtnCallback, this));
	passBtn->setScale(MAX_SCALE);
	passBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	passBtn->setPosition(cocos2d::Point(btnPos.x - btnWidth - btnInterval, btnPos.y));

	//提示按钮
	_hintBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(HINT_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::hintBtnCallback, this));
	_hintBtn->setScale(MAX_SCALE);
	_hintBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_hintBtn->setPosition(cocos2d::Point(btnPos.x, btnPos.y));
	_hintBtn->setDisabledImage(cocos2d::Sprite::create(HINT_DISABLE_BTN));	//提示按钮不可按状态
	_hintBtn->setEnabled(false);	//提示按钮开始不可点击

	//出牌按钮
	_outPokersBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(OUTPOKER_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::outPokersBtnCallback, this));
	_outPokersBtn->setScale(MAX_SCALE);
	_outPokersBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_outPokersBtn->setPosition(cocos2d::Point(btnPos.x + btnWidth + btnInterval, btnPos.y));
	_outPokersBtn->setDisabledImage(cocos2d::Sprite::create(OUTPOKER_DISABLE_BTN));	//出牌按钮不可按状态
	_outPokersBtn->setEnabled(false);

	_btnMenu = cocos2d::Menu::create(passBtn, _hintBtn, _outPokersBtn, nullptr);
	_btnMenu->setPosition(cocos2d::Point::ZERO);
	_btnMenu->setVisible(false);		//初始化时不可见
	this->addChild(_btnMenu);

	//三位玩家的计时器
	_holderCountDown = CountDown::create();
	_holderCountDown->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderCountDown->setPosition(holderPos);
	_holderCountDown->setVisible(false);
	_holderCountDown->setScale(COUNTDOWN_SCALE * MAX_SCALE);
	this->addChild(_holderCountDown);

	_computerOneCountDown = CountDown::create();
	_computerOneCountDown->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOneCountDown->setPosition(computerOnePos);
	_computerOneCountDown->setVisible(false);
	_computerOneCountDown->setScale(COUNTDOWN_SCALE * MAX_SCALE);
	this->addChild(_computerOneCountDown);

	_computerTwoCountDown = CountDown::create();
	//_computerTwoCountDown->setScale(MAX_SCALE);		//缩放效果会被后面的setScale覆盖
	_computerTwoCountDown->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoCountDown->setPosition(computerTwoPos);
	_computerTwoCountDown->setVisible(false);
	_computerTwoCountDown->setScale(COUNTDOWN_SCALE * MAX_SCALE);
	this->addChild(_computerTwoCountDown);

	//没有打得过上家牌的提示
	_passHintSprite = cocos2d::Sprite::create(PASS_HINT);
	_passHintSprite->setScale(MAX_SCALE);
	_passHintSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_passHintSprite->setPosition(cocos2d::Point(BASE_WIDTH * 0.5 * SCALE_X, 
		BASE_HEIGHT * 0.45 * SCALE_Y));
	_passHintSprite->setVisible(false);
	this->addChild(_passHintSprite);

	return true;
}

bool PokerLayer::initContent()
{
	//注册显示手动玩家手中的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderPokersCallback),
		DISPLAY_HOLDER_POKERS,
		nullptr);

	//注册显示预留给地主的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayLandlordPokersCallback),
		DISPLAY_LANDLORD_POKERS,
		nullptr);

	//注册销毁手动玩家上一手打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyHolderLastOutPokersCallback),
		DESTROY_LAST_HOLDER_OUTPOKERS,
		nullptr);

	//注册显示玩家该局打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderOutPokersCallback),
		DISPLAY_HOLDER_OUTPOKERS,
		nullptr);

	//注册销毁电脑玩家1上一手打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerOneLastOutPokersCallback),
		DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//注册显示电脑玩家1该局打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerOneOutPokersCallback),
		DISPLAY_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//注册销毁电脑玩家2上一手打出的牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerTwoLastOutPokersCallback),
		DESTROY_LAST_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	//注册显示电脑玩家2该局打出的牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerTwoOutPokersCallback),
		DISPLAY_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	//注册显示手动玩家出牌相关按钮的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderOutPokersBtnsCallback),
		DISPLAY_HOLDER_OUTPOKERS_BTNS,
		nullptr);

	//注册令出牌按钮可按的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::outPokersBtnEnabledCallback),
		OUTPOKERS_BTN_ENABLED,
		nullptr);

	//注册令出牌按钮不可按的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::outPokersBtnDisabledCallback),
		OUTPOKERS_BTN_DISABLED,
		nullptr);

	//注册提示按钮可按的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::hintBtnEnabledCallback),
		HINT_BTN_ENABLED,
		nullptr);

	//注册显示"没有打得过上家的牌"提示的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::showPassHintCallback),
		SHOW_PASSHINT,
		nullptr);

	//注册手动玩家计时器开始计时的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::holderStartCountDownCallback),
		HOLDER_START_COUNTDOWN,
		nullptr);

	//注册手动玩家计时器停止计时的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::holderStopCountDownCallback),
		HOLDER_STOP_COUNTDOWN,
		nullptr);

	//注册电脑玩家1计时器开始计时的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::computerOneStartCountDownCallback),
		COMPUTER_ONE_START_COUNTDOWN,
		nullptr);

	//注册电脑玩家2计时器开始计时的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::computerTwoStartCountDownCallback),
		COMPUTER_TWO_START_COUNTDOWN,
		nullptr);

	//注册显示提示按钮点击后令提示的扑克选中的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::makeHintPokersSelectedCallback),
		MAKE_HINT_POKERS_SELECTED,
		nullptr);

	return true;
}

bool PokerLayer::initListener()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//吞噬，避免上层触摸操作捕获后再传递给下层

	listener->onTouchBegan = CC_CALLBACK_2(PokerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PokerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PokerLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool PokerLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	auto holderPokerSprites = _lastHolderPokerSprites;

	auto touchPos = this->convertToNodeSpace(touch_->getLocation());
	for (int i = holderPokerSprites.size() - 1; i >= 0; --i)
	{
		auto rect = holderPokerSprites.at(i)->getBoundingBox();
		if (holderPokerSprites.at(i)->getCanClick() && rect.containsPoint(touchPos))
		{
			//播放选牌的音效

			_holderClickedPokerSprites.push_back(holderPokerSprites.at(i));
			if (!holderPokerSprites.at(i)->getIsSelected())
			{
				//如果还未选择这张牌，那就将这张牌露出来
				holderPokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//否则这张牌已经被选择，将其放回
				holderPokerSprites.at(i)->selectedPokerBack();
			}

			//检测当前选择的牌是否可以令出牌按钮可按

			return true;
		}
	}

	//如果点击下的位置不在扑克范围内，那么即使触摸移动后也不会有任何操作
	return false;
}

void PokerLayer::onTouchMoved(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	auto pokerSprites = _lastHolderPokerSprites;

	auto touchPos = this->convertToNodeSpace(touch_->getLocation());
	for (int i = pokerSprites.size() - 1; i >= 0; --i)
	{
		auto rect = pokerSprites.at(i)->getBoundingBox();
		if (pokerSprites.at(i)->getCanClick() && rect.containsPoint(touchPos))
		{
			//当前点击的牌是否是在已经选择的牌集合内，如果在，那么直接结束循环
			bool isInClickedPokerSprites = false;
			for (int k = 0; k < _holderClickedPokerSprites.size(); ++k)
			{
				if (pokerSprites.at(i) == _holderClickedPokerSprites.at(k))
				{
					isInClickedPokerSprites = true;
					break;
				}
			}
			if (isInClickedPokerSprites)
			{
				break;
			}

			//播放点击牌的音效
			//TODO

			_holderClickedPokerSprites.push_back(pokerSprites.at(i));
			if (!pokerSprites.at(i)->getIsSelected())
			{
				//如果还未选择这张牌，那就将这张牌露出来
				pokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//否则这张牌已经被选择，将其放回
				pokerSprites.at(i)->selectedPokerBack();
			}

			//检测当前牌是否可以另出牌按钮可按
			//TODO

			break;
		}
	}
}

void PokerLayer::onTouchEnded(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	//触摸结束，清空clickedPokers
	_holderClickedPokerSprites.clear();
}

std::vector<PokerSprite*> PokerLayer::createPokerSprites(const std::vector<Poker>& pokers)
{
	//由于一个Sprite不能被addChild两次，这里将显示的地主预留牌精灵或者打出的牌设置成一个clone获得的值
	const auto tmp = PokerController::getInstance()->genPokerSprites(pokers);
	std::vector<PokerSprite*> pokerSprites;
	for (int i = 0; i < tmp.size(); ++i)
	{
		pokerSprites.push_back(tmp.at(i)->clone());
	}

	return pokerSprites;
}

void PokerLayer::displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
	float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float scale /*= 1.0f*/)
{
	if (pokers_.size() == 0)
	{
		return;
	}

	int pokersNum = pokers_.size();
	float pokerWidth = pokers_.front()->getContentSize().width * scale * SCALE_X;
	float pokerHeight = pokers_.front()->getContentSize().height * scale * SCALE_Y;
	//两张牌之间的最大间隙
	float	maxIntervalBetweenPokers = pokerWidth - MIMIUM_CARDS_OVERLAPWIDTH * scale * SCALE_X;
	float intervalBetweenPokers = (displayMaxWidth_ - pokerWidth) < maxIntervalBetweenPokers * (pokersNum - 1) ?
		(displayMaxWidth_ - pokerWidth) / (pokersNum - 1) : maxIntervalBetweenPokers;

	//卡牌之间的间隙达到最大时，需要以显示区中点展开显示，不然整体的显示会左偏，造成视觉问题
	if (intervalBetweenPokers == maxIntervalBetweenPokers)
	{
		// 		displayStartX_ = pokersNum % 2 == 0 ?
		// 			displayMiddleX_ - (pokersNum / 2) * intervalBetweenPokers :
		// 			displayMiddleX_ - (pokersNum / 2 + 0.5) * intervalBetweenPokers;
		auto totalPokersWidth = (pokersNum - 1) * intervalBetweenPokers + pokerWidth;
		displayStartX_ = displayMiddleX_ - totalPokersWidth / 2.0f;
	}

	//显示卡牌
	for (int i = 0; i < pokersNum; ++i)
	{
		if (isOnScene_ == false)	//手动玩家持有的牌
		{
			this->addChild(pokers_.at(i));
		}
		else
		{
			displayY_ = pokers_.at(i)->getPosition().y;	//针对待出的牌
		}
		pokers_.at(i)->setScale(scale * MIDDLE_SCALE);
		pokers_.at(i)->setVisible(true);
		pokers_.at(i)->setPosition(cocos2d::Point(displayStartX_ + pokerWidth / 2 + i * intervalBetweenPokers,
			displayY_));
	}
}

void PokerLayer::displayHolderPokersCallback(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);

	//两次无变化，直接返回
	if (_lastHolderPokerSprites.size() == pokers.size())
	{
		return;
	}

	for (int i = 0; i < pokers.size(); ++i)
	{
		cocos2d::log("%d : %d\n", pokers.at(i).type, pokers.at(i).value);
	}

	//需要将上次显示的牌给销毁
	for (int i = 0; i < _lastHolderPokerSprites.size(); ++i)
	{
		_lastHolderPokerSprites.at(i)->removeFromParent();
	}

	const auto pokerSprites = PokerController::getInstance()->genPokerSprites(pokers);
	_lastHolderPokerSprites = pokerSprites;

	if (pokerSprites.size() == 0)
	{
		return;
	}

	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth =  BASE_WIDTH * 5.0 / 6.0 * SCALE_X;
	float displayPokerMiddleX = BASE_WIDTH / 2 * SCALE_X;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2;
	float displayPokerY = SCALE_Y * (pokerSprites.front()->getContentSize().height / 2 + 25);//winSize.height * 0.2;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false);
}

void PokerLayer::displayLandlordPokersCallback(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);

	if (sender_ == nullptr || pokers.size() == 0)
	{
		CCASSERT(1 == 0, "Landlord Pokers is empty!");
	}

	auto pokerSprites = createPokerSprites(pokers);

	const float scale = 0.7f;

	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192 * SCALE_X;
	float displayPokerMiddleX = BASE_WIDTH / 2 * SCALE_X;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = SCALE_Y * (BASE_HEIGHT - scale * (pokerSprites.front()->getContentSize().height / 2 + 10));
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, scale);
}

void PokerLayer::destroyHolderLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_holderPassSprite->setVisible(false);

	for (int i = 0; i < _lastHolderOutPokersSprites.size(); ++i)
	{
		_lastHolderOutPokersSprites.at(i)->removeFromParent();
	}
	_lastHolderOutPokersSprites.clear();
}

void PokerLayer::displayHolderOutPokersCallback(cocos2d::Ref* sender_)
{
	//如果没有出牌，那么显示不出
	if (sender_ == nullptr)
	{
		//显示不出
		_holderPassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);

	if (pokers.size() == 0)
	{
		//显示不出
		_holderPassSprite->setVisible(true);
		return;
	}

	auto pokerSprites = createPokerSprites(pokers);

	//把当前出的牌记录下来
	_lastHolderOutPokersSprites = pokerSprites;

	const float scale = 0.7f;

	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 240 * SCALE_X;
	float displayPokerMiddleX = BASE_WIDTH / 2 * SCALE_X;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = BASE_HEIGHT * 0.4f * SCALE_Y;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, scale);
}

void PokerLayer::destroyComputerOneLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_computerOnePassSprite->setVisible(false);

	for (int i = 0; i < _lastComputerOneOutPokersSprites.size(); ++i)
	{
		_lastComputerOneOutPokersSprites.at(i)->removeFromParent();
	}
	_lastComputerOneOutPokersSprites.clear();
}

void PokerLayer::displayComputerOneOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		//显示不出按钮
		_computerOnePassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);

	if (pokers.size() == 0)
	{
		//显示不出按钮
		_computerOnePassSprite->setVisible(true);
		return;
	}

	auto pokerSprites = createPokerSprites(pokers);

	_lastComputerOneOutPokersSprites = pokerSprites;

	const float scale = 0.7f;

	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 240 * SCALE_X;
	float displayPokerMiddleX = BASE_WIDTH * 0.7f * SCALE_X;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = BASE_HEIGHT * 0.72f * SCALE_Y;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, scale);
}

void PokerLayer::destroyComputerTwoLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_computerTwoPassSprite->setVisible(false);

	for (int i = 0; i < _lastComputerTwoOutPokersSprites.size(); ++i)
	{
		_lastComputerTwoOutPokersSprites.at(i)->removeFromParent();
	}
	_lastComputerTwoOutPokersSprites.clear();
}

void PokerLayer::displayComputerTwoOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		//显示不出按钮
		_computerTwoPassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);
	if (pokers.size() == 0)
	{
		//显示不出按钮
		_computerTwoPassSprite->setVisible(true);
		return;
	}

	auto pokerSprites = createPokerSprites(pokers);

	_lastComputerTwoOutPokersSprites = pokerSprites;

	const float scale = 0.7f;

	//const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 240 * SCALE_X;
	float displayPokerMiddleX = BASE_WIDTH * 0.3f * SCALE_X;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = BASE_HEIGHT * 0.72f * SCALE_Y;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, scale);
}

void PokerLayer::displayHolderOutPokersBtnsCallback(cocos2d::Ref*)
{
	//显示出牌相关按钮
	_btnMenu->setVisible(true);
}

void PokerLayer::passBtnCallback(cocos2d::Ref* sender_)
{
	//点击出牌按钮后，倒计时器停止计时并隐藏
	CountDownController::getInstance()->stopCountDown(HolderPlayerInstance::getInstance());
	//恢复按钮至默认状态（出牌和提示不可按，所有按钮不可见）
	_outPokersBtn->setEnabled(false);
	_hintBtn->setEnabled(false);
	_btnMenu->setVisible(false);
	_passHintSprite->setVisible(false);

	//传递空指针，表示不出牌
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS, nullptr);
	//更新出牌顺序
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}

void PokerLayer::outPokersBtnCallback(cocos2d::Ref* sender_)
{
	//点击出牌按钮后，倒计时器停止计时并隐藏
	CountDownController::getInstance()->stopCountDown(HolderPlayerInstance::getInstance());
	//恢复按钮至默认状态（出牌和提示不可按，所有按钮不可见）
	_outPokersBtn->setEnabled(false);
	_hintBtn->setEnabled(false);
	_btnMenu->setVisible(false);
	_passHintSprite->setVisible(false);
	cocos2d::NotificationCenter::getInstance()->postNotification(HOLDER_OUTPOKERS, nullptr);
}

void PokerLayer::hintBtnCallback(cocos2d::Ref* sender_)
{
	cocos2d::NotificationCenter::getInstance()->postNotification(CLICK_HINT_BTN, nullptr);
}

void PokerLayer::outPokersBtnEnabledCallback(cocos2d::Ref*)
{
	_outPokersBtn->setEnabled(true);
}

void PokerLayer::outPokersBtnDisabledCallback(cocos2d::Ref*)
{
	_outPokersBtn->setEnabled(false);
}

void PokerLayer::hintBtnEnabledCallback(cocos2d::Ref*)
{
	_hintBtn->setEnabled(true);
}

void PokerLayer::holderStartCountDownCallback(cocos2d::Ref* sender_)
{
	if (sender_ != nullptr)
	{
		auto player = reinterpret_cast<Player*>(sender_);
		//std::function<void(void)> function = CC_CALLBACK_0(Player::outPokersCallback, player);
		std::function<void(void)> function = [=](){
			passBtnCallback(nullptr);
		};
		_holderCountDown->setCallbackFunc(function);
	}
	_holderCountDown->startCountDown();
}

void PokerLayer::holderStopCountDownCallback(cocos2d::Ref* sender_)
{
	_holderCountDown->stopCountDown();
}

void PokerLayer::computerOneStartCountDownCallback(cocos2d::Ref* sender_)
{
	if (sender_ != nullptr)
	{
		auto player = reinterpret_cast<Player*>(sender_);
		std::function<void(void)> function = CC_CALLBACK_0(Player::outPokersCallback, player);
		_computerOneCountDown->setCallbackFunc(function);
		_computerOneCountDown->setCountDownUpper(2.0f);
	}
	_computerOneCountDown->startCountDown();
}

void PokerLayer::computerTwoStartCountDownCallback(cocos2d::Ref* sender_)
{
	if (sender_ != nullptr)
	{
		auto player = reinterpret_cast<Player*>(sender_);
		std::function<void(void)> function = CC_CALLBACK_0(Player::outPokersCallback, player);
		_computerTwoCountDown->setCallbackFunc(function);
		_computerTwoCountDown->setCountDownUpper(2.0f);
	}
	_computerTwoCountDown->startCountDown();
}

void PokerLayer::makeHintPokersSelectedCallback(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<std::vector<Poker>*>(sender_);
	auto pokerSprites = PokerController::getInstance()->genPokerSprites(pokers);
	for (int i = 0; i < pokerSprites.size(); ++i)
	{
		pokerSprites.at(i)->selectedPokersOut();	//将该张牌上移，表示被选中
	}
}

void PokerLayer::showPassHintCallback(cocos2d::Ref* sender_)
{
	_passHintSprite->setVisible(true);
}
