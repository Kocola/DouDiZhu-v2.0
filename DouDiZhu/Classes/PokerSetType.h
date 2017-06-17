#ifndef					__POKER_SET_TYPE_H__
#define					__POKER_SET_TYPE_H__

/*	牌面集合的类型	2017.6.10
*/

enum PokersType
{
	NONE,			//什么都不是
	SINGLE,			//单张
	PAIR,				//对子
	TRIPLE,			//三张
	TRIPLEWITHSINGLE,		//三带一
	TRIPLEWITHPAIR,			//三带二
	BOMB,			//炸弹
	KINGBOMB,	//王炸
	STRAIGHT,	//顺子
	PAIRSTRAIGHT,				//双顺
	TRIPLESTRAIGHT,			//三顺
	TRIPLESTRAIGHTWITHSINGLE,				//三顺带一
	TRIPLESTRAIGHTWITHPAIR					//三顺带二
};

#endif