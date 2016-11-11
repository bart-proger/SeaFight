#pragma once
#include "Player.h"


class Enemy : public Player
{
public:
	Enemy();

	void addKill(SDL_Point coord) override;
};

