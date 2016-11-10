#include "Player.h"
#include "Game.h"
#include <sstream>
#include "../Engine/Graphics.h"


Player::Player()
{
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
	memset(enemyShots_, false, sizeof(enemyShots_));
}

void Player::addHit(SDL_Point coord)
{
	enemyShots_[coord.y][coord.x] = ShotType::HIT;
	int deck;
	for (auto s : ships_)
	{
		deck = s.deckAt(coord);
		if (deck > -1)
			s.addDamage(deck);
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
		deck = s.deckAt(coord);
		if (deck > -1)
			s.addDamage(deck);
	}
	//TODO: расставить вокруг убитого корабля отметки
}

string Player::mapData() const
{
	char data[100];
	memset(data, '0', sizeof(data));

	for (auto s : ships_)
	{
		data[s.y() * 10 + s.x()] = '1';
	}
	return string(data);
}

void Player::setDrawOffset(int x, int y)
{
	drawOffset_.x = x;
	drawOffset_.y = y;
}

void Player::draw(Graphics & g)
{
	g.DrawSprite("sea", drawOffset_.x, drawOffset_.y);

	for (int j = 0; j < 10; ++j)
		for (int i = 0; i < 10; ++i)
		{
			switch (enemyShots_[j][i])
			{
				case HIT:
					g.DrawSprite("hit", i*CELL_SIZE + drawOffset_.x, j*CELL_SIZE + drawOffset_.y);
					break;
				case MISS:
					g.DrawSprite("miss", i*CELL_SIZE + drawOffset_.x, j*CELL_SIZE + drawOffset_.y);
					break;
				default:
					break;
			}
		}
	g.DrawSprite("coord_abc", drawOffset_.x, drawOffset_.y - 30);
	g.DrawSprite("coord_123", drawOffset_.x - 30, drawOffset_.y);
}
