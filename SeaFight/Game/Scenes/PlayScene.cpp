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
/*

	game().playerField().Draw(g);
	game().enemyField().Draw(g);
*/

	switch (game().state())
	{
		case Game::WaitEnemy:
			g.DrawSprite("wait_enemy", 415, 110, angle);
			if ((angle += 2) >= 360)
				angle -= 360;
			break;
	}
}

void PlayScene::OnClick(SDL_Point p)
{
	Scene::OnClick(p);

	switch (game().state())
	{
		case Game::MyStep:;
/*
			PlayerField &enemy = game().enemyField();
			SDL_Point coord;
			if (enemy.MapCoordAt(p, coord))
			{
				game().fire(coord);
				std::clog << "fire to {" << coord.x << ", " << coord.y << "}" << std::endl;
			}
			break;*/
	}
}
