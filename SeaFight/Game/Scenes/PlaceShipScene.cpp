#include "PlaceShipScene.h"
#include "../Game.h"
#include <iostream>
#include "../Ship.h"

PlaceShipScene::PlaceShipScene(Game &game):
	Scene(game)
{
}

void PlaceShipScene::Init()
{
	SDL_Rect r1 = { 287, 100, 143, 44 };
	AddButton("btn_ClearMap", r1, ClearMap_Click);

	SDL_Rect r2 = { 302, 214, 107, 44 };
	AddButton("btn_GoFight", r2, GoFight_Click);
}

void PlaceShipScene::Draw(Graphics &g)
{
	Scene::Draw(g);

	game().player().draw(g);
}

void PlaceShipScene::ClearMap_Click(Scene &scene)
{
	std::clog << "click Clear map\n";
	
	scene.game().player().clearShips();
}

void PlaceShipScene::GoFight_Click(Scene &scene)
{
	std::clog << "click Go fight\n";

	scene.game().readyPlay();
	scene.game().setScene(scene.game().playScene);
}

void PlaceShipScene::OnClick(SDL_Point p)
{
	Scene::OnClick(p);

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
