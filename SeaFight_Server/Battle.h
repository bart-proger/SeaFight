#pragma once

#include "Player.h"
#include "WinThread.h"

class Battle
{
public:
	Battle();
	~Battle();

	void AddPlayer(WinTcpClient &);
	bool AllPlayersConnected() const;

private:
	bool IsPlayerConnected(Player* ) const;

	Player* player1;
	Player* player2;
	//	int playersCount;
	//int readyPlayers;
};
