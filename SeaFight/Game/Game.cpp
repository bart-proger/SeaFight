﻿#include "Game.h"
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

void Game::setState(PlayState state)
{
	state_ = state;
	if (scene_ != nullptr)
		scene_->onChangeGameState(/*state_*/);
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

void Game::surrender()
{
	client_.Send(CMD_SURRENDER);
}

void Game::newBattle()
{
	player_.clearEnemyShots();
	enemy_.clearShips();
	enemy_.clearEnemyShots();
	//TODO: + очистить статистику боя
}

void Game::pushCommand(string cmd)
{
SDL_LockMutex(commandsLock_);
	commands_.push(cmd);
SDL_UnlockMutex(commandsLock_);
}

void Game::parseCommands()
{
	while (true)
	{
SDL_LockMutex(commandsLock_);
		bool empty = commands_.empty();
SDL_UnlockMutex(commandsLock_);
		if (empty)
			break;
SDL_LockMutex(commandsLock_);
		string cmd = commands_.front();
		commands_.pop();
SDL_UnlockMutex(commandsLock_);

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

		SDL_Point coord{-1, -1};
		if (args.size() >= 3)
		{
			coord = { atoi(args[1].c_str()), atoi(args[2].c_str()) };
		}

		if (args[0] == CMD_FIRST)
		{
			setState(PlayState::MyShot);
		}
		else if (args[0] == CMD_SECOND)
		{
			setState(PlayState::EnemyShot);
		}
		else if (args[0] == CMD_ENEMY_DISCONNECTED)
		{
			//TODO: show message if enemy disconnected
			setState(PlayState::EnemyDisconnected);
		}
		else if (args[0] == CMD_HIT)
		{
			enemy_.addHit(coord);
		}
		else if (args[0] == CMD_MISS)
		{
			enemy_.addMiss(coord);
			setState(PlayState::EnemyShot);
		}
		else if (args[0] == CMD_KILL)
		{
std::cout << "**add killed ship for enemy\n";
			enemy_.addKill(coord);
		}
		else if (args[0] == CMD_GET_HIT)
		{
			player_.addHit(coord);
		}
		else if (args[0] == CMD_GET_MISS)
		{
			player_.addMiss(coord);
			setState(PlayState::MyShot);
		}
		else if (args[0] == CMD_GET_KILL)
		{
std::cout << "**my ship is killed\n";
			player_.addKill(coord);
		}
		else if (args[0] == CMD_WIN)
		{
			setState(PlayState::Win);
		}
		else if (args[0] == CMD_LOSE)
		{
			setState(PlayState::Lose);
			//TODO: вывод оставшихся кораблей
		}
		else if (args[0] == CMD_ENEMY_SURRENDER)
		{
			setState(PlayState::EnemySurrender);
		}
		else
			std::cout << "[error] Undefined command!\n";
	}
}

bool Game::onInit()
{
	if (!Network::Init())
		return false;

	Graphics &g = graphics();

	if (!g.loadTexture("data/ui.tga"))
		return false;

	commandsLock_ = SDL_CreateMutex();

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
	g.addSprite("btn_surrender", 194, 88, 44, 44);
	g.addSprite("btn_fire", 150, 88, 44, 44);
	g.addSprite("btn_continue", 150, 132, 44, 44);

	mainMenuScene.init();
	placeShipScene.init();
	playScene.init();

	player_.setDrawOffset(35, 35);
	enemy_.setDrawOffset(340, 35);
	
	return true;
}

void Game::onFree()
{
	client_.Disconnect();
	receiveThread_.Free();
	Network::Free();
	SDL_DestroyMutex(commandsLock_);
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
	//TODO: вычислить прошедшее время dt
	scene_->update(0.0f);
}

void Game::onDraw()
{
	graphics().clear();
	scene().draw(graphics());
}
