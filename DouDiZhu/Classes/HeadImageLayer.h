#ifndef					__HEADIMAGE_LAYER_H__
#define					__HEADIMAGE_LAYER_H__

/*	玩家层：存放玩家头像信息	---	2017.6.7 
*/

#include "cocos2d.h"

class HeadImage;

class HeadImageLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(HeadImageLayer);

	virtual bool init() override;

private:
	bool initView();

	bool initContent();

	//将所有头像都设置为农民
	void updateHeadImage();

private:
	//针对不同的callback，将目标头像设置为地主

	void updateHolderHeadImageCallback(cocos2d::Ref*);

	void updateComputerOneHeadImageCallback(cocos2d::Ref*);

	void updateComputerTwoHeadImageCallback(cocos2d::Ref*);

private:
	HeadImage* _computerOneHeadImage;
	HeadImage* _computerTwoHeadImage;
	HeadImage* _holdPlayerHeadImage;
};

#endif