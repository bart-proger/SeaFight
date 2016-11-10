#include "Ship.h"
#include <string>

const int Ship::DIR[4][2] = { { 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 } };


Ship::Ship(int length, SDL_Point pos, Direction dir):
	length_(length),
	pos_(pos),
	dir_(dir)
{
	resetDamage();
}

bool Ship::collidedWith(const Ship &ship) const
{
	
}

int Ship::deckAt(SDL_Point coord) const
{
	SDL_Point p = pos_;
	for (int i = 0; i < length_; ++i)
	{
		if (p.x == coord.x && p.y == coord.y)
		{
			return i;
		}
		p.x += DIR[dir_][0];
		p.y += DIR[dir_][1];
	}
	return -1;
}

void Ship::resetDamage()
{
	memset(damaged_, 0, sizeof(bool) * 4);
	//killed_ = false;
}

void Ship::addDamage(int deck)
{
	damaged_[deck] = true;
}

bool Ship::outOfMap() const
{
	SDL_Point nose{ pos_.x + DIR[dir_][0] * length_, pos_.y + DIR[dir_][1] * length_ };
	return (pos_.x < 0 || pos_.y < 0 || pos_.x >= 10 || pos_.y >= 10 ||
			nose.x < 0 || nose.y < 0 || nose.x >= 10 || nose.y >= 10);
}
