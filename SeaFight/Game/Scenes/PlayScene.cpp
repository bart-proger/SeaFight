#include "PlayScene.h"
#include "../Game.h"
#include <iostream>

PlayScene::PlayScene(Game &game) :
	Scene(game),
	moveAim_(false)
{
}

void PlayScene::init()
{
	if (!font_.loadFromFile("data/Skellyman.ttf"))
		return;

	addButton("btn_surrender", { 100, 350, 44, 44 }, surrender_click);
	addButton("btn_fire", { 400, 350, 44, 44 }, fire_click);
	addButton("btn_continue", { 250, 350, 44, 44 }, continue_click);
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
		case Game::PlayState::MyShot:
				SDL_Point of = game().enemy().drawOffset();
				g.drawSprite("aim", aimPos_.x*Ship::DECK_SIZE + of.x, aimPos_.y*Ship::DECK_SIZE + of.y);
			break;
	}

	if (font_.Loaded())
		g.drawText(font_, SDL_Color{ 0, 0, 0, 255 }, status_, 30, 300);

	Scene::draw(g);
}

void PlayScene::onShow()
{
	moveAim_ = false;
	aimPos_ = { 5, 5 };
	game().setState(Game::PlayState::WaitEnemy);
}

void PlayScene::onPress(SDL_Point p)
{
	Scene::onPress(p);

	moveAim_ = true;
}

void PlayScene::onRelease(SDL_Point p)
{
	Scene::onRelease(p);

	moveAim_ = false;

	if (game().state() == Game::MyShot)
	{
		SDL_Point *c = game().enemy().coordAt(p);
		if (c != nullptr)
			aimPos_ = *c;
	}
}

void PlayScene::onMove(SDL_Point p)
{
	Scene::onMove(p);

	if (game().state() == Game::MyShot)
	{
		if (moveAim_)
		{
			SDL_Point *c = game().enemy().coordAt(p);
			if (c != nullptr)
				aimPos_ = *c;
		}
	}
}

void PlayScene::onChangeGameState(/*Game::PlayState state*/)
{
	hideButton("btn_fire");
	hideButton("btn_surrender");
	hideButton("btn_continue");

	switch (game().state())
	{
		case Game::PlayState::WaitEnemy:
			status_ = "Ожидание подключения противника...";
			break;
		case Game::PlayState::MyShot:
			showButton("btn_fire");
			showButton("btn_surrender");
			status_ = "Огонь!!!";
			break;
		case Game::PlayState::EnemyShot:
			status_ = "Выстрел противника...";
			break;
		case Game::PlayState::Win:
			showButton("btn_continue");
			status_ = "Победа!!!!!!";
			break;
		case Game::PlayState::Lose:
			showButton("btn_continue");
			status_ = "Противник разбил все твои корабли";
			break;
		case Game::PlayState::EnemySurrender:
			showButton("btn_continue");
			status_ = "Противник поднял белый флаг! Победа!!!";
			break;
		default: //EnemyDisconnected
			showButton("btn_continue");
			status_ = "...Соединение с противником прервано. Победа защитана тебе!";
			break;
	}
}

void PlayScene::surrender_click(Scene &scene)
{
	//TODO: сдаться
	scene.game().surrender();
	scene.game().setScene(scene.game().placeShipScene);
}

void PlayScene::continue_click(Scene &scene)
{
	scene.game().setScene(scene.game().placeShipScene);
}

void PlayScene::fire_click(Scene &scene)
{
	PlayScene & sc = static_cast<PlayScene&>(scene);
	//TODO: выстрел
	sc.game().fire(sc.aimPos_);
	std::clog << "fire to (" << sc.aimPos_.x << ", " << sc.aimPos_.y << ") ===> ";
}
