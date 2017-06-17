#include "RuleLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIListView.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

static const std::string layerName = "ruleLayer";

void RuleLayer::createLayer()
{
	auto layer = RuleLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool RuleLayer::init()
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

	return true;
}

bool RuleLayer::initView()
{
	//auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//透明背景层
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		BASE_WIDTH * SCALE_X, BASE_HEIGHT * SCALE_Y);
	this->addChild(transparentBg);

	//对话框背景
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(DIALOG_BG_IMAGE);
	auto len = dialogBg->getContentSize().width;
	dialogBg->setCapInsets(cocos2d::Rect(len / 3, len / 2, len / 3, len / 4));
	dialogBg->setContentSize(cocos2d::Size(DIALOG_WIDTH, DIALOG_HEIGHT));
	//dialogBg->setScale(MAX_SCALE);
	dialogBg->setPosition(cocos2d::Point(BASE_WIDTH / 2 * SCALE_X, BASE_HEIGHT / 2 * SCALE_Y));
	dialogBg->setScale(0.0f);	//创建时不显示，以下行代码实现动画效果
	dialogBg->runAction(cocos2d::EaseBackOut::create(
		cocos2d::ScaleTo::create(0.3, MIDDLE_SCALE)));
	this->addChild(dialogBg);

	//对话框顶部背景
	auto dialogTopBg = cocos2d::Sprite::create(DIALOG_TOP_BG_IMAGE);
	dialogTopBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogTopBg->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2, 
		dialogBg->getContentSize().height - 10));
	dialogBg->addChild(dialogTopBg);

	//对话框顶部标题
	auto dialogTitleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("玩法说明"), "Arial", 34);
	dialogTitleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	dialogTitleTTF->setPosition(cocos2d::Point(dialogTopBg->getContentSize() / 2));
	dialogTopBg->addChild(dialogTitleTTF);

	//窗口关闭按钮
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_CLOSE_BTN),
		nullptr,
		CC_CALLBACK_1(RuleLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Point(dialogBg->getContentSize().width - closeBtn->getContentSize().width / 3,
		dialogBg->getContentSize().height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(closeBtnPos);
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//底部OK按钮
	auto btnOK = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(RuleLayer::backCallback, this));
	btnOK->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	btnOK->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2, 30));
	auto btnOkMenu = cocos2d::Menu::create(btnOK, nullptr);
	btnOkMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(btnOkMenu);

	//OK按钮标题内容
	auto btnTTF = cocos2d::LabelTTF::create(util::GBToUTF8("确 定"), "Arial", 34);
	btnTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	btnTTF->setPosition(btnOK->getContentSize() / 2);
	btnOK->addChild(btnTTF);

	//对话框中间的背景
	_dialogMiddleBg = cocos2d::ui::Scale9Sprite::create(DIALOG_MIDDLE_BG_IMAGE);
	_dialogMiddleBg->setContentSize(cocos2d::Size(664, 300));
	_dialogMiddleBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_dialogMiddleBg->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2,
		btnOK->getPosition().y + btnOK->getContentSize().height + 10));
	dialogBg->addChild(_dialogMiddleBg);

	return true;
}

bool RuleLayer::initContent()
{
	if (initListView() == false)
	{
		return false;
	}

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RuleLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	////吞噬触摸事件向下层传递
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	////android物理返回键
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(RuleLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

bool RuleLayer::initListView()
{
	auto ruleListView = cocos2d::ui::ListView::create();
	ruleListView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);	//设置ListView方向为垂直
	ruleListView->setContentSize(cocos2d::Size(_dialogMiddleBg->getContentSize().width - 5,
		_dialogMiddleBg->getContentSize().height - 10));	//设置ListView大小
	ruleListView->setBounceEnabled(true);	//设置ListView拉至顶部或者底部时的回弹效果
	ruleListView->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	ruleListView->setPosition(cocos2d::Point(5, _dialogMiddleBg->getContentSize().height - 5));
	//设置ListView监听器
	ruleListView->addEventListener((cocos2d::ui::ListView::ccListViewCallback)CC_CALLBACK_2(
		RuleLayer::selectedItemEvent, this));
	ruleListView->addEventListener((cocos2d::ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(
		RuleLayer::selectedItemEventScrollView, this));
	ruleListView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
	_dialogMiddleBg->addChild(ruleListView, 2);

	const std::string rule = "游戏规则说明";
	auto ruleTTF = cocos2d::LabelTTF::create(util::GBToUTF8(rule.c_str()), "Arial", 30);
	ruleTTF->setDimensions(cocos2d::Size(ruleListView->getContentSize().width, 
		ruleTTF->getContentSize().height));	//设置文字显示区域
	ruleTTF->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);//左对齐
	ruleTTF->setColor(cocos2d::Color3B(0x45, 0x1d, 0x15));

	//ruleTTF必须放置在layout中，layout放置在ListView中
	auto layout = cocos2d::ui::Layout::create();
	layout->setContentSize(ruleTTF->getContentSize());
	ruleTTF->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	layout->setPosition(cocos2d::Point::ZERO);
	layout->addChild(ruleTTF);
	ruleListView->addChild(layout);

	return true;
}

bool RuleLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}

void RuleLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//返回
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

void RuleLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//设置窗口消失动画
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(RuleLayer::funcBackCallback, this)),
		nullptr));
}

void RuleLayer::funcBackCallback()
{
	//从当前场景移除设置对话框
	this->removeFromParent();
}

void RuleLayer::selectedItemEvent(cocos2d::Ref* sender_, cocos2d::ui::ListView::EventType type_)
{
	switch (type_){
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
		break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
		break;
	}
	default:
		break;
	}
}

void RuleLayer::selectedItemEventScrollView(cocos2d::Ref* sender_, cocos2d::ui::ScrollView::EventType type_)
{
	switch (type_) {
	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
	{
		break;
	}
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
	{
		break;
	}
	default:
		break;
	}
}