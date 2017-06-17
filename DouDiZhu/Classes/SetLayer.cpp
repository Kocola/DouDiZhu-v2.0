#include "SetLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "util.h"

static const std::string layerName = "setLayer";

using namespace cocos2d;

void SetLayer::createLayer()
{
	auto layer = SetLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()
		->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()
			->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()
		->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool SetLayer::init()
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

bool SetLayer::initContent()
{
	//音量初始化
	_musicSlider->setValue(util::MusicUtil::getBgMusicVolume());
	_effectSlider->setValue(util::MusicUtil::getVolume());

	//滑动条监听器
	_musicSlider->addTargetWithActionForControlEvents(this,
		cccontrol_selector(SetLayer::musicChangedCallback),
		cocos2d::extension::Control::EventType::VALUE_CHANGED);
	_effectSlider->addTargetWithActionForControlEvents(this,
		cccontrol_selector(SetLayer::effectChangedCallback),
		cocos2d::extension::Control::EventType::VALUE_CHANGED);

	//屏蔽屏幕触摸往下层传递
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SetLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	//吞噬触摸事件向下层传递
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//android物理返回键
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(SetLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

void SetLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//返回键触摸后释放操作
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

bool SetLayer::initView()
{
	//auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//添加透明背景层
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		BASE_WIDTH * SCALE_X, BASE_HEIGHT * SCALE_Y);
	this->addChild(transparentBg);

	//对话框背景
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(DIALOG_BG_IMAGE);
	auto len = dialogBg->getContentSize().width;
	//设置伸展区域
	dialogBg->setCapInsets(cocos2d::Rect(len / 3, len / 2, len / 3, len / 4));
	dialogBg->setContentSize(cocos2d::Size(720, 480));
// 	dialogBg->setScaleX(SCALE_X);
// 	dialogBg->setScaleY(SCALE_Y);
	dialogBg->setPosition(cocos2d::Point(BASE_WIDTH / 2 * SCALE_X, BASE_HEIGHT / 2 * SCALE_Y));
	dialogBg->setScale(0);	//创建时不显示，后面通过代码以动画形式展示
	dialogBg->runAction(cocos2d::EaseBackOut::create(
		cocos2d::ScaleTo::create(0.3, MIDDLE_SCALE)));
	this->addChild(dialogBg, 1);

	auto dialogBgSize = dialogBg->getContentSize();

	//顶部背景
	auto dialogBgTop = cocos2d::Sprite::create(DIALOG_TOP_BG_IMAGE);
	dialogBgTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogBgTop->setPosition(cocos2d::Point(dialogBgSize.width / 2, dialogBgSize.height - 10));
	dialogBg->addChild(dialogBgTop);

	//顶部标题
	auto titleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("设	置"), "Arial", 34);
	titleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	titleTTF->setPosition(cocos2d::Point(dialogBgTop->getContentSize() / 2));
	dialogBgTop->addChild(titleTTF);

	//窗口关闭按钮
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_CLOSE_BTN),
		nullptr,
		CC_CALLBACK_1(SetLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Size(dialogBgSize.width - closeBtn->getContentSize().width / 3,
		dialogBgSize.height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(cocos2d::Point(closeBtnPos));
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//对话框中间背景
	auto middleBgSprite = cocos2d::ui::Scale9Sprite::create(DIALOG_MIDDLE_BG_IMAGE);
	len = middleBgSprite->getContentSize().width;
	middleBgSprite->setCapInsets(cocos2d::Rect(len / 3, len / 3, len / 3, len / 3));
	middleBgSprite->setContentSize(cocos2d::Size(664, 303));
	middleBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	middleBgSprite->setPosition(
		cocos2d::Point(dialogBgSize.width / 2, 111));
	dialogBg->addChild(middleBgSprite);

	//退出游戏按钮
	auto quitGameBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(SetLayer::quitGameCallback, this));
	quitGameBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	quitGameBtn->setPosition(cocos2d::Point(dialogBgSize.width / 4, 30));
	auto quiteGameMenu = cocos2d::Menu::create(quitGameBtn, nullptr);
	quiteGameMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(quiteGameMenu);

	//退出游戏按钮文本内容
	auto quitGameTTF = cocos2d::LabelTTF::create(util::GBToUTF8("退出游戏"), "Arial", 32);
	quitGameTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	quitGameTTF->setPosition(cocos2d::Point(quitGameBtn->getContentSize() / 2));
	quitGameBtn->addChild(quitGameTTF);

	//切换账号按钮
	auto switchAccountBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(SetLayer::switchAccountCallback, this));
	switchAccountBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	switchAccountBtn->setPosition(cocos2d::Point(dialogBgSize.width * 0.75, 30));
	auto switchAccountMenu = cocos2d::Menu::create(switchAccountBtn, nullptr);
	switchAccountMenu->setPosition(cocos2d::Vec2::ZERO);
	dialogBg->addChild(switchAccountMenu);

	//切换账号按钮回调函数
	auto switchAccountTTF = cocos2d::LabelTTF::create(util::GBToUTF8("切换账号"), "Arial", 32);
	switchAccountTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	switchAccountTTF->setPosition(cocos2d::Point(switchAccountBtn->getContentSize() / 2));
	switchAccountBtn->addChild(switchAccountTTF);

	//音乐
	auto bgMusic = cocos2d::Sprite::create();
	bgMusic->setPosition(cocos2d::Point(middleBgSprite->getContentSize().width / 2,
		middleBgSprite->getContentSize().height * (2.0f / 3)));
	middleBgSprite->addChild(bgMusic);

	//音乐图标和滑动条
	auto musicIcon = cocos2d::Sprite::create(SET_DIALOG_MUSIC);
	_musicSlider = cocos2d::extension::ControlSlider::create(
		SET_DIALOG_TRACK, SET_DIALOG_PROGRESS, SET_DIALOG_SLIDER);
	_musicSlider->setMinimumValue(0.0f);
	_musicSlider->setMaximumValue(1.0f);

	auto sliderTotalWidth = musicIcon->getContentSize().width + 30
		+ _musicSlider->getContentSize().width;
	musicIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	musicIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgMusic->addChild(musicIcon);

	_musicSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	_musicSlider->setPosition(cocos2d::Point(
		musicIcon->getPosition().x + musicIcon->getContentSize().width + 30, 0));
	bgMusic->addChild(_musicSlider);

	//音效
	auto bgEffect = cocos2d::Sprite::create();
	bgEffect->setPosition(cocos2d::Point(
		middleBgSprite->getContentSize().width / 2.0f,
		middleBgSprite->getContentSize().height * (1.0f / 3)));
	middleBgSprite->addChild(bgEffect);

	//音效图标和滑动条
	auto effectIcon = cocos2d::Sprite::create(SET_DIALOG_EFFECT);
	_effectSlider = cocos2d::extension::ControlSlider::create(
		SET_DIALOG_TRACK, SET_DIALOG_PROGRESS, SET_DIALOG_SLIDER);
	_effectSlider->setMinimumValue(0.0f);
	_effectSlider->setMaximumValue(1.0f);

	effectIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	effectIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgEffect->addChild(effectIcon);

	_effectSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	_effectSlider->setPosition(cocos2d::Point(
		effectIcon->getPosition().x + effectIcon->getContentSize().width + 30, 0));
	bgEffect->addChild(_effectSlider);

	return true;
}

bool SetLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}


void SetLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//设置窗口消失动画
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(SetLayer::funcBackCallback, this)),
		nullptr));
}

void SetLayer::funcBackCallback()
{
	//从当前场景移除设置对话框
	this->removeFromParent();
}

void SetLayer::quitGameCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	cocos2d::Director::getInstance()->end();	//结束游戏
}

void SetLayer::switchAccountCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//切换游戏账号操作
}

void SetLayer::musicChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_)
{
	//当滑块的百分比发生变化时
	if (type_ == cocos2d::extension::ControlSlider::EventType::VALUE_CHANGED)
	{
		auto volumn = _musicSlider->getValue();
		//保存设置的音乐值
		util::MusicUtil::setBgMusicVolume(volumn);
	}
}

void SetLayer::effectChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_)
{
	//当滑块的百分比发生变化时
	if (type_ == cocos2d::extension::ControlSlider::EventType::VALUE_CHANGED)
	{
		auto volumn = _effectSlider->getValue();
		//保存设置的音效值
		util::MusicUtil::setVolume(volumn);
	}
}