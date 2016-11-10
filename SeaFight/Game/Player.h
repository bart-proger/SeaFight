#pragma once
#include <vector>
#include "Ship.h"
#include <string>
using std::string;

class Game;
class Graphics;

class Player
{
public:
	enum ShotType { NONE = 0, HIT, MISS };
	Player();
	
	bool checkShipPosition(const Ship &) const;
	void addShip(const Ship &);
	void clearShips();
	void clearEnemyShots();

	void addHit(SDL_Point coord);
	void addMiss(SDL_Point coord);
	void addKill(SDL_Point coord);
	string mapData() const;

	void setDrawOffset(int x, int y);
	SDL_Point coordAt(SDL_Point p);
	void draw(Graphics & g);
private:
	std::vector<Ship> ships_;
	ShotType enemyShots_[10][10];
	SDL_Point drawOffset_;
};
