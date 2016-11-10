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

void Game::setScene(Scene &value)
{
	scene_ = &value;
}

Scene & Game::scene()
{
	return *scene_;
}

Game::PlayState Game::state() const
{
	return state_;
}

Player & Game::player()
{
	return player_;
}

Player & Game::enemy()
{
	return enemy_;
}

TcpClient & Game::client()
{
	return client_;
}

void Game::parseCommand(string cmd)
{
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
		//NewGame();
		setScene(placeShipScene);
		state_ = WaitEnemy;
		player_.clearEnemyShots();
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
		// TODO: else if (args[0] == CMD_GET_KILL)
		//	{
		//	}
	}
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

bool Game::OnInit()
{
	if (!Network::Init())
		return false;

	Graphics &g = graphics();

 	if (!g.LoadTexture("data/ui.tga"))
		return false;

	if (!font_.LoadFromFile("data/Skellyman.ttf"))
		return false;

	g.AddSprite("btn_PlayOnline", 0, 0, 201, 44);
	g.AddSprite("btn_PlayVsAI", 0, 44, 324, 44);
	g.AddSprite("btn_Quit", 0, 88, 150, 44);
	g.AddSprite("btn_ClearMap", 0, 132, 143, 44);
	g.AddSprite("btn_GoFight", 0, 176, 107, 44);
	g.AddSprite("btn_Surrender", 0, 220, 155, 44);
	g.AddSprite("sea", 0, 272, 240, 240);
	g.AddSprite("ship", 166, 242, 24, 24);
	g.AddSprite("hit", 190, 242, 24, 24);
	g.AddSprite("miss", 214, 242, 24, 24);
	g.AddSprite("coord_abc", 201, 0, 235, 30);
	g.AddSprite("coord_123", 482, 0, 30, 240);
	g.AddSprite("wait_enemy", 332, 32, 94, 94);

	mainMenuScene.Init();
	placeShipScene.Init();

	player_.setDrawOffset(35, 35);
	enemy_.setDrawOffset(340, 35);
	enemy_.clearShips(); //tmp
	
	return true;
}

void Game::OnFree()
{
	client_.Disconnect();
	receiveThread_.Free();
	Network::Free();
}

void Game::OnKeyEvent()
{
}

void Game::OnMouseEvent(SDL_Point p)
{
	scene_->OnClick(p);
}

void Game::OnDraw()
{
	graphics().Clear();
	scene().Draw(graphics());
	SDL_Color c = { 0, 0, 0, 255 };
	graphics().DrawText(font_, c, "Pirates!!!!!!!", 30, 30);
}
