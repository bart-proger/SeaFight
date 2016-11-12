#include "Enemy.h"


Enemy::Enemy()
{
}

void Enemy::addKill(SDL_Point coord)
{
	enemyShots_[coord.y][coord.x] = ShotType::HIT;

	SDL_Point min = coord, max = coord;

	int xx, yy;
	// поиск соседних подбитых палуб корабля по горизонтали
	for (xx = coord.x - 1; xx >= 0; --xx)
	{
		if (enemyShots_[coord.y][xx] == ShotType::HIT)
		{
			min.x = xx;
		}
		else
			break;
	}
	for (xx = coord.x + 1; xx < 10; ++xx)
	{
		if (enemyShots_[coord.y][xx] == ShotType::HIT)
		{
			max.x = xx;
		}
		else
			break;
	}
	// ..по вертикали
	for (yy = coord.y - 1; yy >= 0; --yy)
	{
		if (enemyShots_[yy][coord.x] == ShotType::HIT)
		{
			min.y = yy;
		}
		else
			break;
	}
	for (yy = coord.y + 1; yy < 10; ++yy)
	{
		if (enemyShots_[yy][coord.x] == ShotType::HIT)
		{
			max.y = yy;
		}
		else
			break;
	}

	int lenX = max.x - min.x,
		lenY = max.y - min.y;
	int dir, len;
	if (lenX == 0)
	{
		dir = 3;
		len = lenY + 1;
	}
	else
	{
		dir = 2;
		len = lenX + 1;
	}

	Ship ship{ len, max, static_cast<Ship::Direction>(dir) };
	ship.setKilled(true);
	ships_.push_back(ship);

	auto around = ship.coordsAround();
	for (auto c : around)
	{
		if (c.x >= 0 && c.x < 10 && c.y >= 0 && c.y < 10 && enemyShots_[c.y][c.x] == ShotType::NONE)
			enemyShots_[c.y][c.x] = ShotType::FREE;
	}
}
