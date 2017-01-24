#pragma once
#include "WinTcpListener.h"
#include <vector>
#include "InputThread.h"

class Player;

class Server//: WinThread
{
public:
	Server();
	bool Init(string ip, unsigned short port);
	void Run();
	void Quit();

	Player* readyPlayer() const;
	void setReadyPlayer(Player* );
	void removeDisconnectedPlayers();
	void printPlayersOnline();
private:
	//static bool isDisconnected(Player* );
	
	WinTcpListener listener_;
	std::vector<Player*> players_;
	Player* readyPlayer_;

	InputThread consoleInputThread_;
};

