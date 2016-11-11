#include "Battle.h"
#include <iostream>
#include <ctime>

Battle::Battle():
	player1(NULL),
	player2(NULL)
//	readyPlayers(0)
{
	srand((unsigned int)time(NULL));
	std::cout << "Create new battle\n";
}

Battle::~Battle()
{
	if (player1)
		delete player1;
	player1 = NULL;

	if (player2)
		delete player2;
	player2 = NULL;
}

void Battle::AddPlayer(WinTcpClient &client)
{
/*	int playersCount = 2;

	if (!IsPlayerConnected(player1))
	{
		player1 = new Player(&client);
		player1->Start();
		std::cout << "Player1 connected to battle\n";
		--playersCount;
	} 
	else if (!IsPlayerConnected(player2))
	{
		player2 = new Player(&client);
		player2->Start();
		std::cout << "Player2 connected to battle\n";
		--playersCount;
	}

	if (playersCount == 2)
	{
		player1->setEnemy(player2);
		player2->setEnemy(player1);
	}
	*/
}

bool Battle::IsPlayerConnected(Player* p) const
{
	return (p && p->client().Connected());
}

bool Battle::AllPlayersConnected() const
{
	return (IsPlayerConnected(player1) && IsPlayerConnected(player2));
}

