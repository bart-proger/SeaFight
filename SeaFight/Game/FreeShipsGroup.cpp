#include "FreeShipsGroup.h"
#include "../Engine/Graphics.h"
#include <sstream>

FreeShipsGroup::FreeShipsGroup(int decks, int x, int y) :
	decksCount_(decks),
	rect_{ x, y, decks * (24 + 6) - 6, 24 + 16 },
	shipsCount_(4 - decks + 1),
	drag_(false)
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

bool FreeShipsGroup::pressed(SDL_Point p)
{
	if (SDL_PointInRect(&p, &rect_))
	{
		drag_ = true;
	}
	return drag_;
}

void FreeShipsGroup::move(SDL_Point p)
{
	if (drag_)
	{

	}
}

bool FreeShipsGroup::released(SDL_Point p)
{
	if (drag_)
	{
		drag_ = false;
		return true;
	}
	return false;
}
