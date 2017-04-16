#include "ReceiveThread.h"
#include <iostream>
#include "Game.h"

ReceiveThread::ReceiveThread(Game &game):
	Thread("ReceiveThread"),
	game_(game)
{
}

int ReceiveThread::Process()
{
	string cmd = "";
	
	while (game_.client().receive(cmd))
	{
		std::cout << "server: " << cmd << std::endl;
		if (cmd != CMD_OK)
			game_.pushCommand(cmd);
	}
	game_.onServerDisconnected();

	return 0;
}

