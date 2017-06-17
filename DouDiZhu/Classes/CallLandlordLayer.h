#ifndef					__CALL_LANDLORD_LAYER_H__
#define					__CALL_LANDLORD_LAYER_H__

/*	叫地主层	---	2017.6.9
*/

#include "cocos2d.h"

class CallLandlordLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(CallLandlordLayer);

	virtual bool init() override;

	bool initView();

	bool initContent();

private:
	void holderCallLandlordState(const std::string& name_);

	void computerOneCallLandlordState(const std::string& name_);

	void computerTwoCallLandlordState(const std::string& name_);

private:
	void displayCallLandlordBtnCallback(cocos2d::Ref*);

	//显示电脑玩家1叫分状态回调
	void displayComputerOneCallStateCallback(cocos2d::Ref*);

	//显示电脑玩家2叫分状态回调
	void displayComputerTwoCallStateCallback(cocos2d::Ref*);


	//手动玩家叫分回调
	void noCallCallBack(cocos2d::Ref*);

	void callOneCallback(cocos2d::Ref*);

	void callTwoCallback(cocos2d::Ref*);

	void callThreeCallback(cocos2d::Ref*);

	//电脑玩家1叫分回调
	void computerOneNoCallCallback(cocos2d::Ref*);

	void computerOneCallOneCallback(cocos2d::Ref*);

	void computerOneCallTwoCallback(cocos2d::Ref*);

	void computerOneCallThreeCallback(cocos2d::Ref*);

	//电脑玩家2叫分回调
	void computerTwoNoCallCallback(cocos2d::Ref*);

	void computerTwoCallOneCallback(cocos2d::Ref*);

	void computerTwoCallTwoCallback(cocos2d::Ref*);

	void computerTwoCallThreeCallback(cocos2d::Ref*);

private:
	cocos2d::SpriteFrameCache* _stateSpriteCache;

	cocos2d::Menu*					_btnMenu;	//手动玩家叫地主按钮

	cocos2d::Sprite*					_holderCallLandlordState;
	cocos2d::Sprite*					_computerOneCallLandlordState;
	cocos2d::Sprite*					_computerTwoCallLandlordState;
};

#endif