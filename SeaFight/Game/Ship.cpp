#include "Ship.h"
#include <string>
#include "../Engine/Graphics.h"
#include <sstream>

//								rigth    down      left       up
const int Ship::DIR[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };


Ship::Ship(int length, SDL_Point pos, Direction dir):
	length_(length),
	pos_(pos),
	dir_(dir)
{
	resetDamage();
}

bool Ship::collidedWith(const Ship &ship) const
{
	SDL_Point p[3];
	p[1].x = pos_.x - DIR[dir_][0];
	p[1].y = pos_.y - DIR[dir_][1];
	p[0].x = p[1].x + DIR[static_cast<Direction>((dir_ - 1 + 4) % 4)][0];
	p[0].y = p[1].y + DIR[static_cast<Direction>((dir_ - 1 + 4) % 4)][1];
	p[2].x = p[1].x + DIR[static_cast<Direction>((dir_ + 1) % 4)][0];
	p[2].y = p[1].y + DIR[static_cast<Direction>((dir_ + 1) % 4)][1];

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
	return SDL_Point{ pos_.x + DIR[dir_][0] * deck, pos_.y + DIR[dir_][1] * deck };
}

std::vector<SDL_Point> Ship::coordsAround() const
{
	std::vector<SDL_Point> coords;

	Direction befor = static_cast<Direction>((dir_ - 1 + 4) % 4),
			after = static_cast<Direction>((dir_ + 1) % 4);

	SDL_Point p = { pos_.x - DIR[dir_][0], pos_.y - DIR[dir_][1] };
	coords.push_back(p);

	for (int i = -1; i < length_; ++i)
	{
		coords.push_back(SDL_Point{ p.x + DIR[befor][0], p.y + DIR[befor][1] });
		coords.push_back(SDL_Point{ p.x + DIR[after][0], p.y + DIR[after][1] });
		p.x += DIR[dir_][0];
		p.y += DIR[dir_][1];
	}
	coords.push_back(SDL_Point{ p.x + DIR[befor][0], p.y + DIR[befor][1] });
	coords.push_back(SDL_Point{ p.x + DIR[after][0], p.y + DIR[after][1] });
	coords.push_back(p);
	return coords;
}

void Ship::resetDamage()
{
	memset(damaged_, 0, sizeof(damaged_));
	killed_ = false;
}

void Ship::addDamage(int deck)
{
	damaged_[deck] = true;
}

bool Ship::outOfMap() const
{
	SDL_Point nose{ pos_.x + DIR[dir_][0] * (length_-1), pos_.y + DIR[dir_][1] * (length_-1) };
	return (pos_.x < 0 || pos_.x >= 10 || pos_.y < 0 || pos_.y >= 10 ||
			nose.x < 0 || nose.x >= 10 || nose.y < 0 || nose.y >= 10);
}

void Ship::draw(Graphics &g, SDL_Point offset)
{
	/*SDL_Point p = pos_;
	for (int i = 0; i < length_; ++i)
	{
		g.DrawSprite("ship", offset.x + p.x * DECK_SIZE, offset.y + p.y * DECK_SIZE);
		p.x += DIR[dir_][0];
		p.y += DIR[dir_][1];
	}*/

	std::stringstream ss;
	ss << "ship" << length_;
	int x = offset.x + pos_.x * DECK_SIZE,
		y = offset.y + pos_.y * DECK_SIZE;
	g.drawSprite(ss.str(), x, y, dir_*90/* + angle*/, DECK_SIZE / 2, DECK_SIZE / 2);
/*
	if ((angle += 2) >= 360)
		angle -= 360;*/
}
