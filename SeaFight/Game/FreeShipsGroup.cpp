#include "FreeShipsGroup.h"
#include "../Engine/Graphics.h"
#include <sstream>

FreeShipsGroup::FreeShipsGroup(int shipLength, int x, int y) :
	shipLength_(shipLength),
	shipsCount_(4 - shipLength + 1),
	shipDir_(Ship::Direction::RIGHT),
	rect_{ x, y, shipsCount_ * shipLength_ * (24 + 6) - 6, 24 + 16 },
	drag_(false)
{
}

void FreeShipsGroup::draw(Graphics & g)
{
	int x = rect_.x;
	std::stringstream ss;
	ss << "ship" << shipLength_;
	for (int c = 0; c < shipsCount_; ++c)
	{
		g.DrawSprite(ss.str(), x, rect_.y, 90 * shipDir_);
		x += shipLength_ * 24 + 6;
	}
	g.drawRect(rect_, SDL_Color{0, 0, 255, 255});
}

bool FreeShipsGroup::pressed(SDL_Point p)
{
	drag_ = false;
	if (shipsCount_ > 0 && SDL_PointInRect(&p, &rect_))
	{
		drag_ = true;
	}
	return drag_;
}

/*
void FreeShipsGroup::move(SDL_Point p)
{
	if (drag_)
	{

	}
}*/

bool FreeShipsGroup::released(SDL_Point p)
{
	if (drag_)
	{
		drag_ = false;
		return true;
	}
	return false;
}

void FreeShipsGroup::decShipsCount()
{
	if (shipsCount_ > 0)
	{
		--shipsCount_;
		updateRect();
	}
}

void FreeShipsGroup::rotate()
{
	shipDir_ = static_cast<Ship::Direction>((shipDir_ + 1) % 4);
	updateRect();
}

void FreeShipsGroup::updateRect()
{
	if (shipDir_ % 2 == 0)
	{
		rect_.w = shipsCount_ * shipLength_ * (24 + 6) - 6;
		rect_.h = 24 + 16;
	}
	else
	{
		rect_.w = shipsCount_ * (24 + 6) - 6;
		rect_.h = shipLength_ * 24 + 16;
	}
}
