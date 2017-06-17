#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* 手动玩家	---	2017.6.9
*/

#include "Player.h"

class Poker;

class HolderPlayer : public Player
{
public:
	HolderPlayer();

private:
	bool init();

	bool initContent();

public:
	//手动玩家显示手中的牌
	void displayPokers();

	virtual void callLandlord() override;

	virtual void outPokers(OutPokers* lastOutPokers_) override;

	virtual void outPokersCallback() override;

	//和基类函数的区别是，这里可以拆牌
	virtual std::vector<Poker> searchOutPokers(OutPokers* lastOutPokers_) override;

private:
	//待出的牌是否可以出
	bool isPokerWaitForOutCanOut();

	//设置出牌按钮是否可按
	void checkOutPokerBtnEnabled();

private:
	//从待出牌序列中删除某张牌回调
	void deletePokerWaitForOutCallback(cocos2d::Ref* sender_);

	//向待出牌序列中增加某张牌回调
	void addPokerWaitForOutCallback(cocos2d::Ref* sender_);

	//点击出牌按钮后的出牌回调
	void holderOutPokersCallback(cocos2d::Ref*);

	void clickHintBtnCallback(cocos2d::Ref*);

private:
	std::vector<Poker>			_pokersWaitForOut;		//已点击准备出的牌
	std::vector<Poker>			_hintPokers;	//提示的牌
	//cocos2d::Vector<Poker*>	_holderPokerForPost;		//玩家持有的牌（用于消息传递）
	OutPokers*						_lastOutPokers;		//存放手动玩家前一个玩家出的牌，
};

#endif