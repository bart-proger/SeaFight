#include "Ship.h"
#include <string>
#include "../Engine/Graphics.h"

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
	//FIX: проверка столкновений
	SDL_Point p[3];
	p[1].x = pos_.x - DIR[dir_][0];
	p[1].y = pos_.y - DIR[dir_][1];
	p[0].x = p[1].x + DIR[static_cast<Direction>(dir_ - 1)][0];
	p[0].y = p[1].y + DIR[static_cast<Direction>(dir_ - 1)][1];
	p[2].x = p[1].x + DIR[static_cast<Direction>(dir_ + 1)][0];
	p[2].y = p[1].y + DIR[static_cast<Direction>(dir_ + 1)][1];

	for (int i = -1; i < length_+1; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (ship.deckAt(p[j]) > -1)
				return true;
			p[j].x += DIR[dir_][0];
			p[j].y += DIR[dir_][1];
		}
	}
	return false;
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

SDL_Point Ship::deckCoord(int deck) const
{
	SDL_Point p = pos_;
	for (int i = 0; i < deck; ++i)
	{
		p.x += DIR[dir_][0];
		p.y += DIR[dir_][1];
	}
	return p;
}

void Ship::resetDamage()
{
	memset(damaged_, 0, sizeof(damaged_));
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

void Ship::draw(Graphics &g, SDL_Point offset)
{
	SDL_Point p = pos_;
	for (int i = 0; i < length_; ++i)
	{
		g.DrawSprite("ship", offset.x + p.x * DECK_SIZE, offset.y + p.y * DECK_SIZE);
		p.x += DIR[dir_][0];
		p.y += DIR[dir_][1];
	}
}
