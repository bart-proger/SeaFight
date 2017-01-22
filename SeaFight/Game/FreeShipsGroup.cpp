#include "FreeShipsGroup.h"
#include "../Engine/Graphics.h"
#include <sstream>


FreeShipsGroup::FreeShipsGroup(int shipLength, int x, int y) :
	shipLength_(shipLength),
	rect_{ x, y, 0, 0 }
{
	reset();
}

void FreeShipsGroup::draw(Graphics & g)
{
	if (shipsCount_ == 0)
		return;

	std::stringstream ss;
	ss << "ship" << shipLength_;
	int x = rect_.x + 6;
//	g.drawSprite(ss.str(), x, rect_.y + (rect_.h - Ship::DECK_SIZE) / 2, 90 * shipDir_/*, Ship::DECK_SIZE / 2, Ship::DECK_SIZE / 2*/);
//	x += shipLength_ * Ship::DECK_SIZE + 6;
	
	
	for (int c = /*1*/0; c < shipsCount_; ++c)
	{
		g.drawSprite(ss.str(), x, rect_.y + (rect_.h - Ship::DECK_SIZE) / 2, 90 * shipDir_/*, Ship::DECK_SIZE / 2, Ship::DECK_SIZE / 2*/);
		x += shipLength_ * Ship::DECK_SIZE + 6;
	}
//	g.drawRect(rect_, SDL_Color{0, 0, 255, 255});
}

bool FreeShipsGroup::pressed(SDL_Point p)
{
	return (shipsCount_ > 0 && SDL_PointInRect(&p, &rect_));
}

/*
void FreeShipsGroup::move(SDL_Point p)
{
	if (drag_)
	{

	}
}*/

// bool FreeShipsGroup::released(SDL_Point p)
// {
// 	if (drag_)
// 	{
// 		drag_ = false;
// 		return true;
// 	}
// 	return false;
// }

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
	rect_.h = shipLength_ * Ship::DECK_SIZE + 16;
	rect_.w = shipsCount_ * shipLength_ * Ship::DECK_SIZE + (shipsCount_+1)*6;

// 	if (shipDir_ % 2 == 0)
// 	{
//		rect_.w = shipsCount_ * shipLength_ * (Ship::DECK_SIZE + 6) + 6;
//		rect_.h = Ship::DECK_SIZE + 16;
//	}
//	else
//	{
//		rect_.w = shipsCount_ * (Ship::DECK_SIZE + 6) + 6;
//		rect_.h = shipLength_ * Ship::DECK_SIZE + 16;
//	}
}

void FreeShipsGroup::reset()
{
	shipsCount_ = 4 - shipLength_ + 1;
	shipDir_ = Ship::Direction::UP;
	updateRect();
}
