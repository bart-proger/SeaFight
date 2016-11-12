#include "Player.h"
#include "Game.h"
#include <sstream>
#include "../Engine/Graphics.h"
#include <cstdlib>
#include <ctime>

Player::Player()
{
	srand((unsigned int)time(NULL));
	clearEnemyShots();
}

bool Player::checkShipPosition(const Ship &ship) const
{
	if (ship.outOfMap())
		return false;
	for (auto s: ships_)
	{
		if (s.collidedWith(ship))
			return false;
	}
	return true;
}

void Player::addShip(const Ship &ship)
{
	ships_.push_back(ship);
}

void Player::clearShips()
{
	ships_.clear();
}

void Player::clearEnemyShots()
{
	for (auto s: ships_)
	{
		s.resetDamage();
	}
	memset(enemyShots_, ShotType::NONE, sizeof(enemyShots_));
}

void Player::addHit(SDL_Point coord)
{
	enemyShots_[coord.y][coord.x] = ShotType::HIT;
	int deck;
	for (auto s : ships_)
	{
		deck = s.deckAt(coord);
		if (deck > -1)
		{
			s.addDamage(deck);
			break;
		}
	}
}

void Player::addMiss(SDL_Point coord)
{
	enemyShots_[coord.y][coord.x] = ShotType::MISS;
}

void Player::addKill(SDL_Point coord)
{
	enemyShots_[coord.y][coord.x] = ShotType::HIT;
	int deck;
	for (auto s : ships_)
	{
		if (deck = s.deckAt(coord) > -1)
		{
			s.addDamage(deck);

/*
			auto around = s.coordsAround();
			for (auto c : around)
			{
				if (c.x >= 0 && c.x < 10 && c.y >= 0 && c.y < 10 && enemyShots_[c.y][c.x] == ShotType::NONE)
					enemyShots_[c.y][c.x] = ShotType::FREE;
			}
*/
		}
	}
}

string Player::mapData() const
{
	char data[101];
	memset(data, '0', sizeof(data));
	data[100] = '\0';

	for (auto s : ships_)
	{
		SDL_Point p;
		for (int i = 0; i < s.length(); ++i)
		{
			p = s.deckCoord(i);
			data[p.y * 10 + p.x] = '1';
		}
	}
	return string(data);
}

void Player::setDrawOffset(int x, int y)
{
	drawOffset_.x = x;
	drawOffset_.y = y;
}

SDL_Point Player::coordAt(SDL_Point p)
{
	int x = (p.x - drawOffset_.x) / Ship::DECK_SIZE,
		y = (p.y - drawOffset_.y) / Ship::DECK_SIZE;

	if (x >= 0 && x < 10 && y >= 0 && y < 10)
	{
		return SDL_Point{ x, y };
	}
	return SDL_Point{ -1, -1 };
}

void Player::draw(Graphics & g)
{
	g.DrawSprite("sea", drawOffset_.x, drawOffset_.y);

	for (auto &s : ships_)
	{
		s.draw(g, drawOffset_);
	}

	for (int j = 0; j < 10; ++j)
		for (int i = 0; i < 10; ++i)
		{
			int x = i*Ship::DECK_SIZE + drawOffset_.x,
				y = j*Ship::DECK_SIZE + drawOffset_.y;
			switch (enemyShots_[j][i])
			{
				case ShotType::HIT:
					g.DrawSprite("hit", x, y);
					break;
				case ShotType::MISS:
					g.DrawSprite("miss", x, y);
					break;
				case ShotType::FREE:
					g.DrawSprite("free", x, y);
				default: //NONE
					break;
			}
		}
	g.DrawSprite("coord_abc", drawOffset_.x, drawOffset_.y - 30);
	g.DrawSprite("coord_123", drawOffset_.x - 30, drawOffset_.y);
}
