#include "PlayScene.h"
#include "../Game.h"
#include <iostream>

PlayScene::PlayScene(Game &game) :
	Scene(game)
{
}

void PlayScene::init()
{
	//TODO: кнопка [Сдаться]
	//SDL_Rect = { 250, 250,  };
	if (!font_.LoadFromFile("data/Skellyman.ttf"))
		return;
}

void PlayScene::update(float dt)
{
	//TODO: angle += 0.05 * dt
}

double angle = 0;

void PlayScene::draw(Graphics &g)
{
	Scene::draw(g);

	game().player().draw(g);
	game().enemy().draw(g);

	string status = "";

	if (game().state() == Game::WaitEnemy)
	{
		g.drawSprite("wait_enemy", 415, 110, angle);
		if ((angle += 2) >= 360)
			angle -= 360;
		status = "Wait for enemy to connect...";
	}
	else if (game().state() == Game::MyStep)
		status = "Fire!!!";
	else if (game().state() == Game::EnemyStep)
		status = "Enemy shot...";

	if (font_.Loaded())
		g.drawText(font_, SDL_Color{ 0, 0, 0, 255 }, status, 30, 300);
}

void PlayScene::onRelease(SDL_Point p)
{
	Scene::onRelease(p);

	if (game().state() == Game::MyStep)
	{
		Player &enemy = game().enemy();
		SDL_Point coord = enemy.coordAt(p);
		if (coord.x > -1 && coord.y > -1)
		{
			game().fire(coord);
			std::clog << "fire to (" << coord.x << ", " << coord.y << ") ===> ";
		}
	}
}
