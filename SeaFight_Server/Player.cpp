#include "Player.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Server.h"

Player::Player(Server* server):
	state_(PlayState::Disconnected),
	server_(server),
//	client_(client),//,
	enemy_(NULL),
	WinThread()
{
	std::stringstream ss;
	ss << "player" << ((int)this % 1000);
	name_ = ss.str();

	ClearMap();
}

Player::~Player()
{
	client_.Disconnect();
}

// 
// void Player::setEnemy(Player* enemy)
// {
// 	this->enemy_ = enemy;
// }
// 
// void Player::setState(PlayState value)
// {
// 	this->state_ = value;
// }
// 
// Player::PlayState Player::state() const
// {
// 	return state_;
// }
// 
bool Player::IsReadyPlay() const
{
	return (state_ == PlayState::ReadyPlay);
}

WinTcpClient & Player::client()
{
	return client_;
}

bool Player::IsDisconnected() const
{
	return (state_ == PlayState::Disconnected);
}

// 
// void Player::setClient(WinTcpClient value)
// {
// 	client_ = value;
// }
// 
// Player::Cell & Player::map(int x, int y)
// {
// 	return map_[y][x];
// }

void Player::InitMap(string data)
{
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x)
		{
			if (data[y*10 + x] == '1')
				map_[y][x].hasShip = true;
		}
}

void Player::ClearMap()
{
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x)
		{
			map_[y][x].hasShip = false;
			map_[y][x].attacked = false;
		}
}

void Player::Fire(int x, int y)
{
	std::stringstream ssArgs;
	ssArgs << ":" << x << ":" << y;

	enemy_->map_[y][x].attacked = true;

	if (enemy_->map_[y][x].hasShip)	// hit
	{
		client_.Send(CMD_HIT + ssArgs.str());
		enemy_->client().Send(CMD_GET_HIT + ssArgs.str());
	}
	else                            // miss
	{
		client_.Send(CMD_MISS + ssArgs.str());	
		enemy_->client().Send(CMD_GET_MISS + ssArgs.str());

		PlayEnemy();
	}
	//TODO: kill/get_kill
}

void Player::PlayEnemy()
{
	state_ = PlayState::EnemyStep;
	enemy_->state_ = PlayState::MyStep;
}

void Player::WaitNextEnemy()
{
	if (enemy_ = server_->readyPlayer())
	{
		enemy_->enemy_ = this;
		server_->setReadyPlayer(NULL);
		StartBattle();
		return;
	}

	std::cout << name_ << ": wait next enemy...\n";

	enemy_ = NULL;
	server_->setReadyPlayer(this);

	bool found = false;
	while (!found)
	{
		Sleep(3000);
		//TODO: lock
		if (enemy_)
			found = true;
		//unlock
	}
}

void Player::StartBattle()
{
	if ((rand() % 2) < 1)
	{
		client_.Send(CMD_FIRST);
		enemy_->client_.Send(CMD_SECOND);

		state_ = PlayState::MyStep;
		enemy_->state_ = PlayState::EnemyStep;
	}
	else
	{
		client_.Send(CMD_SECOND);
		enemy_->client_.Send(CMD_FIRST);

		state_ = PlayState::EnemyStep;
		enemy_->state_ = PlayState::MyStep;
	}
	std::cout << name_ << " _vs_ " << enemy_->name_ << " - Start battle!\n";
}

void Player::ParseCommand(string cmd)
{
	if (!strstr(cmd.c_str(), ">"))
	{
		std::cerr << "[error] Bad command format!\n";
		return;
	}

	//string cmd(cmd);
	std::vector<string> args;
	std::stringstream ss(cmd);
	string item;
	while (std::getline(ss, item, ':')) 
	{
		args.push_back(item);
	}

	//TODO: check cmd args

	if (state_ == PlayState::Connected && args[0] == CMD_READY_PLAY)
	{
		InitMap(args[1]);

		state_ = PlayState::ReadyPlay;

		WaitNextEnemy();
	}
	else if (state_ == PlayState::MyStep && args[0] == CMD_FIRE)
	{
		Fire(atoi(args[1].c_str()), atoi(args[2].c_str()));
	}
}

void Player::Process()				//------- ReceiveThread
{
	string data = "";

//TODO: if authorized
	{
		state_ = PlayState::Connected;
	}
// 	else
// 		return;

	std::cout << name_ << " successfully connected\n";

	while (/*client_.Connected() && */client_.Receive(data))
	{
		std::cout << name_ << ": " << data.c_str() << std::endl;
		ParseCommand(data);
	}

	state_ = PlayState::Disconnected;

	if (enemy_)
	{
		enemy_->client().Send(CMD_ENEMY_DISCONNECTED);
		enemy_->enemy_ = NULL;
		enemy_->state_ = PlayState::Connected;
	}
	std::cout << name_ << " disconnected\n";
}