#ifndef					__HEADIMAHE_H__
#define					__HEADIMAHE_H__

/* 玩家头像	---	2017.6.7
*/

#include "cocos2d.h"

class HeadImage : public cocos2d::Node
{
public:
	enum Type
	{
		LEANDLORD,
		FARMER
	};

	enum Orientation
	{
		LEFT,
		RIGHT
	};

public:
	CREATE_FUNC(HeadImage);

public:
	virtual bool init() override;

public:
	void setHeadImageType(Type type_);

	//设置头像朝向
	void setOrientation(Orientation orientation_);

private:
	cocos2d::SpriteFrame* createSpriteFrameWithType(Type type_, Orientation orientation_);

private:
	cocos2d::Sprite*	_headBox;		//头像框
	cocos2d::Sprite*	_curHeadImage;	//当前头像
	Orientation			_orientation;

	static cocos2d::SpriteFrameCache* s_spriteFrameCache;
};

#endif