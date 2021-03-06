#pragma once
#include <SDL2/SDL_rect.h>
#include <vector>

class Graphics;

class Ship
{
public:
	enum Direction { RIGHT = 0, DOWN, LEFT, UP };
	enum { DECK_SIZE = 24 };
	static const int DIR[4][2];
	Ship(int length, SDL_Point pos, Direction dir);

	bool killed() const { return killed_; }
	void setKilled(bool value) { killed_ = value; }
//	bool damaged(int deck) const { return damaged_[deck]; }
	bool collidedWith(const Ship &) const;
	int deckAt(SDL_Point coord) const;
	SDL_Point deckCoord(int deck) const;
	std::vector<SDL_Point> coordsAround() const;
	void resetDamage();
	void addDamage(int deck);
	bool outOfMap() const;
	void draw(Graphics &, SDL_Point offset);

	int x() const { return pos_.x; }
	int y() const { return pos_.y; }
	int length() const { return length_; }

private:
	int length_;
	SDL_Point pos_;
	Direction dir_;
	bool damaged_[4];
	bool killed_;

//	float angle = 0;
};