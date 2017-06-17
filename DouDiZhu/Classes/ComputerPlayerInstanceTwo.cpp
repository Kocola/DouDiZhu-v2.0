#include "ComputerPlayerInstanceTwo.h"

ComputerPlayer ComputerPlayerInstanceTwo::_computerPlayer;

ComputerPlayer* ComputerPlayerInstanceTwo::getInstance()
{
	return &_computerPlayer;
}

