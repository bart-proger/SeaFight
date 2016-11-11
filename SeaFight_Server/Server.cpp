#include "Server.h"
#include "WinNetwork.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

Server::Server():
	readyPlayer_(NULL),
	inputThread_(*this)
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

	inputThread_.StartThread();

	while (listener_.Accept(connectedPlayer->client()))
	{
		RemoveDisconnectedPlayers();

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

void Server::RemoveDisconnectedPlayers()
{
	players_.erase(std::remove_if(players_.begin(), players_.end(), IsDisconnected), players_.end());
}

bool Server::IsDisconnected(Player* p)
{
	return p->IsDisconnected();
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

