#ifndef					__WINDOW_UTIL_H__
#define					__WINDOW_UTIL_H__

/*	窗口相关的函数和变量，用于屏幕适配	---	2017.6.14
*/

#include "cocos2d.h"

namespace util
{
	struct WindowUtil
	{
		//初始化和缩放相关的变量值
		static float baseWidth;	//设计宽度
		static float baseHeight;	//设计高度
		static float screenWidth;	//屏幕宽度
		static float screenHeight;	//屏幕高度
		static float	 scaleX;		//水平缩放值
		static float scaleY;		//竖直缩放值

		//初始化设计尺寸
		static void doInit(const cocos2d::Size& designSize_);
	};
};

//宏定义，便于书写和访问
#define	 SCALE_X	util::WindowUtil::scaleX	
#define SCALE_Y	util::WindowUtil::scaleY
#define BASE_WIDTH util::WindowUtil::baseWidth
#define BASE_HEIGHT util::WindowUtil::baseHeight
#define SCREEN_WIDTH util::WindowUtil::screenWidth
#define SCREEN_HEIGHT util::WindowUtil::screenHeight
#define MIN_SCALE std::min(SCALE_X, SCALE_Y)
#define SCALE MIN_SCALE
#define MAX_SCALE std::max(SCALE_X, SCALE_Y)
#define MIDDLE_SCALE (SCALE_X + SCALE_Y ) / 2.0f

#endif