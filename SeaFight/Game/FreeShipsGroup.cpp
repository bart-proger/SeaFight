#include "FreeShipsGroup.h"
#include "../Engine/Graphics.h"
#include <sstream>

FreeShipsGroup::FreeShipsGroup(int decks, int x, int y) :
	decksCount_(decks),
	rect_{ x, y, decks * (24 + 6) - 6, 24 + 16 },
	shipsCount_(4 - decks + 1)
{
}

void FreeShipsGroup::draw(Graphics & g)
{
	int x = rect_.x;
	std::stringstream ss;
	ss << "ship" << decksCount_;
	for (int c = 0; c < shipsCount_; ++c)
	{
		g.DrawSprite(ss.str(), x, rect_.y);
		x += decksCount_ * 24 + 6;
	}
}
