#include "PlayScene.h"
#include "../Game.h"
#include <iostream>

PlayScene::PlayScene(Game &game) :
	Scene(game)
{
}

void PlayScene::Init()
{
	//TODO: кнопка [Сдаться]
	//SDL_Rect = { 250, 250,  };
}

void PlayScene::Update(float dt)
{
	//TODO: angle += 0.05 * dt
}

double angle = 0;

void PlayScene::Draw(Graphics &g)
{
	Scene::Draw(g);

	game().player().draw(g);
	game().enemy().draw(g);

	if (game().state() == Game::WaitEnemy)
	{
		g.DrawSprite("wait_enemy", 415, 110, angle);
		if ((angle += 2) >= 360)
			angle -= 360;
	}
}

void PlayScene::OnClick(SDL_Point p)
{
	Scene::onClick(p);

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
