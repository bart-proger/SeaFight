#pragma once
#include <SDL2/SDL_rect.h>

class Ship
{
public:
	enum Direction { UP = 0, RIGHT, DOWN, LEFT };
	static const int DIR[4][2];
	Ship(int length, SDL_Point pos, Direction dir);

//	bool killed() const { return killed_; }
//	bool damaged(int deck) const { return damaged_[deck]; }
	bool collidedWith(const Ship &) const;
	int deckAt(SDL_Point coord) const;
	void resetDamage();
	void addDamage(int deck);
	bool outOfMap() const;

	int x() const { return pos_.x; }
	int y() const { return pos_.y; }
	int length() const { return length_; }

private:
	int length_;
	SDL_Point pos_;
	Direction dir_;
	bool damaged_[4];
//	bool killed_;
};