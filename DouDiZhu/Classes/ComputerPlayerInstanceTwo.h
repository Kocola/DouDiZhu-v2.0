#ifndef				__COMPUTER_PLAYER_INSTANCE_TWO_H__
#define				__COMPUTER_PLAYER_INSTANCE_TWO_H__

/*	µçÄÔÍæ¼ÒÊµÀý2	---	2017.6.9
*/

#include "ComputerPlayer.h"
#include "Singleton.h"

class ComputerPlayerInstanceTwo : public Singleton < ComputerPlayer >
{
public:
	static ComputerPlayer* getInstance();

private:
	static ComputerPlayer _computerPlayer;
};

#endif