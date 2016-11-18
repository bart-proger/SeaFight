#include "PlaceShipScene.h"
#include "../Game.h"
#include <iostream>
#include "../Ship.h"

PlaceShipScene::PlaceShipScene(Game &game):
	Scene(game),
	freeShipsGroups_{ {1, 290, 30}, {2, 290, 70}, {3, 290, 110}, {4, 290, 150} },
	selected_{ 0, {-1, -1} }
{
}

void PlaceShipScene::Init()
{
	//SDL_Rect r1 = { 287+180, 100, 143, 44 };
	AddButton("btn_ClearMap", /*r1*/{ 287 + 180, 100, 143, 44 }, ClearMap_Click);
	//SDL_Rect r2 = { 302+180, 214, 107, 44 };
	AddButton("btn_GoFight", /*r2*/{ 302 + 180, 214, 107, 44 }, GoFight_Click);
}

void PlaceShipScene::Draw(Graphics &g)
{
	Scene::Draw(g);

	game().player().draw(g);

	for (int i = 0; i < 4; ++i)
	{
		freeShipsGroups_[i].draw(g);
	}
}

void PlaceShipScene::ClearMap_Click(Scene &scene)
{
	std::clog << "click Clear map\n";
	
	scene.game().player().clearShips();
	//TODO: сброс freeShips
}

void PlaceShipScene::GoFight_Click(Scene &scene)
{
	std::clog << "click Go fight\n";

	scene.game().readyPlay();
	scene.game().setScene(scene.game().playScene);
}

void PlaceShipScene::onClick(SDL_Point p)
{
	Scene::onClick(p);

	Player &player = game().player();
	SDL_Point coord = player.coordAt(p);
	if (coord.x > -1 && coord.y > -1)
	{
		Ship newShip(rand() % 4 + 1, coord, static_cast<Ship::Direction>(rand() % 4));

		if (player.checkShipPosition(newShip))

		{
			player.addShip(newShip);
		}
		else
			std::cout << "Cann't place " << newShip.length() << " decks ship at (" << newShip.x() << ", " << newShip.y() << ")\n";
	}


//TODO: добавление кораблей
//	SDL_Point coord;
// 	if (player.MapCoordAt(p, coord))
// 	{
// 		if (player.PlaceShipPart(coord))
// 			std::clog << "place ship part at (" << coord.x << ", " << coord.y << ")" << std::endl;
// 		else
// 			std::clog << "don't place ship part to (" << coord.x << ", " << coord.y << ")" << std::endl;
// 	}
}

