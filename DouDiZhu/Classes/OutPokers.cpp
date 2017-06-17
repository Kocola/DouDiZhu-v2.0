#include "OutPokers.h"

OutPokers::OutPokers(Player* pokerOwner_, Poker poker_, size_t totalLen_, 
	PokersType pokersType_)
	: _outPokersOwner(pokerOwner_), _lowestPoker(poker_), _totalLen(totalLen_),
	_pokersType(pokersType_)
{
}

PokersType OutPokers::getPokersType() const
{
	return this->_pokersType;
}

void OutPokers::setPokersType(PokersType pokersType_)
{
	this->_pokersType = pokersType_;
}

size_t OutPokers::getTotalLen() const
{
	return this->_totalLen;
}

void OutPokers::setTotalLen(size_t totalLen_)
{
	this->_totalLen = totalLen_;
}

Poker OutPokers::getLowestPoker() const
{
	return this->_lowestPoker;
}

void OutPokers::setLowestPoker(Poker poker_)
{
	this->_lowestPoker = poker_;
}

Player* OutPokers::getPokerOwner() const
{
	return this->_outPokersOwner;
}