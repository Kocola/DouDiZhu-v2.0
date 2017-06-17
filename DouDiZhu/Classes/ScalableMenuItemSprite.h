#ifndef					__SCALABLE_MENU_ITEM_SPRITE_H__
#define					__SCALABLE_MENU_ITEM_SPRITE_H__

/*	ÖØÐ´cocos2dµÄMenuItemSprite --- 2017.6.5
*/

#include "cocos2d.h"

class ScalableMenuItemSprite : public cocos2d::MenuItemSprite
{
public:
	static ScalableMenuItemSprite* create(cocos2d::Node* normalSprite_,
		cocos2d::Node* seletedSprite,
		const cocos2d::ccMenuCallback& callback_);

	virtual void selected() override;

	virtual void unselected() override;
};

#endif