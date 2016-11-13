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
	
	while (game_.client().Connected() && game_.client().Receive(cmd))
	{
		std::cout << "server: " << cmd.c_str() << std::endl;
		if (cmd != CMD_OK)
			game_.pushCommand(cmd);
	}
	return 0;
}

