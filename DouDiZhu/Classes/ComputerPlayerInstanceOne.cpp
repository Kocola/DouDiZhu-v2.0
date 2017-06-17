#include "ComputerPlayerInstanceOne.h"

ComputerPlayer ComputerPlayerInstanceOne::_computerPlayer;

ComputerPlayer* ComputerPlayerInstanceOne::getInstance()
{
	return &_computerPlayer;
}
