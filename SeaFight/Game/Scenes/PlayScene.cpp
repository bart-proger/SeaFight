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
		status = "Ожидание подключения соперника...";
	}
	else if (game().state() == Game::MyStep)
		status = "Огонь!!!";
	else if (game().state() == Game::EnemyStep)
		status = "Выстрел соперника...";

	if (font_.Loaded())
		g.drawText(font_, SDL_Color{ 0, 0, 0, 255 }, status, 30, 300);

	if (aimPos_ != nullptr && game().state() == Game::MyStep)
	{
		SDL_Point of = game().enemy().drawOffset();
		g.drawSprite("aim", aimPos_->x*Ship::DECK_SIZE + of.x, aimPos_->y*Ship::DECK_SIZE + of.y);
	}
}

void PlayScene::onRelease(SDL_Point p)
{
	Scene::onRelease(p);

	if (game().state() == Game::MyStep)
	{
//		Player &enemy = game().enemy();
//		aimPos_ = game().enemy().coordAt(p);
		if (aimPos_ != nullptr)
		{
//TODO: выстрел после нажатия кнопки огонь [-=O]
			game().fire(*aimPos_);
			std::clog << "fire to (" << aimPos_->x << ", " << aimPos_->y << ") ===> ";
			aimPos_ = nullptr;
		}
	}
}

void PlayScene::onMouseMove(SDL_Point p)
{
	Scene::onMouseMove(p);

	aimPos_ = nullptr;
	if (game().state() == Game::MyStep)
	{
		aimPos_ = game().enemy().coordAt(p);
	}
}
