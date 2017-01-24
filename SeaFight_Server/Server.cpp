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
	consoleInputThread_.StartThread();

	for (Player* connectedPlayer = new Player(this); listener_.Accept(connectedPlayer->client()); connectedPlayer = new Player(this))
	{
		removeDisconnectedPlayers();

		players_.push_back(connectedPlayer);
		std::cout << "New connection...\n";

		connectedPlayer->StartThread();
	}
}

Player* Server::readyPlayer() const
{
	//TODO: lock
	return readyPlayer_;	//TODO: poll of ready players
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
	players_.erase(std::remove_if(players_.begin(), players_.end(), [](Player *p)->bool { return p->isDisconnected(); }), players_.end());
}

void Server::Quit()
{
	for (auto &p: players_)
	{
		p->client().Disconnect();
	}
	removeDisconnectedPlayers();
	listener_.Stop();
}

void Server::printPlayersOnline()
{
	//TODO: lock
	std::cout << "---Players online: ---" << std::endl;
	for (auto p: players_)
	{
		if (!p->isDisconnected())
			std::cout << p->name() << std::endl;
	}
	std::cout << "----------------------" << std::endl;
	//unlock
}
