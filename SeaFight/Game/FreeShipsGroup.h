#pragma once
#include <SDL2/SDL_rect.h>
#include "Ship.h"

class Graphics;

class FreeShipsGroup
{
public:
	FreeShipsGroup(int shipLength, int x, int y);
	void draw(Graphics &);
	bool pressed(SDL_Point );
//	void move(SDL_Point );
//	bool released(SDL_Point );
	void decShipsCount();
	void rotate();
	void updateRect();
	void reset();
//prop:
	int shipLength() const { return shipLength_; }
	int shipsCount() const { return shipsCount_; }
	Ship::Direction shipDir() const { return shipDir_; }
private:
	int shipLength_;
	int shipsCount_;
	Ship::Direction shipDir_;

	SDL_Rect rect_;
};