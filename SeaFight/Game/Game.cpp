#include "Game.h"
#include "Scene.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000


Game::Game():
	mainMenuScene(*this),
	placeShipScene(*this),
	playScene(*this),
	scene_(&mainMenuScene),
	//scene_(&placeShipScene),
	receiveThread_(*this),
	state_(WaitEnemy)
{
}

bool Game::connectToServer()
{
	if (!client_.Connect(SERVER_IP, SERVER_PORT))
	{
		std::cout << "Couldn't connect to server: " << SERVER_IP << ":" << SERVER_PORT << std::endl;
		return false;
	}
	if (!receiveThread_.Start())
		return false;

	return true;
}

void Game::readyPlay()
{
	client_.Send(CMD_READY_PLAY ":" + player_.mapData());
}

void Game::fire(SDL_Point coord)
{
	lastFire_ = coord;
	std::stringstream ssCmd;
	ssCmd << CMD_FIRE << ":" << coord.x << ":" << coord.y;
	client_.Send(ssCmd.str());
}

void Game::pushCommand(string cmd)
{
	//TODO: lock
	commands_.push(cmd);
	//unlock
}

void Game::parseCommands()
{
	while (true)
	{
		//TODO: lock
		bool empty = commands_.empty();
		//unlock
		if (empty)
			break;
		//lock
		string cmd = commands_.back();
		commands_.pop();
		//unlock

		if (cmd[0] != '>')
		{
			std::cerr << "[error] Bad command format!\n";
			return;
		}

		std::vector<string> args;
		std::stringstream ss(cmd);
		string item;

		while (std::getline(ss, item, ':'))
		{
			args.push_back(item);
		}

		if (args[0] == CMD_FIRST)
		{
			state_ = MyStep;
		}
		else if (args[0] == CMD_SECOND)
		{
			state_ = EnemyStep;
		}
		else if (args[0] == CMD_ENEMY_DISCONNECTED)
		{
			//TODO: show message if enemy disconnected
			setScene(placeShipScene);
			state_ = PlayState::WaitEnemy;
			player_.clearEnemyShots();

			enemy_.clearEnemyShots();
			enemy_.clearShips();
		}
		else if (args.size() >= 3)
		{
			SDL_Point coord{ atoi(args[1].c_str()), atoi(args[2].c_str()) };

			if (args[0] == CMD_HIT)
			{
				enemy_.addHit(coord);
			}
			else if (args[0] == CMD_MISS)
			{
				enemy_.addMiss(coord);
				state_ = PlayState::EnemyStep;
			}
			else if (args[0] == CMD_KILL)
			{
				enemy_.addKill(coord);
			}
			else if (args[0] == CMD_GET_HIT)
			{
				player_.addHit(coord);
			}
			else if (args[0] == CMD_GET_MISS)
			{
				player_.addMiss(coord);
				state_ = PlayState::MyStep;
			}
			else if (args[0] == CMD_GET_KILL)
			{
				player_.addKill(coord);
			}
		}
	}
}

bool Game::onInit()
{
	if (!Network::Init())
		return false;

	Graphics &g = graphics();

	if (!g.loadTexture("data/ui.tga"))
		return false;

	g.addSprite("btn_PlayOnline", 0, 0, 201, 44);
	g.addSprite("btn_PlayVsAI", 0, 44, 324, 44);
	g.addSprite("btn_Quit", 0, 88, 150, 44);
	g.addSprite("btn_ClearMap", 0, 132, 143, 44);
	g.addSprite("btn_GoFight", 0, 176, 107, 44);
	g.addSprite("btn_Surrender", 0, 220, 155, 44);
	g.addSprite("sea", 0, 272, 240, 240);
	g.addSprite("ship", 166, 242, 24, 24);
	g.addSprite("hit", 190, 242, 24, 24);
	g.addSprite("miss", 214, 242, 24, 24);
	g.addSprite("free", 238, 242, 24, 24);
	g.addSprite("coord_abc", 201, 0, 235, 30);
	g.addSprite("coord_123", 482, 0, 30, 240);
	g.addSprite("wait_enemy", 332, 32, 94, 94);

	g.addSprite("ship4", 250, 270, 96, 24);
	g.addSprite("ship3", 250, 300, 72, 24);
	g.addSprite("ship2", 250, 330, 48, 24);
	g.addSprite("ship1", 250, 360, 24, 24);

	g.addSprite("aim", 262, 242, 24, 24);

	mainMenuScene.init();
	placeShipScene.init();
	playScene.init();

	player_.setDrawOffset(35, 35);
	enemy_.setDrawOffset(340, 35);
	enemy_.clearShips(); //tmp
	
	return true;
}

void Game::onFree()
{
	client_.Disconnect();
	receiveThread_.Free();
	Network::Free();
}

// void Game::onKeyEvent()
// {
// }

void Game::onPress(SDL_Point p)
{
	scene_->onPress(p);
}

void Game::onRelease(SDL_Point p)
{
	scene_->onRelease(p);
}

void Game::onMouseMove(SDL_Point p)
{
	scene_->onMouseMove(p);
}

void Game::onUpdate()
{
	parseCommands();
}

void Game::onDraw()
{
	graphics().clear();
	scene().draw(graphics());
}
