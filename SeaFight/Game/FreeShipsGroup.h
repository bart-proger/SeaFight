#pragma once
#include <SDL2/SDL_rect.h>

class Graphics;

class FreeShipsGroup
{
public:
	FreeShipsGroup(int decks, int x, int y);
	void draw(Graphics & g);

private:
	int decksCount_;
	int shipsCount_;
	SDL_Rect rect_;
};