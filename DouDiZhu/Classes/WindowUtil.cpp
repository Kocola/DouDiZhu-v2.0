#include "WindowUtil.h"

namespace util
{
	float WindowUtil::baseWidth = 0.0f;
	float WindowUtil::baseHeight = 0.0f;
	float WindowUtil::screenWidth = 0.0f;
	float WindowUtil::screenHeight = 0.0f;
	float WindowUtil::scaleX = 0.0f;
	float WindowUtil::scaleY = 0.0f;

	void WindowUtil::doInit(const cocos2d::Size& designSize_)
	{
		baseWidth = designSize_.width;
		baseHeight = designSize_.height;

		auto winSize = cocos2d::Director::getInstance()->getWinSize();

		screenWidth = winSize.width;
		screenHeight = winSize.height;

		scaleX = screenWidth / baseWidth;
		scaleY = screenHeight / baseHeight;
	}
};

