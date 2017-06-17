#include "CustomServiceLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

static const std::string layerName = "feedbackLayer";

void CustomServiceLayer::createLayer()
{
	auto layer = CustomServiceLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()
		->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()
			->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()
		->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool CustomServiceLayer::init()
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

	if (initContent() == false)
	{
		return false;
	}

	//屏蔽屏幕触摸往下层传递
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CustomServiceLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	//吞噬触摸事件向下层传递
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//android物理返回键
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(CustomServiceLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

bool CustomServiceLayer::initView()
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
	//dialogBg->setScale(MAX_SCALE);
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
	auto titleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("客服"), "Arial", 34);
	titleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	titleTTF->setPosition(cocos2d::Point(dialogBgTop->getContentSize() / 2));
	dialogBgTop->addChild(titleTTF);

	//窗口关闭按钮
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_CLOSE_BTN),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Size(dialogBgSize.width - closeBtn->getContentSize().width / 3,
		dialogBgSize.height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(cocos2d::Point(closeBtnPos));
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//对话框中间背景
	_middleBgSprite = cocos2d::ui::Scale9Sprite::create(DIALOG_MIDDLE_BG_IMAGE);
	len = _middleBgSprite->getContentSize().width;
	_middleBgSprite->setCapInsets(cocos2d::Rect(len / 3, len / 3, len / 3, len / 3));
	_middleBgSprite->setContentSize(cocos2d::Size(664, 303));
	_middleBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_middleBgSprite->setPosition(
		cocos2d::Point(dialogBgSize.width / 2, 111));
	dialogBg->addChild(_middleBgSprite);

	//拨打客服电话按钮
	auto callCustomServiceBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::callServiceCallback, this));
	callCustomServiceBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	callCustomServiceBtn->setPosition(cocos2d::Point(dialogBgSize.width / 4, 30));
	auto callCustomServiceMenu = cocos2d::Menu::create(callCustomServiceBtn, nullptr);
	callCustomServiceMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(callCustomServiceMenu);

	//拨打客服电话按钮文本内容
	auto callCustomServiceTTF = cocos2d::LabelTTF::create(util::GBToUTF8("拨打电话"), "Arial", 32);
	callCustomServiceTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	callCustomServiceTTF->setPosition(cocos2d::Point(callCustomServiceBtn->getContentSize() / 2));
	callCustomServiceBtn->addChild(callCustomServiceTTF);

	//意见反馈按钮
	auto feedbackBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::feedbackCallback, this));
	feedbackBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	feedbackBtn->setPosition(cocos2d::Point(dialogBgSize.width * 0.75, 30));
	auto feedbackMenu = cocos2d::Menu::create(feedbackBtn, nullptr);
	feedbackMenu->setPosition(cocos2d::Vec2::ZERO);
	dialogBg->addChild(feedbackMenu);

	//意见反馈按钮文本内容
	auto feedbackTTF = cocos2d::LabelTTF::create(util::GBToUTF8("意见反馈"), "Arial", 32);
	feedbackTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	feedbackTTF->setPosition(cocos2d::Point(feedbackBtn->getContentSize() / 2));
	feedbackBtn->addChild(feedbackTTF);

	return true;
}

bool CustomServiceLayer::initContent()
{
	//客服QQ
	std::string textAccount = "客服QQ：123456789";
	auto QQInfoTtf = cocos2d::LabelTTF::create(util::GBToUTF8(textAccount.c_str()), "", 30);
	QQInfoTtf->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));

	//客服电话
	std::string textPwd = "客服电话：123456789";
	auto showTextPwdTtf = cocos2d::LabelTTF::create(util::GBToUTF8(textPwd.c_str()), "", 30);
	showTextPwdTtf->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));

	auto width = std::max(QQInfoTtf->getContentSize().width, showTextPwdTtf->getContentSize().width);
	auto height = QQInfoTtf->getContentSize().height + showTextPwdTtf->getContentSize().height + 20;

	auto contentBg = cocos2d::Sprite::create();
	contentBg->setContentSize(cocos2d::Size(width, height));
	QQInfoTtf->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	QQInfoTtf->setPosition(cocos2d::Point(width / 2, height));
	showTextPwdTtf->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	showTextPwdTtf->setPosition(cocos2d::Point(width / 2, 0));
	contentBg->addChild(QQInfoTtf);
	contentBg->addChild(showTextPwdTtf);

	contentBg->setPosition(_middleBgSprite->getContentSize() / 2);
	_middleBgSprite->addChild(contentBg);

	return true;
}

bool CustomServiceLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}

void CustomServiceLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//返回键触摸后释放操作
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

void CustomServiceLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//设置窗口消失动画
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(CustomServiceLayer::funcBackCallback, this)),
		nullptr));
}

void CustomServiceLayer::funcBackCallback()
{
	//从当前场景移除设置对话框
	this->removeFromParent();
}

void CustomServiceLayer::callServiceCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//拨打客服电话按钮回调
}

void CustomServiceLayer::feedbackCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//意见反馈按钮回调
}
