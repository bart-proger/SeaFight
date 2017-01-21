#include "PlaceShipScene.h"
#include "../Game.h"
#include <iostream>
#include "../Ship.h"
#include <sstream>

PlaceShipScene::PlaceShipScene(Game &game):
	Scene(game),
	freeShipsGroups_{ {1, 290, 30}, {2, 290, 70}, {3, 290, 134}, {4, 290, 222} },
	selected_(nullptr)
{
}

void PlaceShipScene::init()
{
	//SDL_Rect r1 = { 287+180, 100, 143, 44 };
	addButton("btn_ClearMap", /*r1*/{ 287 + 180, 100, 143, 44 }, ClearMap_Click);
	//SDL_Rect r2 = { 302+180, 214, 107, 44 };
	addButton("btn_GoFight", /*r2*/{ 302 + 180, 214, 107, 44 }, GoFight_Click);
}

void PlaceShipScene::draw(Graphics &g)
{
	Scene::draw(g);

	game().player().draw(g);

	for (int i = 0; i < 4; ++i)
	{
		freeShipsGroups_[i].draw(g);
	}

	if (selected_ == nullptr)
		return;

	std::stringstream ss;
	ss << "ship" << selected_->shipLength();
	g.drawSprite(ss.str(), mousePos_.x - Ship::DECK_SIZE / 2, mousePos_.y - Ship::DECK_SIZE / 2, 90 * selected_->shipDir(), Ship::DECK_SIZE / 2, Ship::DECK_SIZE / 2);
}

void PlaceShipScene::onShow()
{
	game().newBattle();
}

void PlaceShipScene::ClearMap_Click(Scene &scene)
{
	std::clog << "click Clear map\n";
	
	scene.game().player().clearShips();
	PlaceShipScene &sc = dynamic_cast<PlaceShipScene &>(scene);

	for (auto & fsg : sc.freeShipsGroups_)
	{
		fsg.reset();
	}
}

void PlaceShipScene::GoFight_Click(Scene &scene)
{
	std::clog << "click Go fight\n";

	scene.game().readyPlay();
	scene.game().setScene(scene.game().playScene);
}

void PlaceShipScene::onPress(SDL_Point p)
{
	Scene::onPress(p);

	mousePos_ = { -100, -100 };

	for (auto &fsg : freeShipsGroups_)
	{
		if (fsg.pressed(p))
		{
			selected_ = &fsg;
			return;
		}
	}
}

void PlaceShipScene::onRelease(SDL_Point p)
{
	Scene::onRelease(p);

	if (selected_ == nullptr)
		return;

	for (auto &fsg : freeShipsGroups_)
	{
		if (fsg.pressed(p))
		{
			if (selected_ == &fsg)
				selected_->rotate();
			break;
		}
	}

	Player &player = game().player();
	SDL_Point * c = player.coordAt(p);
	if (c != nullptr)
	{
		Ship newShip(selected_->shipLength(), *c, selected_->shipDir());

		if (player.checkShipPosition(newShip))
		{
			player.addShip(newShip);
			selected_->decShipsCount();
//			if (selected_->shipsCount() == 0)
			std::cout << "Placed " << newShip.length() << " decks ship at (" << newShip.x() << ", " << newShip.y() << ")\n";
		}
		else
			std::cout << "Cann't place " << newShip.length() << " decks ship at (" << newShip.x() << ", " << newShip.y() << ")\n";
	}
	selected_ = nullptr;
}

void PlaceShipScene::onMouseMove(SDL_Point p)
{
	if (selected_ == nullptr)
		return;
	mousePos_ = p;
}


