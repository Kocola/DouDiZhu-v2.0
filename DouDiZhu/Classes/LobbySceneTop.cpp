#include "LobbySceneTop.h"

#include "Common.h"
#include "CustomServiceLayer.h"
#include "RuleLayer.h"
#include "SetLayer.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

#include "HeadImageLayer.h"

bool LobbySceneTop::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool LobbySceneTop::initView()
{
	//顶部背景
	auto topBg = cocos2d::ui::Scale9Sprite::create(LOBBY_TOP_BG);
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	topBg->setContentSize(cocos2d::Size(BASE_WIDTH, 100));
	topBg->setScale(SCALE_X);
	topBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	topBg->setPosition(cocos2d::Point(0, winSize.height));
	this->addChild(topBg, 0);

	//头像背景（框）
	auto headBgSprite = cocos2d::ui::Scale9Sprite::create(LOBBY_HEAD_BOX);
	const auto headBgScale = cocos2d::Size(0.54, 0.54);
	headBgSprite->setContentSize(cocos2d::Size(148 * 0.54, 148 * 0.54));
	headBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	headBgSprite->setPosition(cocos2d::Vec2(10, topBg->getContentSize().height / 2));
	topBg->addChild(headBgSprite);

	//头像
	auto headSprite = cocos2d::Sprite::create(LOBBY_HEAD);
	headSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	auto headScaleX = headSprite->getContentSize().width * headBgScale.width / headBgSprite->getContentSize().width;
	auto headScaleY = headSprite->getContentSize().height * headBgScale.height / headBgSprite->getContentSize().height;
	headSprite->setScaleX(headScaleX + 0.05);
	headSprite->setScaleY(headScaleY + 0.05);
	headSprite->setPosition(cocos2d::Point(headBgSprite->getContentSize() / 2));
	headBgSprite->addChild(headSprite, -1);	//让头像放置在头像框下

	//玩家名称
	std::string playerName = util::strongGBToUTF8("谷丝从云");
	auto playerNameText = cocos2d::LabelTTF::create(playerName, "Arial", 18);
	playerNameText->setColor(cocos2d::Color3B(0xF4, 0xE0, 0xDF));
	playerNameText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	playerNameText->setPosition(cocos2d::Point(headBgSprite->getPosition()) +
		cocos2d::Size(headBgSprite->getContentSize().width + 5, 30));
	topBg->addChild(playerNameText);

	//玩家ID
	auto playerID = "ID:123456";
	auto playerIDText = cocos2d::LabelTTF::create(playerID, "Arial", 18);
	playerIDText->setColor(cocos2d::Color3B(0xF4, 0xE0, 0xDF));
	playerIDText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	playerIDText->setPosition(playerNameText->getPosition() + 
		cocos2d::Size(0, -30));
	topBg->addChild(playerIDText);

	//大厅标题
	auto lobbyLogoBg = cocos2d::Sprite::create(LOBBY_SLOGAN_BG);
	lobbyLogoBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	lobbyLogoBg->setPosition(cocos2d::Point(topBg->getContentSize().width / 2, 0));
	topBg->addChild(lobbyLogoBg);
	auto lobbyLogo = cocos2d::Sprite::create(LOBBY_SLOGAN);
	lobbyLogo->setPosition(cocos2d::Point(lobbyLogoBg->getContentSize() / 2));
	lobbyLogoBg->addChild(lobbyLogo);

	//大厅设置按钮
	auto setBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(LOBBY_SETTING),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbySetCallback, this));
	auto topBgSize = topBg->getContentSize();
	setBtn->setPosition(cocos2d::Vec2(topBgSize.width - topBgSize.width / 3 / 6,
		topBgSize.height / 2));

	//游戏规则按钮
	auto ruleBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(LOBBY_RULE),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbyRuleCallback, this));
	ruleBtn->setPosition(cocos2d::Vec2(topBgSize.width  - topBgSize.width / 3 / 2,
		topBgSize.height / 2));

	//反馈按钮
	auto feedbackBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(LOBBY_FEEDBACK),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbyFeedbackCallback, this));
	feedbackBtn->setPosition(cocos2d::Point(topBgSize.width - topBgSize.width / 3 * 5 / 6,
		topBgSize.height / 2));
	
	//按钮之间的分割线
	auto btnLine1 = cocos2d::Sprite::create(LOBBY_BTN_LINE);
	auto btnLine2 = cocos2d::Sprite::create(LOBBY_BTN_LINE);
	auto btnLine1PosX = (setBtn->getPosition().x + ruleBtn->getPosition().x) / 2;
	auto btnLine2PosX = (ruleBtn->getPosition().x + feedbackBtn->getPosition().x) / 2;
	btnLine1->setPosition(cocos2d::Point(btnLine1PosX, ruleBtn->getPositionY()));
	btnLine2->setPosition(cocos2d::Point(btnLine2PosX, ruleBtn->getPositionY()));
	topBg->addChild(btnLine1);
	topBg->addChild(btnLine2);

	//将MenuItemSprite添加到Menu中
	auto menu = cocos2d::Menu::create(setBtn, ruleBtn, feedbackBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);	//没有此行，位置会有问题
	topBg->addChild(menu);

	return true;
}

void LobbySceneTop::lobbySetCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//转向设置界面
	SetLayer::createLayer();
	//PlayerLayer::createLayer();
}

void LobbySceneTop::lobbyRuleCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//转向规则界面
	RuleLayer::createLayer();
}

void LobbySceneTop::lobbyFeedbackCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//转向客服界面
	CustomServiceLayer::createLayer();
}
