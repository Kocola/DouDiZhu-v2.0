#include "HeadImageLayer.h"

#include "Common.h"
#include "HeadImage.h"
#include "Util.h"

static const std::string layerName = "headImageLayer";

void HeadImageLayer::createLayer()
{
	auto layer = HeadImageLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void HeadImageLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool HeadImageLayer::init()
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

bool HeadImageLayer::initView()
{
	//透明层（为了适配而设）
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0x00),
		BASE_WIDTH, BASE_HEIGHT);
	//transparentBg->setScale(SCALE);
	this->addChild(transparentBg);

	//电脑1的位置（右上方）
	_computerOneHeadImage = HeadImage::create();
	_computerOneHeadImage->setScale(MAX_SCALE);
	_computerOneHeadImage->setOrientation(HeadImage::RIGHT);
	_computerOneHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerOneHeadImage->setPosition(
		cocos2d::Point(BASE_WIDTH * 0.9 * SCALE_X, BASE_HEIGHT * 0.65 * SCALE_Y));
	this->addChild(_computerOneHeadImage, 1);

	//电脑2的位置（左上方）
	_computerTwoHeadImage = HeadImage::create();
	_computerTwoHeadImage->setScale(MAX_SCALE);
	_computerTwoHeadImage->setOrientation(HeadImage::LEFT);
	_computerTwoHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerTwoHeadImage->setPosition(
		cocos2d::Point(BASE_WIDTH * 0.1 * SCALE_X, BASE_HEIGHT * 0.65 * SCALE_Y));
	this->addChild(_computerTwoHeadImage);

	//手动玩家的位置
	_holdPlayerHeadImage = HeadImage::create();
	_holdPlayerHeadImage->setScale(MAX_SCALE);
	_holdPlayerHeadImage->setOrientation(HeadImage::LEFT);
	_holdPlayerHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_holdPlayerHeadImage->setPosition(
		cocos2d::Point(BASE_WIDTH * 0.1 * SCALE_X, BASE_HEIGHT * 0.3 * SCALE_Y));
	this->addChild(_holdPlayerHeadImage);

	return true;
}

bool HeadImageLayer::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateHolderHeadImageCallback),
		UPDATE_HOLDER_HEADIMAGE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateComputerOneHeadImageCallback),
		UPDATE_COMPUTERONE_HEADIMAHE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateComputerTwoHeadImageCallback),
		UPDATE_COMPUTERTWO_HEADIMAGE,
		nullptr);

	return true;
}

void HeadImageLayer::updateHeadImage()
{
	_holdPlayerHeadImage->setHeadImageType(HeadImage::FARMER);
	_computerOneHeadImage->setHeadImageType(HeadImage::FARMER);
	_computerTwoHeadImage->setHeadImageType(HeadImage::FARMER);
}


void HeadImageLayer::updateHolderHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_holdPlayerHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}

void HeadImageLayer::updateComputerOneHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_computerOneHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}

void HeadImageLayer::updateComputerTwoHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_computerTwoHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}