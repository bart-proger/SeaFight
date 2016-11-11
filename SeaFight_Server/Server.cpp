#include "Server.h"
#include "WinNetwork.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

Server::Server():
	readyPlayer_(NULL),
	consoleInputThread_(*this)
{
}

bool Server::Init(string ip, unsigned short port)
{
	if (!listener_.Listen(ip, port))
		return false;

	return true;
}

void Server::Run()
{
	Player* connectedPlayer = new Player(this);

	consoleInputThread_.StartThread();

	while (listener_.Accept(connectedPlayer->client()))
	{
		removeDisconnectedPlayers();

		players_.push_back(connectedPlayer);
		std::cout << "New connection...\n";

		connectedPlayer->StartThread();

		connectedPlayer = new Player(this);
	}
}

Player* Server::readyPlayer() const
{
	//TODO: lock
	return readyPlayer_;
	//unlock
}

void Server::setReadyPlayer(Player* value)
{
	//TODO: lock
	readyPlayer_ = value;
	//unlock
}

void Server::removeDisconnectedPlayers()
{
	players_.erase(std::remove_if(players_.begin(), players_.end(), isDisconnected), players_.end());
}

bool Server::isDisconnected(Player* p)
{
	return p->isDisconnected();
}

void Server::Quit()
{
	//TODO: stop all players threads
	listener_.Stop();
}

// 
// void Server::Process()			//---- ManageThread
// {
// 	while (true)
// 	{
// 
// 	}
// }

