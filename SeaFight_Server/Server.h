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
	void RemoveDisconnectedPlayers();
private:
	static bool IsDisconnected(Player* );
	
	WinTcpListener listener_;
	std::vector<Player*> players_;
	Player* readyPlayer_;
	InputThread inputThread_;
};

