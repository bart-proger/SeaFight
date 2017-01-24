#include "Player.h"
#include "InputThread.h"
#include <iostream>
#include "Server.h"

InputThread::InputThread(Server &server):
	WinThread(),
	server_(server)
{
}

void InputThread::Process()
{
	string cmd = "";

	while (true)
	{
		std::cin >> cmd;
		if (cmd == "quit" || cmd == "q")
			break;
		else if (cmd == "players" || cmd == "p")
		{
			server_.printPlayersOnline();
		}
	}

	server_.Quit();
}
