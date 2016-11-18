#pragma once
#include <SDL2/SDL_rect.h>

class Graphics;

class FreeShipsGroup
{
public:
	FreeShipsGroup(int decks, int x, int y);
	void draw(Graphics & g);
	bool pressed(SDL_Point p);
	void move(SDL_Point p);
	bool released(SDL_Point p);

private:
	int decksCount_;
	int shipsCount_;
	SDL_Rect rect_;

	bool drag_;
};