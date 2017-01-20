#include "PlayScene.h"
#include "../Game.h"
#include <iostream>

PlayScene::PlayScene(Game &game) :
	Scene(game)
{
}

void PlayScene::init()
{
	//TODO: кнопка [Сдаться]/[Новое сражение]
	//SDL_Rect = { 250, 250,  };
	if (!font_.loadFromFile("data/Skellyman.ttf"))
		return;

	addButton("btn_surrender", { 100, 350, 44, 44 }, surrender_click);
	addButton("btn_fire", { 400, 350, 44, 44 }, fire_click);
	addButton("btn_continue", { 250, 350, 44, 44 }, continue_click);

	status_ = "Ожидание подключения соперника...";
	hideButton("btn_fire");
	hideButton("btn_surrender");
	hideButton("btn_continue");
}

void PlayScene::update(float dt)
{
	//TODO: angle += 0.05 * dt
	//if (game().state())
}

void PlayScene::draw(Graphics &g)
{
	game().player().draw(g);
	game().enemy().draw(g);

	static double angle = 0;

	switch (game().state())
	{
		case Game::PlayState::WaitEnemy:
			g.drawSprite("wait_enemy", 415, 110, angle);
			if ((angle += 2) >= 360)
				angle -= 360;
			break;
		case Game::PlayState::MyStep:
			if (aimPos_ != nullptr)
			{
				SDL_Point of = game().enemy().drawOffset();
				g.drawSprite("aim", aimPos_->x*Ship::DECK_SIZE + of.x, aimPos_->y*Ship::DECK_SIZE + of.y);
			}
			break;
	}

	if (font_.Loaded())
		g.drawText(font_, SDL_Color{ 0, 0, 0, 255 }, status_, 30, 300);

	Scene::draw(g);
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

	if (game().state() == Game::MyStep)
	{
		aimPos_ = game().enemy().coordAt(p);
	}
	else
	{
		aimPos_ = nullptr;
	}
}

void PlayScene::onChangeGameState(/*Game::PlayState state*/)
{
	switch (game().state())
	{
		case Game::PlayState::WaitEnemy:
			hideButton("btn_fire");
			hideButton("btn_surrender");
			hideButton("btn_continue");
			status_ = "Ожидание подключения соперника...";
			break;
		case Game::PlayState::MyStep:
			showButton("btn_fire");
			showButton("btn_surrender");
			status_ = "Огонь!!!";
			break;
		case Game::PlayState::EnemyStep:
			hideButton("btn_fire");
			hideButton("btn_surrender");
			status_ = "Выстрел соперника...";
			break;
		case Game::PlayState::Win:
			hideButton("btn_surrender");
			hideButton("btn_fire");
			showButton("btn_continue");
			status_ = "Победа!!!!!!";
			break;
		case Game::PlayState::Lose:
			hideButton("btn_surrender");
			hideButton("btn_fire");
			showButton("btn_continue");
			status_ = "Соперник разбил все твои корабли";
			break;
	}
}

void PlayScene::surrender_click(Scene &scene)
{
	//TODO: сдаться
}

void PlayScene::continue_click(Scene &scene)
{
	//TODO: перейти к новой битве
}

void PlayScene::fire_click(Scene &)
{
	//TODO: выстрел
}
