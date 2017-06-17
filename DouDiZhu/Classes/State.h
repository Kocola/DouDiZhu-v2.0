#ifndef					__STATE_H__
#define					__STATE_H__

/*	×´Ì¬»ùÀà	---	2017.6.7
*/

#include "cocos2d.h"

class State : public cocos2d::Ref
{
public:
	virtual void handle() = 0;

	virtual void update() = 0;
};

#endif